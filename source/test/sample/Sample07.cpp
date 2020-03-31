#include "Sample07.h"
#include "Sample07a.h"

#define min2(X, Y) ((X) < (Y) ? (X) : (Y))
typedef void (*fnFunc)(short s, short);

MyClass::MyClass() {}

MyClass::~MyClass() {}

bool MyClass::MyPubFunc(int) {
  ITEM Item;
  ITEM *pItem;
  return true;
}

bool MyClass::MyPrivFunc(int Value) {
  Value = min2(Value, 10);
  return true;
}
