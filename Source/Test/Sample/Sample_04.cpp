#include <string>

class MyClass
{
public:
  std::string m_MyStr;

  bool CheckValue(std::string Text);
};

bool
MyClass::CheckValue(std::string Text)
{
  return true;
}