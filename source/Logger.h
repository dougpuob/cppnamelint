#ifndef __LOGGER_H__
#define __LOGGER_H__

#include <fstream>
#include <memory>
#include <string>
#include <vector>

namespace DcLib {
typedef enum _Type {
  TypeNone = 0,
  TypeInfo = 1 << 1,
  TypeWarn = 1 << 2,
  TypeErr  = 1 << 3,

  TypeAll = 0xFFFFFFFF
} Type;

typedef enum _Flag {
  FlagNone       = 0,
  FlagLineNumber = 1 << 1,
  FlagFileName   = 1 << 2,
  FlagDateTime   = 1 << 3,

  LOG_FLAG_ALL = 0xFFFFFFFF
} Flag;

class FlagInfo {
public:
  FlagInfo(std::string FileName, std::string FuncName, size_t LineNumber, bool bPrintDateTime,
           bool bPrintFileName, bool bPrintLineNumber)
      : FileName{FileName}, FuncName{FuncName}, LineNumber{LineNumber},
        bPrintDateTime{bPrintDateTime}, bPrintFileName{bPrintFileName}, bPrintLineNumber{
                                                                            bPrintLineNumber} {}

  std::string FileName;
  std::string FuncName;
  size_t LineNumber;

  bool bPrintDateTime;
  bool bPrintFileName;
  bool bPrintLineNumber;
};

#define INFO_ALL DcLib::FlagInfo(__FILE__, __func__, __LINE__, true, true, true)
#define INFO_NOTIME DcLib::FlagInfo(__FILE__, __func__, __LINE__, false, true, true)

static std::string m_LogFileName;
static std::size_t m_nBufSize = 0;
static char *m_szBuf          = NULL;

class Log {
private:
  Log() {}

public:
  static std::string Fixed(size_t nValue, size_t nZeroCnt);
  static bool Init(const char *szFileName);
  static size_t Out(const FlagInfo &FlagInfo, const char *szFmt, ...);
  static std::string Format(const char *fmt, va_list vaList);
};
} // namespace DcLib

#endif // __LOGGER_H__
