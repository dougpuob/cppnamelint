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

#if __has_include("filesystem")
#    include <filesystem>
using namespace filesystem;
#else
#    include <boost/filesystem.hpp>
namespace filesystem = boost::filesystem;
#endif
using namespace namelint;

int main(int argc, char** argv)
{
    static const char USAGE[] =
        R"(NameLint utility v0.0.2

  Usage:
    namelint check <file> [--config=<file>] [--log=<file>]
    namelint test   [-a | --all] [-u | --unittest]
    namelint --help
    namelint --version

  Options:
    --config=<file>   [default: namelint.toml]
    --log=<file>      [default: namelint.log]
  )";

    std::map<std::string, docopt::value> Arguments =
        docopt::docopt(USAGE, {argv + 1, argv + argc},
                       false,  // show help if requested
                       "");    // version string

    std::cout << "<file>   = " << Arguments["<file>"] << endl;
    std::cout << "--config = " << Arguments["--config"] << endl;

    int iReturn = 0;

    if (Arguments["check"].asBool() && Arguments["<file>"].asString().length() > 0)
    {
        APP_CONTEXT* pAppCxt = (APP_CONTEXT*)GetAppCxt();

        namelint::Config Config;
        string config_file_path = "";

        config_file_path = ".namelint";
        bool bResult     = filesystem::exists(config_file_path);
        if (!bResult)
        {
            config_file_path = Arguments["--config"].asString();
            bResult          = filesystem::exists(config_file_path);
        }

        if (bResult)
        {
            bResult = Config.LoadFile(config_file_path);
            if (!bResult) {
				cout << "Error: Failed to load config file (format wrong)" << endl;
			}
        }
        else
        {
            cout << "Error: Failed to find a config file" << endl;
        }

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
        iReturn = GetAppCxt()->nAsserted;
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
