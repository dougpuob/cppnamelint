#ifndef __NAMELINT_TRACE_MEMO__H__
#define __NAMELINT_TRACE_MEMO__H__
#include "clang/AST/Decl.h"

#include "Config.h"
#include <map>
#include <string>
#include <vector>

using namespace std;

namespace namelint {

class CodePos {
public:
  size_t nLine;
  size_t nColumn;
};

typedef enum _CheckType {
  CT_None = 0,
  CT_InvalidDecl,
  CT_File,
  CT_Function,
  CT_Parameter,
  CT_Variable,
  CT_EnumTag,
  CT_EnumVal,
  CT_UnionTag,
  CT_UnionVal,
  CT_StructTag,
  CT_StructVal,
  CT_Class,
  CT_Max
} CheckType;

class ErrorDetail {
public:
  bool bIsPtr;
  bool bIsArray;
  CodePos Pos;
  CheckType Type;
  string TargetName;
  string TypeName;
  string Suggestion;

  ErrorDetail(const string &FileName, const string &Suggestion) {
    this->Type       = CT_File;
    this->TargetName = FileName;
    this->Suggestion = Suggestion;
  }

  ErrorDetail(const CodePos &Pos, const CheckType &Type, const bool &bIsPtr, const bool &bIsArray,
              const string &TypeName, const string &Suggestion) {
    this->bIsPtr     = bIsPtr;
    this->bIsArray   = bIsArray;
    this->Pos        = Pos;
    this->Type       = Type;
    this->TargetName = TypeName;
    this->Suggestion = Suggestion;
  }

  ErrorDetail(const CodePos &Pos, const CheckType &Type, const bool &bIsPtr, const bool &bIsArray,
              const string &TypeName, const string &TargetName, const string &Suggestion) {
    this->bIsPtr     = bIsPtr;
    this->bIsArray   = bIsArray;
    this->Pos        = Pos;
    this->Type       = Type;
    this->TypeName   = TypeName;
    this->TargetName = TargetName;
    this->Suggestion = Suggestion;
  }
};

class MemoBoard {
public:
  struct _File {
    string Source;
    string Config;
  } File;

  struct _Dir {
    vector<string> Includes;
  } Dir;

  struct _Assert {
    size_t nInvalidDecl;
  } Assert;

  struct _Checked {
    size_t nFile;
    size_t nFunction;
    size_t nParameter;
    size_t nVariable;
    size_t nEnum;
    size_t nStruct;
    size_t nUnion;
    size_t nClass;
  } Checked;

  struct _Error {
    size_t nFile;
    size_t nFunction;
    size_t nParameter;
    size_t nVariable;
    size_t nEnum;
    size_t nStruct;
    size_t nUnion;
    size_t nClass;
  } Error;

  vector<ErrorDetail *> ErrorDetailList;
  namelint::Config Config;
  clang::EnumDecl *pLastEnumDecl;

  void Clear() {
    memset(&this->Checked, 0, sizeof(this->Checked));
    memset(&this->Error, 0, sizeof(this->Error));
    memset(&this->Assert, 0, sizeof(this->Assert));

    this->Dir.Includes.clear();
    this->ErrorDetailList.clear();
    this->pLastEnumDecl = NULL;
    this->Config.Clear();
  }
  MemoBoard() { Clear(); }
};

} // namespace namelint

#endif