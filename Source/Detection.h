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
    bool _RemoveHeadingUnderscore(string& Text);
    bool _RemoveHeadingPtrChar(string& Text);
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
                                    const map<string, string>& MappedList,
                                    const map<string, string>& MappedListEx);
    size_t _FindHowManyChar(const string& InputStr, char cChar);
    bool _RemoveNamespacesAndElements(string& Text);
    bool _SkipIgnoreFunctions(const string& Name,
                              const vector<string>& IgnoreList);

  public:
    bool CheckFile(const RULETYPE Rule, const string& Name);
    bool CheckFunction(const RULETYPE Rule,
                       const string& Name,
                       const vector<string>& IgnoreNames,
                       const vector<string>& IgnorePrefixs,
                       const bool bAllowedEndWithUnderscopeChar = false);
    bool CheckVariable(const RULETYPE Rule,
                       const string& Type,
                       const string& Name,
                       const vector<string>& IgnorePrefixs,
                       const map<string, string>& MappedList,
                       const map<string, string>& MappedListEx);
};
} // namespace namelint

#endif