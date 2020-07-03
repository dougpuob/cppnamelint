#include <memory>

#include "clang/AST/ASTConsumer.h"

#include "MyFactory.h"

using namespace std;

unique_ptr<MyASTConsumer> MyFactory::newASTConsumer() { return std::make_unique<MyASTConsumer>(); }
