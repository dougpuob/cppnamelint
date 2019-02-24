#ifndef __NAMELINT_COMMON__
#define __NAMELINT_COMMON__

#include <string>

using namespace std;

typedef struct _APP_CONTEXT
{
  void* pTomlConfig;
  string FileName;
  size_t nAsserted;
} APP_CONTEXT;

typedef struct _COMMAND_CHECK
{
  bool bEnabled;
} COMMAND_CHECK;

typedef struct _COMMAND_TEST
{
  bool bEnabled;
} COMMAND_TEST;

typedef struct _INPUT_COMMAND
{
  COMMAND_CHECK Check;
  COMMAND_TEST Test;
} INPUT_COMMAND;

const APP_CONTEXT*
GetAppCxt();

namespace FileSystem {
bool
IsExist(const string& FilePath);
const char*
FindFileNameInPath(const string& FielPath);
} // namespace FileSystem

namespace String {
void
PadTo(string& s, size_t nCount, char cChar);
bool
IsLower(const string& Str);
void
Replace(string& Source, const string& Patn, const string& New);
void
Trim(string& Str);
} // namespace String
#endif