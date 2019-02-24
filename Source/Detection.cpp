#include "Detection.h"
#include "Common.h"
#include <iostream>
#include <iterator>
#include <regex>
#include <string>

//==---------------------------------------------------------------------------
// Private Functions
//==---------------------------------------------------------------------------
namespace namelint {
bool
Detection::_CaptureLowerCasePrefix(string& Name)
{
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

bool
Detection::_IsUpperCamelCaseString(const string& Name,
                                   vector<string> IgnorePrefixs,
                                   const bool bAllowedEndWithUnderscopeChar)
{
  bool bStatus = false;
  vector<string> NewIgnorePrefixs = IgnorePrefixs;
  NewIgnorePrefixs.push_back("");

  string NewRegexPatn = "(^[A-Z][0-9a-zA-Z]*)";
  if (bAllowedEndWithUnderscopeChar) {
    NewRegexPatn += "([0-9a-zA-Z_]*)";
  }
  std::regex Regex(NewRegexPatn);

  for (string Prefix : NewIgnorePrefixs) {
    string TempStr = Name;
    size_t nFoundPos = 0;

    if (Prefix.length() > 0) {
      nFoundPos = TempStr.find(Prefix);
      if (0 == nFoundPos) {
        TempStr =
          TempStr.substr(Prefix.length(), TempStr.length() - Prefix.length());
      }
    }

    nFoundPos = TempStr.find(".");
    if (-1 != nFoundPos) {
      TempStr = TempStr.substr(0, nFoundPos);
    }

    std::smatch Match;
    std::string Result;
    if (std::regex_search(TempStr, Match, Regex)) {
      if (Match.size() >= 2) {
        if (bAllowedEndWithUnderscopeChar) {
          if ((Match[0] == TempStr) || (Match[0] != Match[1])) {
            bStatus = true;
            break;
          }
        } else {
          if (Match[0] == TempStr) {
            bStatus = true;
            break;
          }
        }
      }
    }
  }

  // printf("Checking >%s< (%d)\r\n", Name.c_str(), bStatus);
  return bStatus;
}

bool
Detection::_IsLowerCamelCaseString(const string& Name,
                                   vector<string> IgnorePrefixs)
{
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

bool
Detection::_IsLowerSeperatedString(const string& Name,
                                   vector<string> IgnorePrefixs)
{
  bool bStatus = false;
  if (!::String::IsLower(Name)) {
    return false;
  }
  vector<string> NewIgnorePrefixs = IgnorePrefixs;
  NewIgnorePrefixs.push_back("");

  for (string Prefix : NewIgnorePrefixs) {
    const string NewRegexPatn = Prefix + "^[a-z_]*";
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

bool
Detection::_IsHungarianNotationString(const string& Type,
                                      const string& Name,
                                      const vector<string>& IgnorePrefixs,
                                      const map<string, string>& MappedList)
{
  bool bStatus = true;
  string NewName = Name;
  string NewType = Type;

  if ((Type == "char*") /* sz */ || (Type == "wchar_t*") /* wsz */) {
  } else {
    size_t nPointerNumb = this->_FindHowManyChar(NewType, '*');
    for (size_t nIdx = 0; nIdx < nPointerNumb; nIdx++) {
      if ('p' != NewName[nIdx]) {
        bStatus = false;
        break;
      }
    }

    if (bStatus && (nPointerNumb > 0)) {
      NewName = NewName.substr(nPointerNumb, NewName.length() - nPointerNumb);
      String::Replace(NewType, "*", "");
    }
  }

  if (bStatus) {
    for (vector<string>::const_iterator Iter = IgnorePrefixs.begin();
         Iter != IgnorePrefixs.end();
         Iter++) {
      const size_t nPos = NewName.find_first_of(*Iter);
      if (0 == nPos) {
        NewName =
          NewName.substr(Iter->length(), NewName.length() - Iter->length());
        break;
      }
    }

    map<string, string>::const_iterator Iter = MappedList.find(NewType);

    bStatus = MappedList.end() != Iter;
    if (bStatus) {
      string HungarianHead = NewName;

      bStatus = this->_CaptureLowerCasePrefix(HungarianHead);
      if (bStatus) {
        const auto Str1 = Iter->first;
        const auto Str2 = Iter->second;

        bStatus = ((Str2 == HungarianHead) && (Str1 == NewType));
      }
    } else {
      bStatus = this->_IsUpperCamelCaseString(NewName, IgnorePrefixs);
    }
  }

  return bStatus;
}

size_t
Detection::_FindHowManyChar(const string& InputStr, char cChar)
{
  size_t nCount = 0;
  for (string::const_iterator Iter = InputStr.begin(); Iter != InputStr.end();
       Iter++) {
    if (*Iter == cChar) {
      nCount++;
    }
  }
  return nCount;
}

bool
Detection::_SkipIgnoreFunctions(const string& Name,
                                const vector<string>& IgnoreList)
{
  for (vector<string>::const_iterator Iter = IgnoreList.begin();
       Iter != IgnoreList.end();
       Iter++) {
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
bool
Detection::CheckFile(const RULETYPE Rule, const string& Name)
{
  bool bStatus = false;
  if (Name.length() == 0) {
    return false;
  }

  vector<string> NullIgnorePrefixs;
  switch (Rule) {
    case RULETYPE_DEFAULT:
    case RULETYPE_UPPER_CAMEL_CASE:
      bStatus = this->_IsUpperCamelCaseString(Name, NullIgnorePrefixs);
      break;

    case RULETYPE_LOWER_CAMEL_CASE:
      bStatus = this->_IsLowerCamelCaseString(Name, NullIgnorePrefixs);
      break;

    case RULETYPE_LOWER_SEPERATED:
      bStatus = this->_IsLowerSeperatedString(Name, NullIgnorePrefixs);
      break;
  }
  return bStatus;
}

bool
Detection::CheckFunction(const RULETYPE Rule,
                         const string& Name,
                         const vector<string>& IgnorePrefixs,
                         const bool bAllowedEndWithUnderscopeChar)
{
  if (Name.length() == 0) {
    return false;
  }

  if (IgnorePrefixs.size() > 0) {
    bool bResult = this->_SkipIgnoreFunctions(Name, IgnorePrefixs);
    if (bResult) {
      return true;
    }
  }

  bool bStatus = false;
  switch (Rule) {
    case RULETYPE_DEFAULT:
    case RULETYPE_UPPER_CAMEL_CASE:
      bStatus = this->_IsUpperCamelCaseString(
        Name, IgnorePrefixs, bAllowedEndWithUnderscopeChar);
      break;

    case RULETYPE_LOWER_CAMEL_CASE:
      bStatus = this->_IsLowerCamelCaseString(Name, IgnorePrefixs);
      break;

    case RULETYPE_LOWER_SEPERATED:
      bStatus = this->_IsLowerSeperatedString(Name, IgnorePrefixs);
      break;
  }
  return bStatus;
}

bool
Detection::CheckVariable(const RULETYPE Rule,
                         const string& Type,
                         const string& Name,
                         const vector<string>& IgnorePrefixs,
                         const map<string, string>& MappedList)
{
  if (Name.length() == 0) {
    return false;
  }

  bool bStatus = false;
  switch (Rule) {
    case RULETYPE_DEFAULT:
    case RULETYPE_UPPER_CAMEL_CASE:
      bStatus = this->_IsUpperCamelCaseString(Name, IgnorePrefixs);
      break;

    case RULETYPE_LOWER_CAMEL_CASE:
      bStatus = this->_IsLowerCamelCaseString(Name, IgnorePrefixs);
      break;

    case RULETYPE_LOWER_SEPERATED:
      bStatus = this->_IsLowerSeperatedString(Name, IgnorePrefixs);
      break;

    case RULETYPE_HUNGARIAN:
      bStatus =
        this->_IsHungarianNotationString(Type, Name, IgnorePrefixs, MappedList);
      break;
  }
  return bStatus;
}
} // namespace namelint