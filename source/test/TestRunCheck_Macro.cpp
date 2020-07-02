#include <vector>

#include <gtest/gtest.h>

#include "../Common.h"
#include "../TraceMemo.h"

#include "TestRunCheck_InputConfig.h"

using namespace namelint;

namespace RunCheckMacro {

TEST(PredefinedMacro, MAX_VALUE_ONLY) {

  const string SourceCode = "\
    #define MAX_VALUE (10) \n\
    ";

  AppCxt &AppCxt       = AppCxt::getInstance();
  MemoBoard &MemoBoard = AppCxt.MemoBoard;
  MemoBoard.Clear();

  string ErrorReason;
  AppCxt.MemoBoard.Config.LoadStream(ConfigTomlHungarian, ErrorReason);

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

  AppCxt &AppCxt       = AppCxt::getInstance();
  MemoBoard &MemoBoard = AppCxt.MemoBoard;
  MemoBoard.Clear();

  string ErrorReason;
  AppCxt.MemoBoard.Config.LoadStream(ConfigTomlHungarian, ErrorReason);

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

  AppCxt &AppCxt       = AppCxt::getInstance();
  MemoBoard &MemoBoard = AppCxt.MemoBoard;
  MemoBoard.Clear();

  string ErrorReason;
  AppCxt.MemoBoard.Config.LoadStream(ConfigTomlHungarian, ErrorReason);

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

  AppCxt &AppCxt       = AppCxt::getInstance();
  MemoBoard &MemoBoard = AppCxt.MemoBoard;
  MemoBoard.Clear();

  string ErrorReason;
  AppCxt.MemoBoard.Config.LoadStream(ConfigTomlHungarian, ErrorReason);

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

  AppCxt &AppCxt       = AppCxt::getInstance();
  MemoBoard &MemoBoard = AppCxt.MemoBoard;
  MemoBoard.Clear();

  string ErrorReason;
  AppCxt.MemoBoard.Config.LoadStream(ConfigTomlHungarian, ErrorReason);

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

  AppCxt &AppCxt       = AppCxt::getInstance();
  MemoBoard &MemoBoard = AppCxt.MemoBoard;
  MemoBoard.Clear();

  string ErrorReason;
  AppCxt.MemoBoard.Config.LoadStream(ConfigTomlHungarian, ErrorReason);

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

  AppCxt &AppCxt       = AppCxt::getInstance();
  MemoBoard &MemoBoard = AppCxt.MemoBoard;
  MemoBoard.Clear();

  string ErrorReason;
  AppCxt.MemoBoard.Config.LoadStream(ConfigTomlHungarian, ErrorReason);

  EXPECT_EQ(true, 0 == RunCheckFormStream(MemoBoard, SourceCode));
  EXPECT_EQ(true, 1 == MemoBoard.Checked.nFunction);
  EXPECT_EQ(true, 2 == MemoBoard.Checked.nVariable);
  EXPECT_EQ(true, 0 == MemoBoard.GetTotalError());
  EXPECT_EQ(true, 0 == MemoBoard.GetTotalAssert());
}

TEST(PredefinedMacro, AAAAAAA) {

  const string SourceCode = "const char* szFile = \"AAAAAAA\";";

  AppCxt &AppCxt       = AppCxt::getInstance();
  MemoBoard &MemoBoard = AppCxt.MemoBoard;
  MemoBoard.Clear();

  string ErrorReason;
  AppCxt.MemoBoard.Config.LoadStream(ConfigTomlHungarian, ErrorReason);

  EXPECT_EQ(true, 0 == RunCheckFormStream(MemoBoard, SourceCode));
  EXPECT_EQ(true, 1 == MemoBoard.Checked.nVariable);
  EXPECT_EQ(true, 1 == MemoBoard.GetTotalChecked());
  EXPECT_EQ(true, 0 == MemoBoard.GetTotalError());
  EXPECT_EQ(true, 0 == MemoBoard.GetTotalAssert());
}

TEST(PredefinedMacro, ___FILE___) {

  const string SourceCode = "const char* szFile = __FILE__;";

  AppCxt &AppCxt       = AppCxt::getInstance();
  MemoBoard &MemoBoard = AppCxt.MemoBoard;
  MemoBoard.Clear();

  string ErrorReason;
  AppCxt.MemoBoard.Config.LoadStream(ConfigTomlHungarian, ErrorReason);

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

  AppCxt &AppCxt       = AppCxt::getInstance();
  MemoBoard &MemoBoard = AppCxt.MemoBoard;
  MemoBoard.Clear();

  string ErrorReason;
  AppCxt.MemoBoard.Config.LoadStream(ConfigTomlHungarian, ErrorReason);

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

  AppCxt &AppCxt       = AppCxt::getInstance();
  MemoBoard &MemoBoard = AppCxt.MemoBoard;
  MemoBoard.Clear();

  shared_ptr<ConfigData> pCfgData = AppCxt.MemoBoard.Config.GetData();

  string ErrorReason;
  AppCxt.MemoBoard.Config.LoadStream(ConfigTomlHungarian, ErrorReason);

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

  AppCxt &AppCxt       = AppCxt::getInstance();
  MemoBoard &MemoBoard = AppCxt.MemoBoard;
  MemoBoard.Clear();

  shared_ptr<ConfigData> pCfgData = AppCxt.MemoBoard.Config.GetData();

  string ErrorReason;
  AppCxt.MemoBoard.Config.LoadStream(ConfigTomlHungarian, ErrorReason);

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

  AppCxt &AppCxt       = AppCxt::getInstance();
  MemoBoard &MemoBoard = AppCxt.MemoBoard;
  MemoBoard.Clear();

  shared_ptr<ConfigData> pCfgData = AppCxt.MemoBoard.Config.GetData();

  string ErrorReason;
  AppCxt.MemoBoard.Config.LoadStream(ConfigTomlHungarian, ErrorReason);

  pCfgData->General.Options.bBypassInvalidDecl = true;
  EXPECT_EQ(true, 3 == RunCheckFormStream(MemoBoard, SourceCode));

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

  AppCxt &AppCxt       = AppCxt::getInstance();
  MemoBoard &MemoBoard = AppCxt.MemoBoard;
  MemoBoard.Clear();

  shared_ptr<ConfigData> pCfgData = AppCxt.MemoBoard.Config.GetData();

  string ErrorReason;
  AppCxt.MemoBoard.Config.LoadStream(ConfigTomlHungarian, ErrorReason);

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

  AppCxt &AppCxt       = AppCxt::getInstance();
  MemoBoard &MemoBoard = AppCxt.MemoBoard;
  MemoBoard.Clear();

  shared_ptr<ConfigData> pCfgData = AppCxt.MemoBoard.Config.GetData();

  string ErrorReason;
  AppCxt.MemoBoard.Config.LoadStream(ConfigTomlHungarian, ErrorReason);

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

  AppCxt &AppCxt       = AppCxt::getInstance();
  MemoBoard &MemoBoard = AppCxt.MemoBoard;
  MemoBoard.Clear();

  shared_ptr<ConfigData> pCfgData = AppCxt.MemoBoard.Config.GetData();

  string ErrorReason;
  AppCxt.MemoBoard.Config.LoadStream(ConfigTomlHungarian, ErrorReason);

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

  AppCxt &AppCxt       = AppCxt::getInstance();
  MemoBoard &MemoBoard = AppCxt.MemoBoard;
  MemoBoard.Clear();

  shared_ptr<ConfigData> pCfgData = AppCxt.MemoBoard.Config.GetData();

  string ErrorReason;
  AppCxt.MemoBoard.Config.LoadStream(ConfigTomlHungarian, ErrorReason);
  pCfgData->General.Options.bBypassInvalidDecl = false;
  pCfgData->Hungarian.NullStringList.push_back(MappingPair("TCHAR[]", "sz"));
  AppCxt.MemoBoard.Config.ReformatCStringMap(pCfgData->Hungarian.NullStringList);
  EXPECT_EQ(true, 0 == RunCheckFormStream(MemoBoard, SourceCode));

  EXPECT_EQ(true, 1 == MemoBoard.GetTotalChecked());
  EXPECT_EQ(true, 1 == MemoBoard.Checked.nVariable);

  EXPECT_EQ(true, 0 == MemoBoard.GetTotalError());

  EXPECT_EQ(true, 0 == MemoBoard.GetTotalError());
  EXPECT_EQ(true, 1 == MemoBoard.Assert.nInvalidDecl);
  EXPECT_EQ(true, 1 == MemoBoard.Assert.nErrorOccurred);
  EXPECT_EQ(true, 0 == MemoBoard.Assert.nNumWarnings);

  AppCxt.MemoBoard.Config.LoadStream(ConfigTomlHungarian, ErrorReason);
  pCfgData->General.Options.bBypassInvalidDecl = true;
  pCfgData->Hungarian.NullStringList.push_back(MappingPair("TCHAR[]", "sz"));
  AppCxt.MemoBoard.Config.ReformatCStringMap(pCfgData->Hungarian.NullStringList);

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

  AppCxt &AppCxt       = AppCxt::getInstance();
  MemoBoard &MemoBoard = AppCxt.MemoBoard;
  MemoBoard.Clear();

  shared_ptr<ConfigData> pCfgData = AppCxt.MemoBoard.Config.GetData();

  string ErrorReason;
  AppCxt.MemoBoard.Config.LoadStream(ConfigTomlHungarian, ErrorReason);
  pCfgData->General.Rules.StructTagName = RULETYPE_UPPER_SNAKE;
  EXPECT_EQ(true, 2 == RunCheckFormStream(MemoBoard, SourceCode));

  EXPECT_EQ(true, 3 == MemoBoard.GetTotalChecked());
  EXPECT_EQ(true, 3 == MemoBoard.Checked.nStruct);

  EXPECT_EQ(true, 2 == MemoBoard.GetTotalError());
  EXPECT_EQ(true, 2 == MemoBoard.Error.nStruct);

  EXPECT_EQ(true, 6 == MemoBoard.GetTotalAssert());
  EXPECT_EQ(true, 3 == MemoBoard.Assert.nInvalidDecl);
  EXPECT_EQ(true, 3 == MemoBoard.Assert.nErrorOccurred);
  EXPECT_EQ(true, 0 == MemoBoard.Assert.nNumWarnings);

  // This macro, `MAX_STR`, invalided decles so checking will passed by config option.
  AppCxt.MemoBoard.Config.LoadStream(ConfigTomlHungarian, ErrorReason);
  pCfgData->General.Options.bBypassInvalidDecl = true;
  pCfgData->General.Rules.StructTagName        = RULETYPE_UPPER_SNAKE;
  EXPECT_EQ(true, 2 == RunCheckFormStream(MemoBoard, SourceCode));

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
