//#include "HelloCli/Cli.h"

#include "Common.h"
#include "Config.h"
#include "Detection.h"
#include "ParseAST.h"

#include <docopt.h>
#include <gtest/gtest.h>
#include <sstream>

using namespace namelint;

int main(int argc, char** argv)
{
    //    const char* m_UsageHelp =
    //        "\
//\r\n  COMMANDS\
//\r\n  namelint check <FILE>        Check naming of the input file\
//\r\n  namelint test  <MODE>        Run test\
//\r\n\n";
    //
    //    const char* m_UsageOption =
    //        "\
//\r\n  OPTIONS\
//\r\n  -log[=FILE]                  Write log to a specific file or default\
//\r\n  -config[=FILE]               Apply a specific config or default\
//\r\n\n";
    //

    static const char USAGE[] =
        R"(Name Lint.

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

    std::map<std::string, docopt::value> args = docopt::docopt(USAGE, {argv + 1, argv + argc},
                                                               false,  // show help if requested
                                                               "Naval Fate 2.0");  // version string

    // std::cout << "--config = " << args["--config"]  << endl;
    // std::cout << "--help   = " << args["--help"]    << endl;
    // std::cout << "--abc    = " << args["--abc"]     << endl;

    for (auto const& arg : args)
    {
        std::cout << arg.first << "  \t: " << arg.second << std::endl;
    }

    int iReturn = 0;
    if (args["check"].asBool() && args["<file>"].asString().length() > 0)
    {
        APP_CONTEXT* pAppCxt = (APP_CONTEXT*)GetAppCxt();

        namelint::Config Config;
        Config.Load(args["--config"].asString());
        pAppCxt->pTomlConfig = &Config;

        int iMyArgc            = 3;
        const char* ppMyArgV[] = {"", "*.*", "--"};
        static llvm::cl::OptionCategory NameLintOptions("NameLintOptions");
        CommonOptionsParser NullOptionsParser(iMyArgc, ppMyArgV, NameLintOptions);

        vector<string> SourcePathList;
        SourcePathList.push_back(args["<file>"].asString());
        ClangTool Tool(NullOptionsParser.getCompilations(), SourcePathList);

        Tool.setDiagnosticConsumer(new MyIgnoringDiagConsumer());

        MyFactory MyFactory;
        std::unique_ptr<FrontendActionFactory> Factory = newFrontendActionFactory(&MyFactory);

        Tool.run(Factory.get());
    }
    else if (args["config"].asBool())
    {
        namelint::Config Config;
        Config.Print(args["--config"].asString());
    }
    else if (args["test"].asBool())
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
