#include "Detection.h"
#include <iostream>
#include <iterator>
#include <regex>
#include <string>
#include "Common.h"

//==---------------------------------------------------------------------------
// Private Functions
//==---------------------------------------------------------------------------
namespace namelint {
bool Detection::captureLowerCasePrefix(string &Name)
{
    bool bStatus = false;

    std::smatch match;
    std::string result;

    const string NewRegexPatn = "^[a-z0-9]+";
    std::regex re(NewRegexPatn);

    if (std::regex_search(Name, match, re) && match.size() >= 1)
    {
        bStatus = true;
        Name    = match[0];
    }

    return bStatus;
}

bool Detection::isUpperCamelCaseString(const string &Name,
                                       vector<string> IgnorePrefixs,
                                       bool bAllowedEndWithUnderscopeChar = false)
{
    bool bStatus                    = false;
    vector<string> NewIgnorePrefixs = IgnorePrefixs;
    NewIgnorePrefixs.push_back("");

    string NewRegexPatn = "(^[A-Z][0-9a-zA-Z]*)";
    if (bAllowedEndWithUnderscopeChar)
    {
        NewRegexPatn += "([0-9a-zA-Z_]*)";
    }
    std::regex re(NewRegexPatn);

    for (string Prefix : NewIgnorePrefixs)
    {
        string TempStr   = Name;
        size_t nFoundPos = 0;

        if (Prefix.length() > 0)
        {
            nFoundPos = TempStr.find(Prefix);
            if (0 == nFoundPos)
            {
                TempStr = TempStr.substr(Prefix.length(), TempStr.length() - Prefix.length());
            }
        }

        nFoundPos = TempStr.find(".");
        if (-1 != nFoundPos)
        {
            TempStr = TempStr.substr(0, nFoundPos);
        }

        std::smatch match;
        std::string result;
        if (std::regex_search(TempStr, match, re))
        {
            if (match.size() >= 2)
            {
                if (bAllowedEndWithUnderscopeChar)
                {
                    if ((match[0] == TempStr) || (match[0] != match[1]))
                    {
                        bStatus = true;
                        break;
                    }
                }
                else
                {
                    if (match[0] == TempStr)
                    {
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

bool Detection::isLowerCamelCaseString(const string &Name, vector<string> IgnorePrefixs)
{
    bool bStatus                    = false;
    vector<string> NewIgnorePrefixs = IgnorePrefixs;
    NewIgnorePrefixs.push_back("");

    for (string Prefix : NewIgnorePrefixs)
    {
        // const string NewRegexPatn = "^" + Prefix + "[a-z_]";
        const string NewRegexPatn = "^" + Prefix + "[a-z]";
        std::regex re(NewRegexPatn);
        std::smatch match;
        std::string result;
        if (std::regex_search(Name, match, re) && match.size() >= 1)
        {
            bStatus = true;
            break;
        }
    }

    return bStatus;
}

bool Detection::isLowerSeperatedString(const string &Name, vector<string> IgnorePrefixs)
{
    bool bStatus = false;
    if (!::String::IsLower(Name))
    {
        return false;
    }
    vector<string> NewIgnorePrefixs = IgnorePrefixs;
    NewIgnorePrefixs.push_back("");

    for (string Prefix : NewIgnorePrefixs)
    {
        const string NewRegexPatn = Prefix + "^[a-z_]*";
        std::regex re(NewRegexPatn);
        std::smatch match;
        std::string result;
        if (std::regex_search(Name, match, re) && match.size() >= 1)
        {
            bStatus = true;
            break;
        }
    }

    return bStatus;
}

bool Detection::isHungarianNotationString(const string &Type,
                                          const string &Name,
                                          const vector<string> &IgnorePrefixs,
                                          const map<string, string> &MappedList)
{
    bool bStatus   = true;
    string NewName = Name;
    string NewType = Type;

    if ((Type == "char*") /* sz */ || (Type == "wchar_t*") /* wsz */)
    {
    }
    else
    {
        size_t nPointerNumb = this->findHowManyChar(NewType, '*');
        for (size_t nIdx = 0; nIdx < nPointerNumb; nIdx++)
        {
            if ('p' != NewName[nIdx])
            {
                bStatus = false;
                break;
            }
        }

        if (bStatus && (nPointerNumb > 0))
        {
            NewName = NewName.substr(nPointerNumb, NewName.length() - nPointerNumb);
            String::Replace(NewType, "*", "");
        }
    }

    if (bStatus)
    {
        for (vector<string>::const_iterator iter = IgnorePrefixs.begin();
             iter != IgnorePrefixs.end(); iter++)
        {
            const size_t nPos = NewName.find_first_of(*iter);
            if (0 == nPos)
            {
                NewName = NewName.substr(iter->length(), NewName.length() - iter->length());
                break;
            }
        }

        map<string, string>::const_iterator Iter = MappedList.find(NewType);

        bStatus = MappedList.end() != Iter;
        if (bStatus)
        {
            string HungarianHead = NewName;

            bStatus = this->captureLowerCasePrefix(HungarianHead);
            if (bStatus)
            {
                const auto Str1 = Iter->first;
                const auto Str2 = Iter->second;

                bStatus = ((Str2 == HungarianHead) && (Str1 == NewType));
            }
        }
        else
        {
            bStatus = this->isUpperCamelCaseString(NewName, IgnorePrefixs);
        }
    }

    return bStatus;
}

size_t Detection::findHowManyChar(const string &InputStr, char cChar)
{
    size_t nCount = 0;
    for (string::const_iterator iter1 = InputStr.begin(); iter1 != InputStr.end(); iter1++)
    {
        if (*iter1 == cChar)
        {
            nCount++;
        }
    }
    return nCount;
}

bool Detection::skipIgnoreFunctions(const string &Name, const vector<string> &IgnoreList)
{
    for (vector<string>::const_iterator pIter = IgnoreList.begin(); pIter != IgnoreList.end();
         pIter++)
    {
        if (Name == *pIter)
        {
            return true;
        }
    }
    return false;
}

}  // namespace namelint

//==---------------------------------------------------------------------------
// Public Functions
//==---------------------------------------------------------------------------
namespace namelint {
bool Detection::CheckFile(const RULETYPE Rule, const string &Name)
{
    bool bStatus = false;
    if (Name.length() == 0)
    {
        return false;
    }

    vector<string> NullIgnorePrefixs;
    switch (Rule)
    {
    case RULETYPE_DEFAULT:
    case RULETYPE_UPPER_CAMEL_CASE:
        bStatus = this->isUpperCamelCaseString(Name, NullIgnorePrefixs);
        break;

    case RULETYPE_LOWER_CAMEL_CASE:
        bStatus = this->isLowerCamelCaseString(Name, NullIgnorePrefixs);
        break;

    case RULETYPE_LOWER_SEPERATED:
        bStatus = this->isLowerSeperatedString(Name, NullIgnorePrefixs);
        break;
    }
    return bStatus;
}

bool Detection::CheckFunction(const RULETYPE Rule,
                              const string &Name,
                              const vector<string> &IgnorePrefixs,
                              const bool bAllowedEndWithUnderscopeChar)
{
    if (Name.length() == 0)
    {
        return false;
    }

    Config *pConfig = (Config *)GetAppCxt()->pTomlConfig;
    if (pConfig->GetData().m_WhiteList.IgnoreFunctions.size() > 0)
    {
        bool bResult =
            this->skipIgnoreFunctions(Name, pConfig->GetData().m_WhiteList.IgnoreFunctions);
        if (bResult)
        {
            return true;
        }
    }

    bool bStatus = false;
    switch (Rule)
    {
    case RULETYPE_DEFAULT:
    case RULETYPE_UPPER_CAMEL_CASE:
        bStatus = this->isUpperCamelCaseString(Name, IgnorePrefixs, bAllowedEndWithUnderscopeChar);
        break;

    case RULETYPE_LOWER_CAMEL_CASE:
        bStatus = this->isLowerCamelCaseString(Name, IgnorePrefixs);
        break;

    case RULETYPE_LOWER_SEPERATED:
        bStatus = this->isLowerSeperatedString(Name, IgnorePrefixs);
        break;
    }
    return bStatus;
}

bool Detection::CheckVariable(const RULETYPE Rule,
                              const string &Type,
                              const string &Name,
                              const vector<string> &IgnorePrefixs,
                              const map<string, string> &MappedList)
{
    if (Name.length() == 0)
    {
        return false;
    }

    bool bStatus = false;
    switch (Rule)
    {
    case RULETYPE_DEFAULT:
    case RULETYPE_UPPER_CAMEL_CASE:
        bStatus = this->isUpperCamelCaseString(Name, IgnorePrefixs);
        break;

    case RULETYPE_LOWER_CAMEL_CASE:
        bStatus = this->isLowerCamelCaseString(Name, IgnorePrefixs);
        break;

    case RULETYPE_LOWER_SEPERATED:
        bStatus = this->isLowerSeperatedString(Name, IgnorePrefixs);
        break;

    case RULETYPE_HUNGARIAN:
        bStatus = this->isHungarianNotationString(Type, Name, IgnorePrefixs, MappedList);
        break;
    }
    return bStatus;
}
}  // namespace namelint