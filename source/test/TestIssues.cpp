#include <string>
#include <vector>

#include <gtest/gtest.h>

#include "../Common.h"
#include "../TraceMemo.h"

// clang-format off
namespace TestIssue {
TEST(Issue55, FirstLineIsAnInvalidPathOnLinux) {
  // https://github.com/dougpuob/cppnamelint/issues/55
  const std::string SourceCode = "\
    //                                                                            \n\
    // 1.1.cpp                                                                    \n\
    //                                                                            \n\
    // chapter 1 introduction                                                     \n\
    // modern cpp tutorial                                                        \n\
    //                                                                            \n\
    // created by changkun at changkun.de                                         \n\
    // https://github.com/changkun/modern-cpp-tutorial                            \n\
    //                                                                            \n\
                                                                                  \n\
    #include \"foo.h/\"                                                           \n\
    #include <iostream>                                                           \n\
    #include <functional>                                                         \n\
                                                                                  \n\
    int main() {                                                                  \n\
        // use lambda expression                                                  \n\
        [out = std::ref(std::cout << \"Result from C code: \" << add(1, 2))](){   \n\
            out.get() << \".\n\";                                                 \n\
        }();                                                                      \n\
        return 0;                                                                 \n\
    }";

  AppCxt &AppCxt       = AppCxt::getInstance();
  MemoBoard &MemoBoard = AppCxt.MemoBoard;
  MemoBoard.Clear();
  
  EXPECT_EQ(true, 0 == RunCheckFormStream(MemoBoard, SourceCode));
}

}
// clang-format on
