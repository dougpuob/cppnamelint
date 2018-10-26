#include <sys/stat.h>
#include <iostream>
#include <string>

#include "Common.h"
#include "Config.h"

#include "../Module/tinytoml.git/include/toml/toml.h"

namespace namelint {
Config::Config()
{
    // General
    this->m_Config.General.FileExtName.assign({"*.c", "*.cpp", "*.cc"});
    this->m_Config.General.bCheckFileName     = true;
    this->m_Config.General.bCheckFunctionName = true;
    this->m_Config.General.bCheckVariableName = true;

    // Rule
    this->m_Config.Rule.FileName     = RULETYPE::RULETYPE_DEFAULT;
    this->m_Config.Rule.FunctionName = RULETYPE::RULETYPE_DEFAULT;
    this->m_Config.Rule.VariableName = RULETYPE::RULETYPE_DEFAULT;

    // WhiteList
    this->m_Config.WhiteList.FunctionPrefix.assign({""});
    this->m_Config.WhiteList.VariablePrefix.assign({""});
}

ConfigData &Config::GetData() const { return (ConfigData &)this->m_Config; }

bool Config::Load(string SrcPath)
{
    if (!FileSystem::IsFileExist(SrcPath))
    {
        return false;
    }

    toml::ParseResult pr = toml::parseFile(SrcPath);
    bool bStatus         = pr.valid();
    if (bStatus)
    {
        const toml::Value &value = pr.value;

        // ==----------------------------------------------------------------------------------
        // [General]
        // ==----------------------------------------------------------------------------------
        // General.FileExtName
        const toml::Value *pGeneral_FileExtName = value.find("General.FileExtName");
        if (pGeneral_FileExtName && pGeneral_FileExtName->is<toml::Array>())
        {
            this->m_Config.General.FileExtName.clear();
            [](vector<string> &OutStrVect, vector<toml::Value> InputVect) {
                for (toml::Value value : InputVect)
                {
                    OutStrVect.push_back(value.as<string>());
                }
            }(this->m_Config.General.FileExtName, pGeneral_FileExtName->as<toml::Array>());
        }

        // General.FileExtName
        const toml::Value *pGeneral_CheckVariableName = value.find("General.CheckVariableName");
        if (pGeneral_CheckVariableName && pGeneral_CheckVariableName->is<bool>())
        {
            this->m_Config.General.bCheckVariableName = pGeneral_CheckVariableName->as<bool>();
        }

        // General.CheckFunctionName
        const toml::Value *pGeneral_CheckFunctionName = value.find("General.CheckFunctionName");
        if (pGeneral_CheckFunctionName && pGeneral_CheckFunctionName->is<bool>())
        {
            this->m_Config.General.bCheckVariableName = pGeneral_CheckFunctionName->as<bool>();
        }

        // General.CheckFileName
        const toml::Value *pGeneral_CheckFileName = value.find("General.CheckFileName");
        if (pGeneral_CheckFileName && pGeneral_CheckFileName->is<bool>())
        {
            this->m_Config.General.bCheckVariableName = pGeneral_CheckFileName->as<bool>();
        }

        // ==----------------------------------------------------------------------------------
        // [Rule]
        // ==----------------------------------------------------------------------------------
        // Rule.FileName
        const toml::Value *pRule_FileName = value.find("Rule.FileName");
        if (pRule_FileName && pRule_FileName->is<int>())
        {
            this->m_Config.Rule.FileName = (RULETYPE)pRule_FileName->as<int>();
        }  // Rule.FunctionName
        const toml::Value *pRule_FunctionName = value.find("Rule.FunctionName");
        if (pRule_FunctionName && pRule_FunctionName->is<int>())
        {
            this->m_Config.Rule.FunctionName = (RULETYPE)pRule_FunctionName->as<int>();
        }  // Rule.VariableName
        const toml::Value *pRule_VariableName = value.find("Rule.VariableName");
        if (pRule_VariableName && pRule_VariableName->is<int>())
        {
            this->m_Config.Rule.VariableName = (RULETYPE)pRule_VariableName->as<int>();
        }

        // ==----------------------------------------------------------------------------------
        // [WhiteList]
        // ==----------------------------------------------------------------------------------
        // WhiteList.FunctionPrefix
        const toml::Value *pWhiteList_FunctionPrefix = value.find("WhiteList.FunctionPrefix");
        if (pWhiteList_FunctionPrefix && pWhiteList_FunctionPrefix->is<toml::Array>())
        {
            this->m_Config.WhiteList.FunctionPrefix.clear();
            [](vector<string> &OutStrVect, vector<toml::Value> InputVect) {
                for (toml::Value value : InputVect)
                {
                    OutStrVect.push_back(value.as<string>());
                }
            }(this->m_Config.WhiteList.FunctionPrefix, pWhiteList_FunctionPrefix->as<toml::Array>());
        }

        // WhiteList.VariablePrefix
        const toml::Value *pWhiteList_VariablePrefix = value.find("WhiteList.VariablePrefix");
        if (pWhiteList_VariablePrefix && pWhiteList_VariablePrefix->is<toml::Array>())
        {
            this->m_Config.WhiteList.VariablePrefix.clear();
            [](vector<string> &OutStrVect, vector<toml::Value> InputVect) {
                for (toml::Value value : InputVect)
                {
                    OutStrVect.push_back(value.as<string>());
                }
            }(this->m_Config.WhiteList.VariablePrefix, pWhiteList_VariablePrefix->as<toml::Array>());
        }

        // ==----------------------------------------------------------------------------------
        // [HungarianList]
        // ==----------------------------------------------------------------------------------
        const toml::Value *pHungarianList = value.find("HungarianList");
        if (pHungarianList && pHungarianList->is<toml::Table>())
        {
            this->m_Config.HungarianList.MappedTable.clear();
            [](map<string, string> &OutStrMap, toml::Table InputTable) {
                for (toml::Table::iterator iter = InputTable.begin(); iter != InputTable.end(); iter++)
                {
                    auto str1 = iter->first;
                    auto str2 = iter->second.as<string>();
                    OutStrMap.insert(std::pair<string, string>(str1, str2));
                }
            }(this->m_Config.HungarianList.MappedTable, pHungarianList->as<toml::Table>());
        }
    }

    return true;
}

bool Config::Save(string DstPath) { return false; }
}  // namespace namelint