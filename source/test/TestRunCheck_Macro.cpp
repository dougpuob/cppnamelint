#include <vector>

#include <gtest/gtest.h>

#include "../Common.h"
#include "../TraceMemo.h"

using namespace namelint;

const string ConfigToml = "\
    [General.Options]                                       \n\
      Version                 = 0.3                         \n\
      CheckFileName           = false                       \n\
      CheckVariableName       = true                        \n\
      CheckFunctionName       = true                        \n\
      CheckEnum               = true                        \n\
      CheckStruct             = true                        \n\
      AllowedPrintResult      = false                       \n\
      AllowedWriteJsonResult  = false                       \n\
      AllowedUnderscopeChar   = false                       \n\
      AllowedArrayAffected    = false                       \n\
                                                            \n\
    [General.Rules]                                         \n\
      FileName                = 0 # 0: Default (UpperCamel) \n\
                                  # 1: UpperCamel           \n\
                                  # 3: lower_snake          \n\
                                                            \n\
      FunctionName            = 0 # 0: Default (UpperCamel) \n\
                                  # 1: UpperCamel           \n\
                                  # 2: lowerCamel           \n\
                                  # 3: lower_snake          \n\
                                                            \n\
      VariableName            = 4 # 0: Default (UpperCamel) \n\
                                  # 1: UpperCamel           \n\
                                  # 2: lowerCamel           \n\
                                  # 3: lower_snake          \n\
                                  # 4: Hungarian            \n\
                                                            \n\
      ClassName               = 0 # 0: Default (UpperCamel) \n\
                                  # 1: UpperCamel           \n\
                                  # 2: lowerCamel           \n\
                                  # 3: lower_snake          \n\
                                  # 5: UPPER_SNAKE          \n\
                                                            \n\
      EnumTagName             = 0 # 0: Default (UpperCamel) \n\
                                  # 1: UpperCamel           \n\
                                  # 2: lowerCamel           \n\
                                  # 3: lower_snake          \n\
                                  # 5: UPPER_SNAKE          \n\
                                                            \n\
      EnumValueName           = 0 # 0: Default (UpperCamel) \n\
                                  # 1: UpperCamel           \n\
                                  # 2: lowerCamel           \n\
                                  # 3: lower_snake          \n\
                                  # 5: UPPER_SNAKE          \n\
                                                            \n\
      StructTagName           = 0 # 0: Default (UpperCamel) \n\
                                  # 1: UpperCamel           \n\
                                  # 2: lowerCamel           \n\
                                  # 3: lower_snake          \n\
                                  # 5: UPPER_SNAKE          \n\
                                                            \n\
      StructValueName         = 4 # 0: Default (UpperCamel) \n\
                                  # 1: UpperCamel           \n\
                                  # 2: lowerCamel           \n\
                                  # 3: lower_snake          \n\
                                  # 4: Hungarian            \n\
                                  # 5: UPPER_SNAKE          \n\
                                                            \n\
    [General.IgnoredList]                                   \n\
    VariablePrefix = [\"m_\"]                               \n\
    EnumTagPrefix = [\"_\", \"e\"]                          \n\
    StructTagPrefix = [\"_\", \"s\"]                        \n\
    FunctionName = [\"main\", \"newASTConsumer\"]           \n\
                                                            \n\
    [Hungarian.Others]                                      \n\
    PreferUpperCamelIfMissed = true                         \n\
                                                            \n\
    [Hungarian.NullStringList]                              \n\
    \"char*\"                  = \"sz\"                     \n\
    \"wchar_t*\"               = \"wsz\"                    \n\
    \"char**\"                 = \"psz\"                    \n\
    \"wchar_t**\"              = \"pwsz\"                   \n\
    \"char[]\"                 = \"sz\"                     \n\
    \"wchar_t[]\"              = \"wsz\"                    \n\
                                                            \n\
    [Hungarian.WordList]                                    \n\
    # C Primitive Type                                      \n\
    \"void\"                   = \"\"                       \n\
    \"size_t\"                 = \"n\"                      \n\
    \"int8_t\"                 = \"i8\"                     \n\
    \"int16_t\"                = \"i16\"                    \n\
    \"int32_t\"                = \"i32\"                    \n\
    \"int64_t\"                = \"i64\"                    \n\
    \"uint8_t\"                = \"u8\"                     \n\
    \"uint16_t\"               = \"u16\"                    \n\
    \"uint32_t\"               = \"u32\"                    \n\
    \"uint64_t\"               = \"u64\"                    \n\
    \"char\"                   = \"c\"                      \n\
    \"_Bool\"                  = \"b\"                      \n\
    \"bool\"                   = \"b\"                      \n\
    \"wchar_t\"                = \"wc\"                     \n\
    \"signed char\"            = \"sc\"                     \n\
    \"unsigned char\"          = \"uc\"                     \n\
    \"short\"                  = \"s\"                      \n\
    \"short int\"              = \"si\"                     \n\
    \"signed short\"           = \"ss\"                     \n\
    \"signed short int\"       = \"ssi\"                    \n\
    \"unsigned short\"         = \"us\"                     \n\
    \"unsigned short int\"     = \"usi\"                    \n\
    \"int\"                    = \"i\"                      \n\
    \"signed\"                 = \"s\"                      \n\
    \"signed int\"             = \"si\"                     \n\
    \"unsigned\"               = \"u\"                      \n\
    \"unsigned int\"           = \"ui\"                     \n\
    \"long\"                   = \"l\"                      \n\
    \"long int\"               = \"li\"                     \n\
    \"signed long\"            = \"sl\"                     \n\
    \"signed long int\"        = \"sli\"                    \n\
    \"unsigned long\"          = \"ul\"                     \n\
    \"unsigned long int\"      = \"uli\"                    \n\
    \"long long\"              = \"ll\"                     \n\
    \"long long int\"          = \"lli\"                    \n\
    \"signed long long\"       = \"sll\"                    \n\
    \"signed long long int\"   = \"slli\"                   \n\
    \"unsigned long long\"     = \"ull\"                    \n\
    \"unsigned long long int\" = \"ulli\"                   \n\
    \"float\"                  = \"f\"                      \n\
    \"double\"                 = \"d\"                      \n\
    \"long double\"            = \"ld\"                     \n\
                                                            \n\
    # Windows Type                                          \n\
    \"ULONG\"                  = \"ul\"                     \n\
    \"DWORD\"                  = \"dw\"                     \n\
    \"DWORD64\"                = \"dw64\"                   \n\
    \"WORD\"                   = \"w\"                      \n\
    \"CHAR\"                   = \"c\"                      \n\
    \"BYTE\"                   = \"by\"                     \n\
    \"HANDLE\"                 = \"h\"                      \n\
    \"BOOLEAN\"                = \"b\"                      \n\
    \"LONGLONG\"               = \"ll\"                     \n\
    ";

namespace RunCheckMacro {

TEST(PredefinedMacro, MAX_VALUE_ONLY) {

  const string SourceCode = "\
    #define MAX_VALUE (10) \n\
    ";

  APP_CONTEXT *pAppCxt = (APP_CONTEXT *)GetAppCxt();
  MemoBoard &MemoBoard = pAppCxt->MemoBoard;
  MemoBoard.Clear();

  string ErrorReason;
  pAppCxt->MemoBoard.Config.LoadStream(ConfigToml, ErrorReason);

  EXPECT_EQ(true, 0 == RunCheckFormStream(MemoBoard, SourceCode));
  EXPECT_EQ(true, 0 == MemoBoard.GetTotalChecked());
  EXPECT_EQ(true, 0 == MemoBoard.GetTotalError());
  EXPECT_EQ(true, 0 == MemoBoard.GetTotalAssert());
}

TEST(PredefinedMacro, MAX_VALUE_is_assigned_to_int_value) {

  const string SourceCode = "\
    #define MAX_VALUE (10) \n\
    int iVal = MAX_VALUE;  \n\
    ";

  APP_CONTEXT *pAppCxt = (APP_CONTEXT *)GetAppCxt();
  MemoBoard &MemoBoard = pAppCxt->MemoBoard;
  MemoBoard.Clear();

  string ErrorReason;
  pAppCxt->MemoBoard.Config.LoadStream(ConfigToml, ErrorReason);

  EXPECT_EQ(true, 0 == RunCheckFormStream(MemoBoard, SourceCode));
  EXPECT_EQ(true, 1 == MemoBoard.GetTotalChecked());
  EXPECT_EQ(true, 1 == MemoBoard.Checked.nVariable);
  EXPECT_EQ(true, 0 == MemoBoard.GetTotalError());
  EXPECT_EQ(true, 0 == MemoBoard.GetTotalAssert());
}

TEST(PredefinedMacro, MAX_VALUE_wrong_before_assignment) {

  const string SourceCode = "\
    #define MAX_VALUE (10)  \n\
    int iVal1 =             \n\
    int iVal2 = MAX_VALUE;  \n\
    ";

  APP_CONTEXT *pAppCxt = (APP_CONTEXT *)GetAppCxt();
  MemoBoard &MemoBoard = pAppCxt->MemoBoard;
  MemoBoard.Clear();

  string ErrorReason;
  pAppCxt->MemoBoard.Config.LoadStream(ConfigToml, ErrorReason);

  EXPECT_EQ(true, 0 == RunCheckFormStream(MemoBoard, SourceCode));
  EXPECT_EQ(true, 1 == MemoBoard.GetTotalChecked());
  EXPECT_EQ(true, 1 == MemoBoard.Checked.nVariable);
  EXPECT_EQ(true, 0 == MemoBoard.GetTotalError());
  EXPECT_EQ(true, 0 == MemoBoard.Assert.nInvalidDecl);
  EXPECT_EQ(true, 1 == MemoBoard.Assert.nErrorOccurred);
  EXPECT_EQ(true, 0 == MemoBoard.Assert.nNumWarnings);
}

TEST(PredefinedMacro, MAX_VALUE_at_bottom_line_unref) {

  const string SourceCode = "\
    const int iMaxVal = 10;         \n\
    const char* szFile1 = __FILE__; \n\
    #define MAX_VALUE (10);         \n\
    ";

  APP_CONTEXT *pAppCxt = (APP_CONTEXT *)GetAppCxt();
  MemoBoard &MemoBoard = pAppCxt->MemoBoard;
  MemoBoard.Clear();

  string ErrorReason;
  pAppCxt->MemoBoard.Config.LoadStream(ConfigToml, ErrorReason);

  EXPECT_EQ(true, 0 == RunCheckFormStream(MemoBoard, SourceCode));
  EXPECT_EQ(true, 2 == MemoBoard.Checked.nVariable);
  EXPECT_EQ(true, 0 == MemoBoard.GetTotalError());
  EXPECT_EQ(true, 0 == MemoBoard.GetTotalAssert());
}

TEST(PredefinedMacro, MAX_VALUE_at_first_line_unref) {

  const string SourceCode = "\
    #define MAX_VALUE (10)              \n\
    const int iMaxVal = 10;             \n\
    const char* szFile1 = __FILE__;     \n\
    ";

  APP_CONTEXT *pAppCxt = (APP_CONTEXT *)GetAppCxt();
  MemoBoard &MemoBoard = pAppCxt->MemoBoard;
  MemoBoard.Clear();

  string ErrorReason;
  pAppCxt->MemoBoard.Config.LoadStream(ConfigToml, ErrorReason);

  EXPECT_EQ(true, 0 == RunCheckFormStream(MemoBoard, SourceCode));
  EXPECT_EQ(true, 2 == MemoBoard.Checked.nVariable);
  EXPECT_EQ(true, 0 == MemoBoard.GetTotalError());
  EXPECT_EQ(true, 0 == MemoBoard.GetTotalAssert());
}

TEST(PredefinedMacro, MAX_VALUE_at_first_line_ref) {

  const string SourceCode = "\
    #define MAX_VALUE (10);             \n\
    const int iMaxVal = MAX_VALUE;      \n\
    const char* szFile1 = __FILE__;     \n\
    ";

  APP_CONTEXT *pAppCxt = (APP_CONTEXT *)GetAppCxt();
  MemoBoard &MemoBoard = pAppCxt->MemoBoard;
  MemoBoard.Clear();

  string ErrorReason;
  pAppCxt->MemoBoard.Config.LoadStream(ConfigToml, ErrorReason);

  EXPECT_EQ(true, 0 == RunCheckFormStream(MemoBoard, SourceCode));
  EXPECT_EQ(true, 2 == MemoBoard.Checked.nVariable);
  EXPECT_EQ(true, 0 == MemoBoard.GetTotalError());
  EXPECT_EQ(true, 0 == MemoBoard.GetTotalAssert());
}

TEST(PredefinedMacro, MAX_VALUE_in_func) {

  const string SourceCode = "\
        void Test()                         \n\
        {                                   \n\
            #define MAX_VALUE (10);         \n\
            const int iMaxVal = MAX_VALUE;  \n\
            const char* szFile1 = __FILE__; \n\
        }                                   \n\
    ";

  APP_CONTEXT *pAppCxt = (APP_CONTEXT *)GetAppCxt();
  MemoBoard &MemoBoard = pAppCxt->MemoBoard;
  MemoBoard.Clear();

  string ErrorReason;
  pAppCxt->MemoBoard.Config.LoadStream(ConfigToml, ErrorReason);

  EXPECT_EQ(true, 0 == RunCheckFormStream(MemoBoard, SourceCode));
  EXPECT_EQ(true, 1 == MemoBoard.Checked.nFunction);
  EXPECT_EQ(true, 2 == MemoBoard.Checked.nVariable);
  EXPECT_EQ(true, 0 == MemoBoard.GetTotalError());
  EXPECT_EQ(true, 0 == MemoBoard.GetTotalAssert());
}

TEST(PredefinedMacro, AAAAAAA) {

  const string SourceCode = "const char* szFile = \"AAAAAAA\";";

  APP_CONTEXT *pAppCxt = (APP_CONTEXT *)GetAppCxt();
  MemoBoard &MemoBoard = pAppCxt->MemoBoard;
  MemoBoard.Clear();

  string ErrorReason;
  pAppCxt->MemoBoard.Config.LoadStream(ConfigToml, ErrorReason);

  EXPECT_EQ(true, 0 == RunCheckFormStream(MemoBoard, SourceCode));
  EXPECT_EQ(true, 1 == MemoBoard.Checked.nVariable);
  EXPECT_EQ(true, 1 == MemoBoard.GetTotalChecked());
  EXPECT_EQ(true, 0 == MemoBoard.GetTotalError());
  EXPECT_EQ(true, 0 == MemoBoard.GetTotalAssert());
}

TEST(PredefinedMacro, ___FILE___) {

  const string SourceCode = "const char* szFile = __FILE__;";

  APP_CONTEXT *pAppCxt = (APP_CONTEXT *)GetAppCxt();
  MemoBoard &MemoBoard = pAppCxt->MemoBoard;
  MemoBoard.Clear();

  string ErrorReason;
  pAppCxt->MemoBoard.Config.LoadStream(ConfigToml, ErrorReason);

  EXPECT_EQ(true, 0 == RunCheckFormStream(MemoBoard, SourceCode));
  EXPECT_EQ(true, 1 == MemoBoard.Checked.nVariable);
  EXPECT_EQ(true, 1 == MemoBoard.GetTotalChecked());
  EXPECT_EQ(true, 0 == MemoBoard.GetTotalError());
  EXPECT_EQ(true, 0 == MemoBoard.GetTotalAssert());
}

TEST(PredefinedMacro, TwoVariables) {

  const string SourceCode = "\
        const char* szFile1 = __FILE__;         \n\
        const char* szFile2 = \"AAAAAAA\";      \n\
        ";

  APP_CONTEXT *pAppCxt = (APP_CONTEXT *)GetAppCxt();
  MemoBoard &MemoBoard = pAppCxt->MemoBoard;
  MemoBoard.Clear();

  string ErrorReason;
  pAppCxt->MemoBoard.Config.LoadStream(ConfigToml, ErrorReason);

  EXPECT_EQ(true, 0 == RunCheckFormStream(MemoBoard, SourceCode));
  EXPECT_EQ(true, 2 == MemoBoard.Checked.nVariable);
  EXPECT_EQ(true, 2 == MemoBoard.GetTotalChecked());
  EXPECT_EQ(true, 0 == MemoBoard.GetTotalError());
  EXPECT_EQ(true, 0 == MemoBoard.GetTotalAssert());
}

TEST(Define, pragma_one_with_include) {

  const string SourceCode = "\
        #pragma once                \n\
        #include \"../Resource.h\"  \n\
        #include \"../TestView.h\"  \n\
        ";

  APP_CONTEXT *pAppCxt = (APP_CONTEXT *)GetAppCxt();
  MemoBoard &MemoBoard = pAppCxt->MemoBoard;
  MemoBoard.Clear();

  shared_ptr<ConfigData> pCfgData = pAppCxt->MemoBoard.Config.GetData();

  string ErrorReason;
  pAppCxt->MemoBoard.Config.LoadStream(ConfigToml, ErrorReason);

  pCfgData->General.Options.bBypassInvalidDecl = true;
  EXPECT_EQ(true, 0 == RunCheckFormStream(MemoBoard, SourceCode));
  EXPECT_EQ(true, 0 == MemoBoard.GetTotalChecked());
  EXPECT_EQ(true, 0 == MemoBoard.GetTotalError());
  EXPECT_EQ(true, 0 == MemoBoard.GetTotalAssert());
}

TEST(Define, _T) {

  const string SourceCode = "\
        #define SETTING_INI_NAME   _T(\"Setting.ini\")              \n\
        #define FT2_SITE_MAP_INI   _T(\"C:\\FT2SiteMapping.ini\")   \n\
        #define FT2_SITE_TABLE_INI _T(\"SiteTable.ini\")            \n\
        ";

  APP_CONTEXT *pAppCxt = (APP_CONTEXT *)GetAppCxt();
  MemoBoard &MemoBoard = pAppCxt->MemoBoard;
  MemoBoard.Clear();

  shared_ptr<ConfigData> pCfgData = pAppCxt->MemoBoard.Config.GetData();

  string ErrorReason;
  pAppCxt->MemoBoard.Config.LoadStream(ConfigToml, ErrorReason);

  pCfgData->General.Options.bBypassInvalidDecl = true;
  EXPECT_EQ(true, 0 == RunCheckFormStream(MemoBoard, SourceCode));
  EXPECT_EQ(true, 0 == MemoBoard.GetTotalChecked());
  EXPECT_EQ(true, 0 == MemoBoard.GetTotalError());
  EXPECT_EQ(true, 0 == MemoBoard.GetTotalAssert());
}

TEST(Enum, define_with_enum) {

  const string SourceCode = "\
        #define SETTING_INI_NAME   _T(\"Setting.ini\")              \n\
        #define FT2_SITE_MAP_INI   _T(\"C:\\FT2SiteMapping.ini\")   \n\
        #define FT2_SITE_TABLE_INI _T(\"SiteTable.ini\")            \n\
                                                                    \n\
        typedef enum _SCANF_STYLE                                   \n\
        {                                                           \n\
            DEC = 0,                                                \n\
            HEX,                                                    \n\
        } SCANF_STYLE;                                              \n\
        ";

  APP_CONTEXT *pAppCxt = (APP_CONTEXT *)GetAppCxt();
  MemoBoard &MemoBoard = pAppCxt->MemoBoard;
  MemoBoard.Clear();

  shared_ptr<ConfigData> pCfgData = pAppCxt->MemoBoard.Config.GetData();

  string ErrorReason;
  pAppCxt->MemoBoard.Config.LoadStream(ConfigToml, ErrorReason);

  pCfgData->General.Options.bBypassInvalidDecl = true;
  EXPECT_EQ(true, 0 == RunCheckFormStream(MemoBoard, SourceCode));

  EXPECT_EQ(true, 3 == MemoBoard.GetTotalChecked());
  EXPECT_EQ(true, 3 == MemoBoard.Checked.nEnum);

  EXPECT_EQ(true, 3 == MemoBoard.GetTotalError());
  EXPECT_EQ(true, 3 == MemoBoard.Error.nEnum);

  EXPECT_EQ(true, 0 == MemoBoard.GetTotalAssert());
}

TEST(Enum, NumbSystem) {

  const string SourceCode = "\
        typedef enum {  \n\
            Dec = 0,    \n\
            Hex,        \n\
        } NumbSystem;   \n\
        ";

  APP_CONTEXT *pAppCxt = (APP_CONTEXT *)GetAppCxt();
  MemoBoard &MemoBoard = pAppCxt->MemoBoard;
  MemoBoard.Clear();

  shared_ptr<ConfigData> pCfgData = pAppCxt->MemoBoard.Config.GetData();

  string ErrorReason;
  pAppCxt->MemoBoard.Config.LoadStream(ConfigToml, ErrorReason);

  pCfgData->General.Options.bBypassInvalidDecl = true;
  EXPECT_EQ(true, 0 == RunCheckFormStream(MemoBoard, SourceCode));

  EXPECT_EQ(true, 3 == MemoBoard.GetTotalChecked());
  EXPECT_EQ(true, 3 == MemoBoard.Checked.nEnum);

  EXPECT_EQ(true, 0 == MemoBoard.GetTotalError());

  EXPECT_EQ(true, 0 == MemoBoard.GetTotalAssert());
}

TEST(Enum, pragma_once_ONLY) {

  const string SourceCode = "\
                #pragma once \n\
        ";

  APP_CONTEXT *pAppCxt = (APP_CONTEXT *)GetAppCxt();
  MemoBoard &MemoBoard = pAppCxt->MemoBoard;
  MemoBoard.Clear();

  shared_ptr<ConfigData> pCfgData = pAppCxt->MemoBoard.Config.GetData();

  string ErrorReason;
  pAppCxt->MemoBoard.Config.LoadStream(ConfigToml, ErrorReason);

  EXPECT_EQ(true, 0 == RunCheckFormStream(MemoBoard, SourceCode));
  EXPECT_EQ(true, 0 == MemoBoard.GetTotalChecked());
  EXPECT_EQ(true, 0 == MemoBoard.GetTotalError());
  EXPECT_EQ(true, 0 == MemoBoard.GetTotalAssert());
}

TEST(Enum, pragma_one_above_enum) {

  const string SourceCode = "\
        #pragma once         \n\
        enum NumbSystem {    \n\
            Dec = 0,         \n\
            Hex,             \n\
        };                   \n\
        ";

  APP_CONTEXT *pAppCxt = (APP_CONTEXT *)GetAppCxt();
  MemoBoard &MemoBoard = pAppCxt->MemoBoard;
  MemoBoard.Clear();

  shared_ptr<ConfigData> pCfgData = pAppCxt->MemoBoard.Config.GetData();

  string ErrorReason;
  pAppCxt->MemoBoard.Config.LoadStream(ConfigToml, ErrorReason);

  EXPECT_EQ(true, 0 == RunCheckFormStream(MemoBoard, SourceCode));

  EXPECT_EQ(true, 3 == MemoBoard.GetTotalChecked());
  EXPECT_EQ(true, 3 == MemoBoard.Checked.nEnum);

  EXPECT_EQ(true, 0 == MemoBoard.GetTotalError());

  EXPECT_EQ(true, 1 == MemoBoard.GetTotalAssert());
  EXPECT_EQ(true, 0 == MemoBoard.Assert.nInvalidDecl);
  EXPECT_EQ(true, 0 == MemoBoard.Assert.nErrorOccurred);
  EXPECT_EQ(true, 1 == MemoBoard.Assert.nNumWarnings); // Got 1 warning, but I don't know why !
}

TEST(Struct, TCHAR) {

  const string SourceCode = "\
        static TCHAR szHost[MAX_SITE_NUM][10] = {   \n\
                _T(\"Sdhost1\")  //                 \n\
        };                                          \n\
        ";

  APP_CONTEXT *pAppCxt = (APP_CONTEXT *)GetAppCxt();
  MemoBoard &MemoBoard = pAppCxt->MemoBoard;
  MemoBoard.Clear();

  shared_ptr<ConfigData> pCfgData = pAppCxt->MemoBoard.Config.GetData();

  string ErrorReason;
  pAppCxt->MemoBoard.Config.LoadStream(ConfigToml, ErrorReason);
  pCfgData->General.Options.bBypassInvalidDecl = false;
  pCfgData->Hungarian.NullStringList.push_back(MappingPair("TCHAR[]", "sz"));
  pAppCxt->MemoBoard.Config.ReformatCStringMap(pCfgData->Hungarian.NullStringList);
  EXPECT_EQ(true, 0 == RunCheckFormStream(MemoBoard, SourceCode));

  EXPECT_EQ(true, 1 == MemoBoard.GetTotalChecked());
  EXPECT_EQ(true, 1 == MemoBoard.Checked.nVariable);

  EXPECT_EQ(true, 0 == MemoBoard.GetTotalError());

  EXPECT_EQ(true, 0 == MemoBoard.GetTotalError());
  EXPECT_EQ(true, 1 == MemoBoard.Assert.nInvalidDecl);
  EXPECT_EQ(true, 1 == MemoBoard.Assert.nErrorOccurred);
  EXPECT_EQ(true, 0 == MemoBoard.Assert.nNumWarnings);

  pAppCxt->MemoBoard.Config.LoadStream(ConfigToml, ErrorReason);
  pCfgData->General.Options.bBypassInvalidDecl = true;
  pCfgData->Hungarian.NullStringList.push_back(MappingPair("TCHAR[]", "sz"));
  pAppCxt->MemoBoard.Config.ReformatCStringMap(pCfgData->Hungarian.NullStringList);

  EXPECT_EQ(true, 0 == RunCheckFormStream(MemoBoard, SourceCode));

  EXPECT_EQ(true, 1 == MemoBoard.GetTotalChecked());
  EXPECT_EQ(true, 1 == MemoBoard.Checked.nVariable);

  EXPECT_EQ(true, 0 == MemoBoard.GetTotalError());

  EXPECT_EQ(true, 4 == MemoBoard.GetTotalAssert());
  EXPECT_EQ(true, 2 == MemoBoard.Assert.nInvalidDecl);
  EXPECT_EQ(true, 2 == MemoBoard.Assert.nErrorOccurred);
  EXPECT_EQ(true, 0 == MemoBoard.Assert.nNumWarnings);
}

TEST(Struct, CONST_DEF) {

  const string SourceCode = "\
        typedef struct _CONST_DEF { \n\
            ULONG ulAA[MAX_STR];    \n\
            ULONG ulBB;             \n\
        } CONST_DEF, *PCONST_DEF;   \n\
        ";

  APP_CONTEXT *pAppCxt = (APP_CONTEXT *)GetAppCxt();
  MemoBoard &MemoBoard = pAppCxt->MemoBoard;
  MemoBoard.Clear();

  shared_ptr<ConfigData> pCfgData = pAppCxt->MemoBoard.Config.GetData();

  string ErrorReason;
  pAppCxt->MemoBoard.Config.LoadStream(ConfigToml, ErrorReason);
  pCfgData->General.Rules.StructTagName = RULETYPE_UPPER_SNAKE;
  EXPECT_EQ(true, 0 == RunCheckFormStream(MemoBoard, SourceCode));

  EXPECT_EQ(true, 3 == MemoBoard.GetTotalChecked());
  EXPECT_EQ(true, 3 == MemoBoard.Checked.nStruct);

  EXPECT_EQ(true, 2 == MemoBoard.GetTotalError());
  EXPECT_EQ(true, 2 == MemoBoard.Error.nStruct);

  EXPECT_EQ(true, 6 == MemoBoard.GetTotalAssert());
  EXPECT_EQ(true, 3 == MemoBoard.Assert.nInvalidDecl);
  EXPECT_EQ(true, 3 == MemoBoard.Assert.nErrorOccurred);
  EXPECT_EQ(true, 0 == MemoBoard.Assert.nNumWarnings);

  // This macro, `MAX_STR`, invalided decles so checking will passed by config option.
  pAppCxt->MemoBoard.Config.LoadStream(ConfigToml, ErrorReason);
  pCfgData->General.Options.bBypassInvalidDecl = true;
  pCfgData->General.Rules.StructTagName        = RULETYPE_UPPER_SNAKE;
  EXPECT_EQ(true, 0 == RunCheckFormStream(MemoBoard, SourceCode));

  EXPECT_EQ(true, 3 == MemoBoard.GetTotalChecked());
  EXPECT_EQ(true, 3 == MemoBoard.Checked.nStruct);

  EXPECT_EQ(true, 2 == MemoBoard.GetTotalError());
  EXPECT_EQ(true, 2 == MemoBoard.Error.nStruct);

  EXPECT_EQ(true, 12 == MemoBoard.GetTotalAssert());
  EXPECT_EQ(true, 6 == MemoBoard.Assert.nInvalidDecl);
  EXPECT_EQ(true, 6 == MemoBoard.Assert.nErrorOccurred);
  EXPECT_EQ(true, 0 == MemoBoard.Assert.nNumWarnings);
}

} // namespace RunCheckMacro
