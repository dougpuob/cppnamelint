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

  string ErrorReason;
  ((APP_CONTEXT *)GetAppCxt())->MemoBoard.Config.LoadStream(ConfigToml, ErrorReason);
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
    Config* pCfg = (Config*)&GetAppCxt()->MemoBoard.Config;
    shared_ptr<ConfigData> pCfgData = pCfg->GetData();
    pCfg->Clear();

    Detection Detect;
	EXPECT_EQ(true, Detect.CheckFile(RULETYPE_UPPER_CAMEL, "UtestWnd.h"));
	EXPECT_EQ(true, Detect.CheckFile(RULETYPE_UPPER_CAMEL, "SerialPort.h"));
    EXPECT_EQ(true, Detect.CheckFile(RULETYPE_UPPER_CAMEL, "TestName"));
    EXPECT_EQ(true, Detect.CheckFile(RULETYPE_UPPER_CAMEL, "TestName.h"));
    EXPECT_EQ(true, Detect.CheckFile(RULETYPE_UPPER_CAMEL, "TestName.H"));
    EXPECT_EQ(true, Detect.CheckFile(RULETYPE_UPPER_CAMEL, "TestName.cpp"));
    EXPECT_EQ(true, Detect.CheckFile(RULETYPE_UPPER_CAMEL, "TestName.CPP"));

    pCfgData->General.Options.bAllowedUnderscopeChar = true;
	EXPECT_EQ(true, Detect.CheckFile(RULETYPE_UPPER_CAMEL, "Sample_03.c"));
}

TEST(Config_Detect_CheckFile, UpperCamelCase_Bad)
{
    Config* pCfg = (Config*)&GetAppCxt()->MemoBoard.Config;
    shared_ptr<ConfigData> pCfgData = pCfg->GetData();
    pCfg->Clear();

    Detection Detect;
	EXPECT_EQ(false, Detect.CheckFile(RULETYPE_UPPER_CAMEL, "UTestWnd.h"));
    EXPECT_EQ(false, Detect.CheckFile(RULETYPE_UPPER_CAMEL, "testName"));
    EXPECT_EQ(false, Detect.CheckFile(RULETYPE_UPPER_CAMEL, "testName.h"));
    EXPECT_EQ(false, Detect.CheckFile(RULETYPE_UPPER_CAMEL, "testName.cpp"));
}

//-------------------------------------------------------------------------
// LowerCamelCase
TEST(Config_Detect_CheckFile, LowerCamelCase_Good)
{
    Config* pCfg = (Config*)&GetAppCxt()->MemoBoard.Config;
    shared_ptr<ConfigData> pCfgData = pCfg->GetData();
    pCfg->Clear();

    Detection Detect;
    EXPECT_EQ(true, Detect.CheckFile(RULETYPE_LOWER_CAMEL, "testName"));
    EXPECT_EQ(true, Detect.CheckFile(RULETYPE_LOWER_CAMEL, "testName.h"));
    EXPECT_EQ(true, Detect.CheckFile(RULETYPE_LOWER_CAMEL, "testName.H"));
    EXPECT_EQ(true, Detect.CheckFile(RULETYPE_LOWER_CAMEL, "testName.cpp"));
    EXPECT_EQ(true, Detect.CheckFile(RULETYPE_LOWER_CAMEL, "testName.CPP"));
}

TEST(Config_Detect_CheckFile, LowerCamelCase_Bad)
{
    Config* pCfg = (Config*)&GetAppCxt()->MemoBoard.Config;
    shared_ptr<ConfigData> pCfgData = pCfg->GetData();
    pCfg->Clear();

    Detection Detect;
    EXPECT_EQ(false, Detect.CheckFile(RULETYPE_LOWER_CAMEL, "TestName"));
    EXPECT_EQ(false, Detect.CheckFile(RULETYPE_LOWER_CAMEL, "TestName.h"));
    EXPECT_EQ(false, Detect.CheckFile(RULETYPE_LOWER_CAMEL, "TestName.cpp"));
}

//-------------------------------------------------------------------------
// LowerSeperate
TEST(Config_Detect_CheckFile, LowerSeperated_Good)
{
    Config* pCfg = (Config*)&GetAppCxt()->MemoBoard.Config;
    shared_ptr<ConfigData> pCfgData = pCfg->GetData();
    pCfg->Clear();

    Detection Detect;
    EXPECT_EQ(true, Detect.CheckFile(RULETYPE_LOWER_SNAKE, "testname.h"));
    EXPECT_EQ(true, Detect.CheckFile(RULETYPE_LOWER_SNAKE, "testname_.h"));
    EXPECT_EQ(true, Detect.CheckFile(RULETYPE_LOWER_SNAKE, "test_name.h"));
    EXPECT_EQ(true, Detect.CheckFile(RULETYPE_LOWER_SNAKE, "test_name.cpp"));
    EXPECT_EQ(true, Detect.CheckFile(RULETYPE_LOWER_SNAKE, "test_name_.cpp"));
    EXPECT_EQ(true, Detect.CheckFile(RULETYPE_LOWER_SNAKE, "lowername.CPP"));
}

TEST(Config_Detect_CheckFile, LowerSeperated_Bad)
{
    Config* pCfg = (Config*)&GetAppCxt()->MemoBoard.Config;
    shared_ptr<ConfigData> pCfgData = pCfg->GetData();
    pCfg->Clear();

    Detection Detect;
    EXPECT_EQ(false, Detect.CheckFile(RULETYPE_LOWER_SNAKE, "lowerName.cpp"));
    EXPECT_EQ(false, Detect.CheckFile(RULETYPE_LOWER_SNAKE, "testName.cpp"));
    EXPECT_EQ(false, Detect.CheckFile(RULETYPE_LOWER_SNAKE, "test_Name.cpp"));
    EXPECT_EQ(false, Detect.CheckFile(RULETYPE_LOWER_SNAKE, "tesT_name.cpp"));
    EXPECT_EQ(false, Detect.CheckFile(RULETYPE_LOWER_SNAKE, "tesT_Name_.cpp"));
}
}  // namespace CheckFile

//==-------------------------------------------------------------------------==
// Detection.CheckFunction()
//==-------------------------------------------------------------------------==
namespace TargetIsFunction {

 // Input Parameter
TEST(Config_Detect_CheckFunction, InputParms_Good)
{
    Config* pCfg = (Config*)&GetAppCxt()->MemoBoard.Config;
    shared_ptr<ConfigData> pCfgData = pCfg->GetData();
    pCfg->Clear();

    Detection Detect;	
    EXPECT_EQ(true, Detect.CheckFunction(RULETYPE_DEFAULT           , "MyFunc"	));
    EXPECT_EQ(true, Detect.CheckFunction(RULETYPE_UPPER_CAMEL		, "MyFunc"	));
    EXPECT_EQ(true, Detect.CheckFunction(RULETYPE_LOWER_CAMEL		, "myFunc"	));
    EXPECT_EQ(true, Detect.CheckFunction(RULETYPE_LOWER_SNAKE		, "my_func"	));

    pCfgData->General.Options.bAllowedUnderscopeChar = true;
	EXPECT_EQ(true, Detect.CheckFunction(RULETYPE_UPPER_CAMEL		, "MyFunc_"	));
	EXPECT_EQ(true, Detect.CheckFunction(RULETYPE_UPPER_CAMEL		, "Mem_"	));
	EXPECT_EQ(true, Detect.CheckFunction(RULETYPE_UPPER_CAMEL		, "Fun_"	));
}

TEST(Config_Detect_CheckFunction, InputParms_Bad)
{
    Config* pCfg = (Config*)&GetAppCxt()->MemoBoard.Config;
    shared_ptr<ConfigData> pCfgData = pCfg->GetData();
    pCfg->Clear();

    Detection Detect;
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
    Config* pCfg = (Config*)&GetAppCxt()->MemoBoard.Config;
    shared_ptr<ConfigData> pCfgData = pCfg->GetData();
    pCfg->Clear();
    
	Detection Detect;
    EXPECT_EQ(true, Detect.CheckFunction(RULETYPE_UPPER_CAMEL, "UpperCamelFuncName"	));
    EXPECT_EQ(true, Detect.CheckFunction(RULETYPE_UPPER_CAMEL, "UpperCamelFuncName1"));

    auto& IgnoreName= pCfgData->General.IgnoredList.FunctionName;
    auto& IgnorePrefixs = pCfgData->General.IgnoredList.FunctionPrefix;
        
    IgnoreName.push_back("main");
	IgnorePrefixs.push_back("_");
	IgnorePrefixs.push_back("__");
	IgnorePrefixs.push_back("XXX_");
    pCfgData->General.Options.bAllowedUnderscopeChar = false;
    EXPECT_EQ(true, Detect.CheckFunction(RULETYPE_UPPER_CAMEL, "_UpperCamelFuncName"    ));
    EXPECT_EQ(true, Detect.CheckFunction(RULETYPE_UPPER_CAMEL, "__UpperCamelFuncName"   ));
    EXPECT_EQ(true, Detect.CheckFunction(RULETYPE_UPPER_CAMEL, "XXX_UpperCamelFuncName" ));
	EXPECT_EQ(true, Detect.CheckFunction(RULETYPE_UPPER_CAMEL, "MyFunc3"				));
	EXPECT_EQ(true, Detect.CheckFunction(RULETYPE_UPPER_CAMEL, "main"                   ));

    pCfgData->General.Options.bAllowedUnderscopeChar = true;
	EXPECT_EQ(true, Detect.CheckFunction(RULETYPE_UPPER_CAMEL, "_UpperCamelFuncName_"	));
	EXPECT_EQ(true, Detect.CheckFunction(RULETYPE_UPPER_CAMEL, "_UpperCamelFuncName_A"	));
	EXPECT_EQ(true, Detect.CheckFunction(RULETYPE_UPPER_CAMEL, "main"                   ));
    EXPECT_EQ(true, Detect.CheckFunction(RULETYPE_UPPER_CAMEL, "MyFunc3"                ));
    EXPECT_EQ(true, Detect.CheckFunction(RULETYPE_UPPER_CAMEL, "MyFunc_3"               ));
}

TEST(Config_Detect_CheckFunction, UpperCamelCase_Bad)
{
    Config* pCfg = (Config*)&GetAppCxt()->MemoBoard.Config;
    shared_ptr<ConfigData> pCfgData = pCfg->GetData();
    pCfg->Clear();

    Detection Detect;
    EXPECT_EQ(false, Detect.CheckFunction(RULETYPE_UPPER_CAMEL, "UpperCamelFuncName_"   ));
    EXPECT_EQ(false, Detect.CheckFunction(RULETYPE_UPPER_CAMEL, "Upper_CamelFuncName"   ));
    EXPECT_EQ(false, Detect.CheckFunction(RULETYPE_UPPER_CAMEL, "upperCamelFuncName"    ));
    EXPECT_EQ(false, Detect.CheckFunction(RULETYPE_UPPER_CAMEL, "_UpperCamelFuncName"   ));
    EXPECT_EQ(false, Detect.CheckFunction(RULETYPE_UPPER_CAMEL, "UpperCamelFuncName_AB" ));
}

//-------------------------------------------------------------------------
// LowerCamelCase
TEST(Config_Detect_CheckFunction, LowerCamelCase_Good)
{
    Config* pCfg = (Config*)&GetAppCxt()->MemoBoard.Config;
    shared_ptr<ConfigData> pCfgData = pCfg->GetData();
    pCfg->Clear();

    Detection Detect;
    EXPECT_EQ(true, Detect.CheckFunction(RULETYPE_LOWER_CAMEL, "lowerCamelFuncName"    ));
    EXPECT_EQ(true, Detect.CheckFunction(RULETYPE_LOWER_CAMEL, "lower_CamelFuncName"   ));
    EXPECT_EQ(true, Detect.CheckFunction(RULETYPE_LOWER_CAMEL, "lowerCamelFuncName_"   ));
    EXPECT_EQ(true, Detect.CheckFunction(RULETYPE_LOWER_CAMEL, "lowerCamelFuncName1"   ));
}

TEST(Config_Detect_CheckFunction, LowerCamelCase_Bad)
{
    Config* pCfg = (Config*)&GetAppCxt()->MemoBoard.Config;
    shared_ptr<ConfigData> pCfgData = pCfg->GetData();
    pCfg->Clear();

	Detection Detect;
    EXPECT_EQ(false, Detect.CheckFunction(RULETYPE_LOWER_CAMEL, "LowerCamelFuncName"   ));
    EXPECT_EQ(false, Detect.CheckFunction(RULETYPE_LOWER_CAMEL, "_LowerCamelFuncName"  ));
}

//-------------------------------------------------------------------------
// LowerSeperated
TEST(Config_Detect_CheckFunction, LowerSeperatedCase_Good)
{
    Config* pCfg = (Config*)&GetAppCxt()->MemoBoard.Config;
    shared_ptr<ConfigData> pCfgData = pCfg->GetData();
    pCfg->Clear();

    auto& IgnoreName = pCfgData->General.IgnoredList.FunctionName;
    auto& IgnorePrefixs = pCfgData->General.IgnoredList.FunctionPrefix;

    IgnoreName.push_back("main");
    IgnorePrefixs.push_back("_");
    IgnorePrefixs.push_back("__");

	IgnorePrefixs.push_back("_");
	IgnorePrefixs.push_back("__");
	IgnorePrefixs.push_back("XX_");
	IgnorePrefixs.push_back("XX__");
	IgnorePrefixs.push_back("XXX__");

    Detection Detect;
    EXPECT_EQ(true, Detect.CheckFunction(RULETYPE_LOWER_SNAKE, "lower_separated_funcname"   ));
    EXPECT_EQ(true, Detect.CheckFunction(RULETYPE_LOWER_SNAKE, "lower_separated_funcname_"  ));
    EXPECT_EQ(true, Detect.CheckFunction(RULETYPE_LOWER_SNAKE, "lowerseparatedfuncname"     ));

	EXPECT_EQ(true, Detect.CheckFunction(RULETYPE_LOWER_SNAKE, "_lower_separated_funcname"		));
	EXPECT_EQ(true, Detect.CheckFunction(RULETYPE_LOWER_SNAKE, "__lower_separated_funcname"		));
	EXPECT_EQ(true, Detect.CheckFunction(RULETYPE_LOWER_SNAKE, "XX_lower_separated_funcname"	));
	EXPECT_EQ(true, Detect.CheckFunction(RULETYPE_LOWER_SNAKE, "XXX__lower_separated_funcname"	));
}

TEST(Config_Detect_CheckFunction, LowerSeperatedCase_Bad)
{
    Config* pCfg = (Config*)&GetAppCxt()->MemoBoard.Config;
    shared_ptr<ConfigData> pCfgData = pCfg->GetData();
    pCfg->Clear();

	Detection Detect;
    EXPECT_EQ(false, Detect.CheckFunction(RULETYPE_LOWER_SNAKE, "lowerSeparatedFuncName"		));
	EXPECT_EQ(false, Detect.CheckFunction(RULETYPE_LOWER_SNAKE, "lower_separated__funcname_"	));
	EXPECT_EQ(false, Detect.CheckFunction(RULETYPE_LOWER_SNAKE, "lower_separated_funcname__"	));
	EXPECT_EQ(false, Detect.CheckFunction(RULETYPE_LOWER_SNAKE, "_lower_separated_funcname__"	));
	EXPECT_EQ(false, Detect.CheckFunction(RULETYPE_LOWER_SNAKE, "__lower_separated_funcname"	));
	EXPECT_EQ(false, Detect.CheckFunction(RULETYPE_LOWER_SNAKE, "XX_lower_separated_funcname"	));
	EXPECT_EQ(false, Detect.CheckFunction(RULETYPE_LOWER_SNAKE, "XXX__lower_separated_funcname"	));
}
}  // namespace CheckFunction


//==-------------------------------------------------------------------------==
// Detection.CheckVariable()
//==-------------------------------------------------------------------------==
namespace TargetIsVariable {

// Input Parameter
TEST(Config_Detect_CheckVariable, InputParms_Good)
{
    Config* pCfg = (Config*)&GetAppCxt()->MemoBoard.Config;
    shared_ptr<ConfigData> pCfgData = pCfg->GetData();
    pCfg->Clear();

    auto& WordListMap = pCfgData->Hungarian.WordList;
    auto& NullStringMap = pCfgData->Hungarian.NullStringList;
    
	WordListMap.insert(std::pair<string, string>("int"     , "i"));
	WordListMap.insert(std::pair<string, string>("uint8_t" , "u8"));
	WordListMap.insert(std::pair<string, string>("uint16_t", "u16"));

	NullStringMap.push_back(MappingPair("char*"	 , "sz"));
	NullStringMap.push_back(MappingPair("char**"	 , "psz"));
	NullStringMap.push_back(MappingPair("wchar_t*"  , "wsz"));
	NullStringMap.push_back(MappingPair("wchar_t**" , "pwsz"));
    NullStringMap.push_back(MappingPair("char[]"	 , "sz"));
    NullStringMap.push_back(MappingPair("wchar_t[]" , "wsz"));
    pCfg->ReformatCStringMap(NullStringMap);

    Detection Detect;
    // ...........................................................vvvvvvvvv <-- * character should be removed.
	EXPECT_EQ(true, Detect.CheckVariable(RULETYPE_HUNGARIAN		, "char"	, "szStr"      , PREFER_UC, IS_PTR, NOT_ARRAY));
	EXPECT_EQ(true, Detect.CheckVariable(RULETYPE_HUNGARIAN		, "char"	, "pszStr"     , PREFER_UC, IS_PTR, NOT_ARRAY));
	EXPECT_EQ(true, Detect.CheckVariable(RULETYPE_HUNGARIAN		, "wchar_t" , "wszStr"     , PREFER_UC, IS_PTR, NOT_ARRAY));
	EXPECT_EQ(true, Detect.CheckVariable(RULETYPE_HUNGARIAN		, "wchar_t"	, "pwszStr"    , PREFER_UC, IS_PTR, NOT_ARRAY));

    // ...........................................................vvvvvvvvv <-- [] characters should be removed.
    EXPECT_EQ(true, Detect.CheckVariable(RULETYPE_HUNGARIAN		, "char"	, "szStr"      , PREFER_UC, IS_PTR, IS_ARRAY));
    EXPECT_EQ(true, Detect.CheckVariable(RULETYPE_HUNGARIAN		, "wchar_t"	, "wszStr"     , PREFER_UC, IS_PTR, IS_ARRAY));

	EXPECT_EQ(true, Detect.CheckVariable(RULETYPE_HUNGARIAN		, "int"		 , "piMyValue" , PREFER_UC, IS_PTR, NOT_ARRAY));
    EXPECT_EQ(true, Detect.CheckVariable(RULETYPE_DEFAULT		, "uint8_t"  , "MyFunc"    , PREFER_UC, NOT_PTR, NOT_ARRAY));
    EXPECT_EQ(true, Detect.CheckVariable(RULETYPE_UPPER_CAMEL	, "uint8_t"  , "MyFunc"    , PREFER_UC, NOT_PTR, NOT_ARRAY));
    EXPECT_EQ(true, Detect.CheckVariable(RULETYPE_LOWER_CAMEL	, "uint8_t"  , "myFunc"    , PREFER_UC, NOT_PTR, NOT_ARRAY));
    EXPECT_EQ(true, Detect.CheckVariable(RULETYPE_LOWER_SNAKE	, "uint8_t"  , "my_func"   , PREFER_UC, NOT_PTR, NOT_ARRAY));
    EXPECT_EQ(true, Detect.CheckVariable(RULETYPE_HUNGARIAN		, "int"      , "iMyFunc"   , PREFER_UC, NOT_PTR, NOT_ARRAY));
    EXPECT_EQ(true, Detect.CheckVariable(RULETYPE_HUNGARIAN		, "uint8_t"  , "u8MyFunc"  , PREFER_UC, NOT_PTR, NOT_ARRAY));
    EXPECT_EQ(true, Detect.CheckVariable(RULETYPE_HUNGARIAN		, "uint16_t" , "u16MyFunc" , PREFER_UC, NOT_PTR, NOT_ARRAY));
	
    auto& IgnorePrefixs = pCfgData->General.IgnoredList.VariablePrefix;
	IgnorePrefixs.push_back("m_");
    EXPECT_EQ(true, Detect.CheckVariable(RULETYPE_HUNGARIAN		, "int"      , "m_iMyFunc" , PREFER_UC, NOT_PTR, NOT_ARRAY));
}

TEST(Config_Detect_CheckVariable, PreferUpperCamelIfMissed)
{
    Config* pCfg = (Config*)&GetAppCxt()->MemoBoard.Config;
    shared_ptr<ConfigData> pCfgData = pCfg->GetData();
    pCfg->Clear();

    auto& WordListMap = pCfgData->Hungarian.WordList;
    auto& NullStringMap = pCfgData->Hungarian.NullStringList;

    WordListMap.insert(std::pair<string, string>("uint8_t", "u8"));
    WordListMap.insert(std::pair<string, string>("uint16_t", "u16"));

    Detection Detect;
    EXPECT_EQ(true, Detect.CheckVariable(RULETYPE_HUNGARIAN,  "int",     "MyValue", PREFER_UC, NOT_PTR, NOT_ARRAY));
    EXPECT_EQ(false, Detect.CheckVariable(RULETYPE_HUNGARIAN, "uint8_t", "MyValue", PREFER_UC, NOT_PTR, NOT_ARRAY));
}

TEST(Config_Detect_CheckVariable, InputParms_Bad)
{
    Config* pCfg = (Config*)&GetAppCxt()->MemoBoard.Config;
    shared_ptr<ConfigData> pCfgData = pCfg->GetData();
    pCfg->Clear();

    auto& WordListMap = pCfgData->Hungarian.WordList;
    auto& NullStringMap = pCfgData->Hungarian.NullStringList;

    WordListMap.insert(std::pair<string, string>("uint8_t", "u8"));
    WordListMap.insert(std::pair<string, string>("uint16_t", "u16"));

	WordListMap.insert(std::pair<string, string>("uint8_t", "u8"));
	WordListMap.insert(std::pair<string, string>("uin16_t", "u16"));

    Detection Detect;
    EXPECT_EQ(false, Detect.CheckVariable(RULETYPE_DEFAULT		, "uint8_t"  , ""            , PREFER_UC, IS_PTR, IS_ARRAY));
    EXPECT_EQ(false, Detect.CheckVariable(RULETYPE_UPPER_CAMEL	, "uint8_t"  , ""            , PREFER_UC, IS_PTR, IS_ARRAY));
    EXPECT_EQ(false, Detect.CheckVariable(RULETYPE_LOWER_CAMEL	, "uint8_t"  , ""            , PREFER_UC, IS_PTR, IS_ARRAY));
    EXPECT_EQ(false, Detect.CheckVariable(RULETYPE_LOWER_SNAKE	, "uint8_t"  , ""            , PREFER_UC, IS_PTR, IS_ARRAY));
    EXPECT_EQ(false, Detect.CheckVariable(RULETYPE_LOWER_CAMEL	, "uint8_t"  , ""			 , PREFER_UC, IS_PTR, IS_ARRAY));
    EXPECT_EQ(false, Detect.CheckVariable(RULETYPE_HUNGARIAN	, "uint8_t"  , "u8my_name"   , PREFER_UC, IS_PTR, IS_ARRAY));
    EXPECT_EQ(false, Detect.CheckVariable(RULETYPE_HUNGARIAN	, "uint8_t"  , "u8my_Name"   , PREFER_UC, IS_PTR, IS_ARRAY));
    EXPECT_EQ(false, Detect.CheckVariable(RULETYPE_HUNGARIAN	, "uint8_t"  , "u8my_Name"   , PREFER_UC, IS_PTR, IS_ARRAY));
    EXPECT_EQ(false, Detect.CheckVariable(RULETYPE_HUNGARIAN	, "uint8_t"  , "u16AnyName"  , PREFER_UC, IS_PTR, IS_ARRAY));
    EXPECT_EQ(false, Detect.CheckVariable(RULETYPE_HUNGARIAN	, "uin16_t"  , "u8AnyName"   , PREFER_UC, IS_PTR, IS_ARRAY));
    EXPECT_EQ(false, Detect.CheckVariable(RULETYPE_HUNGARIAN	, "uint8_t"  , "u8_my_func"  , PREFER_UC, IS_PTR, IS_ARRAY));
    EXPECT_EQ(false, Detect.CheckVariable(RULETYPE_HUNGARIAN	, "uin16_t"  , "u16_my_func" , PREFER_UC, IS_PTR, IS_ARRAY));
	EXPECT_EQ(false, Detect.CheckVariable(RULETYPE_HUNGARIAN	, "int" 	 , "iMyValue" 	 , PREFER_UC, IS_PTR, IS_ARRAY));
}

//-------------------------------------------------------------------------
// Multiple Cases
TEST(Config_Detect_CheckVariable, GoodCases)
{
    Config* pCfg = (Config*)&GetAppCxt()->MemoBoard.Config;
    shared_ptr<ConfigData> pCfgData = pCfg->GetData();
    pCfg->Clear();

    auto& WordListMap = pCfgData->Hungarian.WordList;
    auto& NullStringMap = pCfgData->Hungarian.NullStringList;

	WordListMap.insert(std::pair<string, string>("uint8_t", "u8"));

    Detection Detect;
    EXPECT_EQ(true, Detect.CheckVariable(RULETYPE_DEFAULT		, "uint8_t", "MyFunc"  , PREFER_UC, IS_PTR, IS_ARRAY));
    EXPECT_EQ(true, Detect.CheckVariable(RULETYPE_UPPER_CAMEL	, "uint8_t", "MyFunc"  , PREFER_UC, IS_PTR, IS_ARRAY));
    EXPECT_EQ(true, Detect.CheckVariable(RULETYPE_LOWER_CAMEL	, "uint8_t", "myFunc"  , PREFER_UC, IS_PTR, IS_ARRAY));
    EXPECT_EQ(true, Detect.CheckVariable(RULETYPE_LOWER_SNAKE   , "uint8_t", "my_func" , PREFER_UC, IS_PTR, IS_ARRAY));
}

TEST(Config_Detect_CheckVariable, Hungarian_Bad)
{
    Config* pCfg = (Config*)&GetAppCxt()->MemoBoard.Config;
    shared_ptr<ConfigData> pCfgData = pCfg->GetData();
    pCfg->Clear();

    auto& WordListMap = pCfgData->Hungarian.WordList;
    auto& NullStringMap = pCfgData->Hungarian.NullStringList;

	WordListMap.insert(std::pair<string, string>("uint8_t", "u8"));

    Detection Detect;
	EXPECT_EQ(false, Detect.CheckVariable(RULETYPE_HUNGARIAN, "uint8_t", "MyFunc", PREFER_UC, IS_PTR, IS_ARRAY));
}

}  // namespace CheckVariable


//==-------------------------------------------------------------------------==
// Detection.CheckEnum()
//==-------------------------------------------------------------------------==
namespace TargetIsEnum {
TEST(Config_Detect_CheckEnum, UpperCamel)
{
    Config* pCfg = (Config*)&GetAppCxt()->MemoBoard.Config;
    shared_ptr<ConfigData> pCfgData = pCfg->GetData();
    pCfg->Clear();

    Detection Detect;
    EXPECT_EQ(true, Detect.CheckEnumVal(RULETYPE_UPPER_CAMEL, "UsbType10"));
    EXPECT_EQ(false, Detect.CheckEnumVal(RULETYPE_UPPER_CAMEL, "eUsbType11"));
    EXPECT_EQ(true, Detect.CheckEnumVal(RULETYPE_UPPER_CAMEL, "EnUsbType20"));
               
    auto& IgnorePrefixs = pCfgData->General.IgnoredList.EnumTagPrefix;

    IgnorePrefixs.push_back("e_");
    IgnorePrefixs.push_back("En_");
    EXPECT_EQ(true, Detect.CheckEnumVal(RULETYPE_UPPER_CAMEL, "UsbType21"));
    EXPECT_EQ(true, Detect.CheckEnumVal(RULETYPE_UPPER_CAMEL, "e_UsbType30"));
    EXPECT_EQ(true, Detect.CheckEnumVal(RULETYPE_UPPER_CAMEL, "En_UsbType31"));
}

TEST(Config_Detect_CheckEnum, LowerCamel)
{
    Config* pCfg = (Config*)&GetAppCxt()->MemoBoard.Config;
    shared_ptr<ConfigData> pCfgData = pCfg->GetData();
    pCfg->Clear();

    Detection Detect;
    EXPECT_EQ(true, Detect.CheckEnumVal(RULETYPE_LOWER_CAMEL, "usbType10"));
    EXPECT_EQ(true, Detect.CheckEnumVal(RULETYPE_LOWER_CAMEL, "eUsbType11"));
    EXPECT_EQ(false, Detect.CheckEnumVal(RULETYPE_LOWER_CAMEL, "EnUsbType20"));


    auto& IgnorePrefixs = pCfgData->General.IgnoredList.EnumTagPrefix;

    IgnorePrefixs.push_back("e_");
    IgnorePrefixs.push_back("En_");
    EXPECT_EQ(true, Detect.CheckEnumVal(RULETYPE_LOWER_CAMEL, "usbType21"));
    EXPECT_EQ(true, Detect.CheckEnumVal(RULETYPE_LOWER_CAMEL, "e_usbType30"));
    EXPECT_EQ(true, Detect.CheckEnumVal(RULETYPE_LOWER_CAMEL, "En_usbType31"));
}

TEST(Config_Detect_CheckEnum, LowerSnake)
{
    Config* pCfg = (Config*)&GetAppCxt()->MemoBoard.Config;
    shared_ptr<ConfigData> pCfgData = pCfg->GetData();
    pCfg->Clear();

    Detection Detect;
    EXPECT_EQ(true, Detect.CheckEnumVal(RULETYPE_LOWER_SNAKE, "usb_type_10"));
    EXPECT_EQ(true, Detect.CheckEnumVal(RULETYPE_LOWER_SNAKE, "e_usb_type_11"));
    EXPECT_EQ(false, Detect.CheckEnumVal(RULETYPE_LOWER_SNAKE, "En_usb_type_20"));

    auto& IgnorePrefixs = pCfgData->General.IgnoredList.EnumTagPrefix;

    IgnorePrefixs.push_back("e_");
    IgnorePrefixs.push_back("En_");
    EXPECT_EQ(true, Detect.CheckEnumVal(RULETYPE_LOWER_SNAKE, "usb_type_10"));
    EXPECT_EQ(true, Detect.CheckEnumVal(RULETYPE_LOWER_SNAKE, "e_usb_type_11"));
    EXPECT_EQ(true, Detect.CheckEnumVal(RULETYPE_LOWER_SNAKE, "En_usb_type_20"));
}

TEST(Config_Detect_CheckEnum, UpperSnake)
{
    Config* pCfg = (Config*)&GetAppCxt()->MemoBoard.Config;
    shared_ptr<ConfigData> pCfgData = pCfg->GetData();
    pCfg->Clear();

    Detection Detect;
    EXPECT_EQ(true, Detect.CheckEnumVal(RULETYPE_UPPER_SNAKE, "USB_TYPE_10"));
    EXPECT_EQ(false, Detect.CheckEnumVal(RULETYPE_UPPER_SNAKE, "e_USB_TYPE_11"));
    EXPECT_EQ(false, Detect.CheckEnumVal(RULETYPE_UPPER_SNAKE, "En_USB_TYPE_20"));

    auto& IgnorePrefixs = pCfgData->General.IgnoredList.EnumTagPrefix;

    IgnorePrefixs.push_back("e_");
    IgnorePrefixs.push_back("En_");
    EXPECT_EQ(true, Detect.CheckEnumVal(RULETYPE_UPPER_SNAKE, "USB_TYPE_10"));
    EXPECT_EQ(true, Detect.CheckEnumVal(RULETYPE_UPPER_SNAKE, "e_USB_TYPE_11"));
    EXPECT_EQ(true, Detect.CheckEnumVal(RULETYPE_UPPER_SNAKE, "En_USB_TYPE_20"));
}}


//==-------------------------------------------------------------------------==
// Detection.CheckStruct()
//==-------------------------------------------------------------------------==
namespace TargetIsStruct {
TEST(Config_Detect_CheckStruct, UpperCamel)
{
    Config* pCfg = (Config*)&GetAppCxt()->MemoBoard.Config;
    shared_ptr<ConfigData> pCfgData = pCfg->GetData();
    pCfg->Clear();

    Detection Detect;
    EXPECT_EQ(true, Detect.CheckStructVal(RULETYPE_UPPER_CAMEL, "int", "UsbType10", NOT_PTR));
    EXPECT_EQ(false, Detect.CheckStructVal(RULETYPE_UPPER_CAMEL, "int", "eUsbType11", NOT_PTR));
    EXPECT_EQ(true, Detect.CheckStructVal(RULETYPE_UPPER_CAMEL, "int", "EnUsbType20", NOT_PTR));

    auto& IgnorePrefixs = pCfgData->General.IgnoredList.StructTagPrefix;            
    IgnorePrefixs.push_back("e_");
    IgnorePrefixs.push_back("En_");

    EXPECT_EQ(true, Detect.CheckStructVal(RULETYPE_UPPER_CAMEL, "int", "UsbType21", NOT_PTR));
    EXPECT_EQ(true, Detect.CheckStructVal(RULETYPE_UPPER_CAMEL, "int", "e_UsbType30", NOT_PTR));
    EXPECT_EQ(true, Detect.CheckStructVal(RULETYPE_UPPER_CAMEL, "int", "En_UsbType31", NOT_PTR));
}

TEST(Config_Detect_CheckStruct, LowerCamel)
{
    Config* pCfg = (Config*)&GetAppCxt()->MemoBoard.Config;
    shared_ptr<ConfigData> pCfgData = pCfg->GetData();
    pCfg->Clear();

    Detection Detect;
    EXPECT_EQ(true, Detect.CheckStructVal(RULETYPE_LOWER_CAMEL, "int", "usbType10", NOT_PTR));
    EXPECT_EQ(true, Detect.CheckStructVal(RULETYPE_LOWER_CAMEL, "int", "eUsbType11", NOT_PTR));
    EXPECT_EQ(false, Detect.CheckStructVal(RULETYPE_LOWER_CAMEL, "int", "EnUsbType20", NOT_PTR));

    auto& IgnorePrefixs = pCfgData->General.IgnoredList.StructTagPrefix;
    IgnorePrefixs.push_back("e_");
    IgnorePrefixs.push_back("En_");

    EXPECT_EQ(true, Detect.CheckStructVal(RULETYPE_LOWER_CAMEL, "int", "usbType21", NOT_PTR));
    EXPECT_EQ(true, Detect.CheckStructVal(RULETYPE_LOWER_CAMEL, "int", "e_usbType30", NOT_PTR));
    EXPECT_EQ(true, Detect.CheckStructVal(RULETYPE_LOWER_CAMEL, "int", "En_usbType31", NOT_PTR));
}

TEST(Config_Detect_CheckStruct, LowerSnake)
{        
    Config* pCfg = (Config*)&GetAppCxt()->MemoBoard.Config;
    shared_ptr<ConfigData> pCfgData = pCfg->GetData();
    pCfg->Clear();

    Detection Detect;
    EXPECT_EQ(true, Detect.CheckStructVal(RULETYPE_LOWER_SNAKE, "int", "usb_type_10", NOT_PTR));
    EXPECT_EQ(true, Detect.CheckStructVal(RULETYPE_LOWER_SNAKE, "int", "e_usb_type_11", NOT_PTR));
    EXPECT_EQ(false, Detect.CheckStructVal(RULETYPE_LOWER_SNAKE, "int", "En_usb_type_20", NOT_PTR));
                
    auto& IgnorePrefixs = pCfgData->General.IgnoredList.StructTagPrefix;
    IgnorePrefixs.push_back("e_");
    IgnorePrefixs.push_back("En_");

    EXPECT_EQ(true, Detect.CheckStructVal(RULETYPE_LOWER_SNAKE, "int", "usb_type_10", NOT_PTR));
    EXPECT_EQ(true, Detect.CheckStructVal(RULETYPE_LOWER_SNAKE, "int", "e_usb_type_11", NOT_PTR));
    EXPECT_EQ(true, Detect.CheckStructVal(RULETYPE_LOWER_SNAKE, "int", "En_usb_type_20", NOT_PTR));
}

TEST(Config_Detect_CheckStruct, UpperSnake)
{
    Config* pCfg = (Config*)&GetAppCxt()->MemoBoard.Config;
    shared_ptr<ConfigData> pCfgData = pCfg->GetData();
    pCfg->Clear();

    Detection Detect;
    EXPECT_EQ(true, Detect.CheckStructVal(RULETYPE_UPPER_SNAKE, "int", "USB_TYPE_10", NOT_PTR));
    EXPECT_EQ(false, Detect.CheckStructVal(RULETYPE_UPPER_SNAKE, "int", "e_USB_TYPE_11", NOT_PTR));
    EXPECT_EQ(false, Detect.CheckStructVal(RULETYPE_UPPER_SNAKE, "int", "En_USB_TYPE_20", NOT_PTR));

    auto& IgnorePrefixs = pCfgData->General.IgnoredList.StructTagPrefix;
    IgnorePrefixs.push_back("e_");
    IgnorePrefixs.push_back("En_");

    EXPECT_EQ(true, Detect.CheckStructVal(RULETYPE_UPPER_SNAKE, "int", "USB_TYPE_10", NOT_PTR));
    EXPECT_EQ(true, Detect.CheckStructVal(RULETYPE_UPPER_SNAKE, "int", "e_USB_TYPE_11", NOT_PTR));
    EXPECT_EQ(true, Detect.CheckStructVal(RULETYPE_UPPER_SNAKE, "int", "En_USB_TYPE_20", NOT_PTR));
}
}
// clang-format on
