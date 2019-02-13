# **NameLint**
The `NameLint` C/C++ naming convention checking tool which can run on Windows/Linux/MacOS for name of files, functions, variable, and parameters. This project is based on LLVM's LibTooling as a compiler frontend to retrieve AST from C/C++ source files, then check your naming rules like UpperCamel, LowerCamel, LowerSeperated, and Hungarain.

1. File target for C/C++ source code.
1. Cross platform on Windows/Linux/macOS.
1. String target for files, functions, variables, and parameters.
1. Config file format with TOML.
1. Naming rule with UpperCamel, LowerCamel, LowerSeperated, and Hungarain.

`#LLVM` `#Clang` `#LibTooling` `#Compiler` `#Naming` `#NamingConvention` `#Toml` `#NameLint`

----------

## **Usage**
```
NameLint utility v0.0.4

  Usage:
    namelint check <file> [--config=<file>] [--log=<file>]
    namelint test   [-a | --all] [-u | --unittest]
    namelint --help
    namelint --version

  Options:
    --config=<file>   [default: namelint.toml]
    --log=<file>      [default: namelint.log]
```


----------

## **Examples**

### **Commands**

1. `namelint check UpperCamel.c`
1. `namelint check UpperCamel.c --config=namelint.toml`
1. `namelint test -a`

### **Config File**

```toml
[General]
ListFileExtName         = ["*.c","*.h","*.cpp"]
BoolCheckVariableName   = true
BoolCheckFunctionName   = true
BoolCheckFileName       = true

[Rule]
EnumFileName            = 1 # 0: Default (UpperCamelCase)
                            # 1: UpperCamelCase
                            # 3: lower-seperated

EnumFunctionName        = 1 # 0: Default (UpperCamelCase)
                            # 1: UpperCamelCase
                            # 2: lowerCamelCase
                            # 3: lower-seperated

EnumVariableName        = 1 # 0: Default (UpperCamelCase)
                            # 1: UpperCamelCase
                            # 2: lowerCamelCase
                            # 3: lower-seperated
                            # 4: Hungarian
[WhiteList]
BoolAllowedUnderscopeChar    = false

ListFunctionPrefix           = [ "_",
                                 "__"
                               ]
                               
ListVariablePrefix           = [ "m_" ]

IgnoreFunctions              = ["main"]


[HungarianList]
# C Primitive Type
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
"char*"                  = "sz"
"wchar_t*"               = "wsz"
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
C:\working-folder\namelint\namelint.git\Doc>namelint.exe check UpperCamel.c
<file>   = "UpperCamel.c"
--config = "namelint.toml"

ERRORLEVEL=0
```
  
![Passed Case](https://i.imgur.com/rGfl526.png)

### **Failed case**

```shell
C:\working-folder\namelint\namelint.git\Doc>namelint.exe check UpperCamel.c
<file>   = "UpperCamel.c"
--config = "namelint.toml"

[C:\working-folder\namelint\namelint.git\Doc\UpperCamel.c]
  <5,5>  Variable:      u8MyValue (uint8_t)

ERRORLEVEL=1
```
  
![Failed Case](https://i.imgur.com/HM5RZhh.png)


----------

## **Tests**

### **Unit Test**

`namelint test -a`
`namelint test --all`

![Unit Test](https://i.imgur.com/a09h4Yg.png)


### **Sample Test**

`Test/TestWin32.cmd`
`Test/TestLinux.cmd`
![namelint.log](https://i.imgur.com/rEnoOs4.png)


----------

## **Download Pre-built**

- **Windows**
  - **namelint_v0.0.3.7z**[http://bit.ly/2ROBHnO]
  - **namelint_v0.0.4.7z**[http://bit.ly/2tjnIMP]
  
- **Linux**
- **macOS**

----------

## **How to start** (as a Developer)
It is a lazy note, if you need to develop NameLint, please contact with me will save your time. I will write a complete manual later.

1. `git clone https://dougpuob@bitbucket.org/dougpuob/cpp-namelint.git namelint.git`
1. `cd namelint.git`
1. `git submodule init`
1. `git submodule update`
1. `cd Script`
1. Run BuildWin32.cmd/BuildLinux.sh/BuildMacOS.sh .
1. Build the project(Win32=MSVC, Linux=g++-8, macOS=clang++).
1. Run TestWin32.cmd/TestLinux.sh


----------

## License
MIT
