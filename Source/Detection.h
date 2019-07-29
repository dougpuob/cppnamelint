#ifndef __NAMELINT_DETECTION__H__
#define __NAMELINT_DETECTION__H__

#include "Config.h"
#include <map>
#include <string>
#include <vector>

using namespace std;

namespace namelint {

struct RuleOfFunction {
    vector<string> IgnoreNames;
    vector<string> IgnorePrefixs;
    bool bAllowedEndWithUnderscopeChar;

    RuleOfFunction();
    void Reset();
};

struct RuleOfVariable {
    vector<string> IgnorePrefixs;
    map<string, string> TypeNamingMap;
    map<string, string> PtrNamingMap;
    map<string, string> ArrayNamingMap;

    RuleOfVariable();
    void Reset();
};

class Detection {
  private:
    RuleOfFunction m_RuleOfFunction;
    RuleOfVariable m_RuleOfVariable;

  private:
    bool _RemoveHeadingUnderscore(string &Text);
    bool _RemoveHeadingPtrChar(string &Text);
    bool _CaptureLowerCasePrefix(string &Name);
    bool _IsUpperCamelCaseString(const string &Name,
                                 vector<string> IgnorePrefixs,
                                 const bool bAllowedEndWithUnderscopeChar = false);

    bool _IsLowerCamelCaseString(const string &Name, vector<string> IgnorePrefixs);
    bool _IsLowerSeperatedString(const string &Name, vector<string> IgnorePrefixs);
    bool _IsHungarianNotationString(const string &TypeStr,
                                    const string &NameStr,
                                    const bool &bPreferUpperCamel,
                                    const bool &bIsPtr,
                                    const bool &bIsArray,
                                    const vector<string> &IgnorePrefixs,
                                    const map<string, string> &TypeNamingMap,
                                    const map<string, string> &PtrNamingMap,
                                    const map<string, string> &ArrayNamingMap);

    size_t _FindHowManyChar(const string &InputStr, char cChar);
    bool _RemoveNamespacesAndElements(string &Text);
    bool _SkipIgnoreFunctions(const string &Name, const vector<string> &IgnoreList);

  public:
    bool ApplyRuleForFunction(const RuleOfFunction &Rule);
    bool ApplyRuleForVariable(const RuleOfVariable &Rule);

    bool CheckFile(const RULETYPE Rule, const string &Name);
    bool CheckFunction(const RULETYPE Rule, const string &Name);
    bool CheckVariable(const RULETYPE Rule,
                       const string &Type,
                       const string &Name,
                       const bool &bPreferUpperCamel,
                       const bool &bIsPtr,
                       const bool &bIsArray);
};
} // namespace namelint

#endif