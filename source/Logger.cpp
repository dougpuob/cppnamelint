#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

#include "Common.h"
#include "Logger.h"

namespace DcLib {

static std::string m_LogFileName;
static std::size_t m_nContentStartsPos = 55;
static std::size_t m_nBufSize          = 0;
static char *m_szBuf                   = NULL;

std::string Log::Format(const char *szFmt, va_list vaList) {
  if (!DcLib::m_szBuf) {
    DcLib::m_nBufSize = 256;
    DcLib::m_szBuf    = (char *)malloc(DcLib::m_nBufSize);
    memset(DcLib::m_szBuf, 0, DcLib::m_nBufSize);
  }

  int iRetSize = vsnprintf(DcLib::m_szBuf, DcLib::m_nBufSize, szFmt, vaList);
  if ((iRetSize > 0) && ((size_t)iRetSize > DcLib::m_nBufSize)) {
    free(DcLib::m_szBuf);
    DcLib::m_szBuf = NULL;

    DcLib::m_nBufSize = (size_t)iRetSize * 2;
    DcLib::m_szBuf    = (char *)malloc(DcLib::m_nBufSize);
  }

  iRetSize = vsnprintf(DcLib::m_szBuf, DcLib::m_nBufSize, szFmt, vaList);

  static std::string retStr;
  retStr.assign(DcLib::m_szBuf);

  return retStr;
}

bool Log::Init(const char *szFileName, const size_t nContentStartsPos) {
  DcLib::m_LogFileName.assign(szFileName);
  DcLib::m_nContentStartsPos = nContentStartsPos;
  return true;
}

std::string Log::Fixed(size_t nValue, size_t nZeroCnt) {
  std::string value_str   = std::to_string(nValue);
  size_t nAppendZeroCount = nZeroCnt - value_str.length();
  if (nAppendZeroCount < 0) {
    nAppendZeroCount = 0;
  }

  return std::string(nAppendZeroCount, '0').append(value_str);
}

size_t Log::Out(const FlagInfo &FlagInfo, const char *szFmt, ...) {
  static std::fstream FileStream;

  if (DcLib::m_LogFileName.length() == 0) {
    return 0;
  }

  if (!FileStream.is_open()) {
    FileStream.open(DcLib::m_LogFileName, std::ios::app);
  }

  char szBuf[512] = {0};
  string PaddingInfo;

  //
  // Date&Time
  //
  if (FlagInfo.bPrintDateTime) {
    time_t now = time(0);
    tm *ltm    = localtime(&now);

    PaddingInfo = "[" + Log::Fixed(ltm->tm_hour, 2) + Log::Fixed(ltm->tm_min, 2) +
                  Log::Fixed(ltm->tm_sec, 2) + "]";
  }

  //
  // Function Info
  //
  PaddingInfo.append("[");
  if (FlagInfo.bPrintFileName) {
    PaddingInfo.append(Path::FindFileName(FlagInfo.FileName) + string("!") + FlagInfo.FuncName);
  }
  if (FlagInfo.bPrintLineNumber) {
    PaddingInfo.append(string("@") + std::to_string(FlagInfo.LineNumber));
  }
  PaddingInfo.append("] ");

  //
  // Text Message
  //
  va_list vl;
  va_start(vl, szFmt);
  std::string Content = Log::Format(szFmt, vl);
  va_end(vl);

  int iDiff = DcLib::m_nContentStartsPos - PaddingInfo.length();
  if (iDiff > 0) {
    PaddingInfo.append(iDiff, ' ');
  }

  FileStream << PaddingInfo << Content << std::endl;

  return 0;
}

} // namespace DcLib
