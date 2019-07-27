#ifndef __NAMELINT_CONFIG__H__
#define __NAMELINT_CONFIG__H__

#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

namespace namelint {
typedef enum _RULETYPE {
    RULETYPE_DEFAULT = 0,
    RULETYPE_UPPER_CAMEL,
    RULETYPE_LOWER_CAMEL,
    RULETYPE_LOWER_SNAKE,
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

struct Rule {
    RULETYPE FileName;
    RULETYPE FunctionName;
    RULETYPE VariableName;
};

struct WhiteList {
    bool bAllowedEndWithUnderscope;
    bool bAllowedArrayAffected;

    vector<string> IgnoredFuncPrefix;
    vector<string> VariablePrefix;
    vector<string> IgnoredFuncName;

    WhiteList() {
        IgnoredFuncPrefix.clear();
        VariablePrefix.clear();
    }
};

struct HungarianArray {
    bool ArrayAffected;
    std::string Prefix;
};

struct HungarianList {
    std::map<std::string, std::string> TypeNamingMap;
    std::map<std::string, std::string> PtrNamingMap;
    std::map<std::string, std::string> ArrayNamingMap;
};

struct ConfigData {
    Rule m_Rule;
    General m_General;
    WhiteList m_WhiteList;
    HungarianArray m_HungarianArray;
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
} // namespace namelint

#endif // __NAMELINT_CONFIG__H__