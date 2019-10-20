#include "Logger.h"
#include "Common.h"
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <stdarg.h>

namespace DcLib {

// std::string Log::Format(const char *fmt, ...) {
//  int size = 512;
//  char *buffer = 0;
//
//  buffer = new char[size];
//  va_list vl;
//  va_start(vl, fmt);
//
//  int nsize = vsnprintf(buffer, size, fmt, vl);
//  if (size <= nsize) { // fail delete buffer and try again
//    delete[] buffer;
//    buffer = 0;
//    buffer = new char[nsize + 1]; //+1 for /0
//    nsize = vsnprintf(buffer, size, fmt, vl);
//  }
//  std::string ret(buffer);
//  va_end(vl);
//  delete[] buffer;
//  return ret;
//}

bool Log::Init(const char *szFileName) {
  DcLib::m_LogFileName.assign(szFileName);
  return true;
}

std::string Log::Fixed(size_t nValue, size_t nZeroCnt) {
  std::string value_str = std::to_string(nValue);
  size_t nAppendZeroCount = nZeroCnt - value_str.length();
  if (nAppendZeroCount < 0) {
    nAppendZeroCount = 0;
  }

  return std::string(nAppendZeroCount, '0').append(value_str);
}

size_t Log::Out(FlagInfo &FlagInfo, const char *szFmt, ...) {
  static std::fstream FileStream;

  if (DcLib::m_LogFileName.length() == 0) {
    DcLib::Log::Init("Default.log");
  }

  if (!FileStream.is_open()) {
    FileStream.open(DcLib::m_LogFileName, std::ios::app);
  }

  FileStream << std::endl;

  //
  // Date&Time
  //
  if (FlagInfo.bPrintDateTime) {
    time_t now = time(0);
    tm *ltm = localtime(&now);

    FileStream << "[" << Log::Fixed(1900 + ltm->tm_year, 4)
               << Log::Fixed(ltm->tm_mon, 2) << Log::Fixed(ltm->tm_mday, 2);
    FileStream << "-" + Log::Fixed(ltm->tm_hour, 2)
               << Log::Fixed(ltm->tm_min, 2) << Log::Fixed(ltm->tm_sec, 2)
               << "]";
  }

  //
  // Function Info
  //
  FileStream << "[";
  if (FlagInfo.bPrintFileName) {
    FileStream << Path::FindFileName(FlagInfo.FileName) << "!"
               << FlagInfo.FuncName;
  }
  if (FlagInfo.bPrintLineNumber) {
    FileStream << "@" << FlagInfo.LineNumber;
  }
  FileStream << "]";

  //
  // Text Message
  //
  FileStream << szFmt;

  return 0;
} // namespace DcLib

} // namespace DcLib
