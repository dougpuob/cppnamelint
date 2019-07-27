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

RuleOfFunction::RuleOfFunction() { this->Reset(); }

void RuleOfFunction::Reset() {
    this->bAllowedEndWithUnderscopeChar = false;
    this->IgnorePrefixs.clear();
    this->IgnoreNames.clear();
}

RuleOfVariable::RuleOfVariable() { this->Reset(); }
void RuleOfVariable::Reset() {
    this->IgnorePrefixs.clear();
    this->TypeNamingMap.clear();
    this->PtrNamingMap.clear();
    this->ArrayNamingMap.clear();
}

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

bool Detection::_RemoveHeadingPtrChar(string &Text) {
    bool bStatus = false;

    std::smatch Match;
    std::string Result;

    std::regex Regex("^p{1,}");

    if (std::regex_search(Text, Match, Regex) && Match.size() >= 1) {
        bStatus = true;
        Text    = Text.substr(Match.size(), Text.length() - Match.size());
    }

    return bStatus;
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

bool Detection::_IsUpperCamelCaseString(
    const string &Name, vector<string> IgnorePrefixs,
    const bool bAllowedEndWithUnderscopeChar) {
    bool bStatus                    = false;
    vector<string> NewIgnorePrefixs = IgnorePrefixs;
    NewIgnorePrefixs.push_back("");

    string NewRegexPatn = "(^[A-Z][0-9a-zA-Z]*)";
    if (bAllowedEndWithUnderscopeChar) {
        NewRegexPatn += "([0-9a-zA-Z_]*)";
    }
    std::regex Regex(NewRegexPatn);

    for (string Prefix : NewIgnorePrefixs) {
        string TempStr   = Name;
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

bool Detection::_IsLowerCamelCaseString(const string &Name,
                                        vector<string> IgnorePrefixs) {
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

bool Detection::_IsLowerSeperatedString(const string &Name,
                                        vector<string> IgnorePrefixs) {
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

bool Detection::_IsHungarianNotationString(
    const string &TypeStr, const string &NameStr, const bool &bIsPtr,
    const bool &bIsArray, const vector<string> &IgnorePrefixs,
    const map<string, string> &TypeNamingMap,
    const map<string, string> &PtrNamingMap,
    const map<string, string> &ArrayNamingMap) {

    bool bModified = false;

    string NewNameStr = NameStr;
    string NewTypeStr = TypeStr;

    this->_RemoveNamespacesAndElements(NewTypeStr);

    //
    // Prefix
    //
    for (vector<string>::const_iterator Iter = IgnorePrefixs.begin();
         Iter != IgnorePrefixs.end(); Iter++) {
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
    // PtrNamingMap
    //
    if (bIsPtr) {
        for (map<string, string>::const_iterator Iter = PtrNamingMap.begin();
             Iter != PtrNamingMap.end(); Iter++) {
            const auto IterType   = Iter->first;
            const auto IterPrefix = Iter->second;

            string IterTypeNoStar = IterType;
            String::Replace(IterTypeNoStar, "*", "");

            if (IterTypeNoStar == NewTypeStr) {
                const size_t nPos = NewNameStr.find_first_of(IterPrefix);
                if (0 == nPos) {
                    const size_t nStrLen = IterPrefix.length();

                    NewNameStr = NewNameStr.substr(
                        nStrLen, NewNameStr.length() - nStrLen);
                    bModified = true;
                    break;
                }
            }
        }
    }

    //
    // Pointer
    //
    if (bIsPtr) {
        bModified = true;
        this->_RemoveHeadingPtrChar(NewNameStr);
    }

    // TypeNamingMap
    //
    bool bMatchedList = false;
    for (map<string, string>::const_iterator Iter = TypeNamingMap.begin();
         Iter != TypeNamingMap.end(); Iter++) {
        const auto IterType   = Iter->first;
        const auto IterPrefix = Iter->second;

        if (IterType == NewTypeStr) {
            bMatchedList      = true;
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

    if (bIsArray) {
        for (map<string, string>::const_iterator Iter = ArrayNamingMap.begin();
             Iter != ArrayNamingMap.end(); Iter++) {
            const auto IterType   = Iter->first;
            const auto IterPrefix = Iter->second;
            if (IterType == NewTypeStr) {
                const size_t nPos = NewNameStr.find_first_of(IterPrefix);
                if (0 == nPos) {
                    const size_t nStrLen = IterPrefix.length();

                    NewNameStr = NewNameStr.substr(
                        nStrLen, NewNameStr.length() - nStrLen);
                    bModified = true;
                    break;
                }
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
        Text    = Text.substr(nFound + 1, Text.length() - nFound - 1);
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

bool Detection::ApplyRuleForFunction(const RuleOfFunction &Rule) {
    this->m_RuleOfFunction.bAllowedEndWithUnderscopeChar =
        Rule.bAllowedEndWithUnderscopeChar;
    this->m_RuleOfFunction.IgnoreNames   = Rule.IgnoreNames;
    this->m_RuleOfFunction.IgnorePrefixs = Rule.IgnorePrefixs;
    return true;
}
bool Detection::ApplyRuleForVariable(const RuleOfVariable &Rule) {
    this->m_RuleOfVariable.IgnorePrefixs  = Rule.IgnorePrefixs;
    this->m_RuleOfVariable.TypeNamingMap  = Rule.TypeNamingMap;
    this->m_RuleOfVariable.PtrNamingMap   = Rule.PtrNamingMap;
    this->m_RuleOfVariable.ArrayNamingMap = Rule.ArrayNamingMap;
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
        bStatus = this->_IsUpperCamelCaseString(Name, NullIgnorePrefixs);
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
        bool bResult = this->_SkipIgnoreFunctions(
            Name, this->m_RuleOfFunction.IgnoreNames);
        if (bResult) {
            return true;
        }
    }

    APP_CONTEXT *pAppCxt = (APP_CONTEXT *)GetAppCxt();
    if (pAppCxt) {
        pAppCxt->TraceMemo.Checked.nFunction++;
    }

    bool bStatus = false;
    switch (Rule) {
    case RULETYPE_DEFAULT:
    case RULETYPE_UPPER_CAMEL:
        bStatus = this->_IsUpperCamelCaseString(
            Name, this->m_RuleOfFunction.IgnorePrefixs,
            this->m_RuleOfFunction.bAllowedEndWithUnderscopeChar);
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
                              const string &Name, const bool &bIsPtr,
                              const bool &bIsArray) {
    if (Name.length() == 0) {
        return false;
    }

    bool bStatus = false;
    switch (Rule) {
    case RULETYPE_DEFAULT:
    case RULETYPE_UPPER_CAMEL:
        bStatus = this->_IsUpperCamelCaseString(
            Name, this->m_RuleOfVariable.IgnorePrefixs);
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
            Type, Name, bIsPtr, bIsArray, this->m_RuleOfVariable.IgnorePrefixs,
            this->m_RuleOfVariable.TypeNamingMap,
            this->m_RuleOfVariable.PtrNamingMap,
            this->m_RuleOfVariable.ArrayNamingMap);
        break;
    }
    return bStatus;
}
} // namespace namelint
