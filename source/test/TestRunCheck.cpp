#include <vector>

#include <gtest/gtest.h>

#include "../Common.h"
#include "../TraceMemo.h"

int RunCheckFormStream(namelint::MemoBoard &Memo, const string &SourceContent);

using namespace namelint;

APP_CONTEXT *pAppCxt = (APP_CONTEXT *)GetAppCxt();

const string ConfigToml = "\
    [General.Options]                                       \n\
      Version                 = 0.2                         \n\
      CheckFileName           = false                       \n\
      CheckVariableName       = true                        \n\
      CheckFunctionName       = true                        \n\
      CheckEnum               = true                        \n\
      CheckStruct             = true                        \n\
      AllowedPrintResult      = false                       \n\
      AllowedWriteJsonResult  = false                       \n\
      AllowedUnderscopeChar   = false                       \n\
      AllowedArrayAffected    = false                       \n\
    [General.Rules]                                         \n\
      StructTagName           = 5 # 0: Default (UpperCamel) \n\
                                  # 1: UpperCamel           \n\
                                  # 2: lowerCamel           \n\
                                  # 3: lower_snake          \n\
                                  # 5: UPPER_SNAKE          \n\
      StructValueName         = 4 # 0: Default (UpperCamel) \n\
                                  # 1: UpperCamel           \n\
                                  # 2: lowerCamel           \n\
                                  # 3: lower_snake          \n\
                                  # 4: Hungarian            \n\
                                  # 5: UPPER_SNAKE          \n\
    [General.IgnoredList]                                   \n\
      StructTagPrefix         = [ \"_\", \"s\" ]            \n\
    ";

// clang-format off
namespace RunCheck {
TEST(RunCheck, USB_DEVICE_DESCRIPTOR) {

    const string SourceCode = "\
    typedef struct _USB_DEVICE_DESCRIPTOR { \
            uint8_t  u8Length;              \
            uint8_t  u8DescriptorType;      \
            uint16_t u16BcdUSB;             \
            uint8_t  u8DeviceClass;         \
            uint8_t  u8DeviceSubClass;      \
            uint8_t  u8DeviceProtocol;      \
            uint8_t  u8MaxPacketSize0;      \
            uint16_t u16Vendor;             \
            uint16_t u16Product;            \
            uint16_t u16BcdDevice;          \
            uint8_t  u8Manufacturer;        \
            uint8_t  u8Product;             \
            uint8_t  u8SerialNumber;        \
            uint8_t  u8NumConfigurations;   \
    } USB_DEVICE_DESCRIPTOR;";

    MemoBoard& MemoBoard = pAppCxt->MemoBoard;

    string errorReason;
    pAppCxt->MemoBoard.Config.LoadStream(ConfigToml, errorReason);

  EXPECT_EQ(true, 0 == RunCheckFormStream(MemoBoard, SourceCode));
  
  EXPECT_EQ(true, 0 == MemoBoard.Checked.nFile);
  EXPECT_EQ(true, 0 == MemoBoard.Checked.nFunction);
  EXPECT_EQ(true, 0 == MemoBoard.Checked.nParameter);
  EXPECT_EQ(true, 0 == MemoBoard.Checked.nVariable);
  EXPECT_EQ(true, 0 == MemoBoard.Checked.nEnum);
  EXPECT_EQ(true, 15 == MemoBoard.Checked.nStruct);
  EXPECT_EQ(true, 0 == MemoBoard.Checked.nClass);

  EXPECT_EQ(true, 0 == MemoBoard.Error.nFile);
  EXPECT_EQ(true, 0 == MemoBoard.Error.nFunction);
  EXPECT_EQ(true, 0 == MemoBoard.Error.nParameter);
  EXPECT_EQ(true, 0 == MemoBoard.Error.nVariable);
  EXPECT_EQ(true, 0 == MemoBoard.Error.nEnum);
  EXPECT_EQ(true, 0 == MemoBoard.Error.nStruct);
  EXPECT_EQ(true, 0 == MemoBoard.Error.nClass);
}

} // namespace TargetIsGeneral

// clang-format on