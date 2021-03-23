cmake_minimum_required(VERSION 3.10)
project(cppnamelint)


set(CMAKE_CXX_STANDARD          17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS        OFF)

#set(LLVM_CMAKE_PATH "/home/dougpuob/petzone/llvm-lib-8.0.1-debug/lib/cmake/llvm/LLVMConfig.cmake")

#set (LLVM_INSTALL_DIR "/home/dougpuob/petzone/llvm/llvm-prebuilt-install/llvmorg-8.0.0-gcc-debug")
set (LLVM_INSTALL_DIR "/home/dougpuob/petzone/llvm/llvm-prebuilt-install/llvmorg-12.0.0-gcc-debug")

set (SEARCH_PATH
    ${LLVM_INSTALL_DIR}
    ${LLVM_INSTALL_DIR}/lib/cmake
    ${LLVM_INSTALL_DIR}/lib/cmake/llvm
    ${LLVM_INSTALL_DIR}/lib/cmake/clang
    ${LLVM_INSTALL_DIR}/share/clang/cmake/
    ${LLVM_INSTALL_DIR}/share/llvm/cmake/
)

find_package(LLVM REQUIRED CONFIG PATHS ${SEARCH_PATH} NO_DEFAULT_PATH)
message(STATUS "Found LLVM  : ${LLVM_INCLUDE_DIRS} ${LLVM_PACKAGE_VERSION}")

find_package(Clang REQUIRED CONFIG PATHS ${SEARCH_PATH} NO_DEFAULT_PATH)

add_definitions(${LLVM_DEFINITIONS})
include_directories(${LLVM_INCLUDE_DIRS})
llvm_map_components_to_libnames(LLVM_LIBS core clang native support)

###############################################################################
if(CMAKE_BUILD_TYPE STREQUAL Debug)
    set (BUILD_TYPE Debug)
elseif(CMAKE_BUILD_TYPE STREQUAL Release)
    set (BUILD_TYPE Release)
elseif(CMAKE_BUILD_TYPE STREQUAL RelWithDebInfo)
    set (BUILD_TYPE RelWithDebInfo)
else()
    set (BUILD_TYPE release)
endif()


###############################################################################
if(WIN32)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd4141")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd4244")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd4146")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd4291")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd4227")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd4099")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd4996")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd4267")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd4477")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /source-charset:utf-8")
    set(gtest_force_shared_crt ON CACHE BOOL "Always use msvcrt.dll" )
elseif(UNIX AND NOT APPLE)
    set(CC   "/usr/bin/gcc")
    set(CXX  "/usr/bin/g++")
    string(TOLOWER ${BUILD_TYPE} BUILD_TYPE)
    set(CMAKE_CXX_FLAGS "-fno-rtti -g")
elseif(APPLE)
    set(CC   "/usr/bin/clang")
    set(CXX  "/usr/bin/clang++")
    string(TOLOWER ${BUILD_TYPE} BUILD_TYPE)
    set(CMAKE_CXX_FLAGS "-frtti")
endif()


###############################################################################
if (LLVM_DIR_CPPNAMELINT)
    set(LLVM_DIR_CPPNAMELINT_PATH $ENV{LLVM_DIR_CPPNAMELINT}/build/${BUILD_TYPE}/lib)
endif()

if(WIN32)
    set(EXTERNAL_LIB Version)
elseif(UNIX AND NOT APPLE)
    set(EXTERNAL_LIB z tinfo)
elseif(APPLE)
    set(EXTERNAL_LIB z ncurses)
endif()


###############################################################################
if (LLVM_DIR_CPPNAMELINT)
    include_directories(
        $ENV{LLVM_DIR_CPPNAMELINT}/llvm/include
        $ENV{LLVM_DIR_CPPNAMELINT}/clang/include
        $ENV{LLVM_DIR_CPPNAMELINT}/build/include
        $ENV{LLVM_DIR_CPPNAMELINT}/build/tools/clang/include
        $ENV{LLVM_DIR_CPPNAMELINT}/build/${BUILD_TYPE}/include
        $ENV{LLVM_DIR_CPPNAMELINT}/build/${BUILD_TYPE}/tools/clang/include
        $ENV{LLVM_DIR_CPPNAMELINT}/build/${BUILD_TYPE}/tools/llvm/include
        submodule/googletest.git/googletest/include
        submodule/json.git/include
    )
else()
    include_directories(
        ${LLVM_INCLUDE_DIRS}
        submodule/json.git/include
        submodule/googletest.git/googletest/include
    )
    add_definitions(
        ${LLVM_DEFINITIONS}
    )
    # Find the libraries that correspond to the LLVM components
    # that we wish to use
    llvm_map_components_to_libnames(llvm_libs support core irreader)
endif()

###############################################################################
message("CMAKE_CURRENT_SOURCE_DIR   : ${CMAKE_CURRENT_SOURCE_DIR}"  )
message("CMAKE_BUILD_TYPE           : ${CMAKE_BUILD_TYPE}"          )
message("CMAKE_SYSTEM               : ${CMAKE_SYSTEM}"              )
message("CMAKE_SYSTEM_NAME          : ${CMAKE_SYSTEM_NAME}"         )
message("CMAKE_SYSTEM_VERSION       : ${CMAKE_SYSTEM_VERSION}"      )
message("CMAKE_SYSTEM_PROCESSOR     : ${CMAKE_SYSTEM_PROCESSOR}"    )
message("LLVM_DIR                   : ${LLVM_DIR}"                  )
message("LLVM_CMAKE_PATH            : ${LLVM_CMAKE_PATH}"           )

if(WIN32)
    message("Platform                   : WIN32" )
elseif(UNIX AND NOT APPLE)
    message("Platform                   : UNIX AND NOT APPLE" )
elseif(APPLE)
    message("Platform                   : APPLE" )
else()
    message("Platform                   : ERROR HERE" )
endif()

message("BUILD_TYPE                 : ${BUILD_TYPE}")
message("LLVM_DIR_CPPNAMELINT       : $ENV{LLVM_DIR_CPPNAMELINT}")
message("LLVM_DIR_CPPNAMELINT_PATH  : ${LLVM_DIR_CPPNAMELINT_PATH}" )
message("CMAKE_CXX_FLAGS            : ${CMAKE_CXX_FLAGS}" )
message("INC_PATH_1                 : $ENV{LLVM_DIR_CPPNAMELINT}/llvm/include" )
message("INC_PATH_2                 : $ENV{LLVM_DIR_CPPNAMELINT}/clang/include" )
message("INC_PATH_3                 : $ENV{LLVM_DIR_CPPNAMELINT}/build/${BUILD_TYPE}/include" )
message("INC_PATH_4                 : $ENV{LLVM_DIR_CPPNAMELINT}/build/${BUILD_TYPE}/tools/clang/include" )
message("INC_PATH_5                 : $ENV{LLVM_DIR_CPPNAMELINT}/build/${BUILD_TYPE}/tools/llvm/include" )


###############################################################################
option(BUILD_TESTING "Turn OFF to build the testing tree (json)." OFF)

add_subdirectory(submodule/googletest.git)
add_subdirectory(submodule/json.git)


###############################################################################
set(OUTPUT_OS "")
if(WIN32)
    set(OUTPUT_OS "windows")
elseif(UNIX AND NOT APPLE)
    set(OUTPUT_OS "linux")
elseif(APPLE)
    set(OUTPUT_OS "macos")
else()
    set(OUTPUT_OS "error")
endif()

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build/${OUTPUT_OS}/output)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build/${OUTPUT_OS}/output)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build/${OUTPUT_OS}/output)


###############################################################################
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
    source/Logger.h
    source/Logger.cpp
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

set (SELECTED_CLANG_LIBS
    clangTooling
    clangBasic
    clangASTMatchers
    )

###############################################################################
target_link_libraries(
    cppnamelint
    #------------------------#
    # Submodules             #
    #------------------------#
    gtest
    gtest_main
    #------------------------#
    # LLVM's libraries       #
    #------------------------#
    ${LLVM_AVAILABLE_LIBS}
    ${SELECTED_CLANG_LIBS}
    ${EXTERNAL_LIB}
)
