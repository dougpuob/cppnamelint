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
  EXPECT_EQ(true, 0 == MemoBoard.Error.nVariable);
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
  EXPECT_EQ(true, 0 == MemoBoard.Error.nVariable);
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
  EXPECT_EQ(true, 0 == MemoBoard.Error.nVariable);
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
  EXPECT_EQ(true, 0 == MemoBoard.Error.nVariable);
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
  EXPECT_EQ(true, 0 == MemoBoard.Error.nVariable);
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
  EXPECT_EQ(true, 0 == MemoBoard.Error.nVariable);
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
  EXPECT_EQ(true, 0 == MemoBoard.Error.nVariable);
}

TEST(Enum, SCANF_STYLE) {

  const string SourceCode = "\
        #pragma once                                                \n\
                                                                    \n\
        #include \"../Resource.h\"  // main symbols                 \n\
        #include \"../TestView.h\"                                  \n\
                                                                    \n\
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

  string ErrorReason;
  pAppCxt->MemoBoard.Config.LoadStream(ConfigToml, ErrorReason);

  pAppCxt->MemoBoard.Config.GetData()->General.Options.bBypassInvalidDecl = true;
  EXPECT_EQ(true, 0 == RunCheckFormStream(MemoBoard, SourceCode));
  EXPECT_EQ(true, 3 == MemoBoard.Checked.nEnum);
  EXPECT_EQ(true, 3 == MemoBoard.Error.nEnum);
}

TEST(Struct, TCHAR) {

  const string SourceCode = "\
        static TCHAR szHost[MAX_SITE_NUM][10] = {         \n\
                _T(\"Sdhost1\")  //                       \n\
        };                                                \n\
        ";

  APP_CONTEXT *pAppCxt = (APP_CONTEXT *)GetAppCxt();
  MemoBoard &MemoBoard = pAppCxt->MemoBoard;
  MemoBoard.Clear();

  string ErrorReason;
  pAppCxt->MemoBoard.Config.LoadStream(ConfigToml, ErrorReason);
  pAppCxt->MemoBoard.Config.GetData()->General.Options.bBypassInvalidDecl = false;
  pAppCxt->MemoBoard.Config.GetData()->Hungarian.NullStringList.push_back(
      MappingPair("TCHAR[]", "sz"));
  pAppCxt->MemoBoard.Config.ReformatCStringMap(
      pAppCxt->MemoBoard.Config.GetData()->Hungarian.NullStringList);
  EXPECT_EQ(true, 0 == RunCheckFormStream(MemoBoard, SourceCode));
  // PrintTraceMemo(MemoBoard);
  EXPECT_EQ(true, 1 == MemoBoard.Checked.nVariable);
  EXPECT_EQ(true, 0 == MemoBoard.Error.nVariable);
  EXPECT_EQ(true, 1 == MemoBoard.Assert.nInvalidDecl);

  pAppCxt->MemoBoard.Config.LoadStream(ConfigToml, ErrorReason);
  pAppCxt->MemoBoard.Config.GetData()->General.Options.bBypassInvalidDecl = true;
  pAppCxt->MemoBoard.Config.GetData()->Hungarian.NullStringList.push_back(
      MappingPair("TCHAR[]", "sz"));
  pAppCxt->MemoBoard.Config.ReformatCStringMap(
      pAppCxt->MemoBoard.Config.GetData()->Hungarian.NullStringList);
  EXPECT_EQ(true, 0 == RunCheckFormStream(MemoBoard, SourceCode));
  // PrintTraceMemo(MemoBoard);
  EXPECT_EQ(true, 1 == MemoBoard.Checked.nVariable);
  EXPECT_EQ(true, 0 == MemoBoard.Error.nVariable);
  EXPECT_EQ(true, 2 == MemoBoard.Assert.nInvalidDecl);
}

TEST(Struct, CONST_DEF) {

  const string SourceCode = "\
        typedef struct _CONST_DEF                         \n\
        {                                                 \n\
            char cString[MAX_STR];                        \n\
            ULONG ulConstant;                             \n\
        } CONST_DEF, *PCONST_DEF;                         \n\
        ";

  APP_CONTEXT *pAppCxt = (APP_CONTEXT *)GetAppCxt();
  MemoBoard &MemoBoard = pAppCxt->MemoBoard;
  MemoBoard.Clear();

  string ErrorReason;

  pAppCxt->MemoBoard.Config.LoadStream(ConfigToml, ErrorReason);
  pAppCxt->MemoBoard.Config.GetData()->General.Rules.StructTagName = RULETYPE_UPPER_SNAKE;
  EXPECT_EQ(true, 0 == RunCheckFormStream(MemoBoard, SourceCode));
  // PrintTraceMemo(MemoBoard);
  EXPECT_EQ(true, 3 == MemoBoard.Checked.nStruct);
  EXPECT_EQ(true, 0 == MemoBoard.Error.nStruct);
  EXPECT_EQ(true, 3 == MemoBoard.Assert.nInvalidDecl);

  // This macro, `MAX_STR`, invalided decles so checking will passed by config option.
  pAppCxt->MemoBoard.Config.LoadStream(ConfigToml, ErrorReason);
  pAppCxt->MemoBoard.Config.GetData()->General.Options.bBypassInvalidDecl = true;
  pAppCxt->MemoBoard.Config.GetData()->General.Rules.StructTagName        = RULETYPE_UPPER_SNAKE;
  EXPECT_EQ(true, 0 == RunCheckFormStream(MemoBoard, SourceCode));
  // PrintTraceMemo(MemoBoard);
  EXPECT_EQ(true, 3 == MemoBoard.Checked.nStruct);
  EXPECT_EQ(true, 0 == MemoBoard.Error.nStruct);
  EXPECT_EQ(true, 6 == MemoBoard.Assert.nInvalidDecl);
}

// TEST(Struct, THREAD_CONTEXT) {
//
//    const string SourceCode = "\
//        typedef struct _THREAD_CONTEXT                    \n\
//        {                                                 \n\
//            char cScriptFile[MAX_PATH];                   \n\
//                                                          \n\
//            BOOL bForceExitChilds;                        \n\
//            BOOL* pbForceExitParent;                      \n\
//            BOOL bExitParentWhenError;                    \n\
//                                                          \n\
//            HANDLE hThread;                               \n\
//            DWORD dwThread;                               \n\
//            DWORD dwThreadIdx;                            \n\
//        } THREAD_CONTEXT, *PTHREAD_CONTEXT;               \n\
//        ";
//
//    APP_CONTEXT *pAppCxt = (APP_CONTEXT *)GetAppCxt();
//    MemoBoard &MemoBoard = pAppCxt->MemoBoard;
//    MemoBoard.Clear();
//
//    string ErrorReason;
//    pAppCxt->MemoBoard.Config.LoadStream(ConfigToml, ErrorReason);
//
//    pAppCxt->MemoBoard.Config.GetData()->General.Options.bBypassInvalidDecl = true;
//    EXPECT_EQ(true, 0 == RunCheckFormStream(MemoBoard, SourceCode));
//    EXPECT_EQ(true, 3 == MemoBoard.Checked.nEnum);
//    EXPECT_EQ(true, 3 == MemoBoard.Error.nEnum);
//}

} // namespace RunCheckMacro
