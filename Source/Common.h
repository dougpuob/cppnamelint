#ifndef __NAMELINT_COMMON__
#define __NAMELINT_COMMON__

#include <string>

using namespace std;

typedef struct _APP_CONTEXT {
    void *pTomlConfig;
} APP_CONTEXT;

typedef struct _COMMAND_CHECK {
    bool bEnabled;
} COMMAND_CHECK;

typedef struct _COMMAND_TEST {
    bool bEnabled;
} COMMAND_TEST;

typedef struct _INPUT_COMMAND {
    COMMAND_CHECK Check;
    COMMAND_TEST Test;
} INPUT_COMMAND;

const APP_CONTEXT *GetAppCxt();

namespace FileSystem {
bool IsFileExist(const string &FilePath);
const char *FindFileNameInPath(const string &FielPath);
}  // namespace FileSystem

namespace MyString {
void PadTo(string &s, size_t nCount, char cChar);
bool IsLower(const string &Str);
void Replace(string &strBig, const string &strsrc, const string &strdst);
void Trim(string &Str);
}  // namespace MyString
#endif