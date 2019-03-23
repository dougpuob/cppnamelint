#include "Common.h"
#include "Config.h"
#include "Detection.h"
#include "ParseAST.h"

#include <docopt.h>
#include <gtest/gtest.h>
#include <map>
#include <sstream>
#include <string>
#include <vector>

#if __has_include("filesystem")
#include <filesystem>
using namespace filesystem;
#else
#include <boost/filesystem.hpp>
namespace filesystem = boost::filesystem;
#endif
using namespace namelint;

int
main(int iArgc, char** pszArgv)
{
  static const char USAGE[] =
    R"(cppnamelint utility v0.1.1

  Usage:
    cppnamelint check <file> [--config=<file>] [--log=<file>]
    cppnamelint test   [-a | --all] [-u | --unittest]
    cppnamelint --help
    cppnamelint --version

  Options:
    --config=<file>   [default: cppnamelint.toml]
    --log=<file>      [default: cppnamelint.log]
  )";

  std::map<std::string, docopt::value> Arguments =
    docopt::docopt(USAGE,
                   { pszArgv + 1, pszArgv + iArgc },
                   false, // show help if requested
                   "");   // version string

  std::cout << "<file>   = " << Arguments["<file>"] << endl;
  std::cout << "--config = " << Arguments["--config"] << endl;

  int iReturn = 0;

  if (Arguments["check"].asBool() &&
      Arguments["<file>"].asString().length() > 0) {
    APP_CONTEXT* pAppCxt = (APP_CONTEXT*)GetAppCxt();

    namelint::Config Config;
    string ConfigFilePath = "";

    ConfigFilePath = ".cppnamelint";
    bool bResult = filesystem::exists(ConfigFilePath);
    if (!bResult) {
      bResult = filesystem::exists(Arguments["--config"].asString());
      if (bResult) {
        ConfigFilePath = Arguments["--config"].asString();
      }
    }

    if (bResult) {
      bResult = Config.LoadFile(ConfigFilePath);
      if (!bResult) {
        cout << "Error: Failed to load config file (format wrong)" << endl;
      }
    } else {
      cout << "Error: Failed to find a config file" << endl;
    }

    pAppCxt->pTomlConfig = &Config;

    int iMyArgc = 3;
    const char* szMyArgV[] = { "", "*.*", "--" };
    static llvm::cl::OptionCategory NameLintOptions("NameLintOptions");
    CommonOptionsParser NullOptionsParser(iMyArgc, szMyArgV, NameLintOptions);

    vector<string> SourcePathList;
    SourcePathList.push_back(Arguments["<file>"].asString());
    ClangTool Tool(NullOptionsParser.getCompilations(), SourcePathList);

    Tool.setDiagnosticConsumer(new MyIgnoringDiagConsumer());

    MyFactory MyFactory;
    std::unique_ptr<FrontendActionFactory> Factory =
      newFrontendActionFactory(&MyFactory);

    Tool.run(Factory.get());
    iReturn = GetAppCxt()->nAsserted;
  } else if (Arguments["test"].asBool()) {
    ::testing::InitGoogleTest(&iArgc, (char**)pszArgv);
    iReturn = RUN_ALL_TESTS();
  } else {
    iReturn = 1; // Error
  }

  return iReturn;
}
