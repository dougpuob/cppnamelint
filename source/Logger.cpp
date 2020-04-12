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
static std::size_t m_nBufSize = 0;
static char *m_szBuf          = NULL;

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

    DcLib::m_nBufSize = iRetSize * 2;
    DcLib::m_szBuf    = (char *)malloc(DcLib::m_nBufSize);
  }

  iRetSize = vsnprintf(DcLib::m_szBuf, DcLib::m_nBufSize, szFmt, vaList);

  static std::string retStr;
  retStr.assign(DcLib::m_szBuf);

  return retStr;
}

bool Log::Init(const char *szFileName) {
  DcLib::m_LogFileName.assign(szFileName);
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

  //
  // Date&Time
  //
  if (FlagInfo.bPrintDateTime) {
    time_t now = time(0);
    tm *ltm    = localtime(&now);

    FileStream << "[" << Log::Fixed(1900 + ltm->tm_year, 4) << Log::Fixed(ltm->tm_mon, 2)
               << Log::Fixed(ltm->tm_mday, 2);
    FileStream << "'" + Log::Fixed(ltm->tm_hour, 2) << Log::Fixed(ltm->tm_min, 2)
               << Log::Fixed(ltm->tm_sec, 2) << "]";
  }

  //
  // Function Info
  //
  FileStream << "[";
  if (FlagInfo.bPrintFileName) {
    FileStream << Path::FindFileName(FlagInfo.FileName) << "!" << FlagInfo.FuncName;
  }
  if (FlagInfo.bPrintLineNumber) {
    FileStream << "@" << FlagInfo.LineNumber;
  }
  FileStream << "]\t";

  //
  // Text Message
  //
  va_list vl;
  va_start(vl, szFmt);
  std::string retStr = Log::Format(szFmt, vl);
  va_end(vl);
  FileStream << " " << retStr << std::endl;

  return 0;
}

} // namespace DcLib
