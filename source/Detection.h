#ifndef __NAMELINT_DETECTION__H__
#define __NAMELINT_DETECTION__H__

#include "Config.h"
#include <map>
#include <string>
#include <vector>

using namespace std;

namespace namelint {

class Detection {
private:
private:
  int _FindContinuedUnderscope(const string &Name);
  int _FindLower(const string &Name);
  int _FindUpper(const string &Name);

  bool _RemoveHeadingUnderscore(string &Text);
  size_t _RemoveHeadingPtrChar(string &Text);
  bool _CaptureLowerCasePrefix(string &Name);
  int _RemoveIgnoredPrefixs(string &Name, vector<string> IgnorePrefixs);
  bool _IsUpperCamelCaseString(const string &Name, vector<string> IgnorePrefixs,
                               const AllowUnderscope AllowedUnderscope = DoNotAllow);

  bool _IsLowerCamelCaseString(const string &Name, vector<string> IgnorePrefixs);
  bool _IsSnakeString(const string &Name, SNAKETYPE SnakeType, vector<string> IgnorePrefixs);
  bool _IsHungarianNotationString(const string &TypeStr, const string &NameStr,
                                  const bool &bPreferUpperCamel, const bool &bIsPtr,
                                  const bool &bIsArray, const vector<string> &IgnorePrefixs,
                                  const map<string, string> &TypeNamingMap,
                                  const vector<MappingPair> &NullStringMap,
                                  const map<string, string> &ArrayNamingMap);

  size_t _FindHowManyChar(const string &InputStr, char cChar);
  bool _RemoveNamespacesAndElements(string &Text);
  bool _SkipIgnoreFunctions(const string &Name, const vector<string> &IgnoreList);

public:
    bool CheckClass(const RULETYPE Rule, const string& Name, bool IsAbstract);
  bool CheckFile(const RULETYPE Rule, const string &Name);
  bool CheckFunction(const RULETYPE Rule, const string &Name);
  bool CheckVariable(const RULETYPE Rule, const string &Type, const string &Name,
                     const bool &bPreferUpperCamel, const bool &bIsPtr, const bool &bIsArray);
  bool CheckEnumVal(const RULETYPE Rule, const string &Name);
  bool CheckStructVal(const RULETYPE Rule, const string &Type, const string &Name, bool bIsPtr);
};
} // namespace namelint

#endif