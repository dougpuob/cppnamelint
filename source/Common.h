#ifndef __NAMELINT_COMMON__H__
#define __NAMELINT_COMMON__H__

#include "clang/Tooling/Tooling.h"

#include "TraceMemo.h"
#include <string>

using namespace std;
using namespace clang::tooling;
using namespace namelint;

static const bool PREFER_UC = true; // Prefer Upper Camel
static const bool IS_PTR    = true;
static const bool IS_ARRAY  = true;
static const bool NOT_PTR   = false;
static const bool NOT_ARRAY = false;

int RunCheckFormFile(namelint::MemoBoard &Memo);
int RunCheckFormStream(MemoBoard &Memo, const string &SourceContent,
                       const string &VirtFileName = "a.cc");
int RunCheckFormStream(MemoBoard &Memo, const vector<string> &SourceContentList,
                       const string &VirtFileName = "a.cc");

size_t GetTotalError(const MemoBoard &MemoBoard);
size_t GetTotalChecked(const MemoBoard &MemoBoard);

int RunCheck(namelint::MemoBoard &Memo, ClangTool &Tool);
int RunTest(const string &LogFileName, const string &FilterStr);

bool PrintTraceMemo(const MemoBoard &MemoBoard);
bool WriteJsonResult(const MemoBoard &MemoBoard, const string &FilePath);

void LogConfig();
void LogHead();
void LogCheckResult();

typedef struct _APP_CONTEXT {
  void *pTomlConfig;
  namelint::MemoBoard MemoBoard;
  string FileName;
} APP_CONTEXT;

static APP_CONTEXT *GetAppCxt() {
  static APP_CONTEXT m_AppCxt;
  return &m_AppCxt;
}

namespace String {
void Replace(string &Source, const string &Patn, const string &New);
void Trim(string &Str);
} // namespace String

#endif // __NAMELINT_COMMON__H__