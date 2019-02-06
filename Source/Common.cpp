#include "Common.h"

#if __has_include("filesystem")
#    include <filesystem>
using namespace filesystem;
#else
#    include <boost/filesystem.hpp>
namespace filesystem = boost::filesystem;
#endif

static APP_CONTEXT m_AppCxt;
const APP_CONTEXT *GetAppCxt() { return &m_AppCxt; }

namespace FileSystem {
bool IsExist(const string &Path) { return filesystem::exists(Path); }

const char *FindFileNameInPath(const string &Path)
{
    size_t nPos = Path.find_last_of("\\");
    if (nPos == string::npos)
    {
        nPos = Path.find_last_of("/");
        if (nPos == string::npos)
        {
            return Path.c_str();
        }
    }
    return Path.c_str() + nPos;
}

}  // namespace FileSystem

namespace String {

void PadTo(string &Source, size_t nCount, char cChar)
{
    if (nCount > Source.length())
        Source.append(nCount - Source.length(), cChar);
}

bool IsLower(const string &Source)
{
    bool bStatus = true;
    for (std::string::const_iterator iter = Source.begin(); iter != Source.end(); iter++)
    {
        if (isupper(*iter))
        {
            bStatus = false;
            break;
        }
    }

    return bStatus;
}

void Replace(string &Source, const string &Patn, const string &New)
{
    string::size_type pos    = 0;
    string::size_type srclen = Patn.size();
    string::size_type dstlen = New.size();
    while ((pos = Source.find(Patn, pos)) != string::npos)
    {
        Source.replace(pos, srclen, New);
        pos += dstlen;
    }
}

void Trim(string &Source)
{
    if (Source.empty())
    {
        return;
    }

    Source.erase(0, Source.find_first_not_of(" "));
    Source.erase(Source.find_last_not_of(" ") + 1);
}

}  // namespace String