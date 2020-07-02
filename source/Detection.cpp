#include <algorithm>
#include <iostream>
#include <iterator>
#include <regex>
#include <string>
#include <vector>

#include "Common.h"
#include "Detection.h"

//==---------------------------------------------------------------------------
// Private Functions
//==---------------------------------------------------------------------------
namespace namelint {

bool Detection::_RemoveHeadingUnderscore(string &Text) {
  bool bStatus = false;

  std::smatch Match;
  std::string Result;

  std::regex Regex("^_{1,}");

  if (std::regex_search(Text, Match, Regex) && Match.size() >= 1) {
    bStatus = true;
    Text    = Text.substr(Match.size(), Text.length() - Match.size());
  }

  return bStatus;
}

size_t Detection::_RemoveHeadingPtrChar(string &Text) {
  size_t nIdx  = 0;
  char *szText = (char *)Text.c_str();
  for (nIdx = 0; nIdx < Text.length(); nIdx++) {
    if ('p' != *szText) {
      break;
    }
    szText++;
  }

  if (nIdx > 0) {
    Text = Text.substr(nIdx, Text.length() - nIdx);
  }

  return nIdx;
}

int Detection::_RemoveIgnoredPrefixs(string &Name, vector<string> IgnorePrefixs) {
  int iRet = -1;
  for (string Prefix : IgnorePrefixs) {
    iRet++;
    if (0 == Name.find(Prefix)) {
      const size_t nPrefixLen = Prefix.length();

      Name = Name.substr(nPrefixLen, Name.length() - nPrefixLen);
      return iRet;
    }
  }
  return iRet;
}

bool Detection::_CaptureLowerCasePrefix(string &Name) {
  bool bStatus = false;

  std::smatch Match;
  std::string Result;

  const string NewRegexPatn = "^[a-z0-9]+";
  std::regex Regex(NewRegexPatn);

  if (std::regex_search(Name, Match, Regex) && Match.size() >= 1) {
    bStatus = true;
    Name    = Match[0];
  }

  return bStatus;
}

bool Detection::_IsUpperCamelCaseString(const string &Name, vector<string> IgnorePrefixs,
                                        const AllowUnderscope AllowedUnderscope) {
  vector<string> NewIgnorePrefixs = IgnorePrefixs;
  auto wayToSort = [](string strA, string strB) { return strA.length() > strB.length(); };
  std::sort(NewIgnorePrefixs.begin(), NewIgnorePrefixs.end(), wayToSort);

  string NewName = Name;
  int iFound     = _RemoveIgnoredPrefixs(NewName, NewIgnorePrefixs);

  bool bStatus = false;
  switch (AllowedUnderscope) {
  case DoNotAllow: {
    if (string::npos == NewName.find("_")) {
      bStatus = true;
      String::Replace(NewName, "_", "");
    }
    break;
  }
  case AllowedOneUnderscope: {
    size_t count = std::count_if(NewName.begin(), NewName.end(), [](char c) { return (c == '_'); });
    if (count <= 1) {
      bStatus = true;
      String::Replace(NewName, "_", "");
    }
    break;
  }
  case AllowedSingleUnderscope: {
    if (string::npos == NewName.find("__")) {
      bStatus = true;
      String::Replace(NewName, "_", "");
    }
  }
  }

  if (bStatus) {
    // Find contine two upper chars.
    regex Regex("[A-Z]{2}|^[a-z]");
    bStatus = !regex_search(NewName, Regex);
  }

  return bStatus;
}

bool Detection::_IsLowerCamelCaseString(const string &Name, vector<string> IgnorePrefixs) {
  bool bStatus                    = false;
  vector<string> NewIgnorePrefixs = IgnorePrefixs;
  NewIgnorePrefixs.push_back("");

  for (string Prefix : NewIgnorePrefixs) {
    // const string NewRegexPatn = "^" + Prefix + "[a-z_]";
    const string NewRegexPatn = "^" + Prefix + "[a-z]";
    std::regex Regex(NewRegexPatn);
    std::smatch Match;
    std::string Result;
    if (std::regex_search(Name, Match, Regex) && Match.size() >= 1) {
      bStatus = true;
      break;
    }
  }

  return bStatus;
}

int Detection::_FindUpper(const string &Name) {
  char *szNext = (char *)Name.c_str();
  for (size_t nIdx = 0; nIdx < Name.length(); nIdx++) {
    if (isupper(Name[nIdx])) {
      return nIdx;
    }
  }
  return -1;
}

int Detection::_FindContinuedUnderscope(const string &Name) {
  size_t nRet = Name.find("__");
  if (string::npos == nRet) {
    return -1;
  }
  return nRet;
}

int Detection::_FindLower(const string &Name) {
  char *szNext = (char *)Name.c_str();
  for (size_t nIdx = 0; nIdx < Name.length(); nIdx++) {
    if (islower(Name[nIdx])) {
      return nIdx;
    }
  }
  return -1;
}

bool Detection::_IsSnakeString(const string &Name, SNAKETYPE SnakeType,
                               vector<string> IgnorePrefixs) {
  vector<string> NewIgnorePrefixs = IgnorePrefixs;

  auto wayToSort = [](string strA, string strB) { return strA.length() > strB.length(); };
  std::sort(NewIgnorePrefixs.begin(), NewIgnorePrefixs.end(), wayToSort);

  string NewName = Name;
  for (string Prefix : NewIgnorePrefixs) {
    if (0 == NewName.find(Prefix)) {
      const size_t nPrefixLen = Prefix.length();

      NewName = NewName.substr(nPrefixLen, NewName.length() - nPrefixLen);
      break;
    }
  }

  std::smatch Match;
  std::string Result;
  string NewRegexPatn;
  bool bStatus = (_FindContinuedUnderscope(NewName) < 0);

  if (bStatus) {
    switch (SnakeType) {
    case SNAKETYPE_LOWER:
      bStatus = (-1 == _FindUpper(NewName));
      if (bStatus) {
        NewRegexPatn = "\\b[a-z0-9_]+";
      }
      break;
    case SNAKETYPE_UPPER:
      bStatus = (-1 == _FindLower(NewName));
      if (bStatus) {
        NewRegexPatn = "\\b[A-Z0-9_]+";
      }
      break;
    }

    if (bStatus) {
      std::regex Regex(NewRegexPatn);
      if (std::regex_search(NewName, Match, Regex) && Match.size() >= 1) {
        bStatus = true;
      }
    }
  }

  return bStatus;
}

bool Detection::_IsHungarianNotationString(const string &TypeStr, const string &NameStr,
                                           const bool &bPreferUpperCamel, const bool &bIsPtr,
                                           const bool &bIsArray,
                                           const vector<string> &IgnorePrefixs,
                                           const map<string, string> &TypeNamingMap,
                                           const vector<MappingPair> &NullStringMap,
                                           const map<string, string> &ArrayNamingMap) {
  string NewNameStr = NameStr;
  string NewTypeStr = TypeStr;
  this->_RemoveNamespacesAndElements(NewTypeStr);

  //
  // Remove prefix string
  //
  for (vector<string>::const_iterator Iter = IgnorePrefixs.begin(); Iter != IgnorePrefixs.end();
       Iter++) {
    const size_t nPos = NewNameStr.find(*Iter);
    if (0 == nPos) {
      const size_t nStrLen = Iter->length();

      NewNameStr = NewNameStr.substr(nStrLen, NewNameStr.length() - nStrLen);
      break;
    }
  }

  //
  // Remove pointer chars.
  // Remove hungarian prefix chars.
  //
  bool bStatus          = true;
  bool bCNullStrMatched = false;
  if (bIsPtr || bIsArray) {

    // Remove `p` chars.
    size_t nLowerPCount = this->_RemoveHeadingPtrChar(NewNameStr);

    // Remove hungarian notion of C null string.
    for (auto Iter : NullStringMap) {
      const auto IterType   = Iter.Key;
      const auto IterPrefix = Iter.Value;
      string IterTypeNoStar = IterType;
      if (IterTypeNoStar == NewTypeStr) {
        const size_t nNewStrPos = NewNameStr.find(IterPrefix);
        if (0 == nNewStrPos) {
          const size_t nPrefixLen = IterPrefix.length();

          bCNullStrMatched = true;
          NewNameStr       = NewNameStr.substr(nPrefixLen, NewNameStr.length() - nPrefixLen);
          break;
        }
      }
    }
  }

  // Match Hungarian notation. (except C Null string)
  if (bStatus && !bCNullStrMatched) {
    for (map<string, string>::const_iterator Iter = TypeNamingMap.begin();
         Iter != TypeNamingMap.end(); Iter++) {

      const auto IterType   = Iter->first;
      const auto IterPrefix = Iter->second;

      if (IterType == NewTypeStr) {
        const size_t nNewStrPos = NewNameStr.find(IterPrefix);
        bStatus                 = (0 == nNewStrPos);
        if (bStatus) {
          const size_t nPrefixLen = IterPrefix.length();

          // Remove hungarian notation.
          NewNameStr = NewNameStr.substr(nPrefixLen, NewNameStr.length() - nPrefixLen);
        }

        break;
      }
    }
  }

  if (bStatus && bPreferUpperCamel) {
    bStatus = this->_IsUpperCamelCaseString(NewNameStr, IgnorePrefixs);
  }

  return bStatus;
}

size_t Detection::_FindHowManyChar(const string &InputStr, char cChar) {
  size_t nCount = 0;
  for (string::const_iterator Iter = InputStr.begin(); Iter != InputStr.end(); Iter++) {
    if (*Iter == cChar) {
      nCount++;
    }
  }
  return nCount;
}

bool Detection::_RemoveNamespacesAndElements(string &Text) {
  bool bStatus = false;
  std::smatch Match;
  std::string Result;

  // Remove elements
  std::regex Regex("<[a-zA-Z0-9\\*\\:]*>");
  if (std::regex_search(Text, Match, Regex) && Match.size() >= 1) {
    bStatus = true;
    String::Replace(Text, Match[0], "");
  }

  // Remove namespaces
  std::size_t nFound = Text.find_last_of("::");
  if (nFound < std::numeric_limits<size_t>::max()) {
    bStatus = true;
    Text    = Text.substr(nFound + 1, Text.length() - nFound - 1);
  }

  return bStatus;
}

bool Detection::_SkipIgnoreFunctions(const string &Name, const vector<string> &IgnoreList) {
  for (vector<string>::const_iterator Iter = IgnoreList.begin(); Iter != IgnoreList.end(); Iter++) {
    if (Name == *Iter) {
      return true;
    }
  }
  return false;
}

} // namespace namelint

//==---------------------------------------------------------------------------
// Public Functions
//==---------------------------------------------------------------------------
namespace namelint {

bool Detection::CheckFile(const RULETYPE Rule, const string &Name) {
  bool bStatus = false;
  if (Name.length() == 0) {
    return false;
  }

  shared_ptr<ConfigData> pCfgData = AppCxt::getInstance().MemoBoard.Config.GetData();

  string NewName   = Name;
  size_t nFoundPos = NewName.find_last_of(".");
  if (-1 != nFoundPos) {
    NewName = NewName.substr(0, nFoundPos);
  }

  vector<string> NullIgnorePrefixs;
  switch (Rule) {
  case RULETYPE_DEFAULT:
  case RULETYPE_UPPER_CAMEL: {
    bStatus = this->_IsUpperCamelCaseString(NewName, NullIgnorePrefixs,
                                            pCfgData->Camels.Options.AllowUnderscope);
    break;
  }
  case RULETYPE_LOWER_CAMEL: {
    bStatus = this->_IsLowerCamelCaseString(NewName, NullIgnorePrefixs);
    break;
  }
  case RULETYPE_LOWER_SNAKE: {
    bStatus = this->_IsSnakeString(NewName, SNAKETYPE_LOWER, NullIgnorePrefixs);
    break;
  }
  }
  return bStatus;
}

bool Detection::CheckFunction(const RULETYPE Rule, const string &Name) {
  if (Name.length() == 0) {
    return false;
  }

  shared_ptr<ConfigData> pCfgData = AppCxt::getInstance().MemoBoard.Config.GetData();
  vector<string> &IgnorePrefixs   = pCfgData->General.IgnoredList.FunctionPrefix;
  vector<string> &IgnoreNames     = pCfgData->General.IgnoredList.FunctionName;

  if (IgnorePrefixs.size() > 0) {
    bool bResult = this->_SkipIgnoreFunctions(Name, IgnoreNames);
    if (bResult) {
      return true;
    }
  }

  bool bStatus = false;
  switch (Rule) {
  case RULETYPE_DEFAULT:
  case RULETYPE_UPPER_CAMEL: {
    bStatus = this->_IsUpperCamelCaseString(Name, IgnorePrefixs,
                                            pCfgData->Camels.Options.AllowUnderscope);
    break;
  }
  case RULETYPE_LOWER_CAMEL: {
    bStatus = this->_IsLowerCamelCaseString(Name, IgnorePrefixs);
    break;
  }
  case RULETYPE_UPPER_SNAKE: {
    bStatus = this->_IsSnakeString(Name, SNAKETYPE_UPPER, IgnorePrefixs);
    break;
  }
  case RULETYPE_LOWER_SNAKE: {
    bStatus = this->_IsSnakeString(Name, SNAKETYPE_LOWER, IgnorePrefixs);
    break;
  }
  }
  return bStatus;
}

bool Detection::CheckVariable(const RULETYPE Rule, const string &Type, const string &Name,
                              const bool &bPreferUpperCamel, const bool &bIsPtr,
                              const bool &bIsArray) {
  if (Name.length() == 0) {
    return false;
  }

  shared_ptr<ConfigData> pCfgData = AppCxt::getInstance().MemoBoard.Config.GetData();
  vector<string> &IgnorePrefixs   = pCfgData->General.IgnoredList.VariablePrefix;

  bool bStatus = false;
  switch (Rule) {
  case RULETYPE_DEFAULT:
  case RULETYPE_UPPER_CAMEL: {
    bStatus = this->_IsUpperCamelCaseString(Name, IgnorePrefixs,
                                            pCfgData->Camels.Options.AllowUnderscope);
    break;
  }
  case RULETYPE_LOWER_CAMEL: {
    bStatus = this->_IsLowerCamelCaseString(Name, IgnorePrefixs);
    break;
  }
  case RULETYPE_UPPER_SNAKE: {
    bStatus = this->_IsSnakeString(Name, SNAKETYPE_UPPER, IgnorePrefixs);
    break;
  }
  case RULETYPE_LOWER_SNAKE: {
    bStatus = this->_IsSnakeString(Name, SNAKETYPE_LOWER, IgnorePrefixs);
    break;
  }
  case RULETYPE_HUNGARIAN: {
    const auto &WordListMap    = pCfgData->Hungarian.WordList;
    const auto &NullStringMap  = pCfgData->Hungarian.NullStringList;
    const auto &ArrayNamingMap = pCfgData->Hungarian.ArrayList;

    bStatus =
        this->_IsHungarianNotationString(Type, Name, bPreferUpperCamel, bIsPtr, bIsArray,
                                         IgnorePrefixs, WordListMap, NullStringMap, ArrayNamingMap);
    break;
  }
  }
  return bStatus;
}

bool Detection::CheckEnumVal(const RULETYPE Rule, const string &Name) {
  if (Name.length() == 0) {
    return false;
  }

  shared_ptr<ConfigData> pCfgData = AppCxt::getInstance().MemoBoard.Config.GetData();
  vector<string> &IgnorePrefixs   = pCfgData->General.IgnoredList.EnumTagPrefix;

  bool bStatus = false;
  switch (Rule) {
  case RULETYPE_DEFAULT:
  case RULETYPE_UPPER_CAMEL:
    bStatus = this->_IsUpperCamelCaseString(Name, IgnorePrefixs,
                                            pCfgData->Camels.Options.AllowUnderscope);
    break;

  case RULETYPE_LOWER_CAMEL:
    bStatus = this->_IsLowerCamelCaseString(Name, IgnorePrefixs);
    break;

  case RULETYPE_LOWER_SNAKE:
    bStatus = this->_IsSnakeString(Name, SNAKETYPE_LOWER, IgnorePrefixs);
    break;

  case RULETYPE_UPPER_SNAKE:
    bStatus = this->_IsSnakeString(Name, SNAKETYPE_UPPER, IgnorePrefixs);
    break;

  case RULETYPE_HUNGARIAN:
    bStatus = false; // Don't allow.
    break;
  }
  return bStatus;
}

bool Detection::CheckStructVal(const RULETYPE Rule, const string &Type, const string &Name,
                               bool bIsPtr) {
  if (Name.length() == 0) {
    return false;
  }

  shared_ptr<ConfigData> pCfgData = AppCxt::getInstance().MemoBoard.Config.GetData();
  vector<string> &IgnorePrefixs   = pCfgData->General.IgnoredList.StructTagPrefix;

  bool bStatus = false;
  switch (Rule) {
  case RULETYPE_HUNGARIAN: {
    const bool bPreferUpperCamelIfMissed = pCfgData->Hungarian.Options.PreferUpperCamelIfMissed;
    const auto &WordListMap              = pCfgData->Hungarian.WordList;
    const auto &NullStringMap            = pCfgData->Hungarian.NullStringList;
    const auto &ArrayNamingMap           = pCfgData->Hungarian.ArrayList;

    // Apply the same `m_RuleOfVariable` too.
    bStatus =
        this->_IsHungarianNotationString(Type, Name, bPreferUpperCamelIfMissed, bIsPtr, NOT_ARRAY,
                                         IgnorePrefixs, WordListMap, NullStringMap, ArrayNamingMap);
    break;
  }
  case RULETYPE_DEFAULT:
  case RULETYPE_UPPER_CAMEL:
    bStatus = this->_IsUpperCamelCaseString(Name, IgnorePrefixs,
                                            pCfgData->Camels.Options.AllowUnderscope);
    break;

  case RULETYPE_LOWER_CAMEL:
    bStatus = this->_IsLowerCamelCaseString(Name, IgnorePrefixs);
    break;

  case RULETYPE_LOWER_SNAKE:
    bStatus = this->_IsSnakeString(Name, SNAKETYPE_LOWER, IgnorePrefixs);
    break;

  case RULETYPE_UPPER_SNAKE:
    bStatus = this->_IsSnakeString(Name, SNAKETYPE_UPPER, IgnorePrefixs);
    break;
  }
  return bStatus;
}

} // namespace namelint
