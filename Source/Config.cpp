#include <iostream>
#include <string>
#include <sys/stat.h>

#include "Common.h"
#include "Config.h"

#include "../Module/tinytoml.git/include/toml/toml.h"

namespace namelint {
Config::Config()
{
  // General
  this->m_Config.m_General.FileExtName.assign({ "*.c", "*.h", "*.cpp" });
  this->m_Config.m_General.bCheckFileName = true;
  this->m_Config.m_General.bCheckFunctionName = true;
  this->m_Config.m_General.bCheckVariableName = true;

  // Rule
  this->m_Config.m_Rule.FileName = RULETYPE::RULETYPE_DEFAULT;
  this->m_Config.m_Rule.FunctionName = RULETYPE::RULETYPE_DEFAULT;
  this->m_Config.m_Rule.VariableName = RULETYPE::RULETYPE_DEFAULT;

  // WhiteList
  this->m_Config.m_WhiteList.IgnoredFuncPrefix.assign({ "" });
  this->m_Config.m_WhiteList.VariablePrefix.assign({ "" });
}

ConfigData&
Config::GetData() const
{
  return (ConfigData&)this->m_Config;
}

bool
Config::LoadFile(string ConfigFilePath)
{
  bool bStatus = FileSystem::IsExist(ConfigFilePath);
  if (bStatus) {
    std::ifstream InputFileStream(ConfigFilePath);
    std::string Content((std::istreambuf_iterator<char>(InputFileStream)),
                        (std::istreambuf_iterator<char>()));

    bStatus = this->LoadStream(Content);
  }
  return bStatus;
}

bool
Config::LoadStream(string ConfigContent)
{
  istringstream InputStrStream = istringstream(ConfigContent);
  toml::ParseResult ParseRs = toml::parse(InputStrStream);
  bool bStatus = ParseRs.valid();
  if (bStatus) {
    const toml::Value& ParseRsValue = ParseRs.value;

    // ==----------------------------------------------------------------------------------
    // [General]
    // ==----------------------------------------------------------------------------------
    // General.FileExtName
    const toml::Value* pGeneralFileExtName =
      ParseRsValue.find("General.ListFileExtName");
    if (pGeneralFileExtName && pGeneralFileExtName->is<toml::Array>()) {
      this->m_Config.m_General.FileExtName.clear();
      [](vector<string>& OutStrVect, vector<toml::Value> InputVect) {
        for (toml::Value Item : InputVect) {
          OutStrVect.push_back(Item.as<string>());
        }
      }(this->m_Config.m_General.FileExtName,
        pGeneralFileExtName->as<toml::Array>());
    }

    // General.CheckVariableName
    const toml::Value* pGeneralCheckVariableName =
      ParseRsValue.find("General.BoolCheckVariableName");
    if (pGeneralCheckVariableName && pGeneralCheckVariableName->is<bool>()) {
      this->m_Config.m_General.bCheckVariableName =
        pGeneralCheckVariableName->as<bool>();
    }

    // General.CheckFunctionName
    const toml::Value* pGeneralCheckFunctionName =
      ParseRsValue.find("General.BoolCheckFunctionName");
    if (pGeneralCheckFunctionName && pGeneralCheckFunctionName->is<bool>()) {
      this->m_Config.m_General.bCheckFunctionName =
        pGeneralCheckFunctionName->as<bool>();
    }

    // General.CheckFileName
    const toml::Value* pGeneralCheckFileName =
      ParseRsValue.find("General.BoolCheckFileName");
    if (pGeneralCheckFileName && pGeneralCheckFileName->is<bool>()) {
      this->m_Config.m_General.bCheckFileName =
        pGeneralCheckFileName->as<bool>();
    }

    // ==----------------------------------------------------------------------------------
    // [Rule]
    // ==----------------------------------------------------------------------------------
    // Rule.FileName
    const toml::Value* pRuleFileName = ParseRsValue.find("Rule.EnumFileName");
    if (pRuleFileName && pRuleFileName->is<int>()) {
      this->m_Config.m_Rule.FileName = (RULETYPE)pRuleFileName->as<int>();
    }

    // Rule.FunctionName
    const toml::Value* pRuleFunctionName =
      ParseRsValue.find("Rule.EnumFunctionName");
    if (pRuleFunctionName && pRuleFunctionName->is<int>()) {
      this->m_Config.m_Rule.FunctionName =
        (RULETYPE)pRuleFunctionName->as<int>();
    }

    // Rule.VariableName
    const toml::Value* pRuleVariableName =
      ParseRsValue.find("Rule.EnumVariableName");
    if (pRuleVariableName && pRuleVariableName->is<int>()) {
      this->m_Config.m_Rule.VariableName =
        (RULETYPE)pRuleVariableName->as<int>();
    }

    // ==----------------------------------------------------------------------------------
    // [WhiteList]
    // ==----------------------------------------------------------------------------------
    // WhiteList.FunctionPrefix
    const toml::Value* pWhiteListFunctionPrefix =
      ParseRsValue.find("WhiteList.ListFunctionPrefix");
    if (pWhiteListFunctionPrefix &&
        pWhiteListFunctionPrefix->is<toml::Array>()) {
      this->m_Config.m_WhiteList.IgnoredFuncPrefix.clear();
      [](vector<string>& OutStrVect, vector<toml::Value> InputVect) {
        for (toml::Value Item : InputVect) {
          OutStrVect.push_back(Item.as<string>());
        }
      }(this->m_Config.m_WhiteList.IgnoredFuncPrefix,
        pWhiteListFunctionPrefix->as<toml::Array>());
    }

    // WhiteList.VariablePrefix
    const toml::Value* pWhiteListVariablePrefix =
      ParseRsValue.find("WhiteList.ListVariablePrefix");
    if (pWhiteListVariablePrefix &&
        pWhiteListVariablePrefix->is<toml::Array>()) {
      this->m_Config.m_WhiteList.VariablePrefix.clear();
      [](vector<string>& OutStrVect, vector<toml::Value> InputVect) {
        for (toml::Value Item : InputVect) {
          OutStrVect.push_back(Item.as<string>());
        }
      }(this->m_Config.m_WhiteList.VariablePrefix,
        pWhiteListVariablePrefix->as<toml::Array>());
    }

    // WhiteList.IgnoreFunctions
    const toml::Value* pWhiteListIgnoreFunctions =
      ParseRsValue.find("WhiteList.ListIgnoreFunctions");
    if (pWhiteListIgnoreFunctions &&
        pWhiteListIgnoreFunctions->is<toml::Array>()) {
      this->m_Config.m_WhiteList.IgnoredFuncName.clear();
      [](vector<string>& OutStrVect, vector<toml::Value> InputVect) {
        for (toml::Value Item : InputVect) {
          OutStrVect.push_back(Item.as<string>());
        }
      }(this->m_Config.m_WhiteList.IgnoredFuncName,
        pWhiteListIgnoreFunctions->as<toml::Array>());
    }

    // WhiteList.BoolAllowedUnderscopeChar
    const toml::Value* pWhiteListBoolAllowedUnderscopeChar =
      ParseRsValue.find("WhiteList.BoolAllowedUnderscopeChar");
    if (pWhiteListBoolAllowedUnderscopeChar &&
        pWhiteListBoolAllowedUnderscopeChar->is<bool>()) {
      this->m_Config.m_WhiteList.bAllowedEndWithUnderscope =
        pWhiteListBoolAllowedUnderscopeChar->as<bool>();
    }

    // ==----------------------------------------------------------------------------------
    // [HungarianListEx]
    // ==----------------------------------------------------------------------------------
    const toml::Value* pHungarianListEx = ParseRsValue.find("HungarianListEx");
    if (pHungarianListEx && pHungarianListEx->is<toml::Table>()) {
      this->m_Config.m_HungarianListEx.MappedTable.clear();
      [](map<string, string>& OutStrMap, toml::Table InputTable) {
        for (toml::Table::iterator Iter = InputTable.begin();
             Iter != InputTable.end();
             Iter++) {
          auto Str1 = Iter->first;
          auto Str2 = Iter->second.as<string>();
          OutStrMap.insert(std::pair<string, string>(Str1, Str2));
        }
      }(this->m_Config.m_HungarianListEx.MappedTable,
        pHungarianListEx->as<toml::Table>());
    }

    // ==----------------------------------------------------------------------------------
    // [HungarianList]
    // ==----------------------------------------------------------------------------------
    const toml::Value* pHungarianList = ParseRsValue.find("HungarianList");
    if (pHungarianList && pHungarianList->is<toml::Table>()) {
      this->m_Config.m_HungarianList.MappedTable.clear();
      [](map<string, string>& OutStrMap, toml::Table InputTable) {
        for (toml::Table::iterator Iter = InputTable.begin();
             Iter != InputTable.end();
             Iter++) {
          auto Str1 = Iter->first;
          auto Str2 = Iter->second.as<string>();
          OutStrMap.insert(std::pair<string, string>(Str1, Str2));
        }
      }(this->m_Config.m_HungarianList.MappedTable,
        pHungarianList->as<toml::Table>());
    }
  }

  return bStatus;
}

bool
Config::Save(string DstPath)
{
  return false;
}
} // namespace namelint