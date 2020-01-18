# **CppNameLint**

[![Codacy Badge](https://api.codacy.com/project/badge/Grade/43b938056017438d886670b354e52485)](https://app.codacy.com/manual/dougpuob/cpp-namelint?utm_source=github.com&utm_medium=referral&utm_content=dougpuob/cpp-namelint&utm_campaign=Badge_Grade_Dashboard)

| Windows | Linux | macOS |
|---------|-------|-------|
|![](https://dev.azure.com/CppNameLint/cpp-namelint/_apis/build/status/cpp-namelint?branchName=master&jobName=Windows) |![](https://dev.azure.com/CppNameLint/cpp-namelint/_apis/build/status/cpp-namelint?branchName=master&jobName=Linux)   | ![](https://dev.azure.com/CppNameLint/cpp-namelint/_apis/build/status/cpp-namelint?branchName=master&jobName=macOS)


The `cppnamelint` C/C++ naming convention checking tool which can run on Windows/Linux/MacOS for name of files, functions, variable, and parameters. This project is based on LLVM's LibTooling as a compiler frontend to retrieve AST from C/C++ source files, then check your naming rules like UpperCamel, LowerCamel, SnakeCase, and Hungarain.

1. File target for C/C++ source code.
1. Cross platform on Windows/Linux/macOS.
1. String target for files, functions, variables, and parameters.
1. Config file format with TOML.
1. Naming rule with UpperCamel, LowerCamel, SnakeCase, and Hungarain.


`#LLVM` `#Clang` `#LibTooling` `#Compiler` `#Naming` `#NamingConvention` `#Toml` `#CppNameLint`

----------

## **Usage**
```
cppnamelint utility v0.1.2

  Usage:
    cppnamelint check <file> [--config=<file>] [--log=<file>] [--jsonout=<file>] [--includes=<dir1:dir2:...>]
    cppnamelint test   [-a | --all] [-u | --unittest]
    cppnamelint --help
    cppnamelint --version

  Options:
        --config=<file>  [default: cppnamelint.toml]
        --jsonout=<file> [default: cppnamelint.json]
    --log=<file>     [default: cppnamelint.log]
```


----------

## **Examples**

### **Commands**

1. `cppnamelint check UpperCamel.c`
1. `cppnamelint check UpperCamel.c --config=cppnamelint.toml`
1. `cppnamelint test -a`

### **Config File**

```toml
[General.Options]
Version                 = 0.2
FileExtNameList         = ["*.c","*.h","*.cpp"]
CheckVariableName       = true
CheckFunctionName       = true
CheckFileName           = false
AllowedUnderscopeChar   = false
AllowedArrayAffected    = false


[General.Rules]
FileName                = 0 # 0: Default (UpperCamel)
                            # 1: UpperCamel
                            # 3: lower-seperated

FunctionName            = 0 # 0: Default (UpperCamel)
                            # 1: UpperCamel
                            # 2: lowerCamel
                            # 3: lower-seperated

VariableName            = 4 # 0: Default (UpperCamel)
                            # 1: UpperCamel
                            # 2: lowerCamel
                            # 3: lower-seperated
                            # 4: Hungarian

[General.IgnoredList]
FunctionPrefix          = [ "_",
                            "__" ]
VariablePrefix          = [ "m_" ]

FunctionName            = ["main",
                           "newASTConsumer"]


[Hungarian.Others]
PreferUpperCamelIfMissed = true

[Hungarian.PointerList]
"char*"                  = "sz"
"wchar_t*"               = "wsz"
"char**"                 = "psz"
"wchar_t**"              = "pwsz"

[Hungarian.ArrayList]
char                     = "sz"


[Hungarian.WordList]
# C Primitive Type
"void"                   = ""
"size_t"                 = "n"
"int8_t"                 = "i8"
"int16_t"                = "i16"
"int32_t"                = "i32"
"int64_t"                = "i64"
"uint8_t"                = "u8"
"uint16_t"               = "u16"
"uint32_t"               = "u32"
"uint64_t"               = "u64"
"char"                   = "c"
"_Bool"                  = "b"
"bool"                   = "b"
"wchar_t"                = "wc"
"signed char"            = "sc"
"unsigned char"          = "uc"
"short"                  = "s"
"short int"              = "si"
"signed short"           = "ss"
"signed short int"       = "ssi"
"unsigned short"         = "us"
"unsigned short int"     = "usi"
"int"                    = "i"
"signed"                 = "s"
"signed int"             = "si"
"unsigned"               = "u"
"unsigned int"           = "ui"
"long"                   = "l"
"long int"               = "li"
"signed long"            = "sl"
"signed long int"        = "sli"
"unsigned long"          = "ul"
"unsigned long int"      = "uli"
"long long"              = "ll"
"long long int"          = "lli"
"signed long long"       = "sll"
"signed long long int"   = "slli"
"unsigned long long"     = "ull"
"unsigned long long int" = "ulli"
"float"                  = "f"
"double"                 = "d"
"long double"            = "ld"

# Windows Type
"ULONG"                  = "ul"
"DWORD"                  = "dw"
"DWORD64"                = "dw64"
"WORD"                   = "w"
"CHAR"                   = "c"
"BYTE"                   = "by"
"HANDLE"                 = "h"
"BOOLEAN"                = "b"
"LONGLONG"               = "ll"
```

----------

## **Samples**

### **Passed case**

```shell
D:\cppnamelint_v0.1.2>cppnamelint.exe check Test\Sample\UpperCamel_1.c --config=Test\Sample\UpperCamel_1.toml
cppnamelint utility v0.1.2
---------------------------------------------------
 File    = Test\Sample\UpperCamel_1.c
 Config  = Test\Sample\UpperCamel_1.toml
 Checked =    17  [Func:  8 | Param:  4 | Var:  5]
 Error   =     0  [Func:  0 | Param:  0 | Var:  0]
---------------------------------------------------

ERRORLEVEL=0
```
  
![Passed Case](https://i.imgur.com/JmULdqR.png)

### **Failed case**

```shell
D:\cppnamelint_v0.1.2>cppnamelint.exe check Test\Sample\UpperCamel_1.c --config=Test\Sample\UpperCamel_1.toml
cppnamelint utility v0.1.2
---------------------------------------------------
 File    = Test\Sample\UpperCamel_1.c
 Config  = Test\Sample\UpperCamel_1.toml
 Checked =    17  [Func:  8 | Param:  4 | Var:  5]
 Error   =     2  [Func:  0 | Param:  2 | Var:  0]
---------------------------------------------------
  <5, 13> Parameter:    iValue (int)
  <5, 13> Variable :    iValue (int)

ERRORLEVEL=1
```
  
![Failed Case](https://i.imgur.com/YLWolw0.png)


----------

## **Tests**

### **Unit Test**

`cppnamelint test -a`
`cppnamelint test --all`

![Unit Test](https://i.imgur.com/a09h4Yg.png)


### **Sample Test**

`Test/TestWin32.cmd`
`Test/TestLinux.cmd`
![namelint.log](https://i.imgur.com/rEnoOs4.png)


----------

## **Download Pre-built**

- [**Pre-built**](https://github.com/dougpuob/cpp-namelint/releases)


----------


```
{
  "SourceFile" : "Common.cpp",
  "ConfigFile" : "Config.toml",
  "CheckedNumber" : {
    "Function" : 10,
    "Argument" : 10,
    "Variable" : 10
  },
  "ErrorNumber" : {
    "Total" : 100,
    "Function" : 10,
    "Argument" : 10,
    "Variable" : 10
  },
  "Details" : [
    {"Line" : 10, "Column": 10, "Type" : "Function", "Text" : "IsStatus", "Expected" : ""}
    ]
}
```


----------


## License
MIT
