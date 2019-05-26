#ifndef __NAMELINT_MY_AST_CONSUMER__H__
#define __NAMELINT_MY_AST_CONSUMER__H__

#include "clang/AST/ASTConsumer.h"
#include "clang/AST/DeclGroup.h"
#include "clang/Basic/Diagnostic.h"
#include "clang/Frontend/ASTConsumers.h"

#include "clang/AST/ASTConsumer.h"
#include "clang/AST/ASTContext.h"
#include "clang/AST/Decl.h"
#include "clang/AST/DeclGroup.h"
#include "clang/Basic/Diagnostic.h"
#include "clang/Frontend/ASTConsumers.h"
#include <clang/Frontend/CompilerInstance.h>
#include <clang/Frontend/FrontendAction.h>

using namespace clang;

class MyASTConsumer : public clang::ASTConsumer
{
  private:
  public:
    bool HandleTopLevelDecl(DeclGroupRef declGroupRef);
    void HandleTranslationUnit(ASTContext& Ctx);
};

class MyIgnoringDiagConsumer : public clang::IgnoringDiagConsumer
{};

#endif // __NAMELINT_MY_AST_CONSUMER__H__