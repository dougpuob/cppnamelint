#include "Common.h"
#include "Config.h"
#include "Detection.h"

#include "llvm/Support/CommandLine.h"

#include "clang/AST/AST.h"
#include "clang/AST/ASTConsumer.h"
#include "clang/AST/ASTContext.h"
#include "clang/AST/Decl.h"
#include "clang/AST/DeclVisitor.h"
#include "clang/AST/RecursiveASTVisitor.h"
#include "clang/Basic/Diagnostic.h"
#include "clang/Frontend/ASTConsumers.h"
#include "clang/Frontend/CompilerInstance.h"
#include "clang/Frontend/FrontendActions.h"
#include "clang/Lex/Preprocessor.h"
#include "clang/Parse/Parser.h"
#include "clang/Tooling/CommonOptionsParser.h"
#include "clang/Tooling/Tooling.h"

#include "MyAstConsumer.h"
#include "MyAstVisitor.h"
#include "MyFactory.h"

#include <docopt.h>
#include <gtest/gtest.h>
#include <map>
#include <sstream>
#include <string>
#include <vector>

using namespace namelint;

int
main(int iArgc, char** pszArgv)
{
    static const char USAGE[] =
      R"(cppnamelint utility v0.1.2

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
        bool bResult = Path::IsExist(ConfigFilePath);
        if (!bResult) {
            bResult = Path::IsExist(Arguments["--config"].asString());
            if (bResult) {
                ConfigFilePath = Arguments["--config"].asString();
            }
        }

        if (bResult) {
            bResult = Config.LoadFile(ConfigFilePath);
            if (!bResult) {
                cout << "Error: Failed to load config file (format wrong)"
                     << endl;
            }
        } else {
            cout << "Error: Failed to find a config file" << endl;
        }

        pAppCxt->pTomlConfig = &Config;

        int iMyArgc = 3;
        const char* szMyArgV[] = { "", "*.*", "--" };
        static llvm::cl::OptionCategory NameLintOptions("NameLintOptions");
        CommonOptionsParser NullOptionsParser(
          iMyArgc, szMyArgV, NameLintOptions);

        vector<string> SourcePathList;
        SourcePathList.push_back(Arguments["<file>"].asString());

        // Utility to run a FrontendAction over a set of files.
        ClangTool Tool(NullOptionsParser.getCompilations(), SourcePathList);

        // [DiagnosticConsume class]
        // Abstract interface, implemented by clients of the front-end, which
        // formats and prints fully processed diagnostics.
        Tool.setDiagnosticConsumer(
          /*(clang::DiagnosticConsumer*)*/ new IgnoringDiagConsumer());

        MyFactory MyFactory;
        std::unique_ptr<FrontendActionFactory> Factory =
          newFrontendActionFactory(&MyFactory);

        if (0 == Tool.run(Factory.get())) {
            iReturn = GetAppCxt()->nErrorCount;
        } else {
            iReturn = -1;
        }
    } else if (Arguments["test"].asBool()) {
        testing::InitGoogleTest(&iArgc, (char**)pszArgv);
        iReturn = RUN_ALL_TESTS();
    } else {
        // Command miss matched.
        iReturn = -1 /* Error */;
    }

    return iReturn;
}
