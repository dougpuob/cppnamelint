#ifndef __NAMELINT_TRACE_MEMO__H__
#define __NAMELINT_TRACE_MEMO__H__

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

typedef enum _CheckType { CT_None, CT_Function = 1, CT_Parameter = 2, CT_Variable = 3, CT_Max } CheckType;

class ErrorDetail {
  public:
    bool bIsPtr;
    bool bIsArray;
    CodePos Pos;
    CheckType Type;
    string TargetName;
    string TypeName;
    string Suggestion;

    ErrorDetail(const CodePos &Pos,
                const CheckType &Type,
                const bool &bIsPtr,
                const bool &bIsArray,
                const string &TypeName,
                const string &Suggestion) {
        this->bIsPtr     = bIsPtr;
        this->bIsArray   = bIsArray;
        this->Pos        = Pos;
        this->Type       = Type;
        this->TargetName = TypeName;
        this->Suggestion = Suggestion;
    }

    ErrorDetail(const CodePos &Pos,
                const CheckType &Type,
                const bool &bIsPtr,
                const bool &bIsArray,
                const string &TypeName,
                const string &TargetName,
                const string &Suggestion) {
        this->bIsPtr     = bIsPtr;
        this->bIsArray   = bIsArray;
        this->Pos        = Pos;
        this->Type       = Type;
        this->TypeName   = TypeName;
        this->TargetName = TargetName;
        this->Suggestion = Suggestion;
    }
};

class TraceMemo {
  public:
    struct _File {
        string Source;
        string Config;
    } File;

    struct _Dir {
        vector<string> Includes;
    } Dir;

    struct _Checked {
        size_t nFunction;
        size_t nParameter;
        size_t nVariable;
    } Checked;

    struct _Error {
        size_t nFunction;
        size_t nParameter;
        size_t nVariable;
    } Error;

    vector<ErrorDetail *> ErrorDetailList;
};

} // namespace namelint

#endif