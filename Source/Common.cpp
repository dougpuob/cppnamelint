#include "Common.h"
#include <sys/stat.h>

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

bool IsLowerString(const string &Str)
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

}  // namespace FileSystem