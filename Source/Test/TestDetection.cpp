#include <gtest/gtest.h>
#include <numeric>
#include <vector>

#include "../Config.h"
#include "../Detection.h"

using namespace namelint;

// clang-format off
//==-------------------------------------------------------------------------==
// Detection.CheckFile()
//==-------------------------------------------------------------------------==
namespace TargetIsFile {

// Input Parameters
TEST(Config_Detect_CheckFile, InputParms_Good)
{
    Detection Detect;
    EXPECT_EQ(true, Detect.CheckFile(RULETYPE_DEFAULT           , "TestName.cpp"));
    EXPECT_EQ(true, Detect.CheckFile(RULETYPE_UPPER_CAMEL		, "TestName.cpp"));
    EXPECT_EQ(true, Detect.CheckFile(RULETYPE_LOWER_CAMEL		, "testName.cpp"));
    EXPECT_EQ(true, Detect.CheckFile(RULETYPE_LOWER_SNAKE   , "test_name.cpp"));
}

TEST(Config_Detect_CheckFile, InputParms_Bad)
{
    Detection Detect;
    EXPECT_EQ(false, Detect.CheckFile(RULETYPE_DEFAULT          , ""));
    EXPECT_EQ(false, Detect.CheckFile(RULETYPE_UPPER_CAMEL		, ""));
    EXPECT_EQ(false, Detect.CheckFile(RULETYPE_LOWER_CAMEL		, ""));
    EXPECT_EQ(false, Detect.CheckFile(RULETYPE_LOWER_SNAKE  , ""));
    EXPECT_EQ(false, Detect.CheckFile(RULETYPE_HUNGARIAN        , "AnyName.cpp"));
}

//-------------------------------------------------------------------------
// UpperCamelCase
TEST(Config_Detect_CheckFile, UpperCamelCase_Good)
{
    Detection Detect;
    const RULETYPE RuleType = RULETYPE_UPPER_CAMEL;

    EXPECT_EQ(true, Detect.CheckFile(RuleType, "TestName"));
    EXPECT_EQ(true, Detect.CheckFile(RuleType, "TestName.h"));
    EXPECT_EQ(true, Detect.CheckFile(RuleType, "TestName.H"));
    EXPECT_EQ(true, Detect.CheckFile(RuleType, "TestName.cpp"));
    EXPECT_EQ(true, Detect.CheckFile(RuleType, "TestName.CPP"));
}

TEST(Config_Detect_CheckFile, UpperCamelCase_Bad)
{
    Detection Detect;
    const RULETYPE RuleType = RULETYPE_UPPER_CAMEL;

    EXPECT_EQ(false, Detect.CheckFile(RuleType, "testName"));
    EXPECT_EQ(false, Detect.CheckFile(RuleType, "testName.h"));
    EXPECT_EQ(false, Detect.CheckFile(RuleType, "testName.cpp"));
}

//-------------------------------------------------------------------------
// LowerCamelCase
TEST(Config_Detect_CheckFile, LowerCamelCase_Good)
{
    Detection Detect;
    const RULETYPE RuleType = RULETYPE_LOWER_CAMEL;

    EXPECT_EQ(true, Detect.CheckFile(RuleType, "testName"));
    EXPECT_EQ(true, Detect.CheckFile(RuleType, "testName.h"));
    EXPECT_EQ(true, Detect.CheckFile(RuleType, "testName.H"));
    EXPECT_EQ(true, Detect.CheckFile(RuleType, "testName.cpp"));
    EXPECT_EQ(true, Detect.CheckFile(RuleType, "testName.CPP"));
}

TEST(Config_Detect_CheckFile, LowerCamelCase_Bad)
{
    Detection Detect;
    const RULETYPE RuleType = RULETYPE_LOWER_CAMEL;

    EXPECT_EQ(false, Detect.CheckFile(RuleType, "TestName"));
    EXPECT_EQ(false, Detect.CheckFile(RuleType, "TestName.h"));
    EXPECT_EQ(false, Detect.CheckFile(RuleType, "TestName.cpp"));
}

//-------------------------------------------------------------------------
// LowerSeperate
TEST(Config_Detect_CheckFile, LowerSeperated_Good)
{
    Detection Detect;
    const RULETYPE RuleType = RULETYPE_LOWER_SNAKE;

    EXPECT_EQ(true, Detect.CheckFile(RuleType, "testname.h"));
    EXPECT_EQ(true, Detect.CheckFile(RuleType, "testname_.h"));
    EXPECT_EQ(true, Detect.CheckFile(RuleType, "test_name.h"));
    EXPECT_EQ(true, Detect.CheckFile(RuleType, "test_name.cpp"));
    EXPECT_EQ(true, Detect.CheckFile(RuleType, "test_name_.cpp"));
}

TEST(Config_Detect_CheckFile, LowerSeperated_Bad)
{
    Detection Detect;
    const RULETYPE RuleType = RULETYPE_LOWER_SNAKE;

    EXPECT_EQ(false, Detect.CheckFile(RuleType, "lowername.CPP"));
    EXPECT_EQ(false, Detect.CheckFile(RuleType, "lowerName.cpp"));
    EXPECT_EQ(false, Detect.CheckFile(RuleType, "testName.cpp"));
    EXPECT_EQ(false, Detect.CheckFile(RuleType, "test_Name.cpp"));
    EXPECT_EQ(false, Detect.CheckFile(RuleType, "tesT_name.cpp"));
    EXPECT_EQ(false, Detect.CheckFile(RuleType, "tesT_Name_.cpp"));
}
}  // namespace CheckFile

//==-------------------------------------------------------------------------==
// Detection.CheckFunction()
//==-------------------------------------------------------------------------==
namespace TargetIsFunction {

 // Input Parameter
TEST(Config_Detect_CheckFunction, InputParms_Good)
{
	RuleOfFunction Rule;
	Rule.bAllowedEndWithUnderscopeChar = false;
	Rule.IgnoreNames.clear();
	Rule.IgnorePrefixs.clear();

    Detection Detect;
	Detect.ApplyRuleForFunction(Rule);
    EXPECT_EQ(true, Detect.CheckFunction(RULETYPE_DEFAULT           , "MyFunc"	));
    EXPECT_EQ(true, Detect.CheckFunction(RULETYPE_UPPER_CAMEL		, "MyFunc"	));
    EXPECT_EQ(true, Detect.CheckFunction(RULETYPE_LOWER_CAMEL		, "myFunc"	));
    EXPECT_EQ(true, Detect.CheckFunction(RULETYPE_LOWER_SNAKE   , "my_func"	));

	Rule.bAllowedEndWithUnderscopeChar = true;
	Detect.ApplyRuleForFunction(Rule);
	EXPECT_EQ(true, Detect.CheckFunction(RULETYPE_UPPER_CAMEL		, "My_Func"		));
	EXPECT_EQ(true, Detect.CheckFunction(RULETYPE_UPPER_CAMEL		, "My__Func"	));
	EXPECT_EQ(true, Detect.CheckFunction(RULETYPE_UPPER_CAMEL		, "My_Func_A"	));
	EXPECT_EQ(true, Detect.CheckFunction(RULETYPE_UPPER_CAMEL		, "My__Func_B"	));
}

TEST(Config_Detect_CheckFunction, InputParms_Bad)
{
	RuleOfFunction Rule;
	Rule.bAllowedEndWithUnderscopeChar = false;
	Rule.IgnoreNames.clear();
	Rule.IgnorePrefixs.clear();

	Detection Detect;
	Detect.ApplyRuleForFunction(Rule);
    EXPECT_EQ(false, Detect.CheckFunction(RULETYPE_DEFAULT          , ""		));
    EXPECT_EQ(false, Detect.CheckFunction(RULETYPE_UPPER_CAMEL		, ""		));
    EXPECT_EQ(false, Detect.CheckFunction(RULETYPE_LOWER_CAMEL		, ""        ));
    EXPECT_EQ(false, Detect.CheckFunction(RULETYPE_LOWER_SNAKE  , ""        ));
    EXPECT_EQ(false, Detect.CheckFunction(RULETYPE_HUNGARIAN        , "AnyName" ));
}

//-------------------------------------------------------------------------
// UpperCamelCase
TEST(Config_Detect_CheckFunction, UpperCamelCase_Good)
{
	RuleOfFunction Rule;
	Detection Detect;
	Detect.ApplyRuleForFunction(Rule);

    const RULETYPE RuleType = RULETYPE_UPPER_CAMEL;
    EXPECT_EQ(true, Detect.CheckFunction(RuleType, "UpperCamelFuncName"	));
    EXPECT_EQ(true, Detect.CheckFunction(RuleType, "UpperCamelFuncName1"));

	Rule.bAllowedEndWithUnderscopeChar = false;
	Rule.IgnoreNames.push_back("main");
	Rule.IgnorePrefixs.push_back("_");
	Rule.IgnorePrefixs.push_back("__");
	Rule.IgnorePrefixs.push_back("XXX_");
	Detect.ApplyRuleForFunction(Rule);
    EXPECT_EQ(true, Detect.CheckFunction(RuleType, "_UpperCamelFuncName"    ));
    EXPECT_EQ(true, Detect.CheckFunction(RuleType, "__UpperCamelFuncName"   ));
    EXPECT_EQ(true, Detect.CheckFunction(RuleType, "XXX_UpperCamelFuncName" ));
	EXPECT_EQ(true, Detect.CheckFunction(RuleType, "MyFunc3"				));
	EXPECT_EQ(true, Detect.CheckFunction(RuleType, "main"                   ));

	Rule.bAllowedEndWithUnderscopeChar = true;
	Detect.ApplyRuleForFunction(Rule);
	EXPECT_EQ(true, Detect.CheckFunction(RuleType, "_UpperCamelFuncName_AB"	));
	EXPECT_EQ(true, Detect.CheckFunction(RuleType, "main"                   ));
    EXPECT_EQ(true, Detect.CheckFunction(RuleType, "MyFunc3"                ));
    EXPECT_EQ(true, Detect.CheckFunction(RuleType, "MyFunc_3"               ));
}

TEST(Config_Detect_CheckFunction, UpperCamelCase_Bad)
{
	const RULETYPE RuleType = RULETYPE_UPPER_CAMEL;

	RuleOfFunction Rule;
	Detection Detect;
	Detect.ApplyRuleForFunction(Rule);
    EXPECT_EQ(false, Detect.CheckFunction(RuleType, "UpperCamelFuncName_"   ));
    EXPECT_EQ(false, Detect.CheckFunction(RuleType, "Upper_CamelFuncName"   ));
    EXPECT_EQ(false, Detect.CheckFunction(RuleType, "upperCamelFuncName"    ));
    EXPECT_EQ(false, Detect.CheckFunction(RuleType, "_UpperCamelFuncName"   ));
    EXPECT_EQ(false, Detect.CheckFunction(RuleType, "UpperCamelFuncName_AB" ));
}

//-------------------------------------------------------------------------
// LowerCamelCase
TEST(Config_Detect_CheckFunction, LowerCamelCase_Good)
{
    const RULETYPE RuleType = RULETYPE_LOWER_CAMEL;

	RuleOfFunction Rule;
	Detection Detect;
	Detect.ApplyRuleForFunction(Rule);
    EXPECT_EQ(true, Detect.CheckFunction(RuleType, "lowerCamelFuncName"    ));
    EXPECT_EQ(true, Detect.CheckFunction(RuleType, "lower_CamelFuncName"   ));
    EXPECT_EQ(true, Detect.CheckFunction(RuleType, "lowerCamelFuncName_"   ));
    EXPECT_EQ(true, Detect.CheckFunction(RuleType, "lowerCamelFuncName1"   ));
}

TEST(Config_Detect_CheckFunction, LowerCamelCase_Bad)
{
    const RULETYPE RuleType = RULETYPE_LOWER_CAMEL;

	RuleOfFunction Rule;
	Detection Detect;
	Detect.ApplyRuleForFunction(Rule);
    EXPECT_EQ(false, Detect.CheckFunction(RuleType, "LowerCamelFuncName"   ));
    EXPECT_EQ(false, Detect.CheckFunction(RuleType, "_LowerCamelFuncName"  ));
}

//-------------------------------------------------------------------------
// LowerSeperated
TEST(Config_Detect_CheckFunction, LowerSeperatedCase_Good)
{
    const RULETYPE RuleType = RULETYPE_LOWER_SNAKE;

	RuleOfFunction Rule;
	Detection Detect;
	Detect.ApplyRuleForFunction(Rule);
    EXPECT_EQ(true, Detect.CheckFunction(RuleType, "lower_separated_funcname"   ));
    EXPECT_EQ(true, Detect.CheckFunction(RuleType, "lower_separated_funcname_"  ));
    EXPECT_EQ(true, Detect.CheckFunction(RuleType, "lower__separated__funcname" ));
    EXPECT_EQ(true, Detect.CheckFunction(RuleType, "lower_separated_funcname__" ));
    EXPECT_EQ(true, Detect.CheckFunction(RuleType, "lowerseparatedfuncname"     ));
}

TEST(Config_Detect_CheckFunction, LowerSeperatedCase_Bad)
{
    const RULETYPE RuleType = RULETYPE_LOWER_SNAKE;

	RuleOfFunction Rule;
	Detection Detect;
	Detect.ApplyRuleForFunction(Rule);
    EXPECT_EQ(false, Detect.CheckFunction(RuleType, "lowerSeparatedFuncName"	));
}
}  // namespace CheckFunction


//==-------------------------------------------------------------------------==
// Detection.CheckVariable()
//==-------------------------------------------------------------------------==
namespace TargetIsVariable {

// Input Parameter
TEST(Config_Detect_CheckVariable, InputParms_Good)
{
	RuleOfVariable Rule;
    Detection Detect;
	Rule.TypeNamingMap.insert(std::pair<string, string>("int"    , "i"));
	Rule.TypeNamingMap.insert(std::pair<string, string>("uin8_t" , "u8"));
	Rule.TypeNamingMap.insert(std::pair<string, string>("uin16_t", "u16"));

	bool bIsPtr   = false;
	bool bIsArray = false;
	Detect.ApplyRuleForVariable(Rule);
    EXPECT_EQ(true, Detect.CheckVariable(RULETYPE_DEFAULT		, "uin8_t"  , "MyFunc"    , bIsPtr, bIsArray));
    EXPECT_EQ(true, Detect.CheckVariable(RULETYPE_UPPER_CAMEL	, "uin8_t"  , "MyFunc"    , bIsPtr, bIsArray));
    EXPECT_EQ(true, Detect.CheckVariable(RULETYPE_LOWER_CAMEL	, "uin8_t"  , "myFunc"    , bIsPtr, bIsArray));
    EXPECT_EQ(true, Detect.CheckVariable(RULETYPE_LOWER_SNAKE	, "uin8_t"  , "my_func"   , bIsPtr, bIsArray));
    EXPECT_EQ(true, Detect.CheckVariable(RULETYPE_HUNGARIAN		, "int"     , "iMyFunc"   , bIsPtr, bIsArray));
    EXPECT_EQ(true, Detect.CheckVariable(RULETYPE_HUNGARIAN		, "uin8_t"  , "u8MyFunc"  , bIsPtr, bIsArray));
    EXPECT_EQ(true, Detect.CheckVariable(RULETYPE_HUNGARIAN		, "uin16_t" , "u16MyFunc" , bIsPtr, bIsArray));

	Rule.IgnorePrefixs.push_back("m_");
	Detect.ApplyRuleForVariable(Rule);
    EXPECT_EQ(true, Detect.CheckVariable(RULETYPE_HUNGARIAN		, "int"     , "m_iMyFunc" , bIsPtr, bIsArray));
}

TEST(Config_Detect_CheckVariable, InputParms_Bad)
{
	RuleOfVariable Rule;
	Detection Detect;

	Rule.TypeNamingMap.insert(std::pair<string, string>("uin8_t", "u8"));
	Rule.TypeNamingMap.insert(std::pair<string, string>("uin16_t", "u16"));

	bool bIsPtr = false;
	bool bIsArray = false;
	Detect.ApplyRuleForVariable(Rule);
    EXPECT_EQ(false, Detect.CheckVariable(RULETYPE_DEFAULT		, "uin8_t"  , ""            , bIsPtr, bIsArray));
    EXPECT_EQ(false, Detect.CheckVariable(RULETYPE_UPPER_CAMEL	, "uin8_t"  , ""            , bIsPtr, bIsArray));
    EXPECT_EQ(false, Detect.CheckVariable(RULETYPE_LOWER_CAMEL	, "uin8_t"  , ""            , bIsPtr, bIsArray));
    EXPECT_EQ(false, Detect.CheckVariable(RULETYPE_LOWER_SNAKE	, "uin8_t"  , ""            , bIsPtr, bIsArray));
    EXPECT_EQ(false, Detect.CheckVariable(RULETYPE_LOWER_CAMEL	, "uin8_t"  , ""			, bIsPtr, bIsArray));
    EXPECT_EQ(false, Detect.CheckVariable(RULETYPE_HUNGARIAN	, "uin8_t"  , "u8my_name"   , bIsPtr, bIsArray));
    EXPECT_EQ(false, Detect.CheckVariable(RULETYPE_HUNGARIAN	, "uin8_t"  , "u8my_Name"   , bIsPtr, bIsArray));
    EXPECT_EQ(false, Detect.CheckVariable(RULETYPE_HUNGARIAN	, "uin8_t"  , "u8my_Name"   , bIsPtr, bIsArray));
    EXPECT_EQ(false, Detect.CheckVariable(RULETYPE_HUNGARIAN	, "uin8_t"  , "u16AnyName"  , bIsPtr, bIsArray));
    EXPECT_EQ(false, Detect.CheckVariable(RULETYPE_HUNGARIAN	, "uin16_t" , "u8AnyName"   , bIsPtr, bIsArray));
    EXPECT_EQ(false, Detect.CheckVariable(RULETYPE_HUNGARIAN	, "uin8_t"  , "u8_my_func"  , bIsPtr, bIsArray));
    EXPECT_EQ(false, Detect.CheckVariable(RULETYPE_HUNGARIAN	, "uin16_t" , "u16_my_func" , bIsPtr, bIsArray));
}

//-------------------------------------------------------------------------
// Multiple Cases
TEST(Config_Detect_CheckVariable, GoodCases)
{
	const RULETYPE RuleType = RULETYPE_UPPER_CAMEL;

	RuleOfVariable Rule;
	Detection Detect;

	Rule.TypeNamingMap.insert(std::pair<string, string>("uin8_t", "u8"));

	bool bIsPtr = false;
	bool bIsArray = false;
	Detect.ApplyRuleForVariable(Rule);
    EXPECT_EQ(true, Detect.CheckVariable(RULETYPE_DEFAULT		, "uin8_t", "MyFunc"  , bIsPtr, bIsArray));
    EXPECT_EQ(true, Detect.CheckVariable(RULETYPE_UPPER_CAMEL	, "uin8_t", "MyFunc"  , bIsPtr, bIsArray));
    EXPECT_EQ(true, Detect.CheckVariable(RULETYPE_LOWER_CAMEL	, "uin8_t", "myFunc"  , bIsPtr, bIsArray));
    EXPECT_EQ(true, Detect.CheckVariable(RULETYPE_LOWER_SNAKE   , "uin8_t", "my_func" , bIsPtr, bIsArray));
}

TEST(Config_Detect_CheckVariable, Hungarian_Bad)
{
	RuleOfVariable Rule;
	Detection Detect;

	Rule.TypeNamingMap.insert(std::pair<string, string>("uin8_t", "u8"));

	bool bIsPtr = false;
	bool bIsArray = false;
	Detect.ApplyRuleForVariable(Rule);
	EXPECT_EQ(false, Detect.CheckVariable(RULETYPE_HUNGARIAN, "uin8_t", "MyFunc", bIsPtr, bIsArray));
}

}  // namespace CheckVariable

// clang-format on