#include <vector>

#include <gtest/gtest.h>

#include "../Common.h"
#include "../TraceMemo.h"

int RunCheckFormStream(namelint::MemoBoard &Memo, const string &SourceContent);

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
    ";

namespace RunCheckHungarian {

TEST(Variable, Integers) {
  MemoBoard &MemoBoard = ((APP_CONTEXT *)GetAppCxt())->MemoBoard;
  MemoBoard.Clear();

  string ErrorReason;
  MemoBoard.Config.LoadStream(ConfigToml, ErrorReason);
  shared_ptr<ConfigData> pCfgData = MemoBoard.Config.GetData();
  pCfgData->Hungarian.WordList.insert(std::pair<string, string>("int", "i"));

  const string SourceCode = " \n\
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
  EXPECT_EQ(true, 0 == MemoBoard.Checked.nClass);

  EXPECT_EQ(true, 0 == MemoBoard.Error.nFile);
  EXPECT_EQ(true, 0 == MemoBoard.Error.nFunction);
  EXPECT_EQ(true, 0 == MemoBoard.Error.nParameter);
  EXPECT_EQ(true, 0 == MemoBoard.Error.nVariable);
  EXPECT_EQ(true, 0 == MemoBoard.Error.nEnum);
  EXPECT_EQ(true, 0 == MemoBoard.Error.nStruct);
  EXPECT_EQ(true, 0 == MemoBoard.Error.nClass);
}

TEST(Variable, IntegerPointers) {
  MemoBoard &MemoBoard = ((APP_CONTEXT *)GetAppCxt())->MemoBoard;
  MemoBoard.Clear();

  string ErrorReason;
  MemoBoard.Config.LoadStream(ConfigToml, ErrorReason);
  shared_ptr<ConfigData> pCfgData = MemoBoard.Config.GetData();
  pCfgData->Hungarian.WordList.insert(std::pair<string, string>("int", "i"));

  const string SourceCode = "   \n\
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
  EXPECT_EQ(true, 0 == MemoBoard.Checked.nClass);

  EXPECT_EQ(true, 0 == MemoBoard.Error.nFile);
  EXPECT_EQ(true, 0 == MemoBoard.Error.nFunction);
  EXPECT_EQ(true, 0 == MemoBoard.Error.nParameter);
  EXPECT_EQ(true, 0 == MemoBoard.Error.nVariable);
  EXPECT_EQ(true, 0 == MemoBoard.Error.nEnum);
  EXPECT_EQ(true, 0 == MemoBoard.Error.nStruct);
  EXPECT_EQ(true, 0 == MemoBoard.Error.nClass);
}

TEST(Variable, IntegerArraies) {
  MemoBoard &MemoBoard = ((APP_CONTEXT *)GetAppCxt())->MemoBoard;
  MemoBoard.Clear();

  string ErrorReason;
  MemoBoard.Config.LoadStream(ConfigToml, ErrorReason);
  shared_ptr<ConfigData> pCfgData = MemoBoard.Config.GetData();
  pCfgData->Hungarian.WordList.insert(std::pair<string, string>("int", "i"));

  const string SourceCode = "   \n\
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
  EXPECT_EQ(true, 0 == MemoBoard.Checked.nClass);

  EXPECT_EQ(true, 0 == MemoBoard.Error.nFile);
  EXPECT_EQ(true, 0 == MemoBoard.Error.nFunction);
  EXPECT_EQ(true, 0 == MemoBoard.Error.nParameter);
  EXPECT_EQ(true, 0 == MemoBoard.Error.nVariable);
  EXPECT_EQ(true, 0 == MemoBoard.Error.nEnum);
  EXPECT_EQ(true, 0 == MemoBoard.Error.nStruct);
  EXPECT_EQ(true, 0 == MemoBoard.Error.nClass);
}

TEST(Enum, UsbEndpointDescriptor) {
  MemoBoard &MemoBoard = ((APP_CONTEXT *)GetAppCxt())->MemoBoard;
  MemoBoard.Clear();

  string ErrorReason;
  MemoBoard.Config.LoadStream(ConfigToml, ErrorReason);
  shared_ptr<ConfigData> pCfgData = MemoBoard.Config.GetData();

  const string SourceCode = "     \n\
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
  EXPECT_EQ(true, 0 == MemoBoard.Checked.nClass);

  EXPECT_EQ(true, 0 == MemoBoard.Error.nFile);
  EXPECT_EQ(true, 0 == MemoBoard.Error.nFunction);
  EXPECT_EQ(true, 0 == MemoBoard.Error.nParameter);
  EXPECT_EQ(true, 0 == MemoBoard.Error.nVariable);
  EXPECT_EQ(true, 0 == MemoBoard.Error.nEnum);
  EXPECT_EQ(true, 0 == MemoBoard.Error.nStruct);
  EXPECT_EQ(true, 0 == MemoBoard.Error.nClass);
}

TEST(Struct, UsbEndpointDescriptor) {
  MemoBoard &MemoBoard = ((APP_CONTEXT *)GetAppCxt())->MemoBoard;
  MemoBoard.Clear();

  string ErrorReason;
  MemoBoard.Config.LoadStream(ConfigToml, ErrorReason);
  shared_ptr<ConfigData> pCfgData = MemoBoard.Config.GetData();

  const string SourceCode = "                \n\
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
  EXPECT_EQ(true, 0 == MemoBoard.Checked.nClass);

  EXPECT_EQ(true, 0 == MemoBoard.Error.nFile);
  EXPECT_EQ(true, 0 == MemoBoard.Error.nFunction);
  EXPECT_EQ(true, 0 == MemoBoard.Error.nParameter);
  EXPECT_EQ(true, 0 == MemoBoard.Error.nVariable);
  EXPECT_EQ(true, 0 == MemoBoard.Error.nEnum);
  EXPECT_EQ(true, 0 == MemoBoard.Error.nStruct);
  EXPECT_EQ(true, 0 == MemoBoard.Error.nClass);
}

TEST(Function, FnPtr) {
  MemoBoard &MemoBoard = ((APP_CONTEXT *)GetAppCxt())->MemoBoard;
  MemoBoard.Clear();

  string ErrorReason;
  MemoBoard.Config.LoadStream(ConfigToml, ErrorReason);
  shared_ptr<ConfigData> pCfgData = MemoBoard.Config.GetData();

  const string SourceCode = "		\n\
        int (*pFnName1)(int, int);		\n\
        int (*pFnName2)(int iA, int iB);	\n\
        ";

  EXPECT_EQ(true, 0 == RunCheckFormStream(MemoBoard, SourceCode));

  EXPECT_EQ(true, 0 == MemoBoard.Checked.nFile);
  EXPECT_EQ(true, 0 == MemoBoard.Checked.nFunction);
  EXPECT_EQ(true, 2 == MemoBoard.Checked.nParameter);
  EXPECT_EQ(true, 2 == MemoBoard.Checked.nVariable);
  EXPECT_EQ(true, 0 == MemoBoard.Checked.nEnum);
  EXPECT_EQ(true, 0 == MemoBoard.Checked.nStruct);
  EXPECT_EQ(true, 0 == MemoBoard.Checked.nClass);

  EXPECT_EQ(true, 0 == MemoBoard.Error.nFile);
  EXPECT_EQ(true, 0 == MemoBoard.Error.nFunction);
  EXPECT_EQ(true, 0 == MemoBoard.Error.nParameter);
  EXPECT_EQ(true, 0 == MemoBoard.Error.nVariable);
  EXPECT_EQ(true, 0 == MemoBoard.Error.nEnum);
  EXPECT_EQ(true, 0 == MemoBoard.Error.nStruct);
  EXPECT_EQ(true, 0 == MemoBoard.Error.nClass);
}

TEST(Function, MemCpy) {
  MemoBoard &MemoBoard = ((APP_CONTEXT *)GetAppCxt())->MemoBoard;
  MemoBoard.Clear();

  string ErrorReason;
  MemoBoard.Config.LoadStream(ConfigToml, ErrorReason);
  shared_ptr<ConfigData> pCfgData = MemoBoard.Config.GetData();

  const string SourceCode = "							\n\
        void *												\n\
        MemCpy (void *pDest, const void *pSrc, size_t nLen) \n\
        {													\n\
          char *pD = pDest;									\n\
          const char *pS = pSrc;							\n\
          while (nLen--)									\n\
            *pD++ = *pS++;									\n\
          return pDest;										\n\
        }													\n\
        ";

  EXPECT_EQ(true, 0 == RunCheckFormStream(MemoBoard, SourceCode));

  EXPECT_EQ(true, 0 == MemoBoard.Checked.nFile);
  EXPECT_EQ(true, 1 == MemoBoard.Checked.nFunction);
  EXPECT_EQ(true, 3 == MemoBoard.Checked.nParameter);
  EXPECT_EQ(true, 2 == MemoBoard.Checked.nVariable);
  EXPECT_EQ(true, 0 == MemoBoard.Checked.nEnum);
  EXPECT_EQ(true, 0 == MemoBoard.Checked.nStruct);
  EXPECT_EQ(true, 0 == MemoBoard.Checked.nClass);

  EXPECT_EQ(true, 0 == MemoBoard.Error.nFile);
  EXPECT_EQ(true, 0 == MemoBoard.Error.nFunction);
  EXPECT_EQ(true, 0 == MemoBoard.Error.nParameter);
  EXPECT_EQ(true, 0 == MemoBoard.Error.nVariable);
  EXPECT_EQ(true, 0 == MemoBoard.Error.nEnum);
  EXPECT_EQ(true, 0 == MemoBoard.Error.nStruct);
  EXPECT_EQ(true, 0 == MemoBoard.Error.nClass);
}

} // namespace RunCheckHungarian
