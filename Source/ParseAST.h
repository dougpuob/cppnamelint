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

    bool m_bCheckFile;
    bool m_bCheckFunction;
    bool m_bCheckVariable;

    namelint::RULETYPE m_FileRuleType;
    namelint::RULETYPE m_FunctionRuleType;
    namelint::RULETYPE m_VariableRuleType;

    map<string, string> m_HungarianMappedList;
    vector<string> m_FileExt;
    vector<string> m_FunctionIgnorePrefix;
    vector<string> m_VariableIgnorePrefix;

    bool isMainFile(Decl *pDecl);
    bool printPosition(Decl *pDecl);
    void keepFileName(string &FilePath);
    bool getPosition(Decl *pDecl, string &FileName, size_t &nLineNumb, size_t &nColNumb);
    bool classifyTypeName(string &TyeName);
    void stringReplace(string &strBig, const string &strsrc, const string &strdst);
    void stringTrim(string &s);

    bool assertWithFunction(FunctionDecl *pFuncDecl, string &FuncName);
    bool assertWithParm(ParmVarDecl *pParmVarDecl, string &TypeName, string &VarName);
    bool assertWithVar(VarDecl *pVarDecl, string &TypeName, string &VarName);

    bool getFunctionInfo(FunctionDecl *pFuncDecl, string &FuncName);
    bool getParmsInfo(ParmVarDecl *pParmVarDecl, string &VarType, string &VarName);
    bool getVarInfo(VarDecl *pVarDecl, string &VarType, string &VarName);

   public:
    MyASTVisitor(const SourceManager *pSM,
                 const ASTContext *pAstCxt,
                 const namelint::Config *pConfig);
    // bool VisitStmt(Stmt *pStmt);
    // bool VisitCXXRecordDecl(CXXRecordDecl *D);
    // bool VisitCXXConstructorDecl(CXXConstructorDecl *D);
    bool VisitFunctionDecl(FunctionDecl *pFuncDecl);
    bool VisitCXXMethodDecl(CXXMethodDecl *D);
    bool VisitRecordDecl(RecordDecl *D);
    bool VisitVarDecl(VarDecl *pVarDecl);
    bool VisitReturnStmt(ReturnStmt *pRetStmt);
};

class MyASTConsumer : public ASTConsumer {
   private:
   public:
    virtual bool HandleTopLevelDecl(DeclGroupRef declGroupRef);
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