#ifndef __NAMELINT_PARSEAST__H__
#define __NAMELINT_PARSEAST__H__

#include <iostream>
#include <vector>

#include <llvm/Support/CommandLine.h>

#include "clang/AST/AST.h"
#include "clang/AST/ASTConsumer.h"
#include "clang/AST/ASTContext.h"
#include "clang/AST/Decl.h"
#include "clang/AST/DeclVisitor.h"
#include "clang/AST/RecursiveASTVisitor.h"
#include "clang/Frontend/ASTConsumers.h"
#include "clang/Frontend/CompilerInstance.h"
#include "clang/Frontend/FrontendActions.h"
#include "clang/Lex/Preprocessor.h"
#include "clang/Parse/Parser.h"
#include "clang/Tooling/CommonOptionsParser.h"
#include "clang/Tooling/Tooling.h"

#include "Config.h"
#include "Detection.h"

using namespace std;
using namespace clang;
using namespace clang::tooling;
using namespace llvm;
using namespace clang::driver;
using namespace clang::tooling;

class MyASTVisitor : public RecursiveASTVisitor<MyASTVisitor> {
   private:
    ASTContext *m_pAstCxt;
    const SourceManager *m_pSrcMgr;
    namelint::Detection m_Detect;
    string m_FileName;

    bool m_bCheckFile;
    bool m_bCheckFunction;
    bool m_bCheckVariable;
    bool bAllowedEndWithUnderscopeChar;

    namelint::RULETYPE m_FileRuleType;
    namelint::RULETYPE m_FunctionRuleType;
    namelint::RULETYPE m_VariableRuleType;

    map<string, string> m_HungarianMappedList;
    vector<string> m_FileExt;
    vector<string> m_FunctionIgnorePrefix;
    vector<string> m_VariableIgnorePrefix;

    bool isMainFile(Decl *pDecl);
    bool printPosition(Decl *pDecl);
    void keepFileName(string &Path);
    bool getPosition(Decl *pDecl, string &FileName, size_t &nLineNumb, size_t &nColNumb);
    bool classifyTypeName(string &TyeName);
    void stringReplace(string &Source, const string &Patn, const string &New);
    void stringTrim(string &s);

    bool assertWithFunction(FunctionDecl *pDecl, string &FuncName);
    bool assertWithParm(ParmVarDecl *pDecl, string &TypeName, string &VarName);
    bool assertWithVar(VarDecl *pDecl, string &TypeName, string &VarName);

    bool getFunctionInfo(FunctionDecl *pDecl, string &FuncName);
    bool getParmsInfo(ParmVarDecl *pDecl, string &VarType, string &VarName);
    bool getVarInfo(VarDecl *pDecl, string &VarType, string &VarName);

   public:
    MyASTVisitor(const SourceManager *pSM,
                 const ASTContext *pAstCxt,
                 const namelint::Config *pConfig);
    // bool VisitStmt(Stmt *pStmt);
    // bool VisitCXXRecordDecl(CXXRecordDecl *D);
    // bool VisitCXXConstructorDecl(CXXConstructorDecl *D);
    bool VisitFunctionDecl(FunctionDecl *pDecl);
    bool VisitCXXMethodDecl(CXXMethodDecl *pDecl);
    bool VisitRecordDecl(RecordDecl *pDecl);
    bool VisitVarDecl(VarDecl *pDecl);
    bool VisitReturnStmt(ReturnStmt *pRetStmt);
};

class MyASTConsumer : public ASTConsumer {
   private:
   public:
    bool HandleTopLevelDecl(DeclGroupRef declGroupRef);
    void HandleTranslationUnit(ASTContext &Ctx);
};

class MyFactory {
   public:
    std::unique_ptr<MyASTConsumer> newASTConsumer();
};

class MyIgnoringDiagConsumer : public IgnoringDiagConsumer {
   public:
    // virtual void HandleDiagnostic(DiagnosticsEngine::Level DiagLevel, const
    // Diagnostic &Info);
};

#endif