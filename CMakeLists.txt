cmake_minimum_required(VERSION 3.10)
project(namelint)

message("CMAKE_SYSTEM           : ${CMAKE_SYSTEM}"           )
message("CMAKE_SYSTEM_NAME      : ${CMAKE_SYSTEM_NAME}"      )
message("CMAKE_SYSTEM_VERSION   : ${CMAKE_SYSTEM_VERSION}"   )
message("CMAKE_SYSTEM_PROCESSOR : ${CMAKE_SYSTEM_PROCESSOR}" )

set(CMAKE_CXX_STANDARD          14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS        OFF)

set(PREBUILD_DIR $ENV{NAMELINT_DEVTLS} )
set(PREBUILD_DIR_LLVM   ${PREBUILD_DIR}/llvm/7.0.1)


###############################################################################
if(WIN32)
    message("Platform               : WIN32" )
elseif(UNIX AND NOT APPLE)
    message("Platform               : UNIX AND NOT APPLE" )
elseif(APPLE)
    message("Platform               : APPLE" )
else()
    message("Platform               : None" )
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
elseif(APPLE)
    #set(CMAKE_CXX_COMPILER /usr/local/bin/gcc-8)
endif()

message("CMAKE_CXX_FLAGS        : ${CMAKE_CXX_FLAGS}" )

include_directories(
    ${PREBUILD_DIR_LLVM}/include
    ${PREBUILD_DIR_LLVM}/build/include
    ${PREBUILD_DIR_LLVM}/build/tools/clang/include
    ${PREBUILD_DIR_LLVM}/tools/clang/include
    Module/googletest.git/googletest/include
    Module/docopt.cpp
    )


###############################################################################
if(WIN32)
    set(LINK_LIB1 "Build/win32/Module/docopt.cpp/Debug")
    set(LINK_LIB2 "Build/win32/lib/Debug")
elseif(UNIX AND NOT APPLE)
    set(LINK_LIB1 "Build/linux/Module/docopt.cpp")
    set(LINK_LIB2 "Build/linux/lib")
elseif(APPLE)
    set(LINK_LIB1 "Build/darwin/Module/docopt.cpp")
    set(LINK_LIB2 "Build/darwin/lib")
else()
    set(LINK_LIB1 "None")
    set(LINK_LIB2 "None")
endif()

message("LINK_LIB1              : ${LINK_LIB1}" )
message("LINK_LIB2              : ${LINK_LIB2}" )

# link_directories(
#     ${PREBUILD_DIR_LLVM}/build/debug/lib
#     $(LINK_LIB1)
#     $(LINK_LIB2)
#     )


###############################################################################
if(WIN32)
    link_directories(
        ${PREBUILD_DIR_LLVM}/build/debug/lib
        Build/win32/Module/docopt.cpp/Debug
        Build/win32/lib/Debug
        )
elseif(UNIX AND NOT APPLE)
    link_directories(
        ${PREBUILD_DIR_LLVM}/build/debug/lib
        Build/linux/Module/docopt.cpp
        Build/linux/lib
        )
elseif(APPLE)
    link_directories(
        ${PREBUILD_DIR_LLVM}/build/debug/lib
        Build/darwin/Module/docopt.cpp
        Build/darwin/lib
        )
else()
    link_directories(
        ${PREBUILD_DIR_LLVM}/build/debug/lib
        Build/darwin/Module/docopt.cpp
        Build/darwin/lib
        )
endif()



###############################################################################
add_subdirectory(Module/docopt.cpp)
add_subdirectory(Module/googletest.git)


###############################################################################
if(WIN32)
elseif(UNIX AND NOT APPLE)
    set(CMAKE_CXX_FLAGS "-fno-rtti")
elseif(APPLE)
    set(CMAKE_CXX_FLAGS "-fno-rtti -lz")
endif()

message("CMAKE_CXX_FLAGS        : ${CMAKE_CXX_FLAGS}" )

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
    Source/Test/TestDetection.cpp
    )


###############################################################################

if(WIN32)
    set(EXTERNAL_LIB Version)
elseif(UNIX AND NOT APPLE)
elseif(APPLE)
    set(EXTERNAL_LIB ncurses)
endif()

target_link_libraries(
    namelint
    docopt
    gtest
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
    gtest
    gtest_main
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
