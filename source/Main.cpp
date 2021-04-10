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
#include "spdlog/spdlog.h"

// LLVM
#include "clang/Tooling/CompilationDatabase.h"

int main(int Argc, const char **Argv) {

  cout << endl;
  cout << "cppnamelint utility v0.3.4" << endl;
  cout << "---------------------------------------------------" << endl;

  //
  // Initialize LLVM's CommandLine library.
  //
  cl::HideUnrelatedOptions(CppNameLintCategory);
  cl::ParseCommandLineOptions(Argc, Argv);

  //
  // Assign input arguments to variables of AppCxt.
  //
  AppCxt &AppCxt      = AppCxt::getInstance();
  StringRef InputPath = CheckInputSrc;
  SmallString<1024> AbsSrcPath(InputPath);
  llvm::sys::fs::make_absolute(AbsSrcPath);

  AppCxt.MemoBoard.File.Config       = CheckInputConfig;
  AppCxt.MemoBoard.File.Source       = AbsSrcPath.str().str();
  AppCxt.MemoBoard.File.OutputJson   = CheckOutputJson;
  AppCxt.MemoBoard.File.LogFile      = LogFile;
  AppCxt.MemoBoard.File.bVerboseMode = VerboseMode;
  AppCxt.MemoBoard.Dir.Includes      = CheckIncludes;

  if (!CheckInputConfig.empty()) {
    if (!llvm::sys::fs::exists(CheckInputConfig)) {
      cout << "Error: Failed to find config file." << endl;
      return 2;
    }
    string ErrorReason;
    if (!AppCxt.MemoBoard.Config.LoadFile(CheckInputConfig, ErrorReason)) {
      cout << "Error: Failed to load config file (format wrong)." << endl;
      cout << ErrorReason << endl;
      return 3;
    }
  } else {
    // TODO: Load default setting if not input config file.
  }

  if (LogFile.length() > 0) {
    printf("INFO : Log message will print to the file (%s).\n\n", LogFile.c_str());
    AppCxt.MemoBoard.SpdLog = spdlog::basic_logger_mt("", LogFile);
    AppCxt.MemoBoard.SpdLog->set_level(spdlog::level::info);
    LogHead();

    int iPos = AppCxt.MemoBoard.Config.GetData()->Debug.Log.iContentStartsPosition;
  } else {
    AppCxt.MemoBoard.SpdLog = spdlog::stderr_logger_mt("");
    AppCxt.MemoBoard.SpdLog->set_level(spdlog::level::off);
  }

  int iRet = 0;
  if (CheckSubcommand) {
    LogConfig();
    iRet = RunCheckFormFile(AppCxt.MemoBoard);
    LogCheckResult();

  } else if (TestSubcommand) {
    iRet = RunTest(TestOutputJson, TestNameFilter);

  } else {
    iRet = -1; /* Error (Command miss matched.) */
    cl::PrintHelpMessage();
  }

  AppCxt.MemoBoard.SpdLog->info("Program is going to close. (iRet={})", iRet);
  return iRet;
}
