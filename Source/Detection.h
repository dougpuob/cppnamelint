#ifndef __NAMELINT_DETECTION__H__
#define __NAMELINT_DETECTION__H__

#include "Config.h"
#include <map>
#include <string>
#include <vector>

using namespace std;

namespace namelint {
class Detection
{
private:
  bool _CaptureLowerCasePrefix(string& Name);
  bool _IsUpperCamelCaseString(
    const string& Name,
    vector<string> IgnorePrefixs,
    const bool bAllowedEndWithUnderscopeChar = false);

  bool _IsLowerCamelCaseString(const string& Name,
                               vector<string> IgnorePrefixs);
  bool _IsLowerSeperatedString(const string& Name,
                               vector<string> IgnorePrefixs);
  bool _IsHungarianNotationString(const string& Type,
                                  const string& Name,
                                  const vector<string>& IgnorePrefixs,
                                  const map<string, string>& MappedList);
  size_t _FindHowManyChar(const string& InputStr, char cChar);
  bool _SkipIgnoreFunctions(const string& Name,
                            const vector<string>& IgnoreList);

public:
  bool CheckFile(const RULETYPE Rule, const string& Name);
  bool CheckFunction(const RULETYPE Rule,
                     const string& Name,
                     const vector<string>& IgnorePrefixs,
                     const bool bAllowedEndWithUnderscopeChar = false);
  bool CheckVariable(const RULETYPE Rule,
                     const string& Type,
                     const string& Name,
                     const vector<string>& IgnorePrefixs,
                     const map<string, string>& MappedList);
};
} // namespace namelint

#endif