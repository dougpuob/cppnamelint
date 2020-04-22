# **CppNameLint**

![](https://img.shields.io/azure-devops/build/CPPNAMELINT/78202891-aba0-41ab-952b-2152c4a57470/3?style=plastic)
[![Codacy Badge](https://api.codacy.com/project/badge/Grade/43b938056017438d886670b354e52485)](https://app.codacy.com/manual/dougpuob/cpp-namelint?utm_source=github.com&utm_medium=referral&utm_content=dougpuob/cpp-namelint&utm_campaign=Badge_Grade_Dashboard)

| Windows | Linux | macOS |
|---------|-------|-------|
|![](https://dev.azure.com/CppNameLint/cpp-namelint/_apis/build/status/cpp-namelint?branchName=master&jobName=BuildOnWindows) |![](https://dev.azure.com/CppNameLint/cpp-namelint/_apis/build/status/cpp-namelint?branchName=master&jobName=BuildOnLinux)   | ![](https://dev.azure.com/CppNameLint/cpp-namelint/_apis/build/status/cpp-namelint?branchName=master&jobName=BuildOnMacOS)


The `cppnamelint` C/C++ naming convention checking tool which can run on Windows/Linux/MacOS for name of files, functions, variable, and parameters. This project is based on LLVM's LibTooling as a compiler frontend to retrieve AST from C/C++ source files, then check your naming rules like UpperCamel, LowerCamel, SnakeCase, and Hungarain.

1. File target for C/C++ source code.
1. Cross platform on Windows/Linux/macOS.
1. String target for files, functions, variables, and parameters.
1. Config file format with TOML.
1. Naming rule with UpperCamel, LowerCamel, SnakeCase, and Hungarain.


`#LLVM` `#Clang` `#LibTooling` `#Compiler` `#Naming` `#NamingConvention` `#Toml` `#CppNameLint`

----------

## **Usage**

### Commands
1. **Run Check command**  
   - `cppnamelint check UpperCamel.c -config=cppnamelint.toml`
   - `cppnamelint check UpperCamel.c -config=cppnamelint.toml -logfile logfile.log`
   
1. **Run Test command**  
   `cppnamelint test -all`

1. **Run Dump command**  
   TODO.

### Helps
```
$ cppnamelint -help

cppnamelint utility v0.3.0
---------------------------------------------------
USAGE: cppnamelint.exe [subcommand] [options]

SUBCOMMANDS:

  check - Check source with naming rules.
  dump  - Dump default config file. (TODO)
  test  - Run tests.

  Type "cppnamelint.exe <subcommand> -help" to get more help on a specific subcommand

OPTIONS:
  -help              - Display available options (-help-hidden for more)
  -logfile=<LogName> - Print log message to the specific a log file.
  -verbose           - Enable verbose mode.
  -version           - Display the version of this program
```

```
$ cppnamelint check -help

cppnamelint utility v0.3.0
---------------------------------------------------
SUBCOMMAND 'check': Check source with naming rules.

USAGE: cppnamelint.exe check [options] <input file>

OPTIONS:

CppNameLint options:

  -config=<FileName>           - Specific your config file(.toml).
  -include=<-include Dir1 ...> - Specific header folers.
  -jsonout=<FileName>          - Generate result to a JSON file.
  -logfile=<LogName>           - Print log message to the specific a log file.
  -verbose                     - Enable verbose mode.

Generic Options:

  -help                        - Display available options (-help-hidden for more)
```

----------

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
