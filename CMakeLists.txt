cmake_minimum_required(VERSION 3.10)
project(namelint)

message("CMAKE_CURRENT_SOURCE_DIR   : ${CMAKE_CURRENT_SOURCE_DIR}"  )
message("CMAKE_BUILD_TYPE           : ${CMAKE_BUILD_TYPE}"          )
message("CMAKE_SYSTEM               : ${CMAKE_SYSTEM}"              )
message("CMAKE_SYSTEM_NAME          : ${CMAKE_SYSTEM_NAME}"         )
message("CMAKE_SYSTEM_VERSION       : ${CMAKE_SYSTEM_VERSION}"      )
message("CMAKE_SYSTEM_PROCESSOR     : ${CMAKE_SYSTEM_PROCESSOR}"    )

set(CMAKE_CXX_STANDARD          17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS        OFF)


###############################################################################
# Linux:    export NAMELINT_DEVTLS=/home/dougpuob/working-folder/devtls/@Linux/3party-lib
# macOS:    export NAMELINT_DEVTLS=/home/dougpuob/working-folder/devtls/@MacOS/3party-lib
# Windows:  SETX   NAMELINT_DEVTLS=D:\devtls\@Win32\3party-lib
set(PREBUILD_DIR $ENV{NAMELINT_DEVTLS} )
set(PREBUILD_DIR_LLVM   ${PREBUILD_DIR}/llvm/7.0.1)


###############################################################################
if(WIN32)
    message("Platform                   : WIN32" )
elseif(UNIX AND NOT APPLE)
    message("Platform                   : UNIX AND NOT APPLE" )
elseif(APPLE)
    message("Platform                   : APPLE" )
else()
    message("Platform                   : ERROR HERE" )
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
    set( gtest_force_shared_crt ON CACHE BOOL "Always use msvcrt.dll" )
elseif(UNIX AND NOT APPLE)
    # None.
elseif(APPLE)
    # None.
endif()

message("CMAKE_CXX_FLAGS            : ${CMAKE_CXX_FLAGS}" )

include_directories(
    ${PREBUILD_DIR_LLVM}/include
    ${PREBUILD_DIR_LLVM}/build/include
    ${PREBUILD_DIR_LLVM}/build/tools/clang/include
    ${PREBUILD_DIR_LLVM}/tools/clang/include
    Module/googletest.git/googletest/include
    Module/docopt.cpp
    )


###############################################################################
if(CMAKE_BUILD_TYPE STREQUAL Debug)
    SET (BUILD_TYPE debug)
elseif(CMAKE_BUILD_TYPE STREQUAL Release)
    SET (BUILD_TYPE release)
else()
    SET (BUILD_TYPE None)
endif()

link_directories(${PREBUILD_DIR_LLVM}/build/${BUILD_TYPE}/lib)
message("LLVM PATH                  : ${PREBUILD_DIR_LLVM}/build/${BUILD_TYPE}/lib" )


###############################################################################
add_subdirectory(Module/docopt.cpp)
add_subdirectory(Module/googletest.git)


###############################################################################
set(OUTPUT_OS "")
if(WIN32)
    set(OUTPUT_OS "win32")
elseif(UNIX AND NOT APPLE)
    set(OUTPUT_OS "linux")
elseif(APPLE)
    set(OUTPUT_OS "darwin")
else()
    set(OUTPUT_OS "error")
endif()

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/Build/${OUTPUT_OS}/Output)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/Build/${OUTPUT_OS}/Output)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/Build/${OUTPUT_OS}/Output)


###############################################################################
if(WIN32)
elseif(UNIX AND NOT APPLE)
    set(CMAKE_CXX_FLAGS "-fno-rtti")
    link_libraries(stdc++fs)
elseif(APPLE)
    set(CMAKE_CXX_FLAGS "-fno-rtti -lz")
    SET(Boost_USE_STATIC_LIBS ON)
    FIND_PACKAGE(Boost 1.54 COMPONENTS filesystem REQUIRED)
endif()

message("CMAKE_CXX_FLAGS            : ${CMAKE_CXX_FLAGS}" )

add_executable(
    namelint
    Module/tinytoml.git/include/toml/toml.h
    Module/docopt.cpp/docopt.h
    Source/Detection.h
    Source/Detection.cpp
    Source/Common.h
    Source/Common.cpp
    Source/ParseAST.h
    Source/ParseAST.cpp
    Source/Config.h
    Source/Config.cpp
    Source/Main.cpp
    Source/Test/TestConfig.cpp
    Source/Test/TestDetection.cpp
    )


###############################################################################

if(WIN32)
    set(EXTERNAL_LIB Version)
elseif(UNIX AND NOT APPLE)
elseif(APPLE)
    set(EXTERNAL_LIB ncurses ${Boost_LIBRARIES})
endif()

target_link_libraries(
    namelint
    docopt
    gtest
    gtest_main
    ${EXTERNAL_LIB}
    clangAnalysis
    clangARCMigrate
    clangAST
    clangASTMatchers
    clangBasic
    clangCodeGen
    clangCrossTU
    clangDriver
    clangDynamicASTMatchers
    clangEdit
    clangFormat
    clangFrontend
    clangFrontendTool
    clangHandleCXX
    clangHandleLLVM
    clangIndex
    clangLex
    clangParse
    clangRewrite
    clangRewriteFrontend
    clangSema
    clangSerialization
    clangStaticAnalyzerCheckers
    clangStaticAnalyzerCore
    clangStaticAnalyzerFrontend
    clangTooling
    clangToolingASTDiff
    clangToolingCore
    clangToolingInclusions
    clangToolingRefactor
    #Kaleidoscope-Ch4
    #Kaleidoscope-Ch5
    #Kaleidoscope-Ch6
    #Kaleidoscope-Ch7
    #Kaleidoscope-Ch8
    #Kaleidoscope-Ch9
    #libclang
    LLVMAArch64AsmParser
    LLVMAArch64AsmPrinter
    LLVMAArch64CodeGen
    LLVMAArch64Desc
    LLVMAArch64Disassembler
    LLVMAArch64Info
    LLVMAArch64Utils
    LLVMAggressiveInstCombine
    LLVMAMDGPUAsmParser
    LLVMAMDGPUAsmPrinter
    LLVMAMDGPUCodeGen
    LLVMAMDGPUDesc
    LLVMAMDGPUDisassembler
    LLVMAMDGPUInfo
    LLVMAMDGPUUtils
    LLVMAnalysis
    LLVMARMAsmParser
    LLVMARMAsmPrinter
    LLVMARMCodeGen
    LLVMARMDesc
    LLVMARMDisassembler
    LLVMARMInfo
    LLVMARMUtils
    LLVMAsmParser
    LLVMAsmPrinter
    LLVMBinaryFormat
    LLVMBitReader
    LLVMBitWriter
    LLVMBPFAsmParser
    LLVMBPFAsmPrinter
    LLVMBPFCodeGen
    LLVMBPFDesc
    LLVMBPFDisassembler
    LLVMBPFInfo
    LLVMCodeGen
    LLVMCore
    LLVMCoroutines
    LLVMCoverage
    LLVMDebugInfoCodeView
    LLVMDebugInfoDWARF
    LLVMDebugInfoMSF
    LLVMDebugInfoPDB
    LLVMDemangle
    LLVMDlltoolDriver
    LLVMExecutionEngine
    LLVMFuzzMutate
    LLVMGlobalISel
    LLVMHexagonAsmParser
    LLVMHexagonCodeGen
    LLVMHexagonDesc
    LLVMHexagonDisassembler
    LLVMHexagonInfo
    LLVMInstCombine
    LLVMInstrumentation
    LLVMInterpreter
    LLVMipo
    LLVMIRReader
    LLVMLanaiAsmParser
    LLVMLanaiAsmPrinter
    LLVMLanaiCodeGen
    LLVMLanaiDesc
    LLVMLanaiDisassembler
    LLVMLanaiInfo
    LLVMLibDriver
    LLVMLineEditor
    LLVMLinker
    LLVMLTO
    LLVMMC
    LLVMMCDisassembler
    LLVMMCJIT
    LLVMMCParser
    LLVMMipsAsmParser
    LLVMMipsAsmPrinter
    LLVMMipsCodeGen
    LLVMMipsDesc
    LLVMMipsDisassembler
    LLVMMipsInfo
    LLVMMIRParser
    LLVMMSP430AsmPrinter
    LLVMMSP430CodeGen
    LLVMMSP430Desc
    LLVMMSP430Info
    LLVMNVPTXAsmPrinter
    LLVMNVPTXCodeGen
    LLVMNVPTXDesc
    LLVMNVPTXInfo
    LLVMObjCARCOpts
    LLVMObject
    LLVMObjectYAML
    LLVMOption
    LLVMOrcJIT
    LLVMPasses
    LLVMPowerPCAsmParser
    LLVMPowerPCAsmPrinter
    LLVMPowerPCCodeGen
    LLVMPowerPCDesc
    LLVMPowerPCDisassembler
    LLVMPowerPCInfo
    LLVMProfileData
    LLVMRuntimeDyld
    LLVMScalarOpts
    LLVMSelectionDAG
    LLVMSparcAsmParser
    LLVMSparcAsmPrinter
    LLVMSparcCodeGen
    LLVMSparcDesc
    LLVMSparcDisassembler
    LLVMSparcInfo
    LLVMSupport
    LLVMSymbolize
    LLVMSystemZAsmParser
    LLVMSystemZAsmPrinter
    LLVMSystemZCodeGen
    LLVMSystemZDesc
    LLVMSystemZDisassembler
    LLVMSystemZInfo
    LLVMTableGen
    LLVMTarget
    LLVMTestingSupport
    LLVMTransformUtils
    LLVMVectorize
    LLVMWindowsManifest
    LLVMX86AsmParser
    LLVMX86AsmPrinter
    LLVMX86CodeGen
    LLVMX86Desc
    LLVMX86Disassembler
    LLVMX86Info
    LLVMX86Utils
    LLVMXCoreAsmPrinter
    LLVMXCoreCodeGen
    LLVMXCoreDesc
    LLVMXCoreDisassembler
    LLVMXCoreInfo
    LLVMXRay
    LTO
    clangParse
    clangSerialization
    clangDriver
    clangIndex
    clangSema
    clangAnalysis
    clangAST
    clangFrontend
    clangEdit
    clangLex
    clangBasic
    LLVMSupport
    LLVMCore
    LLVMMC
    )
