#include <vector>

#include <gtest/gtest.h>

#include "../Common.h"
#include "../TraceMemo.h"

using namespace namelint;

const string ConfigToml = "\
    [General.Options]                                               \n\
      Version                 = 0.3                                 \n\
      CheckFileName           = false                               \n\
      CheckVariableName       = true                                \n\
      CheckFunctionName       = true                                \n\
      CheckEnum               = true                                \n\
      CheckStruct             = true                                \n\
      AllowedPrintResult      = false                               \n\
      AllowedWriteJsonResult  = false                               \n\
      AllowedUnderscopeChar   = false                               \n\
      AllowedArrayAffected    = false                               \n\
                                                                    \n\
    [General.Rules]                                                 \n\
      FileName                = 0 # 0: Default (UpperCamel)         \n\
                                  # 1: UpperCamel                   \n\
                                  # 3: lower_snake                  \n\
                                                                    \n\
      FunctionName            = 0 # 0: Default (UpperCamel)         \n\
                                  # 1: UpperCamel                   \n\
                                  # 2: lowerCamel                   \n\
                                  # 3: lower_snake                  \n\
                                                                    \n\
      VariableName            = 4 # 0: Default (UpperCamel)         \n\
                                  # 1: UpperCamel                   \n\
                                  # 2: lowerCamel                   \n\
                                  # 3: lower_snake                  \n\
                                  # 4: Hungarian                    \n\
                                                                    \n\
      ClassName               = 0 # 0: Default (UpperCamel)         \n\
                                  # 1: UpperCamel                   \n\
                                  # 2: lowerCamel                   \n\
                                  # 3: lower_snake                  \n\
                                  # 5: UPPER_SNAKE                  \n\
                                                                    \n\
      EnumTagName             = 0 # 0: Default (UpperCamel)         \n\
                                  # 1: UpperCamel                   \n\
                                  # 2: lowerCamel                   \n\
                                  # 3: lower_snake                  \n\
                                  # 5: UPPER_SNAKE                  \n\
                                                                    \n\
      EnumValueName           = 0 # 0: Default (UpperCamel)         \n\
                                  # 1: UpperCamel                   \n\
                                  # 2: lowerCamel                   \n\
                                  # 3: lower_snake                  \n\
                                  # 5: UPPER_SNAKE                  \n\
                                                                    \n\
      StructTagName           = 0 # 0: Default (UpperCamel)         \n\
                                  # 1: UpperCamel                   \n\
                                  # 2: lowerCamel                   \n\
                                  # 3: lower_snake                  \n\
                                  # 5: UPPER_SNAKE                  \n\
                                                                    \n\
      StructValueName         = 4 # 0: Default (UpperCamel)         \n\
                                  # 1: UpperCamel                   \n\
                                  # 2: lowerCamel                   \n\
                                  # 3: lower_snake                  \n\
                                  # 4: Hungarian                    \n\
                                  # 5: UPPER_SNAKE                  \n\
                                                                    \n\
                                                                    \n\
    [Hungarian.Others]                                              \n\
    PreferUpperCamelIfMissed = true                                 \n\
                                                                    \n\
    [Hungarian.NullStringList]                                      \n\
    \"char*\"                  = \"sz\"                             \n\
    \"wchar_t*\"               = \"wsz\"                            \n\
    \"char**\"                 = \"psz\"                            \n\
    \"wchar_t**\"              = \"pwsz\"                           \n\
    \"char[]\"                 = \"sz\"                             \n\
    \"wchar_t[]\"              = \"wsz\"                            \n\
                                                                    \n\
    [Hungarian.WordList]                                            \n\
    # C Primitive Type                                              \n\
    \"void\"                   = \"\"                               \n\
    \"size_t\"                 = \"n\"                              \n\
    \"int8_t\"                 = \"i8\"                             \n\
    \"int16_t\"                = \"i16\"                            \n\
    \"int32_t\"                = \"i32\"                            \n\
    \"int64_t\"                = \"i64\"                            \n\
    \"uint8_t\"                = \"u8\"                             \n\
    \"uint16_t\"               = \"u16\"                            \n\
    \"uint32_t\"               = \"u32\"                            \n\
    \"uint64_t\"               = \"u64\"                            \n\
    \"char\"                   = \"c\"                              \n\
    \"_Bool\"                  = \"b\"                              \n\
    \"bool\"                   = \"b\"                              \n\
    \"wchar_t\"                = \"wc\"                             \n\
    \"signed char\"            = \"sc\"                             \n\
    \"unsigned char\"          = \"uc\"                             \n\
    \"short\"                  = \"s\"                              \n\
    \"short int\"              = \"si\"                             \n\
    \"signed short\"           = \"ss\"                             \n\
    \"signed short int\"       = \"ssi\"                            \n\
    \"unsigned short\"         = \"us\"                             \n\
    \"unsigned short int\"     = \"usi\"                            \n\
    \"int\"                    = \"i\"                              \n\
    \"signed\"                 = \"s\"                              \n\
    \"signed int\"             = \"si\"                             \n\
    \"unsigned\"               = \"u\"                              \n\
    \"unsigned int\"           = \"ui\"                             \n\
    \"long\"                   = \"l\"                              \n\
    \"long int\"               = \"li\"                             \n\
    \"signed long\"            = \"sl\"                             \n\
    \"signed long int\"        = \"sli\"                            \n\
    \"unsigned long\"          = \"ul\"                             \n\
    \"unsigned long int\"      = \"uli\"                            \n\
    \"long long\"              = \"ll\"                             \n\
    \"long long int\"          = \"lli\"                            \n\
    \"signed long long\"       = \"sll\"                            \n\
    \"signed long long int\"   = \"slli\"                           \n\
    \"unsigned long long\"     = \"ull\"                            \n\
    \"unsigned long long int\" = \"ulli\"                           \n\
    \"float\"                  = \"f\"                              \n\
    \"double\"                 = \"d\"                              \n\
    \"long double\"            = \"ld\"                             \n\
                                                                    \n\
    # Windows Type                                                  \n\
    \"ULONG\"                  = \"ul\"                             \n\
    \"DWORD\"                  = \"dw\"                             \n\
    \"DWORD64\"                = \"dw64\"                           \n\
    \"WORD\"                   = \"w\"                              \n\
    \"CHAR\"                   = \"c\"                              \n\
    \"BYTE\"                   = \"by\"                             \n\
    \"HANDLE\"                 = \"h\"                              \n\
    \"BOOLEAN\"                = \"b\"                              \n\
    \"LONGLONG\"               = \"ll\"                             \n\
    ";

namespace RunCheckInvalidDecl {

TEST(MFC, IMPLEMENT_SERIAL) {

  const string SourceCode = "\
                                                                       \n\
    class ToolbarLabel                                                 \n\
      {                                                                \n\
          DECLARE_SERIAL(ToolbarLabel)                                 \n\
                                                                       \n\
      public:                                                          \n\
          ToolbarLabel(UINT uiId = 0, LPCTSTR pStrText = NULL);        \n\
                                                                       \n\
          virtual void OnDraw(CDC* pDc,                                \n\
              const CRect& Rect,                                       \n\
              CBCGPToolBarImages* pImages,                             \n\
              BOOL bHorz                = TRUE,                        \n\
              BOOL bCustomizeMode       = FALSE,                       \n\
              BOOL bHighlight           = FALSE,                       \n\
              BOOL bDrawBorder          = TRUE,                        \n\
              BOOL bGrayDisabledButtons = TRUE);                       \n\
      };                                                               \n\
                                                                       \n\
          IMPLEMENT_SERIAL(ToolbarLabel, CBCGPToolbarButton, 1)        \n\
                                                                       \n\
          ToolbarLabel::ToolbarLabel(UINT uiId, LPCTSTR StrText)       \n\
      {                                                                \n\
          if (StrText != NULL)                                         \n\
          {                                                            \n\
              m_strText = StrText;                                     \n\
          }                                                            \n\
                                                                       \n\
          m_bText = TRUE;                                              \n\
          m_nID = uiId;                                                \n\
          m_iImage = -1;                                               \n\
      }                                                                \n\
    ";

  AppCxt &AppCxt       = AppCxt::getInstance();
  MemoBoard &MemoBoard = AppCxt.MemoBoard;
  MemoBoard.Clear();

  string ErrorReason;
  AppCxt.MemoBoard.Config.LoadStream(ConfigToml, ErrorReason);

  //.........................................................................vvvv <-- Test TARGET
  AppCxt.MemoBoard.Config.GetData()->General.Options.bBypassInvalidDecl = true;
  EXPECT_EQ(true, 0 == RunCheckFormStream(MemoBoard, SourceCode));
  EXPECT_EQ(true, 2 == MemoBoard.Checked.nFunction);
  EXPECT_EQ(true, 0 == MemoBoard.Checked.nParameter);
  EXPECT_EQ(true, 1 == MemoBoard.Checked.nVariable);
  EXPECT_EQ(true, 0 == MemoBoard.Checked.nClass);
  EXPECT_EQ(true, 0 == MemoBoard.Checked.nClass);
  EXPECT_EQ(true, 0 == MemoBoard.Error.nFunction); // <-- This false case is on purpose, because
                                                   //     `bBypassInvalidDecl` is `FALSE`

  //.........................................................................vvvv <-- Test TARGET
  AppCxt.MemoBoard.Config.GetData()->General.Options.bBypassInvalidDecl = false;
  EXPECT_EQ(true, 1 == RunCheckFormStream(MemoBoard, SourceCode));
  EXPECT_EQ(true, 4 == MemoBoard.Checked.nFunction);
  EXPECT_EQ(true, 8 == MemoBoard.Checked.nParameter);
  EXPECT_EQ(true, 2 == MemoBoard.Checked.nVariable);
  EXPECT_EQ(true, 1 == MemoBoard.Checked.nClass);
  EXPECT_EQ(true, 1 == MemoBoard.Error.nFunction); // <-- This false case is on purpose, because
                                                   //     `bBypassInvalidDecl` is `TRUE`
}

} // namespace RunCheckInvalidDecl
