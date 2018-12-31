#include "Common.h"
#include <sys/stat.h>

static APP_CONTEXT m_AppCxt;
const APP_CONTEXT *GetAppCxt() { return &m_AppCxt; }

namespace FileSystem {
bool IsFileExist(const string &FilePath)
{
    struct stat fileStat;
    if (stat(FilePath.c_str(), &fileStat))
    {
        return false;
    }
    return true;
}

const char *FindFileNameInPath(const string &FielPath)
{
    size_t nPos = FielPath.find_last_of("\\");
    if (nPos == string::npos)
    {
        nPos = FielPath.find_last_of("/");
        if (nPos == string::npos)
        {
            return FielPath.c_str();
        }
    }
    return FielPath.c_str() + nPos;
}

}  // namespace FileSystem

namespace MyString {

void PadTo(string &s, size_t nCount, char cChar)
{
    if (nCount > s.length())
        s.append(nCount - s.length(), cChar);
}

bool IsLower(const string &Str)
{
    bool bStatus = true;
    for (std::string::const_iterator iter = Str.begin(); iter != Str.end(); iter++)
    {
        if (isupper(*iter))
        {
            bStatus = false;
            break;
        }
    }

    return bStatus;
}

void Replace(string &strBig, const string &strsrc, const string &strdst)
{
    string::size_type pos    = 0;
    string::size_type srclen = strsrc.size();
    string::size_type dstlen = strdst.size();
    while ((pos = strBig.find(strsrc, pos)) != string::npos)
    {
        strBig.replace(pos, srclen, strdst);
        pos += dstlen;
    }
}

void Trim(string &Str)
{
    if (Str.empty())
    {
        return;
    }

    Str.erase(0, Str.find_first_not_of(" "));
    Str.erase(Str.find_last_not_of(" ") + 1);
}

}  // namespace MyString