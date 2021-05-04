#include <vector>

#include <gtest/gtest.h>

#include "../Common.h"
#include "../TraceMemo.h"

using namespace namelint;

const string ConfigToml = "\
    [General.Options]                                           \n\
      Version                 = 0.3                             \n\
      CheckFileName           = false                           \n\
      CheckVariableName       = true                            \n\
      CheckFunctionName       = true                            \n\
      CheckEnum               = true                            \n\
      CheckStruct             = true                            \n\
      CheckClass              = true                            \n\
      AllowedPrintResult      = false                           \n\
      AllowedWriteJsonResult  = false                           \n\
      AllowedUnderscopeChar   = false                           \n\
      AllowedArrayAffected    = false                           \n\
                                                                \n\
    [General.Rules]                                             \n\
      FileName                = 0 # 0: Default (UpperCamel)     \n\
                                  # 1: UpperCamel               \n\
                                  # 3: lower_snake              \n\
                                                                \n\
      FunctionName            = 0 # 0: Default (UpperCamel)     \n\
                                  # 1: UpperCamel               \n\
                                  # 2: lowerCamel               \n\
                                  # 3: lower_snake              \n\
                                                                \n\
      VariableName            = 4 # 0: Default (UpperCamel)     \n\
                                  # 1: UpperCamel               \n\
                                  # 2: lowerCamel               \n\
                                  # 3: lower_snake              \n\
                                  # 4: Hungarian                \n\
                                                                \n\
      ClassName               = 0 # 0: Default (UpperCamel)     \n\
                                  # 1: UpperCamel               \n\
                                  # 2: lowerCamel               \n\
                                  # 3: lower_snake              \n\
                                  # 5: UPPER_SNAKE              \n\
                                                                \n\
      EnumTagName             = 0 # 0: Default (UpperCamel)     \n\
                                  # 1: UpperCamel               \n\
                                  # 2: lowerCamel               \n\
                                  # 3: lower_snake              \n\
                                  # 5: UPPER_SNAKE              \n\
                                                                \n\
      EnumValueName           = 0 # 0: Default (UpperCamel)     \n\
                                  # 1: UpperCamel               \n\
                                  # 2: lowerCamel               \n\
                                  # 3: lower_snake              \n\
                                  # 5: UPPER_SNAKE              \n\
                                                                \n\
      StructTagName           = 0 # 0: Default (UpperCamel)     \n\
                                  # 1: UpperCamel               \n\
                                  # 2: lowerCamel               \n\
                                  # 3: lower_snake              \n\
                                  # 5: UPPER_SNAKE              \n\
                                                                \n\
      StructValueName         = 4 # 0: Default (UpperCamel)     \n\
                                  # 1: UpperCamel               \n\
                                  # 2: lowerCamel               \n\
                                  # 3: lower_snake              \n\
                                  # 4: Hungarian                \n\
                                  # 5: UPPER_SNAKE              \n\
                                                                \n\
                                                                \n\
    [Hungarian.Others]                                          \n\
    PreferUpperCamelIfMissed = true                             \n\
                                                                \n\
    [Hungarian.NullStringList]                                  \n\
    \"char*\"                  = \"sz\"                         \n\
    \"wchar_t*\"               = \"wsz\"                        \n\
    \"char**\"                 = \"psz\"                        \n\
    \"wchar_t**\"              = \"pwsz\"                       \n\
    \"char[]\"                 = \"sz\"                         \n\
    \"wchar_t[]\"              = \"wsz\"                        \n\
                                                                \n\
    [Hungarian.WordList]                                        \n\
    # C Primitive Type                                          \n\
    \"void\"                   = \"\"                           \n\
    \"size_t\"                 = \"n\"                          \n\
    \"int8_t\"                 = \"i8\"                         \n\
    \"int16_t\"                = \"i16\"                        \n\
    \"int32_t\"                = \"i32\"                        \n\
    \"int64_t\"                = \"i64\"                        \n\
    \"uint8_t\"                = \"u8\"                         \n\
    \"uint16_t\"               = \"u16\"                        \n\
    \"uint32_t\"               = \"u32\"                        \n\
    \"uint64_t\"               = \"u64\"                        \n\
    \"char\"                   = \"c\"                          \n\
    \"_Bool\"                  = \"b\"                          \n\
    \"bool\"                   = \"b\"                          \n\
    \"wchar_t\"                = \"wc\"                         \n\
    \"signed char\"            = \"sc\"                         \n\
    \"unsigned char\"          = \"uc\"                         \n\
    \"short\"                  = \"s\"                          \n\
    \"short int\"              = \"si\"                         \n\
    \"signed short\"           = \"ss\"                         \n\
    \"signed short int\"       = \"ssi\"                        \n\
    \"unsigned short\"         = \"us\"                         \n\
    \"unsigned short int\"     = \"usi\"                        \n\
    \"int\"                    = \"i\"                          \n\
    \"signed\"                 = \"s\"                          \n\
    \"signed int\"             = \"si\"                         \n\
    \"unsigned\"               = \"u\"                          \n\
    \"unsigned int\"           = \"ui\"                         \n\
    \"long\"                   = \"l\"                          \n\
    \"long int\"               = \"li\"                         \n\
    \"signed long\"            = \"sl\"                         \n\
    \"signed long int\"        = \"sli\"                        \n\
    \"unsigned long\"          = \"ul\"                         \n\
    \"unsigned long int\"      = \"uli\"                        \n\
    \"long long\"              = \"ll\"                         \n\
    \"long long int\"          = \"lli\"                        \n\
    \"signed long long\"       = \"sll\"                        \n\
    \"signed long long int\"   = \"slli\"                       \n\
    \"unsigned long long\"     = \"ull\"                        \n\
    \"unsigned long long int\" = \"ulli\"                       \n\
    \"float\"                  = \"f\"                          \n\
    \"double\"                 = \"d\"                          \n\
    \"long double\"            = \"ld\"                         \n\
                                                                \n\
    # Windows Type                                              \n\
    \"ULONG\"                  = \"ul\"                         \n\
    \"DWORD\"                  = \"dw\"                         \n\
    \"DWORD64\"                = \"dw64\"                       \n\
    \"WORD\"                   = \"w\"                          \n\
    \"CHAR\"                   = \"c\"                          \n\
    \"BYTE\"                   = \"by\"                         \n\
    \"HANDLE\"                 = \"h\"                          \n\
    \"BOOLEAN\"                = \"b\"                          \n\
    \"LONGLONG\"               = \"ll\"                         \n\
    ";

namespace RunCheckHungarian {

TEST(Variable, Mixed) {
  MemoBoard &MemoBoard = AppCxt::getInstance().MemoBoard;
  MemoBoard.Clear();

  string ErrorReason;
  MemoBoard.Config.LoadStream(ConfigToml, ErrorReason);
  shared_ptr<ConfigData> pCfgData = MemoBoard.Config.GetData();
  pCfgData->Hungarian.WordList.insert(std::pair<string, string>("int", "i"));

  const string SourceCode = "                                                  \n\
        //                                                                         \n\
        // Variables                                                               \n\
        //                                                                         \n\
        wchar_t*                wszWideString               = NULL;                \n\
        size_t                  nVarSize                    = 0;                   \n\
        int8_t                  i8VarInt8                   = 0;                   \n\
        int16_t                 i16VarInt16                 = 0;                   \n\
        int32_t                 i32VarInt32                 = 0;                   \n\
        int64_t                 i64VarInt64                 = 0;                   \n\
        uint8_t                 u8VarUint8                  = 0;                   \n\
        uint16_t                u16VarUint16                = 0;                   \n\
        uint32_t                u32VarUint32                = 0;                   \n\
        uint64_t                u64VarUint64                = 0;                   \n\
        char                    cVarCahr                    = 'C';                 \n\
        _Bool                   bVarBool1                   = false;               \n\
        bool                    bVarBool2                   = false;               \n\
        wchar_t                 wcVarWideChar               = L\"WideCharString\"; \n\
        signed char             scVarSignedChar             = 0;                   \n\
        unsigned char           ucVarUnsignedChar           = 0;                   \n\
        short                   sVarShort                   = 0;                   \n\
        short int               siVarShortInt               = 0;                   \n\
        signed short            ssVarSignedShort            = 0;                   \n\
        signed short int        ssiVarSignedShortInt        = 0;                   \n\
        unsigned short          usVarUnsignedShort          = 0;                   \n\
        unsigned short int      usiVarUnsignedShortInt      = 0;                   \n\
        int                     iVarInt                     = 0;                   \n\
        signed                  sVarSinged                  = 0;                   \n\
        signed int              siVarSignedInt              = 0;                   \n\
        unsigned                uVarUnsigned                = 0;                   \n\
        unsigned int            uiVarUnsignedInt            = 0;                   \n\
        long                    lVarLong                    = 0;                   \n\
        long int                liVarLongInt                = 0;                   \n\
        signed long             slVarSingedLong             = 0;                   \n\
        signed long int         sliVarSingedLongInt         = 0;                   \n\
        unsigned long           ulVarUnsingedLong           = 0;                   \n\
        unsigned long int       uliVarUnsignedLongInt       = 0;                   \n\
        long long               llVarLongLong               = 0;                   \n\
        long long int           lliVarLongLongInt           = 0;                   \n\
        signed long long        sllVarSignedLongLong        = 0;                   \n\
        signed long long int    slliVarSignedLongLongInt    = 0;                   \n\
        unsigned long long      ullVarUnsignedLongLong      = 0;                   \n\
        unsigned long long int  ulliVarUnsignedLongLongInt  = 0;                   \n\
        float                   fVarFloat                   = 0.0;                 \n\
        double                  dVarDouble                  = 0.0;                 \n\
        long double             ldVarLongDouble             = 0.0;                 \n\
                                                                                   \n\
        ULONG                   ulWinVarUlong               = 0;                   \n\
        DWORD                   dwWinVarDword               = 0;                   \n\
        DWORD64                 dw64WinVarDword64           = 0;                   \n\
        WORD                    wWinVarWord                 = 0;                   \n\
        CHAR                    cWinVarChar                 = 'C';                 \n\
        BYTE                    byWinVarByte                = 0;                   \n\
        HANDLE                  hWinVarHandle               = NULL;                \n\
        BOOLEAN                 bWinVarBoolean              = FALSE;               \n\
        LONGLONG                llWinVarLongLong            = 0;                   \n\
        ";

  EXPECT_EQ(true, 0 == RunCheckFormStream(MemoBoard, SourceCode));

  EXPECT_EQ(true, 0 == MemoBoard.Checked.nFile);
  EXPECT_EQ(true, 0 == MemoBoard.Checked.nFunction);
  EXPECT_EQ(true, 0 == MemoBoard.Checked.nParameter);
  EXPECT_EQ(true, 51 == MemoBoard.Checked.nVariable);
  EXPECT_EQ(true, 0 == MemoBoard.Checked.nEnum);
  EXPECT_EQ(true, 0 == MemoBoard.Checked.nStruct);
  EXPECT_EQ(true, 0 == MemoBoard.Checked.nUnion);
  EXPECT_EQ(true, 0 == MemoBoard.Checked.nClass);

  EXPECT_EQ(true, 0 == MemoBoard.Error.nFile);
  EXPECT_EQ(true, 0 == MemoBoard.Error.nFunction);
  EXPECT_EQ(true, 0 == MemoBoard.Error.nParameter);
  EXPECT_EQ(true, 0 == MemoBoard.Error.nVariable);
  EXPECT_EQ(true, 0 == MemoBoard.Error.nEnum);
  EXPECT_EQ(true, 0 == MemoBoard.Error.nStruct);
  EXPECT_EQ(true, 0 == MemoBoard.Error.nUnion);
  EXPECT_EQ(true, 0 == MemoBoard.Error.nClass);
}

TEST(Variable, Integers) {
  MemoBoard &MemoBoard = AppCxt::getInstance().MemoBoard;
  MemoBoard.Clear();

  string ErrorReason;
  MemoBoard.Config.LoadStream(ConfigToml, ErrorReason);
  shared_ptr<ConfigData> pCfgData = MemoBoard.Config.GetData();
  pCfgData->Hungarian.WordList.insert(std::pair<string, string>("int", "i"));

  const string SourceCode = "       \n\
        int iUsbLowSpeed   = 1;     \n\
        int iUsbFullSpeed  = 2      \n\
        int iUsbHighSpeed  = 3;     \n\
        int iUsbSuperSpeed = 4;     \n\
    ";

  EXPECT_EQ(true, 0 == RunCheckFormStream(MemoBoard, SourceCode));

  EXPECT_EQ(true, 0 == MemoBoard.Checked.nFile);
  EXPECT_EQ(true, 0 == MemoBoard.Checked.nFunction);
  EXPECT_EQ(true, 0 == MemoBoard.Checked.nParameter);
  EXPECT_EQ(true, 4 == MemoBoard.Checked.nVariable);
  EXPECT_EQ(true, 0 == MemoBoard.Checked.nEnum);
  EXPECT_EQ(true, 0 == MemoBoard.Checked.nStruct);
  EXPECT_EQ(true, 0 == MemoBoard.Checked.nUnion);
  EXPECT_EQ(true, 0 == MemoBoard.Checked.nClass);

  EXPECT_EQ(true, 0 == MemoBoard.Error.nFile);
  EXPECT_EQ(true, 0 == MemoBoard.Error.nFunction);
  EXPECT_EQ(true, 0 == MemoBoard.Error.nParameter);
  EXPECT_EQ(true, 0 == MemoBoard.Error.nVariable);
  EXPECT_EQ(true, 0 == MemoBoard.Error.nEnum);
  EXPECT_EQ(true, 0 == MemoBoard.Error.nStruct);
  EXPECT_EQ(true, 0 == MemoBoard.Error.nUnion);
  EXPECT_EQ(true, 0 == MemoBoard.Error.nClass);
}

TEST(Variable, IntegerPointers) {
  MemoBoard &MemoBoard = AppCxt::getInstance().MemoBoard;
  MemoBoard.Clear();

  string ErrorReason;
  MemoBoard.Config.LoadStream(ConfigToml, ErrorReason);
  shared_ptr<ConfigData> pCfgData = MemoBoard.Config.GetData();
  pCfgData->Hungarian.WordList.insert(std::pair<string, string>("int", "i"));

  const string SourceCode = "         \n\
        int* piUsbLowSpeed   = NULL;  \n\
        int* piUsbFullSpeed  = NULL   \n\
        int* piUsbHighSpeed  = NULL;  \n\
        int* piUsbSuperSpeed = NULL;  \n\
    ";

  EXPECT_EQ(true, 0 == RunCheckFormStream(MemoBoard, SourceCode));

  EXPECT_EQ(true, 0 == MemoBoard.Checked.nFile);
  EXPECT_EQ(true, 0 == MemoBoard.Checked.nFunction);
  EXPECT_EQ(true, 0 == MemoBoard.Checked.nParameter);
  EXPECT_EQ(true, 4 == MemoBoard.Checked.nVariable);
  EXPECT_EQ(true, 0 == MemoBoard.Checked.nEnum);
  EXPECT_EQ(true, 0 == MemoBoard.Checked.nStruct);
  EXPECT_EQ(true, 0 == MemoBoard.Checked.nUnion);
  EXPECT_EQ(true, 0 == MemoBoard.Checked.nClass);

  EXPECT_EQ(true, 0 == MemoBoard.Error.nFile);
  EXPECT_EQ(true, 0 == MemoBoard.Error.nFunction);
  EXPECT_EQ(true, 0 == MemoBoard.Error.nParameter);
  EXPECT_EQ(true, 0 == MemoBoard.Error.nVariable);
  EXPECT_EQ(true, 0 == MemoBoard.Error.nEnum);
  EXPECT_EQ(true, 0 == MemoBoard.Error.nStruct);
  EXPECT_EQ(true, 0 == MemoBoard.Error.nUnion);
  EXPECT_EQ(true, 0 == MemoBoard.Error.nClass);
}

TEST(Variable, IntegerArraies) {
  MemoBoard &MemoBoard = AppCxt::getInstance().MemoBoard;
  MemoBoard.Clear();

  string ErrorReason;
  MemoBoard.Config.LoadStream(ConfigToml, ErrorReason);
  shared_ptr<ConfigData> pCfgData = MemoBoard.Config.GetData();
  pCfgData->Hungarian.WordList.insert(std::pair<string, string>("int", "i"));

  const string SourceCode = "         \n\
        int iUsbLowSpeed[8]   = {0};  \n\
        int iUsbFullSpeed[8]  = {0}   \n\
        int iUsbHighSpeed[8]  = {0};  \n\
        int iUsbSuperSpeed[8] = {0};  \n\
    ";

  EXPECT_EQ(true, 0 == RunCheckFormStream(MemoBoard, SourceCode));

  EXPECT_EQ(true, 0 == MemoBoard.Checked.nFile);
  EXPECT_EQ(true, 0 == MemoBoard.Checked.nFunction);
  EXPECT_EQ(true, 0 == MemoBoard.Checked.nParameter);
  EXPECT_EQ(true, 4 == MemoBoard.Checked.nVariable);
  EXPECT_EQ(true, 0 == MemoBoard.Checked.nEnum);
  EXPECT_EQ(true, 0 == MemoBoard.Checked.nStruct);
  EXPECT_EQ(true, 0 == MemoBoard.Checked.nUnion);
  EXPECT_EQ(true, 0 == MemoBoard.Checked.nClass);

  EXPECT_EQ(true, 0 == MemoBoard.Error.nFile);
  EXPECT_EQ(true, 0 == MemoBoard.Error.nFunction);
  EXPECT_EQ(true, 0 == MemoBoard.Error.nParameter);
  EXPECT_EQ(true, 0 == MemoBoard.Error.nVariable);
  EXPECT_EQ(true, 0 == MemoBoard.Error.nEnum);
  EXPECT_EQ(true, 0 == MemoBoard.Error.nStruct);
  EXPECT_EQ(true, 0 == MemoBoard.Error.nUnion);
  EXPECT_EQ(true, 0 == MemoBoard.Error.nClass);
}

TEST(Enum, UsbEndpointDescriptor) {
  MemoBoard &MemoBoard = AppCxt::getInstance().MemoBoard;
  MemoBoard.Clear();

  string ErrorReason;
  MemoBoard.Config.LoadStream(ConfigToml, ErrorReason);
  shared_ptr<ConfigData> pCfgData = MemoBoard.Config.GetData();

  const string SourceCode = "           \n\
        typedef enum _UsbDeviceSpeed {  \n\
            UsbLowSpeed = 0,            \n\
            UsbFullSpeed,               \n\
            UsbHighSpeed,               \n\
            UsbSuperSpeed               \n\
        } UsbDeviceSpeed;               \n\
    ";

  pCfgData->General.IgnoredList.EnumTagPrefix.push_back("_");
  EXPECT_EQ(true, 0 == RunCheckFormStream(MemoBoard, SourceCode));

  EXPECT_EQ(true, 0 == MemoBoard.Checked.nFile);
  EXPECT_EQ(true, 0 == MemoBoard.Checked.nFunction);
  EXPECT_EQ(true, 0 == MemoBoard.Checked.nParameter);
  EXPECT_EQ(true, 0 == MemoBoard.Checked.nVariable);
  EXPECT_EQ(true, 5 == MemoBoard.Checked.nEnum);
  EXPECT_EQ(true, 0 == MemoBoard.Checked.nStruct);
  EXPECT_EQ(true, 0 == MemoBoard.Checked.nUnion);
  EXPECT_EQ(true, 0 == MemoBoard.Checked.nClass);

  EXPECT_EQ(true, 0 == MemoBoard.Error.nFile);
  EXPECT_EQ(true, 0 == MemoBoard.Error.nFunction);
  EXPECT_EQ(true, 0 == MemoBoard.Error.nParameter);
  EXPECT_EQ(true, 0 == MemoBoard.Error.nVariable);
  EXPECT_EQ(true, 0 == MemoBoard.Error.nEnum);
  EXPECT_EQ(true, 0 == MemoBoard.Error.nStruct);
  EXPECT_EQ(true, 0 == MemoBoard.Error.nUnion);
  EXPECT_EQ(true, 0 == MemoBoard.Error.nClass);
}

TEST(Struct, UsbEndpointDescriptor) {
  MemoBoard &MemoBoard = AppCxt::getInstance().MemoBoard;
  MemoBoard.Clear();

  string ErrorReason;
  MemoBoard.Config.LoadStream(ConfigToml, ErrorReason);
  shared_ptr<ConfigData> pCfgData = MemoBoard.Config.GetData();

  const string SourceCode = "                      \n\
        typedef struct _UsbEndpointDescriptor {    \n\
            uint8_t   u8Length;                    \n\
            uint8_t   u8DescriptorType;            \n\
            uint8_t   u8EndpointAddress;           \n\
            uint8_t   u8Attributes;                \n\
            uint16_t  u16MaxPacketSize;            \n\
            uint8_t   u8Interval;                  \n\
        } UsbEndpointDescriptor;                   \n\
    ";

  pCfgData->General.IgnoredList.StructTagPrefix.push_back("_");
  pCfgData->Hungarian.WordList.insert(std::pair<string, string>("uint8_t", "u8"));
  pCfgData->Hungarian.WordList.insert(std::pair<string, string>("uint16_t", "u16"));

  EXPECT_EQ(true, 0 == RunCheckFormStream(MemoBoard, SourceCode));

  EXPECT_EQ(true, 0 == MemoBoard.Checked.nFile);
  EXPECT_EQ(true, 0 == MemoBoard.Checked.nFunction);
  EXPECT_EQ(true, 0 == MemoBoard.Checked.nParameter);
  EXPECT_EQ(true, 0 == MemoBoard.Checked.nVariable);
  EXPECT_EQ(true, 0 == MemoBoard.Checked.nEnum);
  EXPECT_EQ(true, 7 == MemoBoard.Checked.nStruct);
  EXPECT_EQ(true, 0 == MemoBoard.Checked.nUnion);
  EXPECT_EQ(true, 0 == MemoBoard.Checked.nClass);

  EXPECT_EQ(true, 0 == MemoBoard.Error.nFile);
  EXPECT_EQ(true, 0 == MemoBoard.Error.nFunction);
  EXPECT_EQ(true, 0 == MemoBoard.Error.nParameter);
  EXPECT_EQ(true, 0 == MemoBoard.Error.nVariable);
  EXPECT_EQ(true, 0 == MemoBoard.Error.nEnum);
  EXPECT_EQ(true, 0 == MemoBoard.Error.nStruct);
  EXPECT_EQ(true, 0 == MemoBoard.Error.nUnion);
  EXPECT_EQ(true, 0 == MemoBoard.Error.nClass);
}

TEST(Function, FnPtr) {
  MemoBoard &MemoBoard = AppCxt::getInstance().MemoBoard;
  MemoBoard.Clear();

  string ErrorReason;
  MemoBoard.Config.LoadStream(ConfigToml, ErrorReason);
  shared_ptr<ConfigData> pCfgData = MemoBoard.Config.GetData();

  const string SourceCode = "            \n\
        int (*pFnName1)(int, int);       \n\
        int (*pFnName2)(int iA, int iB); \n\
        ";

  EXPECT_EQ(true, 0 == RunCheckFormStream(MemoBoard, SourceCode));

  EXPECT_EQ(true, 0 == MemoBoard.Checked.nFile);
  EXPECT_EQ(true, 0 == MemoBoard.Checked.nFunction);
  EXPECT_EQ(true, 2 == MemoBoard.Checked.nParameter);
  EXPECT_EQ(true, 2 == MemoBoard.Checked.nVariable);
  EXPECT_EQ(true, 0 == MemoBoard.Checked.nEnum);
  EXPECT_EQ(true, 0 == MemoBoard.Checked.nStruct);
  EXPECT_EQ(true, 0 == MemoBoard.Checked.nUnion);
  EXPECT_EQ(true, 0 == MemoBoard.Checked.nClass);

  EXPECT_EQ(true, 0 == MemoBoard.Error.nFile);
  EXPECT_EQ(true, 0 == MemoBoard.Error.nFunction);
  EXPECT_EQ(true, 0 == MemoBoard.Error.nParameter);
  EXPECT_EQ(true, 0 == MemoBoard.Error.nVariable);
  EXPECT_EQ(true, 0 == MemoBoard.Error.nEnum);
  EXPECT_EQ(true, 0 == MemoBoard.Error.nStruct);
  EXPECT_EQ(true, 0 == MemoBoard.Error.nUnion);
  EXPECT_EQ(true, 0 == MemoBoard.Error.nClass);
}

TEST(Function, MemCpy) {
  MemoBoard &MemoBoard = AppCxt::getInstance().MemoBoard;
  MemoBoard.Clear();

  string ErrorReason;
  MemoBoard.Config.LoadStream(ConfigToml, ErrorReason);
  shared_ptr<ConfigData> pCfgData = MemoBoard.Config.GetData();

  const string SourceCode = "                               \n\
        void *                                              \n\
        MemCpy (void *pDest, const void *pSrc, size_t nLen) \n\
        {                                                   \n\
          char *pcD = pDest;                                 \n\
          const char *pcS = pSrc;                            \n\
          while (nLen--)                                    \n\
            *pcD++ = *pcS++;                                  \n\
          return pDest;                                     \n\
        }                                                   \n\
        ";

  EXPECT_EQ(true, 0 == RunCheckFormStream(MemoBoard, SourceCode));

  EXPECT_EQ(true, 0 == MemoBoard.Checked.nFile);
  EXPECT_EQ(true, 1 == MemoBoard.Checked.nFunction);
  EXPECT_EQ(true, 3 == MemoBoard.Checked.nParameter);
  EXPECT_EQ(true, 2 == MemoBoard.Checked.nVariable);
  EXPECT_EQ(true, 0 == MemoBoard.Checked.nEnum);
  EXPECT_EQ(true, 0 == MemoBoard.Checked.nStruct);
  EXPECT_EQ(true, 0 == MemoBoard.Checked.nUnion);
  EXPECT_EQ(true, 0 == MemoBoard.Checked.nClass);

  EXPECT_EQ(true, 0 == MemoBoard.Error.nFile);
  EXPECT_EQ(true, 0 == MemoBoard.Error.nFunction);
  EXPECT_EQ(true, 0 == MemoBoard.Error.nParameter);
  EXPECT_EQ(true, 0 == MemoBoard.Error.nVariable);
  EXPECT_EQ(true, 0 == MemoBoard.Error.nEnum);
  EXPECT_EQ(true, 0 == MemoBoard.Error.nStruct);
  EXPECT_EQ(true, 0 == MemoBoard.Error.nUnion);
  EXPECT_EQ(true, 0 == MemoBoard.Error.nClass);
}

TEST(Class, DataClass) {
  MemoBoard &MemoBoard = AppCxt::getInstance().MemoBoard;
  MemoBoard.Clear();

  string ErrorReason;
  MemoBoard.Config.LoadStream(ConfigToml, ErrorReason);
  shared_ptr<ConfigData> pCfgData = MemoBoard.Config.GetData();

  const string SourceCode = "                              \n\
        class DateClass                                    \n\
        {                                                  \n\
        private:                                           \n\
            int m_iYear;                                   \n\
            int m_iMonth;                                  \n\
            int m_iDday;                                   \n\
                                                           \n\
        public:                                            \n\
            DateClass(int iYear, int iMonth, int iDay)     \n\
            {                                              \n\
                setDate(iYear, iMonth, iDay);              \n\
            }                                              \n\
                                                           \n\
            ~DateClass() {};                               \n\
                                                           \n\
            void SetDate(int iYear, int iMonth, int iDay)  \n\
            {                                              \n\
                m_iYear = iYear;                           \n\
                m_iMonth = iMonth;                         \n\
                m_iDday = iDay;                            \n\
            }                                              \n\
                                                           \n\
            int GetYear()  { return m_iYear;  }            \n\
            int GetMonth() { return m_iMonth; }            \n\
            int GetDay()   { return m_iDday;  }            \n\
        };                                                 \n\
        ";

  pCfgData->General.IgnoredList.VariablePrefix.push_back("m_");

  EXPECT_EQ(true, 0 == RunCheckFormStream(MemoBoard, SourceCode));

  EXPECT_EQ(true, 0 == MemoBoard.Checked.nFile);
  EXPECT_EQ(true, 6 == MemoBoard.Checked.nFunction);
  EXPECT_EQ(true, 6 == MemoBoard.Checked.nParameter);
  EXPECT_EQ(true, 3 == MemoBoard.Checked.nVariable);
  EXPECT_EQ(true, 0 == MemoBoard.Checked.nEnum);
  EXPECT_EQ(true, 0 == MemoBoard.Checked.nStruct);
  EXPECT_EQ(true, 0 == MemoBoard.Checked.nUnion);
  EXPECT_EQ(true, 1 == MemoBoard.Checked.nClass);

  EXPECT_EQ(true, 0 == MemoBoard.Error.nFile);
  EXPECT_EQ(true, 0 == MemoBoard.Error.nFunction);
  EXPECT_EQ(true, 0 == MemoBoard.Error.nParameter);
  EXPECT_EQ(true, 0 == MemoBoard.Error.nVariable);
  EXPECT_EQ(true, 0 == MemoBoard.Error.nEnum);
  EXPECT_EQ(true, 0 == MemoBoard.Error.nStruct);
  EXPECT_EQ(true, 0 == MemoBoard.Error.nUnion);
  EXPECT_EQ(true, 0 == MemoBoard.Error.nClass);
}

// TODO: Seems this function never be supported.
TEST(MacroFunction, GetMin) {
  MemoBoard &MemoBoard = AppCxt::getInstance().MemoBoard;
  MemoBoard.Clear();

  string ErrorReason;
  MemoBoard.Config.LoadStream(ConfigToml, ErrorReason);
  shared_ptr<ConfigData> pCfgData = MemoBoard.Config.GetData();

  const string SourceCode = "#define GetMin(X, Y) ((X) < (Y) ? (X) : (Y))";

  EXPECT_EQ(true, 0 == RunCheckFormStream(MemoBoard, SourceCode));

  EXPECT_EQ(true, 0 == MemoBoard.Checked.nFile);
  EXPECT_EQ(true, 0 == MemoBoard.Checked.nFunction);
  EXPECT_EQ(true, 0 == MemoBoard.Checked.nParameter);
  EXPECT_EQ(true, 0 == MemoBoard.Checked.nVariable);
  EXPECT_EQ(true, 0 == MemoBoard.Checked.nEnum);
  EXPECT_EQ(true, 0 == MemoBoard.Checked.nStruct);
  EXPECT_EQ(true, 0 == MemoBoard.Checked.nUnion);
  EXPECT_EQ(true, 0 == MemoBoard.Checked.nClass);

  EXPECT_EQ(true, 0 == MemoBoard.Error.nFile);
  EXPECT_EQ(true, 0 == MemoBoard.Error.nFunction);
  EXPECT_EQ(true, 0 == MemoBoard.Error.nParameter);
  EXPECT_EQ(true, 0 == MemoBoard.Error.nVariable);
  EXPECT_EQ(true, 0 == MemoBoard.Error.nEnum);
  EXPECT_EQ(true, 0 == MemoBoard.Error.nStruct);
  EXPECT_EQ(true, 0 == MemoBoard.Error.nUnion);
  EXPECT_EQ(true, 0 == MemoBoard.Error.nClass);
}

} // namespace RunCheckHungarian
