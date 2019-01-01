#include <gtest/gtest.h>
#include <numeric>
#include <vector>

#include "../Config.h"
#include "../Detection.h"

using namespace namelint;

//==-------------------------------------------------------------------------==
// Detection.CheckFile()
//==-------------------------------------------------------------------------==
namespace CheckFile {
//-------------------------------------------------------------------------
// Input Parameters
TEST(Config_Detect_CheckFile, InputParms_Good)
{
    Detection Detect;
    EXPECT_EQ(true, Detect.CheckFile(RULETYPE_DEFAULT, "TestName.cpp"));
    EXPECT_EQ(true, Detect.CheckFile(RULETYPE_UPPER_CAMEL_CASE, "TestName.cpp"));
    EXPECT_EQ(true, Detect.CheckFile(RULETYPE_LOWER_CAMEL_CASE, "testName.cpp"));
    EXPECT_EQ(true, Detect.CheckFile(RULETYPE_LOWER_SEPERATED, "test_name.cpp"));
}

TEST(Config_Detect_CheckFile, InputParms_Bad)
{
    Detection Detect;
    EXPECT_EQ(false, Detect.CheckFile(RULETYPE_DEFAULT, ""));
    EXPECT_EQ(false, Detect.CheckFile(RULETYPE_UPPER_CAMEL_CASE, ""));
    EXPECT_EQ(false, Detect.CheckFile(RULETYPE_LOWER_CAMEL_CASE, ""));
    EXPECT_EQ(false, Detect.CheckFile(RULETYPE_LOWER_SEPERATED, ""));
    EXPECT_EQ(false, Detect.CheckFile(RULETYPE_HUNGARIAN, "AnyName.cpp"));
}

//-------------------------------------------------------------------------
// UpperCamelCase
TEST(Config_Detect_CheckFile, UpperCamelCase_Good)
{
    Detection Detect;
    const RULETYPE RuleType = RULETYPE_UPPER_CAMEL_CASE;

    EXPECT_EQ(true, Detect.CheckFile(RuleType, "TestName"));
    EXPECT_EQ(true, Detect.CheckFile(RuleType, "TestName.h"));
    EXPECT_EQ(true, Detect.CheckFile(RuleType, "TestName.H"));
    EXPECT_EQ(true, Detect.CheckFile(RuleType, "TestName.cpp"));
    EXPECT_EQ(true, Detect.CheckFile(RuleType, "TestName.CPP"));
}

TEST(Config_Detect_CheckFile, UpperCamelCase_Bad)
{
    Detection Detect;
    const RULETYPE RuleType = RULETYPE_UPPER_CAMEL_CASE;

    EXPECT_EQ(false, Detect.CheckFile(RuleType, "testName"));
    EXPECT_EQ(false, Detect.CheckFile(RuleType, "testName.h"));
    EXPECT_EQ(false, Detect.CheckFile(RuleType, "testName.cpp"));
}

//-------------------------------------------------------------------------
// LowerCamelCase
TEST(Config_Detect_CheckFile, LowerCamelCase_Good)
{
    Detection Detect;
    const RULETYPE RuleType = RULETYPE_LOWER_CAMEL_CASE;

    EXPECT_EQ(true, Detect.CheckFile(RuleType, "testName"));
    EXPECT_EQ(true, Detect.CheckFile(RuleType, "testName.h"));
    EXPECT_EQ(true, Detect.CheckFile(RuleType, "testName.H"));
    EXPECT_EQ(true, Detect.CheckFile(RuleType, "testName.cpp"));
    EXPECT_EQ(true, Detect.CheckFile(RuleType, "testName.CPP"));
}

TEST(Config_Detect_CheckFile, LowerCamelCase_Bad)
{
    Detection Detect;
    const RULETYPE RuleType = RULETYPE_LOWER_CAMEL_CASE;

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
namespace CheckFunction {
//-------------------------------------------------------------------------
// Input Parameter
TEST(Config_Detect_CheckFunction, InputParms_Good)
{
    Detection Detect;
    vector<string> NullIgnorePrefixs;
    EXPECT_EQ(true, Detect.CheckFunction(RULETYPE_DEFAULT, "MyFunc", NullIgnorePrefixs));
    EXPECT_EQ(true, Detect.CheckFunction(RULETYPE_UPPER_CAMEL_CASE, "MyFunc", NullIgnorePrefixs));
    EXPECT_EQ(true, Detect.CheckFunction(RULETYPE_LOWER_CAMEL_CASE, "myFunc", NullIgnorePrefixs));
    EXPECT_EQ(true, Detect.CheckFunction(RULETYPE_LOWER_SEPERATED, "my_func", NullIgnorePrefixs));
}

TEST(Config_Detect_CheckFunction, InputParms_Bad)
{
    Detection Detect;
    vector<string> NullIgnorePrefixs;
    EXPECT_EQ(false, Detect.CheckFunction(RULETYPE_DEFAULT, "", NullIgnorePrefixs));
    EXPECT_EQ(false, Detect.CheckFunction(RULETYPE_UPPER_CAMEL_CASE, "", NullIgnorePrefixs));
    EXPECT_EQ(false, Detect.CheckFunction(RULETYPE_LOWER_CAMEL_CASE, "", NullIgnorePrefixs));
    EXPECT_EQ(false, Detect.CheckFunction(RULETYPE_LOWER_SEPERATED, "", NullIgnorePrefixs));
    EXPECT_EQ(false, Detect.CheckFunction(RULETYPE_HUNGARIAN, "AnyName", NullIgnorePrefixs));
}

//-------------------------------------------------------------------------
// UpperCamelCase
TEST(Config_Detect_CheckFunction, UpperCamelCase_Good)
{
    Detection Detect;
    vector<string> NullIgnorePrefixs;
    const RULETYPE RuleType = RULETYPE_UPPER_CAMEL_CASE;

    EXPECT_EQ(true, Detect.CheckFunction(RuleType, "UpperCamelFuncName", NullIgnorePrefixs));
    EXPECT_EQ(true, Detect.CheckFunction(RuleType, "Upper_CamelFuncName", NullIgnorePrefixs));
    EXPECT_EQ(true, Detect.CheckFunction(RuleType, "UpperCamelFuncName_", NullIgnorePrefixs));
    EXPECT_EQ(true, Detect.CheckFunction(RuleType, "UpperCamelFuncName1", NullIgnorePrefixs));
}

TEST(Config_Detect_CheckFunction, UpperCamelCase_Bad)
{
    Detection Detect;
    vector<string> NullIgnorePrefixs;
    const RULETYPE RuleType = RULETYPE_UPPER_CAMEL_CASE;

    EXPECT_EQ(false, Detect.CheckFunction(RuleType, "upperCamelFuncName", NullIgnorePrefixs));
    EXPECT_EQ(false, Detect.CheckFunction(RuleType, "_UpperCamelFuncName", NullIgnorePrefixs));
}

//-------------------------------------------------------------------------
// LowerCamelCase
TEST(Config_Detect_CheckFunction, LowerCamelCase_Good)
{
    Detection Detect;
    vector<string> NullIgnorePrefixs;
    const RULETYPE RuleType = RULETYPE_LOWER_CAMEL_CASE;

    EXPECT_EQ(true, Detect.CheckFunction(RuleType, "lowerCamelFuncName", NullIgnorePrefixs));
    EXPECT_EQ(true, Detect.CheckFunction(RuleType, "lower_CamelFuncName", NullIgnorePrefixs));
    EXPECT_EQ(true, Detect.CheckFunction(RuleType, "lowerCamelFuncName_", NullIgnorePrefixs));
    EXPECT_EQ(true, Detect.CheckFunction(RuleType, "lowerCamelFuncName1", NullIgnorePrefixs));
}

TEST(Config_Detect_CheckFunction, LowerCamelCase_Bad)
{
    Detection Detect;
    vector<string> NullIgnorePrefixs;
    const RULETYPE RuleType = RULETYPE_LOWER_CAMEL_CASE;

    EXPECT_EQ(false, Detect.CheckFunction(RuleType, "LowerCamelFuncName", NullIgnorePrefixs));
    EXPECT_EQ(false, Detect.CheckFunction(RuleType, "_LowerCamelFuncName", NullIgnorePrefixs));
}

//-------------------------------------------------------------------------
// LowerSeperated
TEST(Config_Detect_CheckFunction, LowerSeperatedCase_Good)
{
    Detection Detect;
    vector<string> NullIgnorePrefixs;
    const RULETYPE RuleType = RULETYPE_LOWER_SEPERATED;

    EXPECT_EQ(true, Detect.CheckFunction(RuleType, "lower_separated_funcname", NullIgnorePrefixs));
    EXPECT_EQ(true, Detect.CheckFunction(RuleType, "lower_separated_funcname_", NullIgnorePrefixs));
    EXPECT_EQ(true,
              Detect.CheckFunction(RuleType, "lower__separated__funcname", NullIgnorePrefixs));
    EXPECT_EQ(true,
              Detect.CheckFunction(RuleType, "lower_separated_funcname__", NullIgnorePrefixs));
    EXPECT_EQ(true, Detect.CheckFunction(RuleType, "lowerseparatedfuncname", NullIgnorePrefixs));
}

TEST(Config_Detect_CheckFunction, LowerSeperatedCase_Bad)
{
    Detection Detect;
    vector<string> NullIgnorePrefixs;
    const RULETYPE RuleType = RULETYPE_LOWER_SEPERATED;

    EXPECT_EQ(false, Detect.CheckFunction(RuleType, "lowerSeparatedFuncName", NullIgnorePrefixs));
}
}  // namespace CheckFunction

//==-------------------------------------------------------------------------==
// Detection.CheckVariable()
//==-------------------------------------------------------------------------==
namespace CheckVariable {
//-------------------------------------------------------------------------
// Input Parameter
TEST(Config_Detect_CheckVariable, InputParms_Good)
{
    Detection Detect;
    vector<string> NullIgnorePrefixs;
    map<string, string> MappedList;
    MappedList.insert(std::pair<string, string>("uin8_t", "u8"));
    MappedList.insert(std::pair<string, string>("uin16_t", "u16"));
    EXPECT_EQ(true, Detect.CheckVariable(RULETYPE_DEFAULT, "uin8_t", "MyFunc", NullIgnorePrefixs,
                                         MappedList));
    EXPECT_EQ(true, Detect.CheckVariable(RULETYPE_UPPER_CAMEL_CASE, "uin8_t", "MyFunc",
                                         NullIgnorePrefixs, MappedList));
    EXPECT_EQ(true, Detect.CheckVariable(RULETYPE_LOWER_CAMEL_CASE, "uin8_t", "myFunc",
                                         NullIgnorePrefixs, MappedList));
    EXPECT_EQ(true, Detect.CheckVariable(RULETYPE_LOWER_SEPERATED, "uin8_t", "my_func",
                                         NullIgnorePrefixs, MappedList));
    EXPECT_EQ(true, Detect.CheckVariable(RULETYPE_HUNGARIAN, "uin8_t", "u8MyFunc",
                                         NullIgnorePrefixs, MappedList));
    EXPECT_EQ(true, Detect.CheckVariable(RULETYPE_HUNGARIAN, "uin16_t", "u16MyFunc",
                                         NullIgnorePrefixs, MappedList));
    EXPECT_EQ(true, Detect.CheckVariable(RULETYPE_HUNGARIAN, "uin8_t", "u8_my_func",
                                         NullIgnorePrefixs, MappedList));
    EXPECT_EQ(true, Detect.CheckVariable(RULETYPE_HUNGARIAN, "uin16_t", "u16_my_func",
                                         NullIgnorePrefixs, MappedList));
}

TEST(Config_Detect_CheckVariable, InputParms_Bad)
{
    Detection Detect;
    vector<string> NullIgnorePrefixs;
    map<string, string> MappedList;
    MappedList.insert(std::pair<string, string>("uin8_t", "u8"));
    MappedList.insert(std::pair<string, string>("uin16_t", "u16"));
    EXPECT_EQ(false,
              Detect.CheckVariable(RULETYPE_DEFAULT, "uin8_t", "", NullIgnorePrefixs, MappedList));
    EXPECT_EQ(false, Detect.CheckVariable(RULETYPE_UPPER_CAMEL_CASE, "uin8_t", "",
                                          NullIgnorePrefixs, MappedList));
    EXPECT_EQ(false, Detect.CheckVariable(RULETYPE_LOWER_CAMEL_CASE, "uin8_t", "",
                                          NullIgnorePrefixs, MappedList));
    EXPECT_EQ(false, Detect.CheckVariable(RULETYPE_LOWER_SEPERATED, "uin8_t", "", NullIgnorePrefixs,
                                          MappedList));
    EXPECT_EQ(false, Detect.CheckVariable(RULETYPE_HUNGARIAN, "uin8_t", "u8my_name",
                                          NullIgnorePrefixs, MappedList));
    EXPECT_EQ(false, Detect.CheckVariable(RULETYPE_HUNGARIAN, "uin8_t", "u8my_Name",
                                          NullIgnorePrefixs, MappedList));
    EXPECT_EQ(false, Detect.CheckVariable(RULETYPE_HUNGARIAN, "uin8_t", "u8my_Name",
                                          NullIgnorePrefixs, MappedList));
    EXPECT_EQ(false, Detect.CheckVariable(RULETYPE_HUNGARIAN, "uin8_t", "u16AnyName",
                                          NullIgnorePrefixs, MappedList));
    EXPECT_EQ(false, Detect.CheckVariable(RULETYPE_HUNGARIAN, "uin16_t", "u8AnyName",
                                          NullIgnorePrefixs, MappedList));
}

//-------------------------------------------------------------------------
// Multiple Cases
TEST(Config_Detect_CheckVariable, GoodCases)
{
    Detection Detect;
    vector<string> NullIgnorePrefixs;
    const RULETYPE RuleType = RULETYPE_UPPER_CAMEL_CASE;
    map<string, string> MappedList;

    MappedList.insert(std::pair<string, string>("uin8_t", "u8"));
    EXPECT_EQ(true, Detect.CheckVariable(RULETYPE_DEFAULT, "uin8_t", "MyFunc", NullIgnorePrefixs,
                                         MappedList));
    EXPECT_EQ(true, Detect.CheckVariable(RULETYPE_UPPER_CAMEL_CASE, "uin8_t", "MyFunc",
                                         NullIgnorePrefixs, MappedList));
    EXPECT_EQ(true, Detect.CheckVariable(RULETYPE_LOWER_CAMEL_CASE, "uin8_t", "myFunc",
                                         NullIgnorePrefixs, MappedList));
    EXPECT_EQ(true, Detect.CheckVariable(RULETYPE_LOWER_SEPERATED, "uin8_t", "my_func",
                                         NullIgnorePrefixs, MappedList));
}

TEST(Config_Detect_CheckVariable, Hungarian_Bad)
{
    Detection Detect;
    vector<string> NullIgnorePrefixs;
    map<string, string> MappedList;
    MappedList.insert(std::pair<string, string>("uin8_t", "u8"));
    const RULETYPE RuleType = RULETYPE_UPPER_CAMEL_CASE;
    EXPECT_EQ(false, Detect.CheckVariable(RULETYPE_HUNGARIAN, "uin8_t", "MyFunc", NullIgnorePrefixs,
                                          MappedList));
}
}  // namespace CheckVariable
