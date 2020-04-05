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
                                                            \n\
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
                                                            \n\
    [Hungarian.WordList]                                    \n\
      \"size_t\"                 = \"n\"                    \n\
      \"bool\"                   = \"b\"                    \n\
      \"uint8_t\"                = \"u8\"                   \n\
      \"uint16_t\"               = \"u16\"                  \n\
      \"uint32_t\"               = \"u32\"                  \n\
    ";

namespace RunCheck {

TEST(Struct, USB_DEVICE_DESCRIPTOR) {

  const string SourceCode = "\
    typedef struct _USB_DEVICE_DESCRIPTOR { \n\
            uint8_t  u8Length;              \n\
            uint8_t  u8DescriptorType;      \n\
            uint16_t u16BcdUsb;             \n\
            uint8_t  u8DeviceClass;         \n\
            uint8_t  u8DeviceSubClass;      \n\
            uint8_t  u8DeviceProtocol;      \n\
            uint8_t  u8MaxPacketSize0;      \n\
            uint16_t u16Vendor;             \n\
            uint16_t u16Product;            \n\
            uint16_t u16BcdDevice;          \n\
            uint8_t  u8Manufacturer;        \n\
            uint8_t  u8Product;             \n\
            uint8_t  u8SerialNumber;        \n\
            uint8_t  u8NumConfigurations;   \n\
    } USB_DEVICE_DESCRIPTOR;";

  MemoBoard &MemoBoard = pAppCxt->MemoBoard;
  MemoBoard.Clear();

  string ErrorReason;
  pAppCxt->MemoBoard.Config.LoadStream(ConfigToml, ErrorReason);

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

const string SourceCode = "\
    typedef struct _USB_CONFIGURATION_POWER_DESCRIPTOR {  \n\
        bool        bLength;                              \n\
        bool        bDescriptorType;                      \n\
        uint8_t     u8SelfPowerConsumedD0[3];             \n\
        bool        bPowerSummaryId;                      \n\
        bool        bBusPowerSavingD1;                    \n\
        bool        bSelfPowerSavingD1;                   \n\
        bool        bBusPowerSavingD2;                    \n\
        bool        bSelfPowerSavingD2;                   \n\
        bool        bBusPowerSavingD3;                    \n\
        bool        bSelfPowerSavingD3;                   \n\
        uint16_t    u16TransitionTimeFromD1;              \n\
        uint16_t    u16TransitionTimeFromD2;              \n\
        uint16_t    u16TransitionTimeFromD3;              \n\
    } USB_CONFIGURATION_POWER_DESCRIPTOR                  \n\
    ";
TEST(Struct, USB_CONFIGURATION_POWER_DESCRIPTOR_1) {
  MemoBoard &MemoBoard = pAppCxt->MemoBoard;
  MemoBoard.Clear();

  string ErrorReason;
  pAppCxt->MemoBoard.Config.LoadStream(ConfigToml, ErrorReason);

  EXPECT_EQ(true, 0 == RunCheckFormStream(MemoBoard, SourceCode));

  EXPECT_EQ(true, 0 == MemoBoard.Checked.nFile);
  EXPECT_EQ(true, 0 == MemoBoard.Checked.nFunction);
  EXPECT_EQ(true, 0 == MemoBoard.Checked.nParameter);
  EXPECT_EQ(true, 0 == MemoBoard.Checked.nVariable);
  EXPECT_EQ(true, 0 == MemoBoard.Checked.nEnum);
  EXPECT_EQ(true, 14 == MemoBoard.Checked.nStruct);
  EXPECT_EQ(true, 0 == MemoBoard.Checked.nClass);

  EXPECT_EQ(true, 0 == MemoBoard.Error.nFile);
  EXPECT_EQ(true, 0 == MemoBoard.Error.nFunction);
  EXPECT_EQ(true, 0 == MemoBoard.Error.nParameter);
  EXPECT_EQ(true, 0 == MemoBoard.Error.nVariable);
  EXPECT_EQ(true, 0 == MemoBoard.Error.nEnum);
  EXPECT_EQ(true, 0 == MemoBoard.Error.nStruct);
  EXPECT_EQ(true, 0 == MemoBoard.Error.nClass);
}

TEST(Struct, USB_CONFIGURATION_POWER_DESCRIPTOR_2) {
  MemoBoard &MemoBoard = pAppCxt->MemoBoard;
  MemoBoard.Clear();

  string ErrorReason;
  pAppCxt->MemoBoard.Config.LoadStream(ConfigToml, ErrorReason);

  EXPECT_EQ(true, 0 == RunCheckFormStream(MemoBoard, SourceCode));

  EXPECT_EQ(true, 0 == MemoBoard.Checked.nFile);
  EXPECT_EQ(true, 0 == MemoBoard.Checked.nFunction);
  EXPECT_EQ(true, 0 == MemoBoard.Checked.nParameter);
  EXPECT_EQ(true, 0 == MemoBoard.Checked.nVariable);
  EXPECT_EQ(true, 0 == MemoBoard.Checked.nEnum);
  EXPECT_EQ(true, 14 == MemoBoard.Checked.nStruct);
  EXPECT_EQ(true, 0 == MemoBoard.Checked.nClass);

  EXPECT_EQ(true, 0 == MemoBoard.Error.nFile);
  EXPECT_EQ(true, 0 == MemoBoard.Error.nFunction);
  EXPECT_EQ(true, 0 == MemoBoard.Error.nParameter);
  EXPECT_EQ(true, 0 == MemoBoard.Error.nVariable);
  EXPECT_EQ(true, 0 == MemoBoard.Error.nEnum);
  EXPECT_EQ(true, 0 == MemoBoard.Error.nStruct);
  EXPECT_EQ(true, 0 == MemoBoard.Error.nClass);
}

TEST(Union, USB_20_PORT_STATUS) {
  // Those types are NOT in [Hungarian.WordList].
  const string SourceCode = "\
    typedef union _USB_20_PORT_STATUS {             \n\
    USHORT   AsUshort16;                            \n\
        struct {                                    \n\
            USHORT  CurrentConnectStatus : 1;       \n\
            USHORT  PortEnabledDisabled : 1;        \n\
            USHORT  Suspend : 1;                    \n\
            USHORT  OverCurrent : 1;                \n\
            USHORT  Reset : 1;                      \n\
            USHORT  L1 : 1;                         \n\
            USHORT  Reserved0 : 2;                  \n\
            USHORT  PortPower : 1;                  \n\
            USHORT  LowSpeedDeviceAttached : 1;     \n\
            USHORT  HighSpeedDeviceAttached : 1;    \n\
            USHORT  PortTestMode : 1;               \n\
            USHORT  PortIndicatorControl : 1;       \n\
            USHORT  Reserved1 : 3;                  \n\
        };                                          \n\
    }  USB_20_PORT_STATUS;                          \n\
    ";

  MemoBoard &MemoBoard = pAppCxt->MemoBoard;
  MemoBoard.Clear();

  string ErrorReason;
  MemoBoard.Config.LoadStream(ConfigToml, ErrorReason);
  MemoBoard.Config.GetData()->Hungarian.Options.PreferUpperCamelIfMissed = false;

  EXPECT_EQ(true, 0 == RunCheckFormStream(MemoBoard, SourceCode));

  EXPECT_EQ(true, 0 == MemoBoard.Checked.nFile);
  EXPECT_EQ(true, 0 == MemoBoard.Checked.nFunction);
  EXPECT_EQ(true, 0 == MemoBoard.Checked.nParameter);
  EXPECT_EQ(true, 0 == MemoBoard.Checked.nVariable);
  EXPECT_EQ(true, 0 == MemoBoard.Checked.nEnum);
  EXPECT_EQ(true, 14 == MemoBoard.Checked.nStruct);
  EXPECT_EQ(true, 1 == MemoBoard.Checked.nUnion);
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

} // namespace RunCheck
