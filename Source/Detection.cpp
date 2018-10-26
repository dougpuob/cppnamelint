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
    bool bStatus              = false;
    const string NewRegexPatn = "^[a-z0-9]+";
    std::regex re(NewRegexPatn);
    std::smatch match;
    std::string result;
    if (std::regex_search(Name, match, re) && match.size() >= 1)
    {
        bStatus = true;
        Name    = match[0];
    }

    return bStatus;
}

bool Detection::isUpperCamelCaseString(const string &Name, vector<string> IgnorePrefixs)
{
    bool bStatus = false;
    if (0 == IgnorePrefixs.size())
    {
        IgnorePrefixs.push_back("");
    }

    for (string Prefix : IgnorePrefixs)
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
    bool bStatus = false;
    if (0 == IgnorePrefixs.size())
    {
        IgnorePrefixs.push_back("");
    }

    for (string Prefix : IgnorePrefixs)
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
    if (!::FileSystem::IsLowerString(Name))
    {
        return false;
    }

    if (0 == IgnorePrefixs.size())
    {
        IgnorePrefixs.push_back("");
    }

    for (string Prefix : IgnorePrefixs)
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

bool Detection::isHungarianNotationString(const string &Type, const string &Name, const vector<string> &IgnorePrefixs,
                                          const map<string, string> &MappedList)
{
    // RULETYPE_HUNGARIAN
    bool bStatus = false;

    string NewStr = Name;
    for (vector<string>::const_iterator iter = IgnorePrefixs.begin(); iter != IgnorePrefixs.end(); iter++)
    {
        const size_t nPos = NewStr.find_first_of(*iter);
        if (0 == nPos)
        {
            NewStr = NewStr.substr(nPos, NewStr.length() - nPos);
            break;
        }
    }

    if (this->captureLowerCasePrefix(NewStr))
    {
        map<string, string>::const_iterator iter = MappedList.find(Type);
        if (MappedList.end() != iter)
        {
            const auto str1 = iter->first;
            const auto str2 = iter->second;
            if ((str2 == NewStr) && (str1 == Type))
            {
                bStatus = true;
            }
        }
    }

    return bStatus;
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

bool Detection::CheckFunction(const RULETYPE Rule, const string &Name, const vector<string> &IgnorePrefixs)
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

bool Detection::CheckVariable(const RULETYPE Rule, const string &Type, const string &Name,
                              const vector<string> &IgnorePrefixs, const map<string, string> &MappedList)
{
    if (Name.length() == 0)
    {
        return false;
    }
    Type;

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