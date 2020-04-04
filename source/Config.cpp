#include <iostream>
#include <string>
#include <sys/stat.h>

#include "Common.h"
#include "Config.h"

#include "../submodule/tinytoml.git/include/toml/toml.h"

namespace namelint {
Config::Config() {
  // [General.Options]
  this->m_pConfig->General.Options.FileExtNameList.assign({"*.c", "*.h", "*.cpp"});
  this->m_pConfig->General.Options.bCheckVariableName      = true;
  this->m_pConfig->General.Options.bCheckFunctionName      = true;
  this->m_pConfig->General.Options.bCheckFileName          = false;
  this->m_pConfig->General.Options.bCheckEnum              = true;
  this->m_pConfig->General.Options.bCheckStruct            = true;
  this->m_pConfig->General.Options.bAllowedPrintResult     = true;
  this->m_pConfig->General.Options.bAllowedWriteJsonResult = true;
  this->m_pConfig->General.Options.bAllowedUnderscopeChar  = false;
  this->m_pConfig->General.Options.bAllowedArrayAffected   = false;

  // [General.Rules]
  this->m_pConfig->General.Rules.FileName        = RULETYPE::RULETYPE_DEFAULT;
  this->m_pConfig->General.Rules.FunctionName    = RULETYPE::RULETYPE_DEFAULT;
  this->m_pConfig->General.Rules.VariableName    = RULETYPE::RULETYPE_HUNGARIAN;
  this->m_pConfig->General.Rules.ClassName       = RULETYPE::RULETYPE_DEFAULT;
  this->m_pConfig->General.Rules.EnumTagName     = RULETYPE::RULETYPE_DEFAULT;
  this->m_pConfig->General.Rules.EnumValueName   = RULETYPE::RULETYPE_DEFAULT;
  this->m_pConfig->General.Rules.StructTagName   = RULETYPE::RULETYPE_DEFAULT;
  this->m_pConfig->General.Rules.StructValueName = RULETYPE::RULETYPE_DEFAULT;

  // [General.IgnoredList]
  this->m_pConfig->General.IgnoredList.FunctionPrefix.assign({"_", "__", "~"});
  this->m_pConfig->General.IgnoredList.VariablePrefix.assign({"m_"});
  this->m_pConfig->General.IgnoredList.EnumTagPrefix.assign({"_", "e"});
  this->m_pConfig->General.IgnoredList.StructTagPrefix.assign({"_", "s"});
  this->m_pConfig->General.IgnoredList.FunctionName.assign({"main", "newASTConsumer", "TEST"});

  // [Hungarian.Others]
  this->m_pConfig->Hungarian.Others.PreferUpperCamelIfMissed = true;

  //[ Hungarian.WordList]
  this->m_pConfig->Hungarian.WordList.insert(std::pair<string, string>("size_t", "n"));
  this->m_pConfig->Hungarian.WordList.insert(std::pair<string, string>("uint8_t", "u8"));
  this->m_pConfig->Hungarian.WordList.insert(std::pair<string, string>("uint16_t", "u16"));
  this->m_pConfig->Hungarian.WordList.insert(std::pair<string, string>("uint32_t", "u32"));
  this->m_pConfig->Hungarian.WordList.insert(std::pair<string, string>("char", "c"));
  this->m_pConfig->Hungarian.WordList.insert(std::pair<string, string>("_Bool", "b"));
  this->m_pConfig->Hungarian.WordList.insert(std::pair<string, string>("bool", "b"));
  this->m_pConfig->Hungarian.WordList.insert(std::pair<string, string>("int", "i"));
  this->m_pConfig->Hungarian.WordList.insert(std::pair<string, string>("long long", "ll"));
  this->m_pConfig->Hungarian.WordList.insert(std::pair<string, string>("float", "f"));
  this->m_pConfig->Hungarian.WordList.insert(std::pair<string, string>("double", "d"));
}

shared_ptr<ConfigData> Config::GetData() const { return this->m_pConfig; }
bool Config::Clear() {
  this->m_pConfig->General.IgnoredList.FunctionPrefix.clear();
  this->m_pConfig->General.IgnoredList.VariablePrefix.clear();
  this->m_pConfig->General.IgnoredList.FunctionName.clear();
  this->m_pConfig->General.IgnoredList.EnumTagPrefix.clear();
  this->m_pConfig->General.IgnoredList.StructTagPrefix.clear();

  memset(&this->m_pConfig->General.Options, 0, sizeof(this->m_pConfig->General.Options));

  this->m_pConfig->Hungarian.ArrayList.clear();
  this->m_pConfig->Hungarian.NullStringList.clear();
  this->m_pConfig->Hungarian.WordList.clear();

  return true;
}

void Config::ReformatCStringMap(vector<MappingPair> &CStringMap) {
  vector<MappingPair> TempCStringMap = CStringMap;
  CStringMap.clear();
  for (auto Item : TempCStringMap) {
    String::Replace(Item.Key, "*", "");
    String::Replace(Item.Key, "[", "");
    String::Replace(Item.Key, "]", "");
    CStringMap.push_back(MappingPair(Item.Key, Item.Value));
  }
}

bool Config::LoadFile(string ConfigFilePath, string &ErrorReason) {
  Clear();

  bool bStatus = Path::IsExist(ConfigFilePath);
  if (bStatus) {
    std::ifstream InputFileStream(ConfigFilePath);
    std::string Content((std::istreambuf_iterator<char>(InputFileStream)),
                        (std::istreambuf_iterator<char>()));
    bStatus = this->LoadStream(Content, ErrorReason);
  }
  return bStatus;
}

bool Config::LoadStream(string ConfigContent, string &ErrorReason) {
  Clear();

  istringstream InputStrStream = istringstream(ConfigContent);
  toml::ParseResult ParseRs    = toml::parse(InputStrStream);
  bool bStatus                 = ParseRs.valid();

  if (!bStatus) {
    ErrorReason = ParseRs.errorReason;
    return bStatus;
  }

  const toml::Value &ParseRsValue = ParseRs.value;

  // ==----------------------------------------------------------------------------------
  // [General.Options]
  // ==----------------------------------------------------------------------------------
  // General.Options.FileExtNameList
  const toml::Value *pFileExtNameList = ParseRsValue.find("General.Options.FileExtNameList");
  if (pFileExtNameList && pFileExtNameList->is<toml::Array>()) {
    this->m_pConfig->General.Options.FileExtNameList.clear();
    [](vector<string> &OutStrVect, vector<toml::Value> InputVect) {
      for (toml::Value Item : InputVect) {
        OutStrVect.push_back(Item.as<string>());
      }
    }(this->m_pConfig->General.Options.FileExtNameList, pFileExtNameList->as<toml::Array>());
  }

  // General.Options.CheckFileName
  const toml::Value *pChkFileName = ParseRsValue.find("General.Options.CheckFileName");
  if (pChkFileName && pChkFileName->is<bool>()) {
    this->m_pConfig->General.Options.bCheckFileName = pChkFileName->as<bool>();
  }

  // General.Options.CheckVariableName
  const toml::Value *pChkVarName = ParseRsValue.find("General.Options.CheckVariableName");
  if (pChkVarName && pChkVarName->is<bool>()) {
    this->m_pConfig->General.Options.bCheckVariableName = pChkVarName->as<bool>();
  }

  // General.Options.CheckFunctionName
  const toml::Value *pChkFuncName = ParseRsValue.find("General.Options.CheckFunctionName");
  if (pChkFuncName && pChkFuncName->is<bool>()) {
    this->m_pConfig->General.Options.bCheckFunctionName = pChkFuncName->as<bool>();
  }

  // General.Options.CheckEnum
  const toml::Value *pCheckEnum = ParseRsValue.find("General.Options.CheckEnum");
  if (pCheckEnum && pCheckEnum->is<bool>()) {
    this->m_pConfig->General.Options.bCheckEnum = pCheckEnum->as<bool>();
  }

  // General.Options.CheckStruct
  const toml::Value *pChkStruct = ParseRsValue.find("General.Options.CheckStruct");
  if (pChkStruct && pChkStruct->is<bool>()) {
    this->m_pConfig->General.Options.bCheckStruct = pChkStruct->as<bool>();
  }

  // General.Options.AllowedPrintResult
  const toml::Value *pAllowedPrintResult = ParseRsValue.find("General.Options.AllowedPrintResult");
  if (pAllowedPrintResult && pAllowedPrintResult->is<bool>()) {
    this->m_pConfig->General.Options.bAllowedPrintResult = pAllowedPrintResult->as<bool>();
  }

  // General.Options.AllowedWriteJsonResult
  const toml::Value *pAllowedWriteJsonResult =
      ParseRsValue.find("General.Options.AllowedWriteJsonResult");
  if (pAllowedWriteJsonResult && pAllowedWriteJsonResult->is<bool>()) {
    this->m_pConfig->General.Options.bAllowedWriteJsonResult = pAllowedWriteJsonResult->as<bool>();
  }

  // General.Options.AllowedUnderscopeChar
  const toml::Value *pAllowUnderscopeChar =
      ParseRsValue.find("General.Options.AllowedUnderscopeChar");
  if (pAllowUnderscopeChar && pAllowUnderscopeChar->is<bool>()) {
    this->m_pConfig->General.Options.bAllowedUnderscopeChar = pAllowUnderscopeChar->as<bool>();
  }

  // General.Options.AllowedArrayAffected
  const toml::Value *pAllowArrayAffected =
      ParseRsValue.find(" General.Options.AllowedArrayAffected");
  if (pAllowArrayAffected && pAllowArrayAffected->is<bool>()) {
    this->m_pConfig->General.Options.bAllowedArrayAffected = pAllowArrayAffected->as<bool>();
  }

  // ==----------------------------------------------------------------------------------
  // [General.Rules]
  // ==----------------------------------------------------------------------------------
  // General.Rules.FileName
  const toml::Value *pRuleFileName = ParseRsValue.find("General.Rules.FileName");
  if (pRuleFileName && pRuleFileName->is<int>()) {
    this->m_pConfig->General.Rules.FileName = (RULETYPE)pRuleFileName->as<int>();
  }

  // General.Rules.FunctionName
  const toml::Value *pRuleFunctionName = ParseRsValue.find("General.Rules.FunctionName");
  if (pRuleFunctionName && pRuleFunctionName->is<int>()) {
    this->m_pConfig->General.Rules.FunctionName = (RULETYPE)pRuleFunctionName->as<int>();
  }

  // General.Rules.VariableName
  const toml::Value *pRuleVariableName = ParseRsValue.find("General.Rules.VariableName");
  if (pRuleVariableName && pRuleVariableName->is<int>()) {
    this->m_pConfig->General.Rules.VariableName = (RULETYPE)pRuleVariableName->as<int>();
  }

  // General.Rules.ClassName
  const toml::Value *pRuleClassName = ParseRsValue.find("General.Rules.ClassName");
  if (pRuleClassName && pRuleClassName->is<int>()) {
    this->m_pConfig->General.Rules.ClassName = (RULETYPE)pRuleClassName->as<int>();
  }

  // General.Rules.EnumTagName
  const toml::Value *pRuleEnumTagName = ParseRsValue.find("General.Rules.EnumTagName");
  if (pRuleEnumTagName && pRuleEnumTagName->is<int>()) {
    this->m_pConfig->General.Rules.EnumTagName = (RULETYPE)pRuleEnumTagName->as<int>();
  }

  // General.Rules.EnumValueName
  const toml::Value *pRuleEnumValueName = ParseRsValue.find("General.Rules.EnumValueName");
  if (pRuleEnumValueName && pRuleEnumValueName->is<int>()) {
    this->m_pConfig->General.Rules.EnumValueName = (RULETYPE)pRuleEnumValueName->as<int>();
  }

  // General.Rules.StructTagName
  const toml::Value *pRuleStructTagName = ParseRsValue.find("General.Rules.StructTagName");
  if (pRuleStructTagName && pRuleStructTagName->is<int>()) {
    this->m_pConfig->General.Rules.StructTagName = (RULETYPE)pRuleStructTagName->as<int>();
  }

  // General.Rules.StructValueName
  const toml::Value *pRuleStructValueName = ParseRsValue.find("General.Rules.StructValueName");
  if (pRuleStructValueName && pRuleStructValueName->is<int>()) {
    this->m_pConfig->General.Rules.StructValueName = (RULETYPE)pRuleStructValueName->as<int>();
  }

  // ==----------------------------------------------------------------------------------
  // [General.IgnoredList]
  // ==----------------------------------------------------------------------------------
  // General.IgnoredList.FunctionPrefix
  const toml::Value *pIgnoredFuncPrefix = ParseRsValue.find("General.IgnoredList.FunctionPrefix");
  if (pIgnoredFuncPrefix && pIgnoredFuncPrefix->is<toml::Array>()) {
    this->m_pConfig->General.IgnoredList.FunctionPrefix.clear();
    [](vector<string> &OutStrVect, vector<toml::Value> InputVect) {
      for (toml::Value Item : InputVect) {
        OutStrVect.push_back(Item.as<string>());
      }
    }(this->m_pConfig->General.IgnoredList.FunctionPrefix, pIgnoredFuncPrefix->as<toml::Array>());
  }

  // General.IgnoredList.VariablePrefix
  const toml::Value *pIgnoredVarPrefix = ParseRsValue.find("General.IgnoredList.VariablePrefix");
  if (pIgnoredVarPrefix && pIgnoredVarPrefix->is<toml::Array>()) {
    this->m_pConfig->General.IgnoredList.VariablePrefix.clear();
    [](vector<string> &OutStrVect, vector<toml::Value> InputVect) {
      for (toml::Value Item : InputVect) {
        OutStrVect.push_back(Item.as<string>());
      }
    }(this->m_pConfig->General.IgnoredList.VariablePrefix, pIgnoredVarPrefix->as<toml::Array>());
  }

  // General.IgnoredList.EnumTagPrefix
  const toml::Value *pIgnoredEnumTagPrefix = ParseRsValue.find("General.IgnoredList.EnumTagPrefix");
  if (pIgnoredEnumTagPrefix && pIgnoredEnumTagPrefix->is<toml::Array>()) {
    this->m_pConfig->General.IgnoredList.EnumTagPrefix.clear();
    [](vector<string> &OutStrVect, vector<toml::Value> InputVect) {
      for (toml::Value Item : InputVect) {
        OutStrVect.push_back(Item.as<string>());
      }
    }(this->m_pConfig->General.IgnoredList.EnumTagPrefix, pIgnoredEnumTagPrefix->as<toml::Array>());
  }

  // General.IgnoredList.StructTagPrefix
  const toml::Value *pIgnoredStructTagPrefix =
      ParseRsValue.find("General.IgnoredList.StructTagPrefix");
  if (pIgnoredStructTagPrefix && pIgnoredStructTagPrefix->is<toml::Array>()) {
    this->m_pConfig->General.IgnoredList.StructTagPrefix.clear();
    [](vector<string> &OutStrVect, vector<toml::Value> InputVect) {
      for (toml::Value Item : InputVect) {
        OutStrVect.push_back(Item.as<string>());
      }
    }(this->m_pConfig->General.IgnoredList.StructTagPrefix,
      pIgnoredStructTagPrefix->as<toml::Array>());
  }

  // General.IgnoredList.FunctionName
  const toml::Value *pIgnoredFuncName = ParseRsValue.find("General.IgnoredList.FunctionName");
  if (pIgnoredFuncName && pIgnoredFuncName->is<toml::Array>()) {
    this->m_pConfig->General.IgnoredList.FunctionName.clear();
    [](vector<string> &OutStrVect, vector<toml::Value> InputVect) {
      for (toml::Value Item : InputVect) {
        OutStrVect.push_back(Item.as<string>());
      }
    }(this->m_pConfig->General.IgnoredList.FunctionName, pIgnoredFuncName->as<toml::Array>());
  }

  // ==----------------------------------------------------------------------------------
  // [Hungarian.Others]
  // ==----------------------------------------------------------------------------------
  // Hungarian.Others.PreferUpperCamelIfMissed
  const toml::Value *pHungarianPreferUpperCamel =
      ParseRsValue.find("Hungarian.Others.PreferUpperCamelIfMissed");
  if (pHungarianPreferUpperCamel && pHungarianPreferUpperCamel->is<bool>()) {
    this->m_pConfig->Hungarian.Others.PreferUpperCamelIfMissed =
        pHungarianPreferUpperCamel->as<bool>();
  }

  // ==----------------------------------------------------------------------------------
  // [Hungarian.ArrayList]
  // ==----------------------------------------------------------------------------------
  const toml::Value *pHungarianArrayList = ParseRsValue.find("Hungarian.ArrayList");
  if (pHungarianArrayList && pHungarianArrayList->is<toml::Table>()) {
    this->m_pConfig->Hungarian.ArrayList.clear();
    [](map<string, string> &OutStrMap, toml::Table InputTable) {
      for (toml::Table::iterator Iter = InputTable.begin(); Iter != InputTable.end(); Iter++) {
        auto Str1 = Iter->first;
        auto Str2 = Iter->second.as<string>();
        OutStrMap.insert(std::pair<string, string>(Str1, Str2));
      }
    }(this->m_pConfig->Hungarian.ArrayList, pHungarianArrayList->as<toml::Table>());
  }

  // ==----------------------------------------------------------------------------------
  // [Hungarian.NullStringList]
  // ==----------------------------------------------------------------------------------
  const toml::Value *pHungarianNullStringList = ParseRsValue.find("Hungarian.NullStringList");
  if (pHungarianNullStringList && pHungarianNullStringList->is<toml::Table>()) {
    this->m_pConfig->Hungarian.NullStringList.clear();
    [](vector<MappingPair> &OutStrMap, toml::Table InputTable) {
      for (toml::Table::iterator Iter = InputTable.begin(); Iter != InputTable.end(); Iter++) {
        auto Str1 = Iter->first;
        auto Str2 = Iter->second.as<string>();
        OutStrMap.push_back(MappingPair(Str1, Str2));
      }
    }(this->m_pConfig->Hungarian.NullStringList, pHungarianNullStringList->as<toml::Table>());
    ReformatCStringMap(this->m_pConfig->Hungarian.NullStringList);
  }

  // ==----------------------------------------------------------------------------------
  // [Hungarian.WordList]
  // ==----------------------------------------------------------------------------------
  const toml::Value *pHungarianWordList = ParseRsValue.find("Hungarian.WordList");
  if (pHungarianWordList && pHungarianWordList->is<toml::Table>()) {
    this->m_pConfig->Hungarian.WordList.clear();
    [](map<string, string> &OutStrMap, toml::Table InputTable) {
      for (toml::Table::iterator Iter = InputTable.begin(); Iter != InputTable.end(); Iter++) {
        auto Str1 = Iter->first;
        auto Str2 = Iter->second.as<string>();
        OutStrMap.insert(std::pair<string, string>(Str1, Str2));
      }
    }(this->m_pConfig->Hungarian.WordList, pHungarianWordList->as<toml::Table>());
  }

  return bStatus;
}

bool Config::Save(string DstPath) { return false; }
} // namespace namelint
