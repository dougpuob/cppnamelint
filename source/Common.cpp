#include <algorithm>
#include <stdio.h>
#include <stdlib.h>

// Submodule projects
#include <gtest/gtest.h>
#include <nlohmann/json.hpp>

// This project
#include "Common.h"
#include "Config.h"
#include "Detection.h"
#include "MyAstConsumer.h"
#include "MyAstVisitor.h"
#include "MyFactory.h"
#include "TraceMemo.h"

// LLVM
#include "clang/Tooling/CompilationDatabase.h"

using namespace nlohmann;

namespace String {

void Replace(string &Source, const string &Patn, const string &New) {
  string::size_type Pos    = 0;
  string::size_type SrcLen = Patn.size();
  string::size_type DstLen = New.size();
  while ((Pos = Source.find(Patn, Pos)) != string::npos) {
    Source.replace(Pos, SrcLen, New);
    Pos += DstLen;
  }
}

void Trim(string &Source) {
  if (Source.empty()) {
    return;
  }

  Source.erase(0, Source.find_first_not_of("\t"));
  Source.erase(0, Source.find_first_not_of(" "));
  Source.erase(Source.find_last_not_of("\t") + 1);
  Source.erase(Source.find_last_not_of(" ") + 1);
}
} // namespace String

LOG_DECISION_DEFAULT(false);
int RunCheckFormStream(namelint::MemoBoard &Memo, const string &SourceContent,
                       const string &VirtFileName) {
  //
  // Load source code file then create compilatation database.
  //
  std::string ErrorMessage;
  FixedCompilationDatabase Compilations("./", std::vector<std::string>());

  //
  // Create clang tool then add clang tool arguments.
  //
  ClangTool Tool(Compilations, std::vector<std::string>(1, VirtFileName));
  Tool.mapVirtualFile(VirtFileName, SourceContent);

  //
  // Execute `check` command.
  //
  int iRet = RunCheck(Memo, Tool);

  return iRet;
}

int RunCheck(namelint::MemoBoard &Memo, ClangTool &Tool) {
  int iRet = 0;

  //
  // Check input parameters.
  //
  DcLib::Log::Out(INFO_ALL, "Source File = %s", Memo.File.Source.c_str());
  DcLib::Log::Out(INFO_ALL, "Config File = %s", Memo.File.Config.c_str());
  DcLib::Log::Out(INFO_ALL, "OutputJson  = %s", Memo.File.OutputJson.c_str());

  //
  // Feed header directories from input commands to ClangTools'.
  //
  for (auto inc : Memo.Dir.Includes) {
    llvm::SmallString<128> IncDirPath(inc);
    llvm::sys::fs::make_absolute(IncDirPath);

    vector<string> inc_dir;
    inc_dir.push_back("-I");
    inc_dir.push_back(IncDirPath.c_str());
    DcLib::Log::Out(INFO_ALL, "-I %s", IncDirPath.c_str());
    Tool.appendArgumentsAdjuster(getInsertArgumentAdjuster(inc_dir, ArgumentInsertPosition::BEGIN));
  }

  //
  // Add `-E` option (Only run the preprocessor) to ClantTool.
  //
  Tool.appendArgumentsAdjuster(getInsertArgumentAdjuster("-E", // Run the preprocessor
                                                         ArgumentInsertPosition::BEGIN));

  //
  // Add `verbose` option to ClantTool.
  //
  if (Memo.File.bVerboseMode) {
    Tool.appendArgumentsAdjuster(getInsertArgumentAdjuster("-v", // Verbose
                                                           ArgumentInsertPosition::BEGIN));
  }

  //
  // Make it parses header file.
  //
  Tool.appendArgumentsAdjuster(getInsertArgumentAdjuster("--language=c++", // C++
                                                         ArgumentInsertPosition::BEGIN));
  DcLib::Log::Out(INFO_ALL, "--language=c++");

    Tool.appendArgumentsAdjuster(getInsertArgumentAdjuster("-cc1",
                                                         ArgumentInsertPosition::BEGIN));

  //
  // Bypass DiagnosticConsumer to disable diagnostic feature.
  //
  Tool.setDiagnosticConsumer(new IgnoringDiagConsumer());

  //
  // Check file name if config option is ENABLED.
  //
  shared_ptr<ConfigData> pConfig = Memo.Config.GetData();
  GeneralOptions *pOptions       = &pConfig->General.Options;
  if (!pOptions->bCheckFileName) {
    DcLib::Log::Out(INFO_ALL, "Skipped, becuase config file is disable. (bCheckFileName)");
  } else {
    Memo.Checked.nFile++;
    llvm::StringRef SrcPath(Memo.File.Source.c_str());
    string FileBaseName = llvm::sys::path::filename(SrcPath).str();

    Detection Detect;
    GeneralRules *pRules = &pConfig->General.Rules;
    if (!Detect.CheckFile(pRules->FileName, FileBaseName)) {
      Memo.Error.nFile++;
      Memo.ErrorDetailList.push_back(new ErrorDetail(FileBaseName, ""));
    }
  }
 
  //
  // Check input source file except file name which are possiblely did above.
  //
  MyFactory MyFactory;
  std::unique_ptr<FrontendActionFactory> NewFactory = newFrontendActionFactory(&MyFactory);

  // Go with ClangTool
  if (0 == Tool.run(NewFactory.get())) {
    iRet = GetTotalError(Memo);
    if (Memo.Config.GetData()->General.Options.bAllowedPrintResult) {
      PrintTraceMemo(Memo);
    }
    if ((Memo.File.OutputJson.length() > 0) ||
        Memo.Config.GetData()->General.Options.bAllowedWriteJsonResult) {
      string OutputJson = Memo.File.OutputJson;
      if (OutputJson.length() == 0) {
        OutputJson = "cppnamelint.json";
      }
      WriteJsonResult(Memo, OutputJson);
    }
  } else {
    iRet = -1;
  }

  return iRet;
}

int RunCheckFormFile(namelint::MemoBoard &Memo) {

  if (!llvm::sys::fs::exists(Memo.File.Source)) {
    cout << "Error: Failed to find input source file." << endl;
    return 1;
  }

  //
  // Load source code file then create compilatation database.
  //
  std::string ErrorMessage;
  auto Compilations = FixedCompilationDatabase::loadFromFile(Memo.File.Source, ErrorMessage);
  if (nullptr == Compilations) {
    printf("Error: Failed to load and convert to compliation database.\n");
    printf("       (%s) \n", ErrorMessage.c_str());
    return 2;
  }

  //
  // Create clang tool then add clang tool arguments.
  //
  ClangTool Tool(*Compilations, {Memo.File.Source});

  //
  // Execute `check` command.
  //
  int iRet = RunCheck(Memo, Tool);

  return iRet;
}

int RunTest(const string &LogFileName = "", const string &FilterStr = "") {

  vector<string> Args;
  Args.push_back("This");

  if (LogFileName.length() > 0) {
    Args.push_back("--gtest_output=json:" + LogFileName);
  }

  if (FilterStr.length() > 0) {
    Args.push_back("--gtest_filter=" + FilterStr);
  }

  vector<char *> CharArgs;
  for (size_t nIdx = 0; nIdx < Args.size(); nIdx++) {
    CharArgs.push_back(Args[nIdx].data());
  }

  int iArgc  = Args.size();
  char **psz = CharArgs.data();
  testing::InitGoogleTest(&iArgc, (char **)psz);
  int iRet = RUN_ALL_TESTS();
  return iRet;
}

size_t GetTotalError(const MemoBoard &MemoBoard) {
  return MemoBoard.Error.nFile + MemoBoard.Error.nParameter + MemoBoard.Error.nFunction +
         MemoBoard.Error.nVariable + MemoBoard.Error.nEnum + MemoBoard.Error.nStruct;
}

size_t GetTotalChecked(const MemoBoard &MemoBoard) {
  return MemoBoard.Checked.nFile + MemoBoard.Checked.nParameter + MemoBoard.Checked.nFunction +
         MemoBoard.Checked.nVariable + MemoBoard.Checked.nEnum + MemoBoard.Checked.nStruct;
}

bool DataToJson(const MemoBoard &MemoBoard, json &JsonDoc) {
  json TotalList            = json::array();
  JsonDoc["File"]["Source"] = MemoBoard.File.Source;
  JsonDoc["File"]["Config"] = MemoBoard.File.Config;

  JsonDoc["Checked"]["Function"]  = MemoBoard.Checked.nFunction;
  JsonDoc["Checked"]["Parameter"] = MemoBoard.Checked.nParameter;
  JsonDoc["Checked"]["Variable"]  = MemoBoard.Checked.nVariable;

  JsonDoc["Error"]["Function"]  = MemoBoard.Error.nFunction;
  JsonDoc["Error"]["Parameter"] = MemoBoard.Error.nParameter;
  JsonDoc["Error"]["Variable"]  = MemoBoard.Error.nVariable;

  json JsonErrDetail;
  json ErrorDetailList = json::array();
  for (const ErrorDetail *pErrDetail : MemoBoard.ErrorDetailList) {
    JsonErrDetail["Line"]   = pErrDetail->Pos.nLine;
    JsonErrDetail["Column"] = pErrDetail->Pos.nColumn;
    JsonErrDetail["Type"]   = (int)pErrDetail->Type;
    JsonErrDetail["TypeName"] =
        pErrDetail->TypeName + (pErrDetail->bIsPtr ? "*" : "") + (pErrDetail->bIsArray ? "[]" : "");
    JsonErrDetail["TargetName"] = pErrDetail->TargetName;
    JsonErrDetail["Expected"]   = pErrDetail->Suggestion;
    ErrorDetailList.push_back(JsonErrDetail);
  }

  JsonDoc["ErrorDetailList"] = ErrorDetailList;
  TotalList.push_back(JsonDoc);
  // cout << pretty_print(JsonDoc) << endl;

  return true;
}

bool PrintTraceMemo(const MemoBoard &MemoBoard) {

  bool bStatus     = true;
  char szText[512] = {0};

  cout << " File    = " << llvm::sys::path::filename(MemoBoard.File.Source).data() << endl;
  cout << " Config  = " << llvm::sys::path::filename(MemoBoard.File.Config).data() << endl;
  for (size_t nIdx = 0; nIdx < MemoBoard.Dir.Includes.size(); nIdx++) {
    sprintf(szText, " Inc[%2lu] = %s", nIdx + 1, MemoBoard.Dir.Includes[nIdx].c_str());
    printf("%s\n", szText);
    DcLib::Log::Out(INFO_ALL, szText);
  }

  sprintf(szText,
          " Checked = %5lu  [File:%u | Func:%3u | Param:%3u | Var:%3u | Enum:%3u | Struct:%3u | "
          "Union:%3u | "
          "Class:%3u]",
          GetTotalChecked(MemoBoard), MemoBoard.Checked.nFile, MemoBoard.Checked.nFunction,
          MemoBoard.Checked.nParameter, MemoBoard.Checked.nVariable, MemoBoard.Checked.nEnum,
          MemoBoard.Checked.nStruct, MemoBoard.Checked.nUnion, MemoBoard.Checked.nClass);
  printf("%s\n", szText);
  DcLib::Log::Out(INFO_ALL, szText);

  sprintf(szText,
          " Error   = %5lu  [File:%u | Func:%3u | Param:%3u | Var:%3u | Enum:%3u | Struct:%3u | "
          "Union:%3u | "
          "Class:%3u]",
          GetTotalError(MemoBoard), MemoBoard.Error.nFile, MemoBoard.Error.nFunction,
          MemoBoard.Error.nParameter, MemoBoard.Error.nVariable, MemoBoard.Error.nEnum,
          MemoBoard.Error.nStruct, MemoBoard.Error.nUnion, MemoBoard.Error.nClass);
  printf("%s\n", szText);
  DcLib::Log::Out(INFO_ALL, szText);

  printf("------------------------------------------------------------\n");
  DcLib::Log::Out(INFO_ALL, "------------------------------------------------------------");

  for (const ErrorDetail *pErrDetail : MemoBoard.ErrorDetailList) {
    switch (pErrDetail->Type) {
    case CheckType::CT_File:
      cout << std::left << "  < 0, 0 >" << std::left << std::setw(15)
           << " File: " << pErrDetail->TargetName.c_str() << endl;
      break;

    case CheckType::CT_Function:
      sprintf(szText, "  <%4zu, %4zu> Function  : %s", pErrDetail->Pos.nLine,
              pErrDetail->Pos.nColumn, pErrDetail->TargetName.c_str());

      printf("%s\n", szText);
      DcLib::Log::Out(INFO_ALL, szText);
      break;

    case CheckType::CT_Parameter:
      sprintf(szText, "  <%4zu, %4zu> Parameter : %s (%s%s)", pErrDetail->Pos.nLine,
              pErrDetail->Pos.nColumn, pErrDetail->TargetName.c_str(), pErrDetail->TypeName.c_str(),
              (pErrDetail->bIsPtr ? "*" : ""));

      printf("%s\n", szText);
      DcLib::Log::Out(INFO_ALL, szText);
      break;

    case CheckType::CT_Variable:
      sprintf(szText, "  <%4zu, %4zu> Variable  : %s (%s%s%s)", pErrDetail->Pos.nLine,
              pErrDetail->Pos.nColumn, pErrDetail->TargetName.c_str(), pErrDetail->TypeName.c_str(),
              (pErrDetail->bIsPtr ? "*" : ""), (pErrDetail->bIsArray ? "[]" : ""));

      printf("%s\n", szText);
      DcLib::Log::Out(INFO_ALL, szText);
      break;

    case CheckType::CT_Class:
      sprintf(szText, "  <%4zu, %4zu> Class     : %s", pErrDetail->Pos.nLine,
              pErrDetail->Pos.nColumn, pErrDetail->TargetName.c_str());

      printf("%s\n", szText);
      DcLib::Log::Out(INFO_ALL, szText);
      break;

    case CheckType::CT_EnumTag:
      sprintf(szText, "  <%4zu, %4zu> Enum Tag  : %s", pErrDetail->Pos.nLine,
              pErrDetail->Pos.nColumn, pErrDetail->TargetName.c_str());

      printf("%s\n", szText);
      DcLib::Log::Out(INFO_ALL, szText);
      break;

    case CheckType::CT_EnumVal:
      sprintf(szText, "  <%4zu, %4zu> Enum Val  : %s (%s)", pErrDetail->Pos.nLine,
              pErrDetail->Pos.nColumn, pErrDetail->TargetName.c_str(),
              pErrDetail->TypeName.c_str());

      printf("%s\n", szText);
      DcLib::Log::Out(INFO_ALL, szText);
      break;

    case CheckType::CT_StructTag:
      sprintf(szText, "  <%4zu, %4zu> Struct Tag: %s (%s)", pErrDetail->Pos.nLine,
              pErrDetail->Pos.nColumn, pErrDetail->TargetName.c_str(),
              pErrDetail->TypeName.c_str());

      printf("%s\n", szText);
      DcLib::Log::Out(INFO_ALL, szText);
      break;

    case CheckType::CT_StructVal:
      sprintf(szText, "  <%4zu, %4zu> Struct Val: %s (%s)", pErrDetail->Pos.nLine,
              pErrDetail->Pos.nColumn, pErrDetail->TargetName.c_str(),
              pErrDetail->TypeName.c_str());

      printf("%s\n", szText);
      DcLib::Log::Out(INFO_ALL, szText);
      break;

    default:
      bStatus = false;
    }
  }

  return bStatus;
}

bool WriteJsonResult(const MemoBoard &MemoBoard, const string &FilePath) {
  if (!llvm::sys::fs::exists(FilePath)) {
    json JasonEmty = json::array();
    ofstream MyFile;
    MyFile.open(FilePath);
    MyFile << JasonEmty;
    MyFile.close();
  }

  json JsonNew;
  json JsonAll = NULL;
  try {
    std::ifstream IfStm(FilePath);
    JsonAll = json::parse(IfStm);
  } catch (const std::exception &Exp) {
    cout << Exp.what() << endl;
  }

  if (JsonAll == NULL) {
    JsonAll = json::array();
  }

  if (DataToJson(MemoBoard, JsonNew)) {
    ofstream MyFile;
    MyFile.open(FilePath);
    JsonAll.push_back(JsonNew);
    MyFile << JsonAll;
    MyFile.close();
    return true;
  }
  return false;
}

void LogHead() {
  AppCxt &AppCxt = AppCxt::getInstance();
  int iPos       = AppCxt.MemoBoard.Config.GetData()->Debug.Log.iContentStartsPosition;

  DcLib::Log::Out(INFO_NONE, "");
  DcLib::Log::Out(INFO_NONE, "");
  DcLib::Log::Out(INFO_NONE,
                  "=============================================================================="
                  "=========================================================================");
  DcLib::Log::Out(INFO_NONE,
                  "0         0         0         0         0         0         0         0       "
                  "  0        0          1         1         1         1         1         1");
  DcLib::Log::Out(INFO_NONE,
                  "012345678911234567892123456789312345678941234567895123456789612345678971234567"
                  "8981234567899123456789012345678911234567892123456789312345678941234567895");
  DcLib::Log::Out(INFO_NONE,
                  "=============================================================================="
                  "=========================================================================");
  DcLib::Log::Out(INFO_ALL, "INFO : ContentStartsPosition = %d.", iPos);
  DcLib::Log::Out(INFO_ALL, "INFO : Log message will print to the file (%s).",
                  AppCxt.MemoBoard.File.LogFile.c_str());
}

void LogConfig() {
  AppCxt &AppCxt                  = AppCxt::getInstance();
  shared_ptr<ConfigData> pCfgData = AppCxt.MemoBoard.Config.GetData();

  DcLib::Log::Out(INFO_ALL, "bCheckFileName      = %d", pCfgData->General.Options.bCheckFileName);
  DcLib::Log::Out(INFO_ALL, "bCheckFunctionName  = %d",
                  pCfgData->General.Options.bCheckFunctionName);
  DcLib::Log::Out(INFO_ALL, "bCheckEnum          = %d", pCfgData->General.Options.bCheckEnum);
  DcLib::Log::Out(INFO_ALL, "bCheckStruct        = %d", pCfgData->General.Options.bCheckStruct);
  DcLib::Log::Out(INFO_ALL, "bCheckVariableName  = %d",
                  pCfgData->General.Options.bCheckVariableName);
}

void LogCheckResult() {
  AppCxt &AppCxt = AppCxt::getInstance();

  DcLib::Log::Out(INFO_ALL, "Assert.nErrorOccurred = %d", AppCxt.MemoBoard.Assert.nErrorOccurred);
  DcLib::Log::Out(INFO_ALL, "Assert.nInvalidDecl   = %d", AppCxt.MemoBoard.Assert.nInvalidDecl);
  DcLib::Log::Out(INFO_ALL, "Assert.nNumWarnings   = %d", AppCxt.MemoBoard.Assert.nNumWarnings);

  DcLib::Log::Out(INFO_ALL, "Checked.nClass        = %d", AppCxt.MemoBoard.Checked.nClass);
  DcLib::Log::Out(INFO_ALL, "Checked.nEnum         = %d", AppCxt.MemoBoard.Checked.nEnum);
  DcLib::Log::Out(INFO_ALL, "Checked.nFile         = %d", AppCxt.MemoBoard.Checked.nFile);
  DcLib::Log::Out(INFO_ALL, "Checked.nFunction     = %d", AppCxt.MemoBoard.Checked.nFunction);
  DcLib::Log::Out(INFO_ALL, "Checked.nParameter    = %d", AppCxt.MemoBoard.Checked.nParameter);
  DcLib::Log::Out(INFO_ALL, "Checked.nStruct       = %d", AppCxt.MemoBoard.Checked.nStruct);
  DcLib::Log::Out(INFO_ALL, "Checked.nUnion        = %d", AppCxt.MemoBoard.Checked.nUnion);
  DcLib::Log::Out(INFO_ALL, "Checked.nVariable     = %d", AppCxt.MemoBoard.Checked.nVariable);

  DcLib::Log::Out(INFO_ALL, "Error.nClass          = %d", AppCxt.MemoBoard.Error.nClass);
  DcLib::Log::Out(INFO_ALL, "Error.nEnum           = %d", AppCxt.MemoBoard.Error.nEnum);
  DcLib::Log::Out(INFO_ALL, "Error.nFile           = %d", AppCxt.MemoBoard.Error.nFile);
  DcLib::Log::Out(INFO_ALL, "Error.nFunction       = %d", AppCxt.MemoBoard.Error.nFunction);
  DcLib::Log::Out(INFO_ALL, "Error.nParameter      = %d", AppCxt.MemoBoard.Error.nParameter);
  DcLib::Log::Out(INFO_ALL, "Error.nStruct         = %d", AppCxt.MemoBoard.Error.nStruct);
  DcLib::Log::Out(INFO_ALL, "Error.nUnion          = %d", AppCxt.MemoBoard.Error.nUnion);
  DcLib::Log::Out(INFO_ALL, "Error.nVariable       = %d", AppCxt.MemoBoard.Error.nVariable);
}
