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
    set (BUILD_TYPE NONE)
endif()


###############################################################################
set(LLVM_VERSION 8.0.0)# llvmorg-8.0.0
set(NAMELINT_LLVM_LIB_VER "$ENV{NAMELINT_LLVM_LIB}/${LLVM_VERSION}")
if(WIN32)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd4141")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd4244")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd4146")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd4291")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd4227")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd4099")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd4996")
    set(gtest_force_shared_crt ON CACHE BOOL "Always use msvcrt.dll" )
    set(NAMELINT_LLVM_LIB_PATH ${NAMELINT_LLVM_LIB_VER}/build/${BUILD_TYPE}/lib)
elseif(UNIX AND NOT APPLE)
    set(CMAKE_CXX_FLAGS "-frtti")
    set(NAMELINT_LLVM_LIB_PATH ${NAMELINT_LLVM_LIB_VER}/build/lib)
elseif(APPLE)
    set(CMAKE_CXX_FLAGS "-frtti -lz")
    set(NAMELINT_LLVM_LIB_PATH ${NAMELINT_LLVM_LIB_VER}/build/lib)
endif()


###############################################################################
include_directories(
        ${NAMELINT_LLVM_LIB_VER}/llvm/include
        ${NAMELINT_LLVM_LIB_VER}/clang/include
        ${NAMELINT_LLVM_LIB_VER}/build/include
        ${NAMELINT_LLVM_LIB_VER}/build/tools/clang/include
        Module/googletest.git/googletest/include
        Module/jsoncons.git/include
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
message("LLVM_VERSION               : ${LLVM_VERSION}")
message("NAMELINT_LLVM_LIB          : $ENV{NAMELINT_LLVM_LIB}")
message("NAMELINT_LLVM_LIB_VER      : ${NAMELINT_LLVM_LIB_VER}" )
message("NAMELINT_LLVM_LIB_PATH     : ${NAMELINT_LLVM_LIB_PATH}" )
message("CMAKE_CXX_FLAGS            : ${CMAKE_CXX_FLAGS}" )
message("INC_PATH_1                 : ${NAMELINT_LLVM_LIB_VER}/llvm/include" )
message("INC_PATH_2                 : ${NAMELINT_LLVM_LIB_VER}/clang/include" )
message("INC_PATH_3                 : ${NAMELINT_LLVM_LIB_VER}/build/include" )
message("INC_PATH_4                 : ${NAMELINT_LLVM_LIB_VER}/build/tools/clang/include" )
message("INC_PATH_5                 : Module/googletest.git/googletest/include" )


###############################################################################
add_subdirectory(Module/docopt.cpp)
add_subdirectory(Module/googletest.git)
add_subdirectory(Module/jsoncons.git)


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

if(WIN32)
    set(EXTERNAL_LIB Version)
elseif(UNIX AND NOT APPLE)
    set(EXTERNAL_LIB)
elseif(APPLE)
    set(EXTERNAL_LIB ncurses)
endif()

target_link_libraries(
        cppnamelint
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
