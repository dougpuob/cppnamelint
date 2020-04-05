#ifndef __NAMELINT_CONFIG__H__
#define __NAMELINT_CONFIG__H__

#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <vector>

using namespace std;

namespace namelint {
typedef enum _RULETYPE {
  RULETYPE_DEFAULT = 0,
  RULETYPE_UPPER_CAMEL,
  RULETYPE_LOWER_CAMEL,
  RULETYPE_LOWER_SNAKE,
  RULETYPE_HUNGARIAN,
  RULETYPE_UPPER_SNAKE,
  RULETYPE_NA,
} RULETYPE;

typedef enum _SNAKETYPE {
  SNAKETYPE_LOWER = 1,
  SNAKETYPE_UPPER = 2,
} SNAKETYPE;

struct GeneralOptions {
  vector<string> FileExtNameList;
  bool bCheckVariableName;
  bool bCheckFunctionName;
  bool bCheckFileName;
  bool bCheckEnum;
  bool bCheckStruct;
  bool bAllowedPrintResult;
  bool bAllowedWriteJsonResult;
  bool bAllowedUnderscopeChar;
  bool bAllowedArrayAffected;
};

struct GeneralRules {
  RULETYPE FileName;
  RULETYPE FunctionName;
  RULETYPE VariableName;
  RULETYPE ClassName;
  RULETYPE EnumTagName;
  RULETYPE EnumValueName;
  RULETYPE StructTagName;
  RULETYPE StructValueName;
};

struct GeneralIgnoredList {
  vector<string> FunctionPrefix;
  vector<string> VariablePrefix;
  vector<string> FunctionName;
  vector<string> EnumTagPrefix;
  vector<string> StructTagPrefix;
};

struct General {
  GeneralRules Rules;
  GeneralOptions Options;
  GeneralIgnoredList IgnoredList;
};

struct HungarianOptions {
  bool PreferUpperCamelIfMissed;
};

struct MappingPair {
  string Key;
  string Value;
  MappingPair(string &Key, string &Value) {
    this->Key   = Key;
    this->Value = Value;
  }
  MappingPair(const char *szKey, const char *szValue) {
    this->Key   = szKey;
    this->Value = szValue;
  }
};
typedef std::map<std::string, std::string> HungarianMap;

struct Hungarian {
  HungarianOptions Options;
  vector<MappingPair> NullStringList;
  HungarianMap ArrayList;
  HungarianMap WordList;
};

typedef enum _AllowUnderscope {
  DoNotAllow = 0,
  AllowedOneUnderscope,
  AllowedSingleUnderscope
} AllowUnderscope;

struct CamelsOptions {
  namelint::AllowUnderscope AllowUnderscope;
};

struct Camels {
  CamelsOptions Options;
};

struct ConfigData {
  struct General General;
  struct Hungarian Hungarian;
  struct Camels Camels;
};

class Config {
private:
  shared_ptr<ConfigData> m_pConfig = std::make_shared<ConfigData>();

public:
  Config();
  void ReformatCStringMap(vector<MappingPair> &CStringMap);
  bool Clear();
  bool LoadFile(string ConfigFilePath, string &ErrorReason);
  bool LoadStream(string ConfigContent, string &ErrorReason);
  bool Save(string DstPath);
  shared_ptr<ConfigData> GetData() const;
};
} // namespace namelint

#endif // __NAMELINT_CONFIG__H__