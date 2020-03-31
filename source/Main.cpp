#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

#include <gtest/gtest.h>
#include <nlohmann/json.hpp>

#include "CommandLine.h"
#include "Common.h"
#include "Config.h"
#include "Detection.h"
#include "MyAstConsumer.h"
#include "MyAstVisitor.h"
#include "MyFactory.h"

#include "clang/Tooling/CompilationDatabase.h"

using namespace nlohmann;
using namespace namelint;

size_t GetTotalError(const MemoBoard &MemoBoard);
bool DataToJson(const MemoBoard &MemoBoard, json &JsonDoc);
bool PrintTraceMemo(const MemoBoard &MemoBoard);
bool WriteJsonResult(const MemoBoard &MemoBoard, const string &FilePath);

int RunCheck(namelint::MemoBoard &Memo) {
  int iRet = 0;

  string OutputJson = CheckOutputJson;
  vector<string> InputIncs;

  Memo.File.Source = CheckInputSrc;
  Memo.File.Config = CheckInputConfig;
  Memo.Dir.Includes = InputIncs;

  if (OutputJson.length() == 0) {
    OutputJson = "cppnamelint.json";
  }

  //
  // Check input parameters.
  //
  DcLib::Log::Out(INFO_ALL, "Source File = %s", Memo.File.Source.c_str());
  DcLib::Log::Out(INFO_ALL, "Config File = %s", Memo.File.Config.c_str());
  DcLib::Log::Out(INFO_ALL, "OutputJson  = %s", OutputJson.c_str());

  if (!llvm::sys::fs::exists(CheckInputSrc)) {
    cout << "Error: Failed to find input source file." << endl;
    return 1;
  }

  if (!llvm::sys::fs::exists(CheckInputConfig)) {
    cout << "Error: Failed to find config file." << endl;
    return 2;
  }

  string errorReason;
  if (!Memo.Config.LoadFile(CheckInputSrc, errorReason)) {
    cout << "Error: Failed to load config file (format wrong)." << endl;
    cout << errorReason << endl;
    return 3;
  }

  //
  // Load source code file then create compilatation database.
  //
  std::string ErrorMessage;
  auto Compilations =
      FixedCompilationDatabase::loadFromFile(Memo.File.Source, ErrorMessage);

  //
  // Create clang tool then add clang tool arguments.
  //
  vector<string> SingleFileInList = { Memo.File.Source };
  ClangTool Tool(*Compilations, SingleFileInList);
  // Tool.appendArgumentsAdjuster(getInsertArgumentAdjuster("--I./",
  // ArgumentInsertPosition::BEGIN));
  Tool.appendArgumentsAdjuster(
      getInsertArgumentAdjuster("-v", ArgumentInsertPosition::BEGIN));
  Tool.appendArgumentsAdjuster(getInsertArgumentAdjuster(
      "--language=c++", ArgumentInsertPosition::BEGIN)); // Make it parses header file.

  Tool.setDiagnosticConsumer(new IgnoringDiagConsumer());

  Detection Detect;
  shared_ptr<ConfigData> pConfig = Memo.Config.GetData();
  GeneralOptions *pOptions = &pConfig->General.Options;
  if (pOptions->bCheckFileName) {
    RuleOfFile Rule;
    Rule.bAllowedUnderscopeChar = pOptions->bAllowedUnderscopeChar;
    Detect.ApplyRuleForFile(Rule);

    Memo.Checked.nFile++;

    string FileBaseName = Path::FindFileName(Memo.File.Source);
    GeneralRules *pRules = &pConfig->General.Rules;
    if (!Detect.CheckFile(pRules->FileName, FileBaseName)) {
      Memo.Error.nFile++;
      Memo.ErrorDetailList.push_back(new ErrorDetail(FileBaseName, ""));
    }
  }

  MyFactory MyFactory;
  std::unique_ptr<FrontendActionFactory> Factory =
      newFrontendActionFactory(&MyFactory);

  // Go
  if (0 == Tool.run(Factory.get())) {
    iRet = GetTotalError(Memo);
    PrintTraceMemo(Memo);
    WriteJsonResult(Memo, OutputJson);
  } else {
    iRet = -1;
  }

  return iRet;
}

int RunTest() {
  int iRet = 0;
  return iRet;
}

int RunDump() {
  int iRet = 0;
  return iRet;
}

int main(int Argc, const char **Argv) {

  cout << "cppnamelint utility v0.3.0" << endl;
  cout << "---------------------------------------------------" << endl;

  cl::HideUnrelatedOptions(CppNameLintCategory);
  cl::ParseCommandLineOptions(Argc, Argv);

  int iRet = 0;
  if (LogFile.length() > 0) {
    DcLib::Log::Init(LogFile.c_str());
  }

  APP_CONTEXT *pAppCxt = (APP_CONTEXT *)GetAppCxt();
  pAppCxt->MemoBoard.Option.bEnableLog = (LogFile.length() > 0);

  if (CheckSubcommand) {
    iRet = RunCheck(pAppCxt->MemoBoard);
  } else if (TestSubcommand) {
    testing::InitGoogleTest(&Argc, (char **)Argv);
    iRet = RUN_ALL_TESTS();
  } else {
    iRet = -1; /* Error (Command miss matched.) */
    cl::PrintHelpMessage();
  }

  cout << endl;
  return iRet;
}

size_t GetTotalError(const MemoBoard &MemoBoard) {
  return MemoBoard.Error.nFile + MemoBoard.Error.nParameter +
         MemoBoard.Error.nFunction + MemoBoard.Error.nVariable;
}

size_t GetTotalChecked(const MemoBoard &MemoBoard) {
  return MemoBoard.Checked.nFile + MemoBoard.Checked.nParameter +
         MemoBoard.Checked.nFunction + MemoBoard.Checked.nVariable;
}

bool DataToJson(const MemoBoard &MemoBoard, json &JsonDoc) {
  json TotalList = json::array();
  JsonDoc["File"]["Source"] = MemoBoard.File.Source;
  JsonDoc["File"]["Config"] = MemoBoard.File.Config;

  JsonDoc["Checked"]["Function"] = MemoBoard.Checked.nFunction;
  JsonDoc["Checked"]["Parameter"] = MemoBoard.Checked.nParameter;
  JsonDoc["Checked"]["Variable"] = MemoBoard.Checked.nVariable;

  JsonDoc["Error"]["Function"] = MemoBoard.Error.nFunction;
  JsonDoc["Error"]["Parameter"] = MemoBoard.Error.nParameter;
  JsonDoc["Error"]["Variable"] = MemoBoard.Error.nVariable;

  json JsonErrDetail;
  json ErrorDetailList = json::array();
  for (const ErrorDetail *pErrDetail : MemoBoard.ErrorDetailList) {
    JsonErrDetail["Line"] = pErrDetail->Pos.nLine;
    JsonErrDetail["Column"] = pErrDetail->Pos.nColumn;
    JsonErrDetail["Type"] = (int)pErrDetail->Type;
    JsonErrDetail["TypeName"] = pErrDetail->TypeName +
                                (pErrDetail->bIsPtr ? "*" : "") +
                                (pErrDetail->bIsArray ? "[]" : "");
    JsonErrDetail["TargetName"] = pErrDetail->TargetName;
    JsonErrDetail["Expected"] = pErrDetail->Suggestion;
    ErrorDetailList.push_back(JsonErrDetail);
  }

  JsonDoc["ErrorDetailList"] = ErrorDetailList;
  TotalList.push_back(JsonDoc);
  // cout << pretty_print(JsonDoc) << endl;

  return true;
}

bool PrintTraceMemo(const MemoBoard &MemoBoard) {

  bool bStatus = true;
  char szText[512] = {0};

  cout << " File    = " << MemoBoard.File.Source << endl;
  cout << " Config  = " << MemoBoard.File.Config << endl;
  for (size_t nIdx = 0; nIdx < MemoBoard.Dir.Includes.size(); nIdx++) {
    sprintf(szText, " Inc[%2d] = %s", nIdx + 1,
            MemoBoard.Dir.Includes[nIdx].c_str());
    printf("%s\n", szText);
    if (MemoBoard.Option.bEnableLog) {
      DcLib::Log::Out(INFO_ALL, szText);
    }
  }

  sprintf(szText, " Checked = %5d  [File:%d | Func:%3d | Param:%3d | Var:%3d]",
          GetTotalChecked(MemoBoard), MemoBoard.Checked.nFile,
          MemoBoard.Checked.nFunction, MemoBoard.Checked.nParameter,
          MemoBoard.Checked.nVariable);
  printf("%s\n", szText);
  if (MemoBoard.Option.bEnableLog) {
    DcLib::Log::Out(INFO_ALL, szText);
  }

  sprintf(szText, " Error   = %5d  [File:%d | Func:%3d | Param:%3d | Var:%3d]",
          GetTotalError(MemoBoard), MemoBoard.Error.nFile,
          MemoBoard.Error.nFunction, MemoBoard.Error.nParameter,
          MemoBoard.Error.nVariable);
  printf("%s\n", szText);
  if (MemoBoard.Option.bEnableLog) {
    DcLib::Log::Out(INFO_ALL, szText);
  }

  printf("------------------------------------------------------------\n");
  if (MemoBoard.Option.bEnableLog) {
    DcLib::Log::Out(
        INFO_ALL,
        "------------------------------------------------------------");
  }

  for (const ErrorDetail *pErrDetail : MemoBoard.ErrorDetailList) {
    switch (pErrDetail->Type) {
    case CheckType::CT_File:
      cout << std::left << "  < 0, 0 >" << std::left << std::setw(15)
           << " File: " << pErrDetail->TargetName.c_str() << endl;
      break;

    case CheckType::CT_Function:
      sprintf(szText, "  <%4d, %4d> Function: %s", pErrDetail->Pos.nLine,
              pErrDetail->Pos.nColumn, pErrDetail->TargetName.c_str());

      printf("%s\n", szText);
      if (MemoBoard.Option.bEnableLog) {
        DcLib::Log::Out(INFO_ALL, szText);
      }
      break;

    case CheckType::CT_Parameter:
      sprintf(szText, "  <%4d, %4d> Parameter: %s (%s%s)",
              pErrDetail->Pos.nLine, pErrDetail->Pos.nColumn,
              pErrDetail->TargetName.c_str(), pErrDetail->TypeName.c_str(),
              (pErrDetail->bIsPtr ? "*" : ""));

      printf("%s\n", szText);
      if (MemoBoard.Option.bEnableLog) {
        DcLib::Log::Out(INFO_ALL, szText);
      }
      break;

    case CheckType::CT_Variable:
      sprintf(szText, "  <%4d, %4d> Variable : %s (%s%s%s)",
              pErrDetail->Pos.nLine, pErrDetail->Pos.nColumn,
              pErrDetail->TargetName.c_str(), pErrDetail->TypeName.c_str(),
              (pErrDetail->bIsPtr ? "*" : ""),
              (pErrDetail->bIsArray ? "[]" : ""));

      printf("%s\n", szText);
      if (MemoBoard.Option.bEnableLog) {
        DcLib::Log::Out(INFO_ALL, szText);
      }
      break;

    default:
      bStatus = false;
    }
  }

  return bStatus;
}

bool WriteJsonResult(const MemoBoard &MemoBoard, const string &FilePath) {
  if (!Path::IsExist(FilePath)) {
    json JasonEmty = json::array();
    ofstream MyFile;
    MyFile.open(FilePath);
    MyFile << JasonEmty;
    MyFile.close();
  } else {
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
