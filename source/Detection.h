#ifndef __NAMELINT_DETECTION__H__
#define __NAMELINT_DETECTION__H__

#include "Config.h"
#include <map>
#include <string>
#include <vector>

using namespace std;

namespace namelint {

struct RuleOfFile {
  bool bAllowedUnderscopeChar;

  RuleOfFile();
  void Reset();
};

struct RuleOfFunction {
  vector<string> IgnoreNames;
  vector<string> IgnorePrefixs;
  bool bAllowedUnderscopeChar;

  RuleOfFunction();
  void Reset();
};

struct RuleOfVariable {
  vector<string> IgnorePrefixs;
  map<string, string> WordListMap;
  vector<MappingPair> NullStringMap;
  map<string, string> ArrayNamingMap;

  bool bAllowedUnderscopeChar;

  RuleOfVariable();
  void Reset();
};

struct RuleOfStruct {
  vector<string> IgnorePrefixs;

  RuleOfStruct();
  void Reset();
};

struct RuleOfEnum {
  vector<string> IgnorePrefixs;

  RuleOfEnum();
  void Reset();
};

class Detection {
private:
  RuleOfFile m_RuleOfFile;
  RuleOfVariable m_RuleOfVariable;
  RuleOfEnum m_RuleOfEnum;
  RuleOfStruct m_RuleOfStruct;

private:
  int _FindContinuedUnderscope(const string &Name);
  int _FindLower(const string &Name);
  int _FindUpper(const string &Name);

  bool _RemoveHeadingUnderscore(string &Text);
  size_t _RemoveHeadingPtrChar(string &Text);
  bool _CaptureLowerCasePrefix(string &Name);
  bool _IsUpperCamelCaseString(const string &Name, vector<string> IgnorePrefixs,
                               const bool AllowedUnderscopeChar = false);

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
  bool ApplyRuleForVariable(const RuleOfVariable &Rule);
  bool ApplyRuleForEnum(const RuleOfEnum &Rule);

  bool CheckFile(const RULETYPE Rule, const string &Name);
  bool CheckFunction(const RULETYPE Rule, const string &Name);
  bool CheckVariable(const RULETYPE Rule, const string &Type, const string &Name,
                     const bool &bPreferUpperCamel, const bool &bIsPtr, const bool &bIsArray);
  bool CheckEnumVal(const RULETYPE Rule, const string &Name);
  bool CheckStructVal(const RULETYPE Rule, const string &Type, const string &Name, bool bIsPtr);
};
} // namespace namelint

#endif