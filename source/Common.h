#ifndef __NAMELINT_COMMON__H__
#define __NAMELINT_COMMON__H__

#include "TraceMemo.h"
#include <string>

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