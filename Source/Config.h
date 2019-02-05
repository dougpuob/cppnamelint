#ifndef __NAMELINT_CONFIG__H__
#define __NAMELINT_CONFIG__H__

#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

namespace namelint {
typedef enum _RULETYPE
{
    RULETYPE_DEFAULT = 0,
    RULETYPE_UPPER_CAMEL_CASE,
    RULETYPE_LOWER_CAMEL_CASE,
    RULETYPE_LOWER_SEPERATED,
    RULETYPE_HUNGARIAN
} RULETYPE;

class General {
   public:
    vector<string> FileExtName;
    bool bCheckVariableName;
    bool bCheckFunctionName;
    bool bCheckFileName;

   public:
    General() { FileExtName.clear(); }
};

class Rule {
   public:
    RULETYPE FileName;
    RULETYPE FunctionName;
    RULETYPE VariableName;
};

class WhiteList {
   public:
    vector<string> FunctionPrefix;
    vector<string> VariablePrefix;
    bool bAllowedUnderscopeChar;

   public:
    WhiteList()
    {
        FunctionPrefix.clear();
        VariablePrefix.clear();
    }
};

class HungarianList {
   public:
    std::map<std::string, std::string> MappedTable;
};

class ConfigData {
   public:
    Rule m_Rule;
    General m_General;
    WhiteList m_WhiteList;
    HungarianList m_HungarianList;
};

class Config {
   private:
    ConfigData m_Config;

   public:
    Config();
    bool LoadFile(string ConfigFilePath);
    bool LoadStream(string ConfigContent);
    bool Save(string DstPath);
    ConfigData &GetData() const;
};
}  // namespace namelint

#endif  // __NAMELINT_CONFIG__H__