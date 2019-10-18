#ifndef __LEARN_IT_H__
#define __LEARN_IT_H__

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

#include <plog/Log.h>

using namespace std;
using namespace clang;
using namespace clang::tooling;
using namespace llvm;
using namespace clang::driver;
using namespace clang::tooling;

class LearnIt {
public:
  LearnIt();
  bool LearnRecordDecl(RecordDecl &Decl);
  bool LearnFunctionDecl(FunctionDecl &Decl);
};

#endif // __LEARN_IT_H__
