// Standard libraries
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

// Submodule projects
#include <gtest/gtest.h>
#include <nlohmann/json.hpp>

// This project
#include "Common.h"
#include "Config.h"
#include "Detection.h"
#include "MyAstConsumer.h"
#include "MyAstVisitor.h"
#include "MyCommandLine.h"
#include "MyFactory.h"

// LLVM
#include "clang/Tooling/CompilationDatabase.h"

LOG_DECISION_DEFAULT(false);

void LogHead() {
  APP_CONTEXT *pAppCxt = (APP_CONTEXT *)GetAppCxt();
  int iPos             = pAppCxt->MemoBoard.Config.GetData()->Debug.Log.iContentStartsPosition;

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
  DcLib::Log::Out(INFO_ALL, "INFO : Log message will print to the file (%s).", LogFile.c_str());
}

void LogConfig() {
  APP_CONTEXT *pAppCxt            = (APP_CONTEXT *)GetAppCxt();
  shared_ptr<ConfigData> pCfgData = pAppCxt->MemoBoard.Config.GetData();

  DcLib::Log::Out(INFO_ALL, "CheckSubcommand     = %d", (bool)CheckSubcommand);
  DcLib::Log::Out(INFO_ALL, "TestSubcommand      = %d", (bool)TestSubcommand);

  DcLib::Log::Out(INFO_ALL, "bCheckFileName      = %d", pCfgData->General.Options.bCheckFileName);
  DcLib::Log::Out(INFO_ALL, "bCheckFunctionName  = %d",
                  pCfgData->General.Options.bCheckFunctionName);
  DcLib::Log::Out(INFO_ALL, "bCheckEnum          = %d", pCfgData->General.Options.bCheckEnum);
  DcLib::Log::Out(INFO_ALL, "bCheckStruct        = %d", pCfgData->General.Options.bCheckStruct);
  DcLib::Log::Out(INFO_ALL, "bCheckVariableName  = %d",
                  pCfgData->General.Options.bCheckVariableName);
}

void LogCheckResult() {
  APP_CONTEXT *pAppCxt = (APP_CONTEXT *)GetAppCxt();

  DcLib::Log::Out(INFO_ALL, "Assert.nErrorOccurred = %d", pAppCxt->MemoBoard.Assert.nErrorOccurred);
  DcLib::Log::Out(INFO_ALL, "Assert.nInvalidDecl   = %d", pAppCxt->MemoBoard.Assert.nInvalidDecl);
  DcLib::Log::Out(INFO_ALL, "Assert.nNumWarnings   = %d", pAppCxt->MemoBoard.Assert.nNumWarnings);

  DcLib::Log::Out(INFO_ALL, "Checked.nClass        = %d", pAppCxt->MemoBoard.Checked.nClass);
  DcLib::Log::Out(INFO_ALL, "Checked.nEnum         = %d", pAppCxt->MemoBoard.Checked.nEnum);
  DcLib::Log::Out(INFO_ALL, "Checked.nFile         = %d", pAppCxt->MemoBoard.Checked.nFile);
  DcLib::Log::Out(INFO_ALL, "Checked.nFunction     = %d", pAppCxt->MemoBoard.Checked.nFunction);
  DcLib::Log::Out(INFO_ALL, "Checked.nParameter    = %d", pAppCxt->MemoBoard.Checked.nParameter);
  DcLib::Log::Out(INFO_ALL, "Checked.nStruct       = %d", pAppCxt->MemoBoard.Checked.nStruct);
  DcLib::Log::Out(INFO_ALL, "Checked.nUnion        = %d", pAppCxt->MemoBoard.Checked.nUnion);
  DcLib::Log::Out(INFO_ALL, "Checked.nVariable     = %d", pAppCxt->MemoBoard.Checked.nVariable);

  DcLib::Log::Out(INFO_ALL, "Error.nClass          = %d", pAppCxt->MemoBoard.Error.nClass);
  DcLib::Log::Out(INFO_ALL, "Error.nEnum           = %d", pAppCxt->MemoBoard.Error.nEnum);
  DcLib::Log::Out(INFO_ALL, "Error.nFile           = %d", pAppCxt->MemoBoard.Error.nFile);
  DcLib::Log::Out(INFO_ALL, "Error.nFunction       = %d", pAppCxt->MemoBoard.Error.nFunction);
  DcLib::Log::Out(INFO_ALL, "Error.nParameter      = %d", pAppCxt->MemoBoard.Error.nParameter);
  DcLib::Log::Out(INFO_ALL, "Error.nStruct         = %d", pAppCxt->MemoBoard.Error.nStruct);
  DcLib::Log::Out(INFO_ALL, "Error.nUnion          = %d", pAppCxt->MemoBoard.Error.nUnion);
  DcLib::Log::Out(INFO_ALL, "Error.nVariable       = %d", pAppCxt->MemoBoard.Error.nVariable);
}

int main(int Argc, const char **Argv) {

  cout << endl;
  cout << "cppnamelint utility v0.3.3" << endl;
  cout << "---------------------------------------------------" << endl;

  //
  // Initialize LLVM's CommandLine library.
  //
  cl::HideUnrelatedOptions(CppNameLintCategory);
  cl::ParseCommandLineOptions(Argc, Argv);

  //
  // Assign input arguments to variables of AppCxt.
  //
  APP_CONTEXT *pAppCxt = (APP_CONTEXT *)GetAppCxt();
  StringRef InputPath  = CheckInputSrc;
  SmallString<1024> AbsSrcPath(InputPath);
  llvm::sys::fs::make_absolute(AbsSrcPath);

  pAppCxt->MemoBoard.File.Config  = CheckInputConfig;
  pAppCxt->MemoBoard.File.Source  = AbsSrcPath.str();
  pAppCxt->MemoBoard.Dir.Includes = CheckIncludes;

  if (!CheckInputConfig.empty()) {
    if (!llvm::sys::fs::exists(CheckInputConfig)) {
      cout << "Error: Failed to find config file." << endl;
      return 2;
    }
    string ErrorReason;
    if (!pAppCxt->MemoBoard.Config.LoadFile(CheckInputConfig, ErrorReason)) {
      cout << "Error: Failed to load config file (format wrong)." << endl;
      cout << ErrorReason << endl;
      return 3;
    }
  } else {
    // TODO: Load default setting if not input config file.
  }

  if (LogFile.length() > 0) {
    printf("INFO : Log message will print to the file (%s).\n\n", LogFile.c_str());
    printf("INFO : Log message will print to the file (%s).\n\n", LogFile.c_str());
    LogHead();

    int iPos = pAppCxt->MemoBoard.Config.GetData()->Debug.Log.iContentStartsPosition;
    DcLib::Log::Init(LogFile.c_str(), iPos);
  }

  LOG_DECISION_CHANGE(pAppCxt->MemoBoard.Config.GetData()->Debug.Log.bMain);

  int iRet = 0;
  if (CheckSubcommand) {
    LogConfig();
    iRet = RunCheckFormFile(pAppCxt->MemoBoard);
    LogCheckResult();

  } else if (TestSubcommand) {
    iRet = RunTest(TestOutputJson, TestNameFilter);

  } else {
    iRet = -1; /* Error (Command miss matched.) */
    cl::PrintHelpMessage();
  }

  DcLib::Log::Out(INFO_ALL, "Program is going to close. (iRet=%d)", iRet);
  return iRet;
}
