cmake_minimum_required(VERSION 3.10)
project(cppnamelint)


set(CMAKE_CXX_STANDARD          14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS        OFF)


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
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /source-charset:utf-8")
    set(gtest_force_shared_crt ON CACHE BOOL "Always use msvcrt.dll" )
elseif(UNIX AND NOT APPLE)
    set(CC   "/usr/bin/gcc-8")
    set(CXX  "/usr/bin/g++-8")
    string(TOLOWER ${BUILD_TYPE} BUILD_TYPE)
    set(CMAKE_CXX_FLAGS "-frtti -g")
elseif(APPLE)
    set(CC   "/usr/bin/clang-8")
    set(CXX  "/usr/bin/clang++-8")
    string(TOLOWER ${BUILD_TYPE} BUILD_TYPE)
    set(CMAKE_CXX_FLAGS "-frtti")
endif()


###############################################################################
set(NAMELINT_LLVM_LIB_PATH $ENV{NAMELINT_LLVM_LIB}/build/${BUILD_TYPE}/lib)
if(WIN32)
    set(EXTERNAL_LIB Version)
elseif(UNIX AND NOT APPLE)
    set(EXTERNAL_LIB z tinfo)
elseif(APPLE)
    set(EXTERNAL_LIB z ncurses)
endif()


###############################################################################
include_directories(
    $ENV{NAMELINT_LLVM_LIB}/llvm/include
    $ENV{NAMELINT_LLVM_LIB}/clang/include
    $ENV{NAMELINT_LLVM_LIB}/build/include
    $ENV{NAMELINT_LLVM_LIB}/build/tools/clang/include
    $ENV{NAMELINT_LLVM_LIB}/build/${BUILD_TYPE}/include
    $ENV{NAMELINT_LLVM_LIB}/build/${BUILD_TYPE}/tools/clang/include
    $ENV{NAMELINT_LLVM_LIB}/build/${BUILD_TYPE}/tools/llvm/include
    Module/googletest.git/googletest/include
    Module/nlohmannjson.git/include
    Module/plog.git/include
    Module/docopt.cpp
)

link_directories(${NAMELINT_LLVM_LIB_PATH})


###############################################################################
message("CMAKE_CURRENT_SOURCE_DIR   : ${CMAKE_CURRENT_SOURCE_DIR}"  )
message("CMAKE_BUILD_TYPE           : ${CMAKE_BUILD_TYPE}"          )
message("CMAKE_SYSTEM               : ${CMAKE_SYSTEM}"              )
message("CMAKE_SYSTEM_NAME          : ${CMAKE_SYSTEM_NAME}"         )
message("CMAKE_SYSTEM_VERSION       : ${CMAKE_SYSTEM_VERSION}"      )
message("CMAKE_SYSTEM_PROCESSOR     : ${CMAKE_SYSTEM_PROCESSOR}"    )

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
message("NAMELINT_LLVM_LIB          : $ENV{NAMELINT_LLVM_LIB}")
message("NAMELINT_LLVM_LIB_PATH     : ${NAMELINT_LLVM_LIB_PATH}" )
#message("CMAKE_CXX_FLAGS            : ${CMAKE_CXX_FLAGS}" )
message("INC_PATH_1                 : $ENV{NAMELINT_LLVM_LIB}/llvm/include" )
message("INC_PATH_2                 : $ENV{NAMELINT_LLVM_LIB}/clang/include" )
message("INC_PATH_3                 : $ENV{NAMELINT_LLVM_LIB}/build/${BUILD_TYPE}/include" )
message("INC_PATH_4                 : $ENV{NAMELINT_LLVM_LIB}/build/${BUILD_TYPE}/tools/clang/include" )
message("INC_PATH_5                 : $ENV{NAMELINT_LLVM_LIB}/build/${BUILD_TYPE}/tools/llvm/include" )


###############################################################################
option(BUILD_TESTING "Turn OFF to build the testing tree (nlohmannjson)." OFF)

add_subdirectory(Module/docopt.cpp)
add_subdirectory(Module/googletest.git)
add_subdirectory(Module/nlohmannjson.git)
add_subdirectory(Module/plog.git)


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
add_executable(
    cppnamelint
    Module/tinytoml.git/include/toml/toml.h
    Module/docopt.cpp/docopt.h
    Source/TraceMemo.h
    Source/Main.cpp
    Source/Detection.h
    Source/Detection.cpp
    Source/Common.h
    Source/Common.cpp
    Source/Config.h
    Source/Config.cpp
    Source/LearnIt.h
    Source/LearnIt.cpp
    Source/MyFactory.h
    Source/MyFactory.cpp
    Source/MyAstVisitor.h
    Source/MyAstVisitor.cpp
    Source/MyAstConsumer.h
    Source/MyAstConsumer.cpp
    Source/Test/TestConfig.cpp
    Source/Test/TestDetection.cpp
)


###############################################################################
target_link_libraries(
    cppnamelint
    docopt
    gtest
    gtest_main
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
    ${EXTERNAL_LIB}
)
