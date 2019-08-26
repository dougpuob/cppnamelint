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
#include <fstream>
#include <gtest/gtest.h>
#include <iostream>
#include <map>
#include <nlohmann/json.hpp>
#include <sstream>
#include <string>
#include <vector>

using namespace nlohmann;
using namespace namelint;

size_t GetTotalError(const TraceMemo &TraceMemo);

bool DataToJson(const TraceMemo &TraceMemo, json &JsonDoc);

bool PrintTraceMemo(const TraceMemo &TraceMemo);

bool WriteJsonResult(const TraceMemo &TraceMemo, const string &FilePath);

int main(int iArgc, char **pszArgv) {
    const char *szTitle = "cppnamelint utility v0.2.5";
    static const char *szUsage =
        R"(
  Usage:
    cppnamelint check <file> [--config=<file>] [--log=<file>] [--jsonout=<file>] [--includes=<dir1:dir2:...>]
    cppnamelint test   [-a | --all] [-u | --unittest]
    cppnamelint --help
    cppnamelint --version

  Options:
	--config=<file>  [default: cppnamelint.toml]    
	--jsonout=<file> [default: cppnamelint.json]    
    --log=<file>     [default: cppnamelint.log]
  )";

    map<string, docopt::value> Arguments = docopt::docopt(szUsage, {pszArgv + 1, pszArgv + iArgc},
                                                          false, // show help if requested
                                                          "");   // version string

    int iReturn = 0;

    // for convenience
    // using json = nlohmann::json;

    cout << szTitle << endl;
    cout << "---------------------------------------------------" << endl;
    if (Arguments["check"].asBool() && Arguments["<file>"].asString().length() > 0) {
        APP_CONTEXT *pAppCxt = (APP_CONTEXT *)GetAppCxt();

        namelint::Config Config;

        string ConfigFilePath = Arguments["--config"].asString();
        bool bResult          = Path::IsExist(ConfigFilePath);
        if (bResult) {
            bResult = Config.LoadFile(ConfigFilePath);
            if (!bResult) {
                cout << "Error: Failed to load config file (format wrong)" << endl;
            }
        } else {
            cout << "Error: Failed to find a config file" << endl;
        }

        string JsonOutFilePath = "cppnamelint.json";
        if (Arguments["--jsonout"]) {
            JsonOutFilePath = Arguments["--jsonout"].asString();
        }

        pAppCxt->TraceMemo.File.Config = ConfigFilePath;
        pAppCxt->pTomlConfig           = &Config;

        if (Arguments["--includes"]) {
            vector<string> IncludeDirs;
            size_t nCount = String::Split(Arguments["--includes"].asString(), IncludeDirs, ',');
            for (size_t nIdx = 0; nIdx < nCount; nIdx++) {
                string FullPath;
                if (Path::NormPath(IncludeDirs[nIdx].c_str(), FullPath)) {
                    string IncArg = "-I" + FullPath;
                    pAppCxt->TraceMemo.Dir.Includes.push_back(IncArg);
                }
            }
        }

        int iMyArgc      = 3 + pAppCxt->TraceMemo.Dir.Includes.size();
        char **pszMyArgV = new char *[iMyArgc];
        pszMyArgV[0]     = strdup("");
        pszMyArgV[1]     = strdup("*.*");
        pszMyArgV[2]     = strdup("--");
        size_t nIdx      = 3;
        for (auto Item : pAppCxt->TraceMemo.Dir.Includes) {
            pszMyArgV[nIdx] = strdup(Item.c_str());
            nIdx++;
        }

        static llvm::cl::OptionCategory NameLintOptions("NameLintOptions");
        CommonOptionsParser NullOptionsParser(iMyArgc, (const char **)pszMyArgV, NameLintOptions);

        string FileNamePath            = Arguments["<file>"].asString();
        string FileName                = Path::FindFileName(FileNamePath);
        pAppCxt->TraceMemo.File.Source = FileNamePath;

        // Utility to run a FrontendAction over a set of files.
        vector<string> SourcePathList;
        SourcePathList.push_back(FileNamePath);
        ClangTool Tool(NullOptionsParser.getCompilations(), SourcePathList);

        // [DiagnosticConsume class]
        // Abstract interface, implemented by clients of the front-end, which
        // formats and prints fully processed diagnostics.
        Tool.setDiagnosticConsumer(
            /*(clang::DiagnosticConsumer*)*/ new IgnoringDiagConsumer());

        MyFactory MyFactory;
        std::unique_ptr<FrontendActionFactory> Factory = newFrontendActionFactory(&MyFactory);

        Detection dect;
        shared_ptr<ConfigData> pConfig = Config.GetData();
        if (pConfig->General.Options.bCheckFileName) {
            RuleOfFile Rule;
            Rule.bAllowedUnderscopeChar = pConfig->General.Options.bAllowedUnderscopeChar;
            dect.ApplyRuleForFile(Rule);

            pAppCxt->TraceMemo.Checked.nFile++;
            if (!dect.CheckFile(pConfig->General.Rules.FileName, FileName)) {
                pAppCxt->TraceMemo.Error.nFile++;
                pAppCxt->TraceMemo.ErrorDetailList.push_back(new ErrorDetail(FileName, ""));
            }
        }

        if (0 == Tool.run(Factory.get())) {
            iReturn = GetTotalError(GetAppCxt()->TraceMemo);
            PrintTraceMemo(GetAppCxt()->TraceMemo);
            WriteJsonResult(GetAppCxt()->TraceMemo, JsonOutFilePath);
        } else {
            iReturn = -1;
        }

        for (size_t nIdx = 0; nIdx < (size_t)iMyArgc; nIdx++) {
            free(pszMyArgV[nIdx]);
        }
        delete[] pszMyArgV;

    } else if (Arguments["test"].asBool()) {
        testing::InitGoogleTest(&iArgc, (char **)pszArgv);
        iReturn = RUN_ALL_TESTS();
    } else if (Arguments["nonono"].asBool()) {
        std::cout << "<file>   = " << Arguments["<file>"] << endl;
    } else {
        // Command miss matched.
        iReturn = -1 /* Error */;
    }

    return iReturn;
}

size_t GetTotalError(const TraceMemo &TraceMemo) {
    return TraceMemo.Error.nFile + TraceMemo.Error.nParameter + TraceMemo.Error.nFunction + TraceMemo.Error.nVariable;
}

size_t GetTotalChecked(const TraceMemo &TraceMemo) {
    return TraceMemo.Checked.nFile + TraceMemo.Checked.nParameter + TraceMemo.Checked.nFunction +
           TraceMemo.Checked.nVariable;
}

bool DataToJson(const TraceMemo &TraceMemo, json &JsonDoc) {
    json TotalList            = json::array();
    JsonDoc["File"]["Source"] = TraceMemo.File.Source;
    JsonDoc["File"]["Config"] = TraceMemo.File.Config;

    JsonDoc["Checked"]["Function"]  = TraceMemo.Checked.nFunction;
    JsonDoc["Checked"]["Parameter"] = TraceMemo.Checked.nParameter;
    JsonDoc["Checked"]["Variable"]  = TraceMemo.Checked.nVariable;

    JsonDoc["Error"]["Function"]  = TraceMemo.Error.nFunction;
    JsonDoc["Error"]["Parameter"] = TraceMemo.Error.nParameter;
    JsonDoc["Error"]["Variable"]  = TraceMemo.Error.nVariable;

    json JsonErrDetail;
    json ErrorDetailList = json::array();
    for (const ErrorDetail *pErrDetail : TraceMemo.ErrorDetailList) {
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

bool PrintTraceMemo(const TraceMemo &TraceMemo) {
    bool bStatus = true;
    cout << " File    = " << TraceMemo.File.Source << endl;
    cout << " Config  = " << TraceMemo.File.Config << endl;
    for (size_t nIdx = 0; nIdx < TraceMemo.Dir.Includes.size(); nIdx++) {
        printf(" Inc[%2d] = %s\n", nIdx + 1, TraceMemo.Dir.Includes[nIdx].c_str());
    }

    printf(" Checked = %5d  [File:%d | Func:%3d | Param:%3d | Var:%3d]\n", GetTotalChecked(TraceMemo),
           TraceMemo.Checked.nFile, TraceMemo.Checked.nFunction, TraceMemo.Checked.nParameter,
           TraceMemo.Checked.nVariable);

    printf(" Error   = %5d  [File:%d | Func:%3d | Param:%3d | Var:%3d]\n", GetTotalError(TraceMemo),
           TraceMemo.Error.nFile, TraceMemo.Error.nFunction, TraceMemo.Error.nParameter, TraceMemo.Error.nVariable);

    cout << "---------------------------------------------------" << endl;
    for (const ErrorDetail *pErrDetail : TraceMemo.ErrorDetailList) {
        switch (pErrDetail->Type) {
        case CheckType::CT_File:
            cout << std::left << "  < 0, 0 >" << std::left << std::setw(15) << " File: " << pErrDetail->TargetName
                 << endl;
            break;

        case CheckType::CT_Function:
            cout << std::left << "  <" << pErrDetail->Pos.nLine << ", " << pErrDetail->Pos.nColumn << ">" << std::left
                 << std::setw(15) << " Function: " << pErrDetail->TargetName << endl;
            break;

        case CheckType::CT_Parameter:
            cout << std::left << "  <" << pErrDetail->Pos.nLine << ", " << pErrDetail->Pos.nColumn << ">" << std::left
                 << std::setw(15) << " Parameter: " << pErrDetail->TargetName << " (" << pErrDetail->TypeName
                 << (pErrDetail->bIsPtr ? "*" : "") << ")" << endl;
            break;

        case CheckType::CT_Variable:
            cout << std::left << "  <" << pErrDetail->Pos.nLine << ", " << pErrDetail->Pos.nColumn << ">" << std::left
                 << std::setw(15) << " Variable : " << pErrDetail->TargetName << " (" << pErrDetail->TypeName
                 << (pErrDetail->bIsPtr ? "*" : "") << (pErrDetail->bIsArray ? "[]" : "") << ")" << endl;
            break;

        default:
            bStatus = false;
        }
    }

    return bStatus;
}

bool WriteJsonResult(const TraceMemo &TraceMemo, const string &FilePath) {
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

    if (DataToJson(TraceMemo, JsonNew)) {
        ofstream MyFile;
        MyFile.open(FilePath);
        JsonAll.push_back(JsonNew);
        MyFile << JsonAll;
        MyFile.close();
        return true;
    }
    return false;
}