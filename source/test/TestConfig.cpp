#include <algorithm>
#include <numeric>
#include <vector>

#include <gtest/gtest.h>

#include "../Config.h"

using namespace namelint;

// clang-format off

namespace TargetIsGeneral {

TEST(GeneralOptions, Default) {
  Config MyConfig;

  //
  // General
  //
  std::vector<string> *pVect =
      &MyConfig.GetData()->General.Options.FileExtNameList;
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
  GeneralRules *pRule = &MyConfig.GetData()->General.Rules;
  EXPECT_EQ(RULETYPE::RULETYPE_DEFAULT, pRule->FileName);
  EXPECT_EQ(RULETYPE::RULETYPE_DEFAULT, pRule->FunctionName);
  EXPECT_EQ(RULETYPE::RULETYPE_DEFAULT, pRule->VariableName);
}

TEST(GeneralOptions, Chk_GeneralOptions) {
  string content = "\
	[General.Options] \r\n\
		FileExtNameList  = [\"*.a\",\"*.b\",\"*.c\",\"*.d\"] \r\n\
		CheckVariableName = false \r\n\
		CheckFunctionName = false \r\n\
		CheckFileName	  = false \r\n\
	";

  Config MyConfig;
  string errorReason;
  bool bStatus = MyConfig.LoadStream(content, errorReason);
  EXPECT_EQ(true, bStatus);

  GeneralOptions *pGeneral = &MyConfig.GetData()->General.Options;
  std::vector<string> *pVect = &pGeneral->FileExtNameList;
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

TEST(GeneralOptions, Chk_GeneralRules) {
  string content = "\
	[General.Rules] \r\n\
		FileName 	 = 3 \r\n\
		FunctionName = 3 \r\n\
		VariableName = 4 \r\n";

  Config MyConfig;
  string errorReason;
  bool bStatus = MyConfig.LoadStream(content, errorReason);
  // EXPECT_EQ(true, bStatus);

  // GeneralRules *pRule = &MyConfig.GetData()->General.Rules;
  // EXPECT_EQ(RULETYPE::RULETYPE_LOWER_SNAKE , pRule->FileName);
  // EXPECT_EQ(RULETYPE::RULETYPE_LOWER_SNAKE , pRule->FunctionName);
  // EXPECT_EQ(RULETYPE::RULETYPE_HUNGARIAN   , pRule->VariableName);
}

TEST(GeneralOptions, Fake_WhiteList) {
  string content = "\
	[General.IgnoredList] \r\n\
		FunctionPrefix 	 = [ \"_\", \"__\" ]    \r\n\
		VariablePrefix 	 = [ \"m_\", \"g_\" ]";

  Config MyConfig;
  string errorReason;
  bool bStatus = MyConfig.LoadStream(content, errorReason);
  EXPECT_EQ(true, bStatus);

  GeneralIgnoredList *pIgnoredList = &MyConfig.GetData()->General.IgnoredList;

  EXPECT_EQ(true, 2 == pIgnoredList->FunctionPrefix.size());
  EXPECT_EQ(true, pIgnoredList->FunctionPrefix.end() !=
                      std::find(pIgnoredList->FunctionPrefix.begin(),
                                pIgnoredList->FunctionPrefix.end(), "_"));
  EXPECT_EQ(true, pIgnoredList->FunctionPrefix.end() !=
                      std::find(pIgnoredList->FunctionPrefix.begin(),
                                pIgnoredList->FunctionPrefix.end(), "__"));

  EXPECT_EQ(true, 2 == pIgnoredList->FunctionPrefix.size());
  EXPECT_EQ(true, pIgnoredList->VariablePrefix.end() !=
                      std::find(pIgnoredList->VariablePrefix.begin(),
                                pIgnoredList->VariablePrefix.end(), "m_"));
  EXPECT_EQ(true, pIgnoredList->VariablePrefix.end() !=
                      std::find(pIgnoredList->VariablePrefix.begin(),
                                pIgnoredList->VariablePrefix.end(), "g_"));
}

} // namespace TargetIsGeneral

// clang-format on