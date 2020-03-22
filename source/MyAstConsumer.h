#ifndef __NAMELINT_MY_AST_CONSUMER__H__
#define __NAMELINT_MY_AST_CONSUMER__H__

#include "clang/AST/ASTConsumer.h"
#include "clang/Basic/Diagnostic.h"

using namespace clang;

class MyASTConsumer : public clang::ASTConsumer {
private:
public:
  bool HandleTopLevelDecl(DeclGroupRef declGroupRef);
  void HandleTranslationUnit(ASTContext &Ctx);
};

class MyIgnoringDiagConsumer : public clang::IgnoringDiagConsumer {};

#endif // __NAMELINT_MY_AST_CONSUMER__H__