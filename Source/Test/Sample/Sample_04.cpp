#include <string>

#define IN
#define OUT
#define OPT

static uint32_t Crc32Table[] = {};

class MyClass {
  public:
    std::string m_MyStr;

    bool CheckValue(std::string Text);
};

bool MyClass::CheckValue(std::string Text) { return true; }