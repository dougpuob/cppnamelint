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
    EXPECT_EQ(true, Detect.CheckFile(RULETYPE_LOWER_SEPERATED   , "test_name.cpp"));
}

TEST(Config_Detect_CheckFile, InputParms_Bad)
{
    Detection Detect;
    EXPECT_EQ(false, Detect.CheckFile(RULETYPE_DEFAULT          , ""));
    EXPECT_EQ(false, Detect.CheckFile(RULETYPE_UPPER_CAMEL		, ""));
    EXPECT_EQ(false, Detect.CheckFile(RULETYPE_LOWER_CAMEL		, ""));
    EXPECT_EQ(false, Detect.CheckFile(RULETYPE_LOWER_SEPERATED  , ""));
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
    const RULETYPE RuleType = RULETYPE_LOWER_SEPERATED;

    EXPECT_EQ(true, Detect.CheckFile(RuleType, "testname.h"));
    EXPECT_EQ(true, Detect.CheckFile(RuleType, "testname_.h"));
    EXPECT_EQ(true, Detect.CheckFile(RuleType, "test_name.h"));
    EXPECT_EQ(true, Detect.CheckFile(RuleType, "test_name.cpp"));
    EXPECT_EQ(true, Detect.CheckFile(RuleType, "test_name_.cpp"));
}

TEST(Config_Detect_CheckFile, LowerSeperated_Bad)
{
    Detection Detect;
    const RULETYPE RuleType = RULETYPE_LOWER_SEPERATED;

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
    Detection Detect;
    vector<string> NullIgnoreName;
    vector<string> NullIgnorePrefixs;
    EXPECT_EQ(true, Detect.CheckFunction(RULETYPE_DEFAULT           , "MyFunc"     , NullIgnoreName, NullIgnorePrefixs));
    EXPECT_EQ(true, Detect.CheckFunction(RULETYPE_UPPER_CAMEL		, "MyFunc"     , NullIgnoreName, NullIgnorePrefixs));
    EXPECT_EQ(true, Detect.CheckFunction(RULETYPE_UPPER_CAMEL		, "My_Func"    , NullIgnoreName, NullIgnorePrefixs, true));
    EXPECT_EQ(true, Detect.CheckFunction(RULETYPE_UPPER_CAMEL		, "My__Func"   , NullIgnoreName, NullIgnorePrefixs, true));
    EXPECT_EQ(true, Detect.CheckFunction(RULETYPE_UPPER_CAMEL		, "My_Func_A"  , NullIgnoreName, NullIgnorePrefixs, true));
    EXPECT_EQ(true, Detect.CheckFunction(RULETYPE_UPPER_CAMEL		, "My__Func_B" , NullIgnoreName, NullIgnorePrefixs, true));
    EXPECT_EQ(true, Detect.CheckFunction(RULETYPE_LOWER_CAMEL		, "myFunc"     , NullIgnoreName, NullIgnorePrefixs));
    EXPECT_EQ(true, Detect.CheckFunction(RULETYPE_LOWER_SEPERATED   , "my_func"    , NullIgnoreName, NullIgnorePrefixs));
}

TEST(Config_Detect_CheckFunction, InputParms_Bad)
{
    Detection Detect;
    vector<string> NullIgnoreName;
    vector<string> NullIgnorePrefixs;
    EXPECT_EQ(false, Detect.CheckFunction(RULETYPE_DEFAULT          , ""        , NullIgnoreName, NullIgnorePrefixs));
    EXPECT_EQ(false, Detect.CheckFunction(RULETYPE_UPPER_CAMEL		, ""        , NullIgnoreName, NullIgnorePrefixs));
    EXPECT_EQ(false, Detect.CheckFunction(RULETYPE_LOWER_CAMEL		, ""        , NullIgnoreName, NullIgnorePrefixs));
    EXPECT_EQ(false, Detect.CheckFunction(RULETYPE_LOWER_SEPERATED  , ""        , NullIgnoreName, NullIgnorePrefixs));
    EXPECT_EQ(false, Detect.CheckFunction(RULETYPE_HUNGARIAN        , "AnyName" , NullIgnoreName, NullIgnorePrefixs));
}

//-------------------------------------------------------------------------
// UpperCamelCase
TEST(Config_Detect_CheckFunction, UpperCamelCase_Good)
{
    Detection Detect;
    vector<string> NullIgnoreName;
	vector<string> NullIgnorePrefixs;	
    const RULETYPE RuleType = RULETYPE_UPPER_CAMEL;
    EXPECT_EQ(true, Detect.CheckFunction(RuleType, "UpperCamelFuncName"     , NullIgnoreName, NullIgnorePrefixs));
    EXPECT_EQ(true, Detect.CheckFunction(RuleType, "UpperCamelFuncName1"    , NullIgnoreName, NullIgnorePrefixs));

	vector<string> IgnoreName;
	IgnoreName.push_back("main");

    vector<string> IgnorePrefixs;
    IgnorePrefixs.push_back("_");
    IgnorePrefixs.push_back("__");
    IgnorePrefixs.push_back("XXX_");
    EXPECT_EQ(true, Detect.CheckFunction(RuleType, "_UpperCamelFuncName"    , IgnoreName, IgnorePrefixs));
    EXPECT_EQ(true, Detect.CheckFunction(RuleType, "__UpperCamelFuncName"   , IgnoreName, IgnorePrefixs));
    EXPECT_EQ(true, Detect.CheckFunction(RuleType, "XXX_UpperCamelFuncName" , IgnoreName, IgnorePrefixs));
    EXPECT_EQ(true, Detect.CheckFunction(RuleType, "_UpperCamelFuncName_AB" , IgnoreName, IgnorePrefixs, true));
	EXPECT_EQ(true, Detect.CheckFunction(RuleType, "main"                   , IgnoreName, IgnorePrefixs, false));
	EXPECT_EQ(true, Detect.CheckFunction(RuleType, "main"                   , IgnoreName, IgnorePrefixs, true));
    EXPECT_EQ(true, Detect.CheckFunction(RuleType, "MyFunc3"                , IgnoreName, IgnorePrefixs, true));
    EXPECT_EQ(true, Detect.CheckFunction(RuleType, "MyFunc3"                , IgnoreName, IgnorePrefixs, false));
    EXPECT_EQ(true, Detect.CheckFunction(RuleType, "MyFunc_3"               , IgnoreName, IgnorePrefixs, true));
}

TEST(Config_Detect_CheckFunction, UpperCamelCase_Bad)
{
    Detection Detect;
    vector<string> NullIgnoreName;
    vector<string> NullIgnorePrefixs;
    const RULETYPE RuleType = RULETYPE_UPPER_CAMEL;

    EXPECT_EQ(false, Detect.CheckFunction(RuleType, "UpperCamelFuncName_"   , NullIgnoreName, NullIgnorePrefixs));
    EXPECT_EQ(false, Detect.CheckFunction(RuleType, "Upper_CamelFuncName"   , NullIgnoreName, NullIgnorePrefixs));
    EXPECT_EQ(false, Detect.CheckFunction(RuleType, "upperCamelFuncName"    , NullIgnoreName, NullIgnorePrefixs));
    EXPECT_EQ(false, Detect.CheckFunction(RuleType, "_UpperCamelFuncName"   , NullIgnoreName, NullIgnorePrefixs));
    EXPECT_EQ(false, Detect.CheckFunction(RuleType, "UpperCamelFuncName_AB" , NullIgnoreName, NullIgnorePrefixs, false));
}

//-------------------------------------------------------------------------
// LowerCamelCase
TEST(Config_Detect_CheckFunction, LowerCamelCase_Good)
{
    Detection Detect;
    vector<string> NullIgnoreName;
    vector<string> NullIgnorePrefixs;
    const RULETYPE RuleType = RULETYPE_LOWER_CAMEL;

    EXPECT_EQ(true, Detect.CheckFunction(RuleType, "lowerCamelFuncName"     , NullIgnoreName, NullIgnorePrefixs));
    EXPECT_EQ(true, Detect.CheckFunction(RuleType, "lower_CamelFuncName"    , NullIgnoreName, NullIgnorePrefixs));
    EXPECT_EQ(true, Detect.CheckFunction(RuleType, "lowerCamelFuncName_"    , NullIgnoreName, NullIgnorePrefixs));
    EXPECT_EQ(true, Detect.CheckFunction(RuleType, "lowerCamelFuncName1"    , NullIgnoreName, NullIgnorePrefixs));
}

TEST(Config_Detect_CheckFunction, LowerCamelCase_Bad)
{
    Detection Detect;
    vector<string> NullIgnoreName;
    vector<string> NullIgnorePrefixs;
    const RULETYPE RuleType = RULETYPE_LOWER_CAMEL;

    EXPECT_EQ(false, Detect.CheckFunction(RuleType, "LowerCamelFuncName"    , NullIgnoreName, NullIgnorePrefixs));
    EXPECT_EQ(false, Detect.CheckFunction(RuleType, "_LowerCamelFuncName"   , NullIgnoreName, NullIgnorePrefixs));
}

//-------------------------------------------------------------------------
// LowerSeperated
TEST(Config_Detect_CheckFunction, LowerSeperatedCase_Good)
{
    Detection Detect;
    vector<string> NullIgnoreName;
    vector<string> NullIgnorePrefixs;
    const RULETYPE RuleType = RULETYPE_LOWER_SEPERATED;

    EXPECT_EQ(true, Detect.CheckFunction(RuleType, "lower_separated_funcname"   , NullIgnoreName, NullIgnorePrefixs));
    EXPECT_EQ(true, Detect.CheckFunction(RuleType, "lower_separated_funcname_"  , NullIgnoreName, NullIgnorePrefixs));
    EXPECT_EQ(true, Detect.CheckFunction(RuleType, "lower__separated__funcname" , NullIgnoreName, NullIgnorePrefixs));
    EXPECT_EQ(true, Detect.CheckFunction(RuleType, "lower_separated_funcname__" , NullIgnoreName, NullIgnorePrefixs));
    EXPECT_EQ(true, Detect.CheckFunction(RuleType, "lowerseparatedfuncname"     , NullIgnoreName, NullIgnorePrefixs));
}

TEST(Config_Detect_CheckFunction, LowerSeperatedCase_Bad)
{
    Detection Detect;
    vector<string> NullIgnoreName;
    vector<string> NullIgnorePrefixs;
    const RULETYPE RuleType = RULETYPE_LOWER_SEPERATED;

    EXPECT_EQ(false, Detect.CheckFunction(RuleType, "lowerSeparatedFuncName", NullIgnoreName, NullIgnorePrefixs));
}
}  // namespace CheckFunction


//==-------------------------------------------------------------------------==
// Detection.CheckVariable()
//==-------------------------------------------------------------------------==
namespace TargetIsVariable {

// Input Parameter
TEST(Config_Detect_CheckVariable, InputParms_Good)
{
    Detection Detect;
    vector<string> NullIgnorePrefixs;
    map<string, string> MappedList;
	map<string, string> MappedListEx;

    MappedList.insert(std::pair<string, string>("int"    , "i"));
    MappedList.insert(std::pair<string, string>("uin8_t" , "u8"));
    MappedList.insert(std::pair<string, string>("uin16_t", "u16"));

    EXPECT_EQ(true, Detect.CheckVariable(RULETYPE_DEFAULT			, "uin8_t"  , "MyFunc"      , NullIgnorePrefixs, MappedList, MappedListEx));
    EXPECT_EQ(true, Detect.CheckVariable(RULETYPE_UPPER_CAMEL		, "uin8_t"  , "MyFunc"      , NullIgnorePrefixs, MappedList, MappedListEx));
    EXPECT_EQ(true, Detect.CheckVariable(RULETYPE_LOWER_CAMEL		, "uin8_t"  , "myFunc"      , NullIgnorePrefixs, MappedList, MappedListEx));
    EXPECT_EQ(true, Detect.CheckVariable(RULETYPE_LOWER_SEPERATED   , "uin8_t"  , "my_func"     , NullIgnorePrefixs, MappedList, MappedListEx));
    EXPECT_EQ(true, Detect.CheckVariable(RULETYPE_HUNGARIAN         , "int"     , "iMyFunc"     , NullIgnorePrefixs, MappedList, MappedListEx));
    EXPECT_EQ(true, Detect.CheckVariable(RULETYPE_HUNGARIAN         , "uin8_t"  , "u8MyFunc"    , NullIgnorePrefixs, MappedList, MappedListEx));
    EXPECT_EQ(true, Detect.CheckVariable(RULETYPE_HUNGARIAN         , "uin16_t" , "u16MyFunc"   , NullIgnorePrefixs, MappedList, MappedListEx));

    vector<string> IgnorePrefixs;
    IgnorePrefixs.push_back("m_");
    EXPECT_EQ(true, Detect.CheckVariable(RULETYPE_HUNGARIAN         , "int"     , "m_iMyFunc"   , IgnorePrefixs, MappedList, MappedListEx));
}

TEST(Config_Detect_CheckVariable, InputParms_Bad)
{
    Detection Detect;
    vector<string> NullIgnorePrefixs;
    map<string, string> MappedList;
	map<string, string> MappedListEx;

    MappedList.insert(std::pair<string, string>("uin8_t", "u8"));
    MappedList.insert(std::pair<string, string>("uin16_t", "u16"));

    EXPECT_EQ(false, Detect.CheckVariable(RULETYPE_DEFAULT          , "uin8_t"  , ""            , NullIgnorePrefixs, MappedList, MappedListEx));
    EXPECT_EQ(false, Detect.CheckVariable(RULETYPE_UPPER_CAMEL		, "uin8_t"  , ""            , NullIgnorePrefixs, MappedList, MappedListEx));
    EXPECT_EQ(false, Detect.CheckVariable(RULETYPE_LOWER_CAMEL		, "uin8_t"  , ""            , NullIgnorePrefixs, MappedList, MappedListEx));
    EXPECT_EQ(false, Detect.CheckVariable(RULETYPE_LOWER_SEPERATED  , "uin8_t"  , ""            , NullIgnorePrefixs, MappedList, MappedListEx));
    EXPECT_EQ(false, Detect.CheckVariable(RULETYPE_HUNGARIAN        , "uin8_t"  , "u8my_name"   , NullIgnorePrefixs, MappedList, MappedListEx));
    EXPECT_EQ(false, Detect.CheckVariable(RULETYPE_HUNGARIAN        , "uin8_t"  , "u8my_Name"   , NullIgnorePrefixs, MappedList, MappedListEx));
    EXPECT_EQ(false, Detect.CheckVariable(RULETYPE_HUNGARIAN        , "uin8_t"  , "u8my_Name"   , NullIgnorePrefixs, MappedList, MappedListEx));
    EXPECT_EQ(false, Detect.CheckVariable(RULETYPE_HUNGARIAN        , "uin8_t"  , "u16AnyName"  , NullIgnorePrefixs, MappedList, MappedListEx));
    EXPECT_EQ(false, Detect.CheckVariable(RULETYPE_HUNGARIAN        , "uin16_t" , "u8AnyName"   , NullIgnorePrefixs, MappedList, MappedListEx));	
    EXPECT_EQ(false, Detect.CheckVariable(RULETYPE_HUNGARIAN		, "uin8_t"  , "u8_my_func"  , NullIgnorePrefixs, MappedList, MappedListEx));
    EXPECT_EQ(false, Detect.CheckVariable(RULETYPE_HUNGARIAN		, "uin16_t" , "u16_my_func" , NullIgnorePrefixs, MappedList, MappedListEx));
}

//-------------------------------------------------------------------------
// Multiple Cases
TEST(Config_Detect_CheckVariable, GoodCases)
{
    Detection Detect;
    vector<string> NullIgnorePrefixs;
    const RULETYPE RuleType = RULETYPE_UPPER_CAMEL;
    map<string, string> MappedList;
	map<string, string> MappedListEx;

    MappedList.insert(std::pair<string, string>("uin8_t", "u8"));

    EXPECT_EQ(true, Detect.CheckVariable(RULETYPE_DEFAULT           , "uin8_t", "MyFunc"    , NullIgnorePrefixs, MappedList, MappedListEx));
    EXPECT_EQ(true, Detect.CheckVariable(RULETYPE_UPPER_CAMEL		, "uin8_t", "MyFunc"    , NullIgnorePrefixs, MappedList, MappedListEx));
    EXPECT_EQ(true, Detect.CheckVariable(RULETYPE_LOWER_CAMEL		, "uin8_t", "myFunc"    , NullIgnorePrefixs, MappedList, MappedListEx));
    EXPECT_EQ(true, Detect.CheckVariable(RULETYPE_LOWER_SEPERATED   , "uin8_t", "my_func"   , NullIgnorePrefixs, MappedList, MappedListEx));
}

TEST(Config_Detect_CheckVariable, Hungarian_Bad)
{
    Detection Detect;
    vector<string> NullIgnorePrefixs;
    map<string, string> MappedList;
	map<string, string> MappedListEx;

    MappedList.insert(std::pair<string, string>("uin8_t", "u8"));

	EXPECT_EQ(false, Detect.CheckVariable(RULETYPE_HUNGARIAN, "uin8_t", "MyFunc", NullIgnorePrefixs, MappedList, MappedListEx));
}

}  // namespace CheckVariable

// clang-format on