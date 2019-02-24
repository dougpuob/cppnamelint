#include <gtest/gtest.h>
#include <numeric>
#include <vector>

#include "../Config.h"

using namespace namelint;

namespace TargetIsGeneral {

TEST(General, Default)
{
  Config config;

  //
  // General
  //
  std::vector<string>* pVect = &config.GetData().m_General.FileExtName;
  EXPECT_EQ(true, 3 == pVect->size());
  EXPECT_EQ(true,
            pVect->end() != std::find(pVect->begin(), pVect->end(), "*.c"));
  EXPECT_EQ(true,
            pVect->end() != std::find(pVect->begin(), pVect->end(), "*.h"));
  EXPECT_EQ(true,
            pVect->end() != std::find(pVect->begin(), pVect->end(), "*.cpp"));

  //
  // Rule
  //
  Rule* pRule = &config.GetData().m_Rule;
  EXPECT_EQ(RULETYPE::RULETYPE_DEFAULT, pRule->FileName);
  EXPECT_EQ(RULETYPE::RULETYPE_DEFAULT, pRule->FunctionName);
  EXPECT_EQ(RULETYPE::RULETYPE_DEFAULT, pRule->VariableName);

  //
  // WhiteList
  //
  WhiteList* pWhiteList = &config.GetData().m_WhiteList;
  EXPECT_EQ(1, pWhiteList->FunctionPrefix.size());
  EXPECT_EQ(1, pWhiteList->VariablePrefix.size());
}

TEST(General, Fake_General)
{
  string content = "\
	[General] \r\n\
		ListFileExtName  = [\"*.a\",\"*.b\",\"*.c\",\"*.d\"] \r\n\
		BoolCheckVariableName = false \r\n\
		BoolCheckFunctionName = false \r\n\
		BoolCheckFileName	  = false \r\n\
	";

  Config config;
  bool bStatus = config.LoadStream(content);
  EXPECT_EQ(true, bStatus);

  General* pGeneral = &config.GetData().m_General;
  std::vector<string>* pVect = &pGeneral->FileExtName;
  EXPECT_EQ(true, 4 == pVect->size());
  EXPECT_EQ(true,
            pVect->end() != std::find(pVect->begin(), pVect->end(), "*.a"));
  EXPECT_EQ(true,
            pVect->end() != std::find(pVect->begin(), pVect->end(), "*.b"));
  EXPECT_EQ(true,
            pVect->end() != std::find(pVect->begin(), pVect->end(), "*.c"));
  EXPECT_EQ(true,
            pVect->end() != std::find(pVect->begin(), pVect->end(), "*.d"));

  EXPECT_EQ(true, false == pGeneral->bCheckFileName);
  EXPECT_EQ(true, false == pGeneral->bCheckFunctionName);
  EXPECT_EQ(true, false == pGeneral->bCheckVariableName);
}

TEST(General, Fake_Rule)
{
  string content = "\
	[Rule] \r\n\
		EnumFileName 	 = 3 \r\n\
		EnumFunctionName = 3 \r\n\
		EnumVariableName = 4 \r\n\
	";

  Config config;
  bool bStatus = config.LoadStream(content);
  EXPECT_EQ(true, bStatus);

  Rule* pRule = &config.GetData().m_Rule;
  EXPECT_EQ(RULETYPE::RULETYPE_LOWER_SEPERATED, pRule->FileName);
  EXPECT_EQ(RULETYPE::RULETYPE_LOWER_SEPERATED, pRule->FunctionName);
  EXPECT_EQ(RULETYPE::RULETYPE_HUNGARIAN, pRule->VariableName);
}

TEST(General, Fake_WhiteList)
{
  string content = "\
	[WhiteList] \r\n\
		ListFunctionPrefix 	 = [ \"_\", \"__\" ]    \r\n\
		ListVariablePrefix 	 = [ \"m_\", \"g_\" ]   \r\n\
		BoolAllowedUnderscopeChar = true            \r\n\
	";

  Config config;
  bool bStatus = config.LoadStream(content);
  EXPECT_EQ(true, bStatus);

  WhiteList* pWhiteList = &config.GetData().m_WhiteList;

  EXPECT_EQ(true, 2 == pWhiteList->FunctionPrefix.size());
  EXPECT_EQ(true,
            pWhiteList->FunctionPrefix.end() !=
              std::find(pWhiteList->FunctionPrefix.begin(),
                        pWhiteList->FunctionPrefix.end(),
                        "_"));
  EXPECT_EQ(true,
            pWhiteList->FunctionPrefix.end() !=
              std::find(pWhiteList->FunctionPrefix.begin(),
                        pWhiteList->FunctionPrefix.end(),
                        "__"));

  EXPECT_EQ(true, 2 == pWhiteList->FunctionPrefix.size());
  EXPECT_EQ(true,
            pWhiteList->VariablePrefix.end() !=
              std::find(pWhiteList->VariablePrefix.begin(),
                        pWhiteList->VariablePrefix.end(),
                        "m_"));
  EXPECT_EQ(true,
            pWhiteList->VariablePrefix.end() !=
              std::find(pWhiteList->VariablePrefix.begin(),
                        pWhiteList->VariablePrefix.end(),
                        "g_"));

  EXPECT_EQ(true, pWhiteList->bAllowedUnderscopeChar);
}

} // namespace TargetIsGeneral