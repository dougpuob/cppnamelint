//#include "HelloCli/Cli.h"

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

using namespace namelint;

int main(int argc, char** argv)
{
    static const char USAGE[] =
        R"(NameLint utility v0.0.1

  Usage:
    namelint check <file> [--config=<file>] [--log=<file>]
    namelint test   [-a | --all] [-u | --unittest]
    namelint config [--config=<file>]
    namelint --help
    namelint --version

  Options:
    --config=<file>   [default: namelint.toml]
    --log=<file>      [default: namelint.log]
  )";

    std::map<std::string, docopt::value> Arguments =
        docopt::docopt(USAGE, {argv + 1, argv + argc},
                       false,              // show help if requested
                       "Naval Fate 2.0");  // version string

    std::cout << "--config = " << Arguments["--config"] << endl;
    std::cout << "--help   = " << Arguments["--help"] << endl;
    std::cout << "--abc    = " << Arguments["--abc"] << endl;

    int iReturn = 0;

    if (Arguments["check"].asBool() && Arguments["<file>"].asString().length() > 0)
    {
        APP_CONTEXT* pAppCxt = (APP_CONTEXT*)GetAppCxt();

        namelint::Config Config;
        Config.Load(Arguments["--config"].asString());
        pAppCxt->pTomlConfig = &Config;

        int iMyArgc            = 3;
        const char* ppMyArgV[] = {"", "*.*", "--"};
        static llvm::cl::OptionCategory NameLintOptions("NameLintOptions");
        CommonOptionsParser NullOptionsParser(iMyArgc, ppMyArgV, NameLintOptions);

        vector<string> SourcePathList;
        SourcePathList.push_back(Arguments["<file>"].asString());
        ClangTool Tool(NullOptionsParser.getCompilations(), SourcePathList);

        Tool.setDiagnosticConsumer(new MyIgnoringDiagConsumer());

        MyFactory MyFactory;
        std::unique_ptr<FrontendActionFactory> Factory = newFrontendActionFactory(&MyFactory);

        Tool.run(Factory.get());
    }
    else if (Arguments["config"].asBool())
    {
        namelint::Config Config;
        Config.Print(Arguments["--config"].asString());
    }
    else if (Arguments["test"].asBool())
    {
        ::testing::InitGoogleTest(&argc, (char**)argv);
        iReturn = RUN_ALL_TESTS();
    }
    else
    {
        iReturn = 1;  // Error
    }

    return iReturn;
}
