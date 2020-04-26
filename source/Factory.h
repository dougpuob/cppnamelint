#ifndef __NAMELINT_MY_FACTORY__H__
#define __NAMELINT_MY_FACTORY__H__

#include "AstConsumer.h"
#include <memory>

class MyFactory {
public:
  std::unique_ptr<MyASTConsumer> newASTConsumer();
};

#endif