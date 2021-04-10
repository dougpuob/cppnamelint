#===----------------------------------------------------------------------===#
#                           The MIT License (MIT)
#             Copyright (c) 2020 Douglas Chen <dougpuob@gmail.com>
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to
# deal in the Software without restriction, including without limitation the
# rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
# sell copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
# FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
# IN THE SOFTWARE.
#===----------------------------------------------------------------------===#
cmake_minimum_required(VERSION 3.10)
project(cppnamelint)

set(CMAKE_CXX_STANDARD          17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS        OFF)

message(STATUS "CMAKE_CURRENT_SOURCE_DIR : ${CMAKE_CURRENT_SOURCE_DIR}"  )
message(STATUS "CMAKE_BUILD_TYPE         : ${CMAKE_BUILD_TYPE}"          )
message(STATUS "CMAKE_SYSTEM             : ${CMAKE_SYSTEM}"              )
message(STATUS "CMAKE_SYSTEM_NAME        : ${CMAKE_SYSTEM_NAME}"         )
message(STATUS "CMAKE_SYSTEM_VERSION     : ${CMAKE_SYSTEM_VERSION}"      )
message(STATUS "CMAKE_SYSTEM_PROCESSOR   : ${CMAKE_SYSTEM_PROCESSOR}"    )


###############################################################################
# LLVM libraries
###############################################################################
find_package(LLVM  REQUIRED CONFIG PATHS ${LLVM_INSTALL_DIR} NO_DEFAULT_PATH)
find_package(Clang REQUIRED CONFIG PATHS ${LLVM_INSTALL_DIR} NO_DEFAULT_PATH)

include_directories(${LLVM_INCLUDE_DIRS})
include_directories(${CLANG_INCLUDE_DIRS})

add_definitions(${LLVM_DEFINITIONS})
add_definitions(${CLANG_DEFINITIONS})

set(SELECTED_CLANG_LIBS clangTooling clangBasic clangAST clangFrontend)

message(STATUS "LLVM_INSTALL_DIR         : ${LLVM_INSTALL_DIR}")
message(STATUS "CLANG_INCLUDE_DIRS       : ${CLANG_INCLUDE_DIRS}")
message(STATUS "LLVM_INCLUDE_DIRS        : ${LLVM_INCLUDE_DIRS}")
message(STATUS "LLVM_LIBRARY_DIRS        : ${LLVM_LIBRARY_DIRS}")
message(STATUS "LLVM_PACKAGE_VERSION     : ${LLVM_PACKAGE_VERSION}")
message(STATUS "LLVM_DIR                 : ${LLVM_DIR}")
message(STATUS "LLVM_CMAKE_PATH          : ${LLVM_CMAKE_PATH}")
message(STATUS "LLVM_DEFINITIONS         : ${LLVM_DEFINITIONS}")

###############################################################################
# This project
###############################################################################
if(CMAKE_HOST_WIN32)
    set(OUTPUT_OS "windows")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd4141")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd4244")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd4146")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd4291")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd4227")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd4099")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd4996")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd4267")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd4477")
    #set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /source-charset:utf-8")
    set(gtest_force_shared_crt ON CACHE BOOL "Always use msvcrt.dll" )
    set(EXTERNAL_LIB Version)
elseif(CMAKE_HOST_APPLE)
    set(OUTPUT_OS "macos")
    set(CMAKE_CXX_FLAGS "-frtti")
    set(EXTERNAL_LIB z ncurses)
elseif(CMAKE_HOST_UNIX)
    set(OUTPUT_OS "linux")
    set(CMAKE_CXX_FLAGS "-fno-rtti -g")
endif()

# Output folders
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build/${OUTPUT_OS}/output)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build/${OUTPUT_OS}/output)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build/${OUTPUT_OS}/output)

add_executable(
    cppnamelint
    submodule/tinytoml.git/include/toml/toml.h
    source/TraceMemo.h
    source/Main.cpp
    source/Detection.h
    source/Detection.cpp
    source/Common.h
    source/Common.cpp
    source/Config.h
    source/Config.cpp
    source/DumpDecl.h
    source/DumpDecl.cpp
    source/MyCommandLine.h
    source/MyFactory.h
    source/MyFactory.cpp
    source/MyAstVisitor.h
    source/MyAstVisitor.cpp
    source/MyAstVisitorPriv.cpp
    source/MyAstConsumer.h
    source/MyAstConsumer.cpp
    source/test/TestConfig.cpp
    source/test/TestDetection.cpp
    source/test/TestRunCheck.cpp
    source/test/TestIssue55.cpp
    source/test/TestRunCheck_UpperCamel.cpp
    source/test/TestRunCheck_LowerCamel.cpp
    source/test/TestRunCheck_UpperSnake.cpp
    source/test/TestRunCheck_LowerSnake.cpp
    source/test/TestRunCheck_Hungarian.cpp
    source/test/TestRunCheck_InvalidDecl.cpp
    source/test/TestRunCheck_Macro.cpp
    source/test/TestRunCheck_CppClass.cpp
    source/test/TestRunCheck_CppEnum.cpp
    source/test/TestRunCheck_CppStruct.cpp
)

include_directories(
    submodule/json.git/include
    submodule/googletest.git/googletest/include
	submodule/spdlog.git/include
)


target_link_libraries(
    cppnamelint
    gtest
    gtest_main
    ${LLVM_AVAILABLE_LIBS}  # Defined in LLVMConfig.cmake file.
    ${SELECTED_CLANG_LIBS}  # Defined in this project.
    ${EXTERNAL_LIB}         # Defined in this project.
)


###############################################################################
# Third-party libraries
###############################################################################
option(BUILD_TESTING "Turn OFF to build the testing tree (json)." OFF)

add_subdirectory(submodule/googletest.git)
add_subdirectory(submodule/json.git)
add_subdirectory(submodule/spdlog.git)

