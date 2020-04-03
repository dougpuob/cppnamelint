#include <numeric>
#include <vector>

#include <gtest/gtest.h>

#include "../Common.h"
#include "../Config.h"
#include "../Detection.h"

using namespace namelint;

void SetUp() {
  const string ConfigToml = "\
        [General.Options]                                       \n\
          CheckStruct             = true                        \n\
        [General.IgnoredList]                                   \n\
          StructTagPrefix         = [ \"e\", \"En\" ]           \n\
        ";

  string errorReason;
  ((APP_CONTEXT *)GetAppCxt())->MemoBoard.Config.LoadStream(ConfigToml, errorReason);
}

// clang-format off
//==-------------------------------------------------------------------------==
// Detection.CheckFile()
//==-------------------------------------------------------------------------==
namespace TargetIsFile {

// Input Parameters
TEST(Config_Detect_CheckFile, InputParms_Good)
{
    Detection Detect;
    EXPECT_EQ(true, Detect.CheckFile(RULETYPE_DEFAULT		, "TestName.cpp"));
    EXPECT_EQ(true, Detect.CheckFile(RULETYPE_UPPER_CAMEL	, "TestName.cpp"));
    EXPECT_EQ(true, Detect.CheckFile(RULETYPE_LOWER_CAMEL	, "testName.cpp"));
    EXPECT_EQ(true, Detect.CheckFile(RULETYPE_LOWER_SNAKE   , "test_name.cpp"));
}

TEST(Config_Detect_CheckFile, InputParms_Bad)
{
    Detection Detect;
    EXPECT_EQ(false, Detect.CheckFile(RULETYPE_DEFAULT		, ""));
    EXPECT_EQ(false, Detect.CheckFile(RULETYPE_UPPER_CAMEL	, ""));
    EXPECT_EQ(false, Detect.CheckFile(RULETYPE_LOWER_CAMEL	, ""));
    EXPECT_EQ(false, Detect.CheckFile(RULETYPE_LOWER_SNAKE  , ""));
    EXPECT_EQ(false, Detect.CheckFile(RULETYPE_HUNGARIAN	, "AnyName.cpp"));
}

//-------------------------------------------------------------------------
// UpperCamelCase
TEST(Config_Detect_CheckFile, UpperCamelCase_Good)
{
    Detection Detect;
    const RULETYPE RuleType = RULETYPE_UPPER_CAMEL;

	EXPECT_EQ(true, Detect.CheckFile(RuleType, "UtestWnd.h"));
	EXPECT_EQ(true, Detect.CheckFile(RuleType, "SerialPort.h"));
    EXPECT_EQ(true, Detect.CheckFile(RuleType, "TestName"));
    EXPECT_EQ(true, Detect.CheckFile(RuleType, "TestName.h"));
    EXPECT_EQ(true, Detect.CheckFile(RuleType, "TestName.H"));
    EXPECT_EQ(true, Detect.CheckFile(RuleType, "TestName.cpp"));
    EXPECT_EQ(true, Detect.CheckFile(RuleType, "TestName.CPP"));

	RuleOfFile Rule;
	Rule.bAllowedUnderscopeChar = true;
	Detect.ApplyRuleForFile(Rule);
	EXPECT_EQ(true, Detect.CheckFile(RuleType, "Sample_03.c"));
}

TEST(Config_Detect_CheckFile, UpperCamelCase_Bad)
{
    Detection Detect;
    const RULETYPE RuleType = RULETYPE_UPPER_CAMEL;

	EXPECT_EQ(false, Detect.CheckFile(RuleType, "UTestWnd.h"));
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
    EXPECT_EQ(true, Detect.CheckFile(RuleType, "lowername.CPP"));
}

TEST(Config_Detect_CheckFile, LowerSeperated_Bad)
{
    Detection Detect;
    const RULETYPE RuleType = RULETYPE_LOWER_SNAKE;
        
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
	Rule.bAllowedUnderscopeChar = false;
	Rule.IgnoreNames.clear();
	Rule.IgnorePrefixs.clear();

    Detection Detect;
	Detect.ApplyRuleForFunction(Rule);
    EXPECT_EQ(true, Detect.CheckFunction(RULETYPE_DEFAULT           , "MyFunc"	));
    EXPECT_EQ(true, Detect.CheckFunction(RULETYPE_UPPER_CAMEL		, "MyFunc"	));
    EXPECT_EQ(true, Detect.CheckFunction(RULETYPE_LOWER_CAMEL		, "myFunc"	));
    EXPECT_EQ(true, Detect.CheckFunction(RULETYPE_LOWER_SNAKE		, "my_func"	));

	Rule.bAllowedUnderscopeChar = true;
	Detect.ApplyRuleForFunction(Rule);
	EXPECT_EQ(true, Detect.CheckFunction(RULETYPE_UPPER_CAMEL		, "MyFunc_"	));
	EXPECT_EQ(true, Detect.CheckFunction(RULETYPE_UPPER_CAMEL		, "Mem_"	));
	EXPECT_EQ(true, Detect.CheckFunction(RULETYPE_UPPER_CAMEL		, "Fun_"	));
}

TEST(Config_Detect_CheckFunction, InputParms_Bad)
{
	RuleOfFunction Rule;
	Rule.bAllowedUnderscopeChar = false;
	Rule.IgnoreNames.clear();
	Rule.IgnorePrefixs.clear();

	Detection Detect;
	Detect.ApplyRuleForFunction(Rule);
	EXPECT_EQ(false, Detect.CheckFunction(RULETYPE_UPPER_CAMEL		, "My__Func"	));
	EXPECT_EQ(false, Detect.CheckFunction(RULETYPE_UPPER_CAMEL		, "My_Func_A"	));
	EXPECT_EQ(false, Detect.CheckFunction(RULETYPE_UPPER_CAMEL		, "My__Func_B"	));
    EXPECT_EQ(false, Detect.CheckFunction(RULETYPE_DEFAULT          , ""			));
    EXPECT_EQ(false, Detect.CheckFunction(RULETYPE_UPPER_CAMEL		, ""			));
    EXPECT_EQ(false, Detect.CheckFunction(RULETYPE_LOWER_CAMEL		, ""			));
    EXPECT_EQ(false, Detect.CheckFunction(RULETYPE_LOWER_SNAKE		, ""			));
    EXPECT_EQ(false, Detect.CheckFunction(RULETYPE_HUNGARIAN        , "AnyName"		));
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

	Rule.bAllowedUnderscopeChar = false;
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

	Rule.bAllowedUnderscopeChar = true;
	Detect.ApplyRuleForFunction(Rule);
	EXPECT_EQ(true, Detect.CheckFunction(RuleType, "_UpperCamelFuncName_"	));
	EXPECT_EQ(true, Detect.CheckFunction(RuleType, "_UpperCamelFuncName_A"	));
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

	Rule.IgnorePrefixs.push_back("_");
	Rule.IgnorePrefixs.push_back("__");
	Rule.IgnorePrefixs.push_back("XX_");
	Rule.IgnorePrefixs.push_back("XX__");
	Rule.IgnorePrefixs.push_back("XXX__");

	Detect.ApplyRuleForFunction(Rule);
    EXPECT_EQ(true, Detect.CheckFunction(RuleType, "lower_separated_funcname"   ));
    EXPECT_EQ(true, Detect.CheckFunction(RuleType, "lower_separated_funcname_"  ));
    EXPECT_EQ(true, Detect.CheckFunction(RuleType, "lowerseparatedfuncname"     ));

	EXPECT_EQ(true, Detect.CheckFunction(RuleType, "_lower_separated_funcname"		));
	EXPECT_EQ(true, Detect.CheckFunction(RuleType, "__lower_separated_funcname"		));
	EXPECT_EQ(true, Detect.CheckFunction(RuleType, "XX_lower_separated_funcname"	));
	EXPECT_EQ(true, Detect.CheckFunction(RuleType, "XXX__lower_separated_funcname"	));
}

TEST(Config_Detect_CheckFunction, LowerSeperatedCase_Bad)
{
    const RULETYPE RuleType = RULETYPE_LOWER_SNAKE;

	RuleOfFunction Rule;
	Detection Detect;

	Detect.ApplyRuleForFunction(Rule);
    EXPECT_EQ(false, Detect.CheckFunction(RuleType, "lowerSeparatedFuncName"		));
	EXPECT_EQ(false, Detect.CheckFunction(RuleType, "lower_separated__funcname_"	));
	EXPECT_EQ(false, Detect.CheckFunction(RuleType, "lower_separated_funcname__"	));
	EXPECT_EQ(false, Detect.CheckFunction(RuleType, "_lower_separated_funcname__"	));
	EXPECT_EQ(false, Detect.CheckFunction(RuleType, "__lower_separated_funcname"	));
	EXPECT_EQ(false, Detect.CheckFunction(RuleType, "XX_lower_separated_funcname"	));
	EXPECT_EQ(false, Detect.CheckFunction(RuleType, "XXX__lower_separated_funcname"	));
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
	Rule.WordListMap.insert(std::pair<string, string>("int"     , "i"));
	Rule.WordListMap.insert(std::pair<string, string>("uint8_t" , "u8"));
	Rule.WordListMap.insert(std::pair<string, string>("uint16_t", "u16"));

	Rule.NullStringMap.push_back(MappingPair("char*"	 , "sz"));
	Rule.NullStringMap.push_back(MappingPair("char**"	 , "psz"));
	Rule.NullStringMap.push_back(MappingPair("wchar_t*"  , "wsz"));
	Rule.NullStringMap.push_back(MappingPair("wchar_t**" , "pwsz"));

    Rule.NullStringMap.push_back(MappingPair("char[]"	 , "sz"));
    Rule.NullStringMap.push_back(MappingPair("wchar_t[]" , "wsz"));

	bool bPrefer   = true;
	bool bIsPtr    = true;
	bool bNotPtr   = false;
	bool bIsArray  = true;
	bool bNotArray = false;
	Detect.ApplyRuleForVariable(Rule);
	    
    // ...........................................................vvvvvvvvv <-- * character should be removed.
	EXPECT_EQ(true, Detect.CheckVariable(RULETYPE_HUNGARIAN		, "char"	, "szStr"      , bPrefer, bIsPtr, bNotArray));
	EXPECT_EQ(true, Detect.CheckVariable(RULETYPE_HUNGARIAN		, "char"	, "pszStr"     , bPrefer, bIsPtr, bNotArray));
	EXPECT_EQ(true, Detect.CheckVariable(RULETYPE_HUNGARIAN		, "wchar_t" , "wszStr"     , bPrefer, bIsPtr, bNotArray));
	EXPECT_EQ(true, Detect.CheckVariable(RULETYPE_HUNGARIAN		, "wchar_t"	, "pwszStr"    , bPrefer, bIsPtr, bNotArray));

    // ...........................................................vvvvvvvvv <-- [] characters should be removed.
    EXPECT_EQ(true, Detect.CheckVariable(RULETYPE_HUNGARIAN		, "char"	, "szStr"      , bPrefer, bNotPtr, bIsArray));
    EXPECT_EQ(true, Detect.CheckVariable(RULETYPE_HUNGARIAN		, "wchar_t"	, "wszStr"     , bPrefer, bNotPtr, bIsArray));

	EXPECT_EQ(true, Detect.CheckVariable(RULETYPE_HUNGARIAN		, "int"		 , "piMyValue" , bPrefer, bIsPtr,  bNotArray));
    EXPECT_EQ(true, Detect.CheckVariable(RULETYPE_DEFAULT		, "uint8_t"  , "MyFunc"    , bPrefer, bNotPtr, bNotArray));
    EXPECT_EQ(true, Detect.CheckVariable(RULETYPE_UPPER_CAMEL	, "uint8_t"  , "MyFunc"    , bPrefer, bNotPtr, bNotArray));
    EXPECT_EQ(true, Detect.CheckVariable(RULETYPE_LOWER_CAMEL	, "uint8_t"  , "myFunc"    , bPrefer, bNotPtr, bNotArray));
    EXPECT_EQ(true, Detect.CheckVariable(RULETYPE_LOWER_SNAKE	, "uint8_t"  , "my_func"   , bPrefer, bNotPtr, bNotArray));
    EXPECT_EQ(true, Detect.CheckVariable(RULETYPE_HUNGARIAN		, "int"      , "iMyFunc"   , bPrefer, bNotPtr, bNotArray));
    EXPECT_EQ(true, Detect.CheckVariable(RULETYPE_HUNGARIAN		, "uint8_t"  , "u8MyFunc"  , bPrefer, bNotPtr, bNotArray));
    EXPECT_EQ(true, Detect.CheckVariable(RULETYPE_HUNGARIAN		, "uint16_t" , "u16MyFunc" , bPrefer, bNotPtr, bNotArray));
	
	Rule.IgnorePrefixs.push_back("m_");
	Detect.ApplyRuleForVariable(Rule);
    EXPECT_EQ(true, Detect.CheckVariable(RULETYPE_HUNGARIAN		, "int"      , "m_iMyFunc" , bPrefer, bNotPtr, bNotArray));
}

TEST(Config_Detect_CheckVariable, PreferUpperCamelIfMissed)
{
    RuleOfVariable Rule;
    Detection Detect;

	bool bIsPtr = true;
	bool bNotPtr = false;
	bool bIsArray = true;
	bool bNotArray = false;
    bool bPreferUpperCamel = true;

    Rule.WordListMap.insert(std::pair<string, string>("uint8_t", "u8"));
    Rule.WordListMap.insert(std::pair<string, string>("uint16_t", "u16"));
	Detect.ApplyRuleForVariable(Rule);

    EXPECT_EQ(true, Detect.CheckVariable(RULETYPE_HUNGARIAN,  "int",     "MyValue", bPreferUpperCamel, bNotPtr, bNotArray));
    EXPECT_EQ(false, Detect.CheckVariable(RULETYPE_HUNGARIAN, "uint8_t", "MyValue", bPreferUpperCamel, bNotPtr, bNotArray));
}

TEST(Config_Detect_CheckVariable, InputParms_Bad)
{
	RuleOfVariable Rule;
	Detection Detect;

	Rule.WordListMap.insert(std::pair<string, string>("uint8_t", "u8"));
	Rule.WordListMap.insert(std::pair<string, string>("uin16_t", "u16"));

	bool bPrefer = true;
	bool bIsPtr  = false;
	bool bIsArray = false;
	Detect.ApplyRuleForVariable(Rule);
    EXPECT_EQ(false, Detect.CheckVariable(RULETYPE_DEFAULT		, "uint8_t"  , ""            , bPrefer, bIsPtr, bIsArray));
    EXPECT_EQ(false, Detect.CheckVariable(RULETYPE_UPPER_CAMEL	, "uint8_t"  , ""            , bPrefer, bIsPtr, bIsArray));
    EXPECT_EQ(false, Detect.CheckVariable(RULETYPE_LOWER_CAMEL	, "uint8_t"  , ""            , bPrefer, bIsPtr, bIsArray));
    EXPECT_EQ(false, Detect.CheckVariable(RULETYPE_LOWER_SNAKE	, "uint8_t"  , ""            , bPrefer, bIsPtr, bIsArray));
    EXPECT_EQ(false, Detect.CheckVariable(RULETYPE_LOWER_CAMEL	, "uint8_t"  , ""			 , bPrefer, bIsPtr, bIsArray));
    EXPECT_EQ(false, Detect.CheckVariable(RULETYPE_HUNGARIAN	, "uint8_t"  , "u8my_name"   , bPrefer, bIsPtr, bIsArray));
    EXPECT_EQ(false, Detect.CheckVariable(RULETYPE_HUNGARIAN	, "uint8_t"  , "u8my_Name"   , bPrefer, bIsPtr, bIsArray));
    EXPECT_EQ(false, Detect.CheckVariable(RULETYPE_HUNGARIAN	, "uint8_t"  , "u8my_Name"   , bPrefer, bIsPtr, bIsArray));
    EXPECT_EQ(false, Detect.CheckVariable(RULETYPE_HUNGARIAN	, "uint8_t"  , "u16AnyName"  , bPrefer, bIsPtr, bIsArray));
    EXPECT_EQ(false, Detect.CheckVariable(RULETYPE_HUNGARIAN	, "uin16_t"  , "u8AnyName"   , bPrefer, bIsPtr, bIsArray));
    EXPECT_EQ(false, Detect.CheckVariable(RULETYPE_HUNGARIAN	, "uint8_t"  , "u8_my_func"  , bPrefer, bIsPtr, bIsArray));
    EXPECT_EQ(false, Detect.CheckVariable(RULETYPE_HUNGARIAN	, "uin16_t"  , "u16_my_func" , bPrefer, bIsPtr, bIsArray));	
	EXPECT_EQ(false, Detect.CheckVariable(RULETYPE_HUNGARIAN	, "int" 	 , "iMyValue" 	 , bPrefer, true,   bIsArray));
}

//-------------------------------------------------------------------------
// Multiple Cases
TEST(Config_Detect_CheckVariable, GoodCases)
{
	const RULETYPE RuleType = RULETYPE_UPPER_CAMEL;

	RuleOfVariable Rule;
	Detection Detect;

	Rule.WordListMap.insert(std::pair<string, string>("uint8_t", "u8"));

	bool bPrefer = true;
	bool bIsPtr = false;
	bool bIsArray = false;
	Detect.ApplyRuleForVariable(Rule);
    EXPECT_EQ(true, Detect.CheckVariable(RULETYPE_DEFAULT		, "uint8_t", "MyFunc"  , bPrefer, bIsPtr, bIsArray));
    EXPECT_EQ(true, Detect.CheckVariable(RULETYPE_UPPER_CAMEL	, "uint8_t", "MyFunc"  , bPrefer, bIsPtr, bIsArray));
    EXPECT_EQ(true, Detect.CheckVariable(RULETYPE_LOWER_CAMEL	, "uint8_t", "myFunc"  , bPrefer, bIsPtr, bIsArray));
    EXPECT_EQ(true, Detect.CheckVariable(RULETYPE_LOWER_SNAKE   , "uint8_t", "my_func" , bPrefer, bIsPtr, bIsArray));
}

TEST(Config_Detect_CheckVariable, Hungarian_Bad)
{
	RuleOfVariable Rule;
	Detection Detect;

	Rule.WordListMap.insert(std::pair<string, string>("uint8_t", "u8"));

	bool bPrefer = true;
	bool bIsPtr = false;
	bool bIsArray = false;
	Detect.ApplyRuleForVariable(Rule);
	EXPECT_EQ(false, Detect.CheckVariable(RULETYPE_HUNGARIAN, "uint8_t", "MyFunc", bPrefer, bIsPtr, bIsArray));
}

}  // namespace CheckVariable


//==-------------------------------------------------------------------------==
// Detection.CheckEnum()
//==-------------------------------------------------------------------------==
namespace TargetIsEnum {
    TEST(Config_Detect_CheckEnum, UpperCamel)
    {
        RuleOfEnum Rule;
        Detection Detect;        

        EXPECT_EQ(true, Detect.CheckEnumVal(RULETYPE_UPPER_CAMEL, "UsbType10"));
        EXPECT_EQ(false, Detect.CheckEnumVal(RULETYPE_UPPER_CAMEL, "eUsbType11"));
        EXPECT_EQ(true, Detect.CheckEnumVal(RULETYPE_UPPER_CAMEL, "EnUsbType20"));
                
        Rule.IgnorePrefixs.push_back("e_");
        Rule.IgnorePrefixs.push_back("En_");
        Detect.ApplyRuleForEnum(Rule);
        EXPECT_EQ(true, Detect.CheckEnumVal(RULETYPE_UPPER_CAMEL, "UsbType21"));
        EXPECT_EQ(true, Detect.CheckEnumVal(RULETYPE_UPPER_CAMEL, "e_UsbType30"));
        EXPECT_EQ(true, Detect.CheckEnumVal(RULETYPE_UPPER_CAMEL, "En_UsbType31"));
    }

    TEST(Config_Detect_CheckEnum, LowerCamel)
    {
        RuleOfEnum Rule;
        Detection Detect;

        EXPECT_EQ(true, Detect.CheckEnumVal(RULETYPE_LOWER_CAMEL, "usbType10"));
        EXPECT_EQ(true, Detect.CheckEnumVal(RULETYPE_LOWER_CAMEL, "eUsbType11"));
        EXPECT_EQ(false, Detect.CheckEnumVal(RULETYPE_LOWER_CAMEL, "EnUsbType20"));


        Rule.IgnorePrefixs.push_back("e_");
        Rule.IgnorePrefixs.push_back("En_");
        Detect.ApplyRuleForEnum(Rule);
        EXPECT_EQ(true, Detect.CheckEnumVal(RULETYPE_LOWER_CAMEL, "usbType21"));
        EXPECT_EQ(true, Detect.CheckEnumVal(RULETYPE_LOWER_CAMEL, "e_usbType30"));
        EXPECT_EQ(true, Detect.CheckEnumVal(RULETYPE_LOWER_CAMEL, "En_usbType31"));
    }

    TEST(Config_Detect_CheckEnum, LowerSnake)
    {
        RuleOfEnum Rule;
        Detection Detect;

        EXPECT_EQ(true, Detect.CheckEnumVal(RULETYPE_LOWER_SNAKE, "usb_type_10"));
        EXPECT_EQ(true, Detect.CheckEnumVal(RULETYPE_LOWER_SNAKE, "e_usb_type_11"));
        EXPECT_EQ(false, Detect.CheckEnumVal(RULETYPE_LOWER_SNAKE, "En_usb_type_20"));


        Rule.IgnorePrefixs.push_back("e_");
        Rule.IgnorePrefixs.push_back("En_");
        Detect.ApplyRuleForEnum(Rule);
        EXPECT_EQ(true, Detect.CheckEnumVal(RULETYPE_LOWER_SNAKE, "usb_type_10"));
        EXPECT_EQ(true, Detect.CheckEnumVal(RULETYPE_LOWER_SNAKE, "e_usb_type_11"));
        EXPECT_EQ(true, Detect.CheckEnumVal(RULETYPE_LOWER_SNAKE, "En_usb_type_20"));
    }

    TEST(Config_Detect_CheckEnum, UpperSnake)
    {
        RuleOfEnum Rule;
        Detection Detect;

        EXPECT_EQ(true, Detect.CheckEnumVal(RULETYPE_UPPER_SNAKE, "USB_TYPE_10"));
        EXPECT_EQ(false, Detect.CheckEnumVal(RULETYPE_UPPER_SNAKE, "e_USB_TYPE_11"));
        EXPECT_EQ(false, Detect.CheckEnumVal(RULETYPE_UPPER_SNAKE, "En_USB_TYPE_20"));


        Rule.IgnorePrefixs.push_back("e_");
        Rule.IgnorePrefixs.push_back("En_");
        Detect.ApplyRuleForEnum(Rule);
        EXPECT_EQ(true, Detect.CheckEnumVal(RULETYPE_UPPER_SNAKE, "USB_TYPE_10"));
        EXPECT_EQ(true, Detect.CheckEnumVal(RULETYPE_UPPER_SNAKE, "e_USB_TYPE_11"));
        EXPECT_EQ(true, Detect.CheckEnumVal(RULETYPE_UPPER_SNAKE, "En_USB_TYPE_20"));
    }
}


//==-------------------------------------------------------------------------==
// Detection.CheckStruct()
//==-------------------------------------------------------------------------==
namespace TargetIsStruct {
    TEST(Config_Detect_CheckStruct, UpperCamel)
    {
        Detection Detect;
        RuleOfStruct Rule;

        EXPECT_EQ(true, Detect.CheckStructVal(RULETYPE_UPPER_CAMEL, "int", "UsbType10", NOT_PTR));
        EXPECT_EQ(false, Detect.CheckStructVal(RULETYPE_UPPER_CAMEL, "int", "eUsbType11", NOT_PTR));
        EXPECT_EQ(true, Detect.CheckStructVal(RULETYPE_UPPER_CAMEL, "int", "EnUsbType20", NOT_PTR));

        Rule.IgnorePrefixs.push_back("e_");
        Rule.IgnorePrefixs.push_back("En_");
        Detect.ApplyRuleForStruct(Rule);
        EXPECT_EQ(true, Detect.CheckStructVal(RULETYPE_UPPER_CAMEL, "int", "UsbType21", NOT_PTR));
        EXPECT_EQ(true, Detect.CheckStructVal(RULETYPE_UPPER_CAMEL, "int", "e_UsbType30", NOT_PTR));
        EXPECT_EQ(true, Detect.CheckStructVal(RULETYPE_UPPER_CAMEL, "int", "En_UsbType31", NOT_PTR));
    }

    TEST(Config_Detect_CheckStruct, LowerCamel)
    {
        RuleOfStruct Rule;
        Detection Detect;

        EXPECT_EQ(true, Detect.CheckStructVal(RULETYPE_LOWER_CAMEL, "int", "usbType10", NOT_PTR));
        EXPECT_EQ(true, Detect.CheckStructVal(RULETYPE_LOWER_CAMEL, "int", "eUsbType11", NOT_PTR));
        EXPECT_EQ(false, Detect.CheckStructVal(RULETYPE_LOWER_CAMEL, "int", "EnUsbType20", NOT_PTR));


        Rule.IgnorePrefixs.push_back("e_");
        Rule.IgnorePrefixs.push_back("En_");
        Detect.ApplyRuleForStruct(Rule);
        EXPECT_EQ(true, Detect.CheckStructVal(RULETYPE_LOWER_CAMEL, "int", "usbType21", NOT_PTR));
        EXPECT_EQ(true, Detect.CheckStructVal(RULETYPE_LOWER_CAMEL, "int", "e_usbType30", NOT_PTR));
        EXPECT_EQ(true, Detect.CheckStructVal(RULETYPE_LOWER_CAMEL, "int", "En_usbType31", NOT_PTR));
    }

    TEST(Config_Detect_CheckStruct, LowerSnake)
    {
        RuleOfStruct Rule;
        Detection Detect;

        EXPECT_EQ(true, Detect.CheckStructVal(RULETYPE_LOWER_SNAKE, "int", "usb_type_10", NOT_PTR));
        EXPECT_EQ(true, Detect.CheckStructVal(RULETYPE_LOWER_SNAKE, "int", "e_usb_type_11", NOT_PTR));
        EXPECT_EQ(false, Detect.CheckStructVal(RULETYPE_LOWER_SNAKE, "int", "En_usb_type_20", NOT_PTR));


        Rule.IgnorePrefixs.push_back("e_");
        Rule.IgnorePrefixs.push_back("En_");
        Detect.ApplyRuleForStruct(Rule);
        EXPECT_EQ(true, Detect.CheckStructVal(RULETYPE_LOWER_SNAKE, "int", "usb_type_10", NOT_PTR));
        EXPECT_EQ(true, Detect.CheckStructVal(RULETYPE_LOWER_SNAKE, "int", "e_usb_type_11", NOT_PTR));
        EXPECT_EQ(true, Detect.CheckStructVal(RULETYPE_LOWER_SNAKE, "int", "En_usb_type_20", NOT_PTR));
    }

    TEST(Config_Detect_CheckStruct, UpperSnake)
    {
        RuleOfStruct Rule;
        Detection Detect;

        EXPECT_EQ(true, Detect.CheckStructVal(RULETYPE_UPPER_SNAKE, "int", "USB_TYPE_10", NOT_PTR));
        EXPECT_EQ(false, Detect.CheckStructVal(RULETYPE_UPPER_SNAKE, "int", "e_USB_TYPE_11", NOT_PTR));
        EXPECT_EQ(false, Detect.CheckStructVal(RULETYPE_UPPER_SNAKE, "int", "En_USB_TYPE_20", NOT_PTR));


        Rule.IgnorePrefixs.push_back("e_");
        Rule.IgnorePrefixs.push_back("En_");
        Detect.ApplyRuleForStruct(Rule);
        EXPECT_EQ(true, Detect.CheckStructVal(RULETYPE_UPPER_SNAKE, "int", "USB_TYPE_10", NOT_PTR));
        EXPECT_EQ(true, Detect.CheckStructVal(RULETYPE_UPPER_SNAKE, "int", "e_USB_TYPE_11", NOT_PTR));
        EXPECT_EQ(true, Detect.CheckStructVal(RULETYPE_UPPER_SNAKE, "int", "En_USB_TYPE_20", NOT_PTR));
    }
}
// clang-format on
