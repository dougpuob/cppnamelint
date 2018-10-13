#include <iostream>
#include <vector>


#include "llvm/Support/CommandLine.h"

#include "clang/AST/ASTConsumer.h"
#include "clang/AST/ASTContext.h"
#include "clang/Parse/Parser.h"
#include "clang/Tooling/CommonOptionsParser.h"
#include "clang/Tooling/Tooling.h"
#include "clang/AST/RecursiveASTVisitor.h"
#include "clang/AST/Decl.h"
#include "clang/AST/AST.h"
#include "clang/AST/DeclVisitor.h"
#include "clang/Frontend/ASTConsumers.h"
#include "clang/Frontend/FrontendActions.h"
#include "clang/Frontend/CompilerInstance.h"
#include "clang/Lex/Preprocessor.h"

using namespace std;
using namespace clang;
using namespace clang::tooling;
using namespace llvm;
using namespace clang::driver;
using namespace clang::tooling;




class MyASTVisitor : public RecursiveASTVisitor<MyASTVisitor> {
private:
    const SourceManager *m_pSM;    
    ASTContext          *m_pAstCxt;

    const char *LastLocFilename = "";
    unsigned LastLocLine = ~0U;

    //void dumpLocation(SourceLocation Loc);
    //void dumpSourceRange(SourceRange R);
    //void dumpAttr(Decl *D);
    bool dumpPosition(Decl* pDecl);
    void keepFileName(string& FilePath);

public:
    MyASTVisitor(const SourceManager *pSM);

    //bool VisitCXXConstructorDecl(CXXConstructorDecl *D);
    bool VisitStmt(Stmt* pStmt);
    bool VisitFunctionDecl(FunctionDecl* pFuncDecl);
    bool VisitCXXMethodDecl(CXXMethodDecl *D);
    bool VisitRecordDecl(RecordDecl *D);
    bool VisitVarDecl(VarDecl *pVarDecl);
    bool VisitReturnStmt(ReturnStmt *pRetStmt);

    //bool VisitCXXRecordDecl(CXXRecordDecl *D);
};

class MyASTConsumer : public ASTConsumer {
private:
public:    
    virtual bool HandleTopLevelDecl(DeclGroupRef declGroupRef);
    void MyASTConsumer::HandleTranslationUnit(ASTContext & 	Ctx);

};

class MyFactory {
public:
    std::unique_ptr<MyASTConsumer> newASTConsumer();
};


class MyIgnoringDiagConsumer : public IgnoringDiagConsumer
{
public:
    //virtual void HandleDiagnostic(DiagnosticsEngine::Level DiagLevel, const Diagnostic &Info);
};

