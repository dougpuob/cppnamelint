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
Detection::_RemoveHeadingUnderscore(string& Text)
{
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

bool
Detection::_RemoveHeadingPtrChar(string& Text)
{
    bool bStatus = false;

    std::smatch Match;
    std::string Result;

    std::regex Regex("^p{1,}");

    if (std::regex_search(Text, Match, Regex) && Match.size() >= 1) {
        bStatus = true;
        Text = Text.substr(Match.size(), Text.length() - Match.size());
    }

    return bStatus;
}

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
                TempStr = TempStr.substr(Prefix.length(),
                                         TempStr.length() - Prefix.length());
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
Detection::_IsHungarianNotationString(const string& TypeStr,
                                      const string& NameStr,
                                      const vector<string>& IgnorePrefixs,
                                      const map<string, string>& MappedList,
                                      const map<string, string>& MappedListEx)
{
    bool bModified = false;

    string NewNameStr = NameStr;
    string NewTypeStr = TypeStr;

    this->_RemoveNamespacesAndElements(NewTypeStr);

    //
    // Prefix
    //
    for (vector<string>::const_iterator Iter = IgnorePrefixs.begin();
         Iter != IgnorePrefixs.end();
         Iter++) {
        const size_t nPos = NewNameStr.find_first_of(*Iter);
        if (0 == nPos) {
            const size_t nStrLen = Iter->length();
            NewNameStr =
              NewNameStr.substr(nStrLen, NewNameStr.length() - nStrLen);
            bModified = true;
            break;
        }
    }

    //
    // MappedListEx
    //
    for (map<string, string>::const_iterator Iter = MappedListEx.begin();
         Iter != MappedListEx.end();
         Iter++) {
        const auto IterType = Iter->first;
        const auto IterPrefix = Iter->second;
        if (IterType == NewTypeStr) {
            const size_t nPos = NewNameStr.find_first_of(IterPrefix);
            if (0 == nPos) {
                const size_t nStrLen = IterPrefix.length();
                NewNameStr =
                  NewNameStr.substr(nStrLen, NewNameStr.length() - nStrLen);
                bModified = true;
                break;
            }
        }
    }

    //
    // Pointer
    //
    size_t nPtrCnt = this->_FindHowManyChar(NewTypeStr, '*');
    if (nPtrCnt > 0) {
        bModified = true;
        String::Replace(NewTypeStr, "*", "");
        this->_RemoveHeadingPtrChar(NewNameStr);
    }

    //
    // MappedList
    //
    bool bMatchedList = false;
    for (map<string, string>::const_iterator Iter = MappedList.begin();
         Iter != MappedList.end();
         Iter++) {
        const auto IterType = Iter->first;
        const auto IterPrefix = Iter->second;

        if (IterType == NewTypeStr) {
            bMatchedList = true;
            const size_t nPos = NewNameStr.find_first_of(IterPrefix);
            if (0 == nPos) {
                const size_t nStrLen = IterPrefix.length();
                NewNameStr =
                  NewNameStr.substr(nStrLen, NewNameStr.length() - nStrLen);

                bModified = true;
                break;
            } else if (IterPrefix == "") {
                // Bypass
                bModified = true;
                break;
            }
        }
    }

    if (bModified) {
        this->_RemoveHeadingUnderscore(NewNameStr);
    }

    bool bIsUpperCamel =
      this->_IsUpperCamelCaseString(NewNameStr, IgnorePrefixs);

    bool bStatus =
      (bMatchedList && bModified && bIsUpperCamel) ||  // Hungarian notation
      (!bMatchedList && bModified && bIsUpperCamel) || // Pointer of object
      (!bMatchedList && !bModified && bIsUpperCamel);  // Object
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
Detection::_RemoveNamespacesAndElements(string& Text)
{
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
        case RULETYPE_UPPER_CAMEL:
            bStatus = this->_IsUpperCamelCaseString(Name, NullIgnorePrefixs);
            break;

        case RULETYPE_LOWER_CAMEL:
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
                         const vector<string>& IgnoreNames,
                         const vector<string>& IgnorePrefixs,
                         const bool bAllowedEndWithUnderscopeChar)
{
    if (Name.length() == 0) {
        return false;
    }

    if (IgnorePrefixs.size() > 0) {
        bool bResult = this->_SkipIgnoreFunctions(Name, IgnoreNames);
        if (bResult) {
            return true;
        }
    }

    bool bStatus = false;
    switch (Rule) {
        case RULETYPE_DEFAULT:
        case RULETYPE_UPPER_CAMEL:
            bStatus = this->_IsUpperCamelCaseString(
              Name, IgnorePrefixs, bAllowedEndWithUnderscopeChar);
            break;

        case RULETYPE_LOWER_CAMEL:
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
                         const map<string, string>& MappedList,
                         const map<string, string>& MappedListEx)
{
    if (Name.length() == 0) {
        return false;
    }

    bool bStatus = false;
    switch (Rule) {
        case RULETYPE_DEFAULT:
        case RULETYPE_UPPER_CAMEL:
            bStatus = this->_IsUpperCamelCaseString(Name, IgnorePrefixs);
            break;

        case RULETYPE_LOWER_CAMEL:
            bStatus = this->_IsLowerCamelCaseString(Name, IgnorePrefixs);
            break;

        case RULETYPE_LOWER_SEPERATED:
            bStatus = this->_IsLowerSeperatedString(Name, IgnorePrefixs);
            break;

        case RULETYPE_HUNGARIAN:
            bStatus = this->_IsHungarianNotationString(
              Type, Name, IgnorePrefixs, MappedList, MappedListEx);
            break;
    }
    return bStatus;
}
} // namespace namelint