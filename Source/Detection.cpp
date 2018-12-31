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

bool Detection::isUpperCamelCaseString(const string &Name, vector<string> IgnorePrefixs)
{
    bool bStatus                    = false;
    vector<string> NewIgnorePrefixs = IgnorePrefixs;
    NewIgnorePrefixs.push_back("");

    for (string Prefix : NewIgnorePrefixs)
    {
        const string NewRegexPatn = "^" + Prefix + "[A-Z]";
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

bool Detection::isLowerCamelCaseString(const string &Name, vector<string> IgnorePrefixs)
{
    bool bStatus                    = false;
    vector<string> NewIgnorePrefixs = IgnorePrefixs;
    NewIgnorePrefixs.push_back("");

    for (string Prefix : NewIgnorePrefixs)
    {
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
    if (!::MyString::IsLower(Name))
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
            MyString::Replace(NewType, "*", "");
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
                NewName = NewName.substr(nPos, NewName.length() - nPos);
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
                              const vector<string> &IgnorePrefixs)
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