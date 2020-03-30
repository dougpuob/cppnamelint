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

RuleOfFile::RuleOfFile() { this->Reset(); }

void RuleOfFile::Reset() { this->bAllowedUnderscopeChar = false; }

RuleOfFunction::RuleOfFunction() { this->Reset(); }

void RuleOfFunction::Reset() {
  this->bAllowedUnderscopeChar = false;
  this->IgnorePrefixs.clear();
  this->IgnoreNames.clear();
}

RuleOfVariable::RuleOfVariable() { this->Reset(); }
void RuleOfVariable::Reset() {
  this->bAllowedUnderscopeChar = false;
  this->IgnorePrefixs.clear();
  this->WordListMap.clear();
  this->NullStringMap.clear();
  this->ArrayNamingMap.clear();
}

bool Detection::_RemoveHeadingUnderscore(string &Text) {
  bool bStatus = false;

  std::smatch Match;
  std::string Result;

  std::regex Regex("^_{1,}");

  if (std::regex_search(Text, Match, Regex) && Match.size() >= 1) {
    bStatus = true;
    Text = Text.substr(Match.size(), Text.length() - Match.size());
  }

  return bStatus;
}

size_t Detection::_RemoveHeadingPtrChar(string &Text) {
  size_t nIdx = 0;
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

bool Detection::_CaptureLowerCasePrefix(string &Name) {
  bool bStatus = false;

  std::smatch Match;
  std::string Result;

  const string NewRegexPatn = "^[a-z0-9]+";
  std::regex Regex(NewRegexPatn);

  if (std::regex_search(Name, Match, Regex) && Match.size() >= 1) {
    bStatus = true;
    Name = Match[0];
  }

  return bStatus;
}

bool Detection::_IsUpperCamelCaseString(const string &Name,
                                        vector<string> IgnorePrefixs,
                                        const bool bAllowedUnderscopeChar) {

  vector<string> NewIgnorePrefixs = IgnorePrefixs;
  NewIgnorePrefixs.push_back("");

  auto wayToSort = [](string strA, string strB) {
    return strA.length() > strB.length();
  };
  std::sort(NewIgnorePrefixs.begin(), NewIgnorePrefixs.end(), wayToSort);

  size_t nUnderlineCount = 0;

  string TempStr = Name;
  for (string Prefix : NewIgnorePrefixs) {
    size_t nFoundPos = TempStr.find(".");
    if (-1 != nFoundPos) {
      TempStr = TempStr.substr(0, nFoundPos);
    }

    if (Prefix.length() > 0) {
      nFoundPos = TempStr.find(Prefix);
      if (0 == nFoundPos) {
        TempStr =
            TempStr.substr(Prefix.length(), TempStr.length() - Prefix.length());
        break;
      }
    }
  }

  bool bStatus = false;
  if (TempStr.length() > 0 && isupper(TempStr[0])) {
    char *szBuf = (char *)TempStr.c_str();
    while ((*szBuf != '\0') && isupper(*szBuf)) {
      szBuf++;
      if (isupper(*szBuf)) {
        bStatus = false;
        break;
      }

      while ((*szBuf != '\0')) {
        if (isupper(*szBuf)) {
          break;
        }

        if (bAllowedUnderscopeChar)
          bStatus = islower(*szBuf) || isdigit(*szBuf) || (*szBuf == '_');
        else
          bStatus = islower(*szBuf) || isdigit(*szBuf);

        if (!bStatus) {
          break;
        }
        szBuf++;
      }
    }
  }

  return bStatus;
}

bool Detection::_IsLowerCamelCaseString(const string &Name,
                                        vector<string> IgnorePrefixs) {
  bool bStatus = false;
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

bool Detection::_IsLowerSeperatedString(const string &Name,
                                        vector<string> IgnorePrefixs) {
  vector<string> NewIgnorePrefixs = IgnorePrefixs;

  auto wayToSort = [](string strA, string strB) {
    return strA.length() > strB.length();
  };
  std::sort(NewIgnorePrefixs.begin(), NewIgnorePrefixs.end(), wayToSort);

  string NewName = Name;
  for (string Prefix : NewIgnorePrefixs) {
    if (0 == NewName.find(Prefix)) {
      const size_t nPrefixLen = Prefix.length();

      NewName = NewName.substr(nPrefixLen, NewName.length() - nPrefixLen);
      break;
    }
  }

  char *szText = (char *)NewName.c_str();
  if (szText[0] == '_') {
    return false;
  }

  for (size_t nIdx = 0; szText[nIdx] != '\0'; nIdx++) {
    if (isupper(szText[nIdx])) {
      return false;
    }
  }

  bool bStatus = true;
  while (*szText != '\0') {
    if (*szText == '_') {
      szText++;
      if (*szText == '_') {
        bStatus = false;
        break;
      }
    }
    szText++;
  }

  return bStatus;
}

bool Detection::_IsHungarianNotationString(
    const string &TypeStr, const string &NameStr, const bool &bPreferUpperCamel,
    const bool &bIsPtr, const bool &bIsArray,
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
  for (vector<string>::const_iterator Iter = IgnorePrefixs.begin();
       Iter != IgnorePrefixs.end(); Iter++) {
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
  bool bSzStringMatched = false;
  if (bIsPtr || bIsArray) {
    size_t nLowerPCount = this->_RemoveHeadingPtrChar(NewNameStr);
    for (auto Iter : NullStringMap) {
      const auto IterType = Iter.Key;
      const auto IterPrefix = Iter.Value;
      string IterTypeNoStar = IterType;
      if (IterTypeNoStar == NewTypeStr) {
        const size_t nNewStrPos = NewNameStr.find(IterPrefix);
        if (0 == nNewStrPos) {
          const size_t nPrefixLen = IterPrefix.length();

          bSzStringMatched = true;
          NewNameStr =
              NewNameStr.substr(nPrefixLen, NewNameStr.length() - nPrefixLen);
          break;
        }
      }
    }
  }

  bool bStatus = true;
  bool bSpecificTypeMatched = false;
  if (!bSzStringMatched) {
    for (map<string, string>::const_iterator Iter = TypeNamingMap.begin();
         Iter != TypeNamingMap.end(); Iter++) {
      const auto IterType = Iter->first;
      const auto IterPrefix = Iter->second;
      if (IterType == NewTypeStr) {
        bStatus = false;
        const size_t nNewStrPos = NewNameStr.find(IterPrefix);
        if (0 == nNewStrPos) {
          const size_t nPrefixLen = IterPrefix.length();

          bStatus = true;
          bSpecificTypeMatched = true;
          NewNameStr =
              NewNameStr.substr(nPrefixLen, NewNameStr.length() - nPrefixLen);
          break;
        }
      }
    }
  }

  // bool bStatus = (bSzStringMatched || bSpecificTypeMatched) ||	//
  // Eithor
  // one.
  //		      !(bSzStringMatched || bSpecificTypeMatched);
  ////
  // Both
  // not.
  if (bStatus) {
    if (bPreferUpperCamel) {
      bStatus = this->_IsUpperCamelCaseString(NewNameStr, IgnorePrefixs);
    } else {
      bStatus = this->_IsLowerCamelCaseString(NewNameStr, IgnorePrefixs);
    }
  }

  return bStatus;
}

size_t Detection::_FindHowManyChar(const string &InputStr, char cChar) {
  size_t nCount = 0;
  for (string::const_iterator Iter = InputStr.begin(); Iter != InputStr.end();
       Iter++) {
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
    Text = Text.substr(nFound + 1, Text.length() - nFound - 1);
  }

  return bStatus;
}

bool Detection::_SkipIgnoreFunctions(const string &Name,
                                     const vector<string> &IgnoreList) {
  for (vector<string>::const_iterator Iter = IgnoreList.begin();
       Iter != IgnoreList.end(); Iter++) {
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

bool Detection::ApplyRuleForFile(const RuleOfFile &Rule) {
  this->m_RuleOfFile.bAllowedUnderscopeChar = Rule.bAllowedUnderscopeChar;
  return true;
}

bool Detection::ApplyRuleForFunction(const RuleOfFunction &Rule) {
  this->m_RuleOfFunction.bAllowedUnderscopeChar = Rule.bAllowedUnderscopeChar;
  this->m_RuleOfFunction.IgnoreNames = Rule.IgnoreNames;
  this->m_RuleOfFunction.IgnorePrefixs = Rule.IgnorePrefixs;
  return true;
}
bool Detection::ApplyRuleForVariable(const RuleOfVariable &Rule) {
  this->m_RuleOfVariable.IgnorePrefixs = Rule.IgnorePrefixs;
  this->m_RuleOfVariable.WordListMap = Rule.WordListMap;
  this->m_RuleOfVariable.ArrayNamingMap = Rule.ArrayNamingMap;
  this->m_RuleOfVariable.bAllowedUnderscopeChar = Rule.bAllowedUnderscopeChar;

  this->m_RuleOfVariable.NullStringMap.clear();
  for (auto Item : Rule.NullStringMap) {
    String::Replace(Item.Key, "*", "");
    String::Replace(Item.Key, "[", "");
    String::Replace(Item.Key, "]", "");
    this->m_RuleOfVariable.NullStringMap.push_back(
        MappingPair(Item.Key, Item.Value));
  }
  return true;
}

bool Detection::CheckFile(const RULETYPE Rule, const string &Name) {
  bool bStatus = false;
  if (Name.length() == 0) {
    return false;
  }

  vector<string> NullIgnorePrefixs;
  switch (Rule) {
  case RULETYPE_DEFAULT:
  case RULETYPE_UPPER_CAMEL:
    bStatus = this->_IsUpperCamelCaseString(
        Name, NullIgnorePrefixs, this->m_RuleOfFile.bAllowedUnderscopeChar);
    break;

  case RULETYPE_LOWER_CAMEL:
    bStatus = this->_IsLowerCamelCaseString(Name, NullIgnorePrefixs);
    break;

  case RULETYPE_LOWER_SNAKE:
    bStatus = this->_IsLowerSeperatedString(Name, NullIgnorePrefixs);
    break;
  }
  return bStatus;
}

bool Detection::CheckFunction(const RULETYPE Rule, const string &Name) {
  if (Name.length() == 0) {
    return false;
  }

  if (this->m_RuleOfFunction.IgnorePrefixs.size() > 0) {
    bool bResult =
        this->_SkipIgnoreFunctions(Name, this->m_RuleOfFunction.IgnoreNames);
    if (bResult) {
      return true;
    }
  }

  bool bStatus = false;
  switch (Rule) {
  case RULETYPE_DEFAULT:
  case RULETYPE_UPPER_CAMEL:
    bStatus = this->_IsUpperCamelCaseString(
        Name, this->m_RuleOfFunction.IgnorePrefixs,
        this->m_RuleOfFunction.bAllowedUnderscopeChar);
    break;

  case RULETYPE_LOWER_CAMEL:
    bStatus = this->_IsLowerCamelCaseString(
        Name, this->m_RuleOfFunction.IgnorePrefixs);
    break;

  case RULETYPE_LOWER_SNAKE:
    bStatus = this->_IsLowerSeperatedString(
        Name, this->m_RuleOfFunction.IgnorePrefixs);
    break;
  }
  return bStatus;
}

bool Detection::CheckVariable(const RULETYPE Rule, const string &Type,
                              const string &Name, const bool &bPreferUpperCamel,
                              const bool &bIsPtr, const bool &bIsArray) {
  if (Name.length() == 0) {
    return false;
  }

  bool bStatus = false;
  switch (Rule) {
  case RULETYPE_DEFAULT:
  case RULETYPE_UPPER_CAMEL:
    bStatus = this->_IsUpperCamelCaseString(
        Name, this->m_RuleOfVariable.IgnorePrefixs,
        this->m_RuleOfVariable.bAllowedUnderscopeChar);
    break;

  case RULETYPE_LOWER_CAMEL:
    bStatus = this->_IsLowerCamelCaseString(
        Name, this->m_RuleOfVariable.IgnorePrefixs);
    break;

  case RULETYPE_LOWER_SNAKE:
    bStatus = this->_IsLowerSeperatedString(
        Name, this->m_RuleOfVariable.IgnorePrefixs);
    break;

  case RULETYPE_HUNGARIAN:
    bStatus = this->_IsHungarianNotationString(
        Type, Name, bPreferUpperCamel, bIsPtr, bIsArray,
        this->m_RuleOfVariable.IgnorePrefixs,
        this->m_RuleOfVariable.WordListMap,
        this->m_RuleOfVariable.NullStringMap,
        this->m_RuleOfVariable.ArrayNamingMap);
    break;
  }
  return bStatus;
}
} // namespace namelint
