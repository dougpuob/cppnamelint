#ifndef __NAMELINT_COMMON__H__
#define __NAMELINT_COMMON__H__

#include "TraceMemo.h"
#include <string>

// static const bool bPreferUpperCamel = true;
// static const bool bIsPtr = true;
// static const bool bIsArray = true;
// static const bool bNotPtr = false;
// static const bool bNotArray = false;

static const bool PREFER_UPPER_CAMEL = true;
static const bool IS_PTR = true;
static const bool IS_ARRAY = true;
static const bool NOT_PTR = false;
static const bool NOT_ARRAY = false;

using namespace std;

typedef struct _APP_CONTEXT {
  void *pTomlConfig;
  namelint::MemoBoard MemoBoard;
  string FileName;
} APP_CONTEXT;

const APP_CONTEXT *GetAppCxt();

namespace Path {
bool IsExist(const string &FilePath);
const char *FindFileName(const string &FielPath);
bool NormPath(const char *szPath, string &NewPath);
} // namespace Path

namespace String {
void PadTo(string &s, size_t nCount, char cChar);
bool IsLower(const string &Str);
void Replace(string &Source, const string &Patn, const string &New);
void Trim(string &Str);
size_t Split(const std::string &txt, std::vector<std::string> &strs, char ch);
} // namespace String
#endif // __NAMELINT_COMMON__H__