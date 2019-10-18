#include <memory>

#include "MyFactory.h"
#include "clang/AST/ASTConsumer.h"

using namespace std;

unique_ptr<MyASTConsumer> MyFactory::newASTConsumer() {
  return llvm::make_unique<MyASTConsumer>();
}
