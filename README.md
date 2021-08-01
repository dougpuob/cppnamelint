# CppNameLint
![My name is "Upper camel"](https://i.imgur.com/Aeigvpj.png) My name is **Upper Camel**. (My partner drew this mascot for the project)

| Windows | Linux | macOS |
|---------|-------|-------|
|![](https://dev.azure.com/CppNameLint/cpp-namelint/_apis/build/status/cpp-namelint?branchName=master&jobName=BuildOnWindows) |![](https://dev.azure.com/CppNameLint/cpp-namelint/_apis/build/status/cpp-namelint?branchName=master&jobName=BuildOnLinux)   | ![](https://dev.azure.com/CppNameLint/cpp-namelint/_apis/build/status/cpp-namelint?branchName=master&jobName=BuildOnMacOS)


The project is a naming convention checking tool executing on Windows/Linux/MacOS. It is based on LLVM's LibTooling as a compiler frontend to retrieve AST of C/C++ source files, then check your naming convention.

1. Check for C and C++ programming languages.
1. Check naming of file, functions, variables, and parameters.
1. Execute on Windows/Linux/macOS.
1. Load config file format with TOML.
1. Output results to console or save an a JSON file.
1. Support rules with `UpperCamelCase`, `lowerCamelCase`, `UPPER_SNAKE_CASE`, `lower_snake_case`, and `szHungarainNotion`.
1. Integrate with [Azure DevOps(CI/CD)](https://dev.azure.com/CppNameLint/cpp-namelint/_build?definitionId=3).

⭐If you like this project or this project gives you some help, please also give me a **STAR** on GitHub, let me know I am not alone.


————————————————————————————————————————————
## ● Quick Start
1. **You are an user:** 
   - Use it directly, please goto the `release` page to download the artifacts files by Azure DevOps.
       https://github.com/dougpuob/cpp-namelint/releases

   - Know more, please start from **Usage**.

1. **You are a developer** 
   - This project is based on `llvmorg-8.0.0`.
   - How to build this project:
     - https://github.com/dougpuob/cpp-namelint/blob/master/doc/how-to-build-cppnamelint.md
   - How to build LLVM:
     - https://github.com/dougpuob/cpp-namelint/blob/master/doc/how-to-build-llvm.md   
   - Simple example to use ClangTool.
     - https://github.com/dougpuob/example-hello-clangtool
   - Prebuilt LLVM artifacts packages, which I use with Azure DevOps.
     - https://bit.ly/3htcnBs (GoogleDrive)   

————————————————————————————————————————————

## ● Usage

### Commands
1. **Run Check command**  
   ``` pwsh
   # Check source file with a specfic config file.  
   $ cppnamelint check YouPlayGround.cpp -config cppnamelint.toml
   
   # Check source file with a specfic config file, and specific header directories (Dir1 and Dir2)
   $ cppnamelint check YouPlayGround.cpp -config cppnamelint.toml -include Dir1 -include Dir2
   
   # Check source file with a specfic config file, and save check result as a JSON file to the specific path.  
   $ cppnamelint check YouPlayGround.cpp -config cppnamelint.toml -jsonout result.json
   
   # Check source file with a specfic config file, and save log to the specific path.  
   $ cppnamelint check YouPlayGround.cpp -config cppnamelint.toml -logfile logout.log
   $ cppnamelint check YouPlayGround.cpp -config cppnamelint.toml -jsonout result.json -logfile logout.log
   ```
   
   ![](https://i.imgur.com/2i1HpWZ.png)
      
1. **Run Test command**  
   ``` pwsh
   # Run Unit Test (Google Test)
   $ cppnamelint test
   ```

### Helps

``` pwsh
# Show usage help to subcommands.
$ cppnamelint -help
```
![](https://i.imgur.com/X6bE6L8.png)
   

``` pwsh
# Show usage help to `check` subcommand.
$ cppnamelint check -help
```
![](https://i.imgur.com/xtuDptW.png)


————————————————————————————————————————————


## ● Tests

### Unit Test
![Unit Test](https://i.imgur.com/ug3YKuT.png)


————————————————————————————————————————————


## ● Scripts

### `cppnamelint.py`

This is a Python script, which privodes several features:
1. Integrate automation with CI/CD (build, packing, and test).
2. Enhance `cppnamelint` utility, making it more convenient to integrated into your project.

``` pwsh
$ python .\cppnamelint.py -h
usage: cppnamelint.py [-h] [-verbose] [-dbg] [-log LOG]
                      {check,checkdir,format,test,chkenv,bldgtest,bldgpack,bldgcfg} ...

positional arguments:
  {check,checkdir,format,test,chkenv,bldgtest,bldgpack,bldgcfg}
    check               check command
    checkdir            checkdir command
    format              format command
    test                test command
    chkenv              chkenv command for checking build environment
    bldgtest            bldgtest command for building this project
    bldgpack            bldgpack command for packing this project
    bldgcfg             bldgcfg command for doing config via Cmake

optional arguments:
  -h, --help            show this help message and exit
  -verbose              increase output verbosity
  -dbg                  enable debug mode output verbosity
  -log LOG              log file path
```

### Commands
1. **Check whole files in a specfic directory**  
   ``` pwsh
    $ python .\cppnamelint.py checkdir -h
    usage: cppnamelint.py checkdir [-h] [-cfg CFG] [-json JSON] [-inc INC] srcdir

    positional arguments:
      srcdir      Input source code file dir

    optional arguments:
      -h, --help  show this help message and exit
      -cfg CFG    Config file path
      -json JSON  Json result output file path
      -inc INC    None or more include directory. (-inc Dir1 -inc Dir2 ...)
    
    
   # Check source file with a specfic config file.  
   $ python .\cppnamelint.py checkdir ../source -cfg ../cppnamelint.toml
   ```


————————————————————————————————————————————


## ● Screenshots
### Passed case

``` pwsh
C:\>cppnamelint.exe check YouPlayGround.cpp -config cppnamelint.toml
cppnamelint utility v0.3.1
---------------------------------------------------
 File    = YouPlayGround.cpp
 Config  = cppnamelint.toml
 Checked =     6  [File:0 | Func:  5 | Param:  1 | Var:  0 | Enum:  0 | Struct:  0 | Union:  0 | Class:  0]
 Error   =     0  [File:0 | Func:  0 | Param:  0 | Var:  0 | Enum:  0 | Struct:  0 | Union:  0 | Class:  0]
------------------------------------------------------------
```
  
![Passed Case](https://i.imgur.com/CBP64B6.png)

### Failed case

```shell
C:\>cppnamelint.exe check YouPlayGround.cpp -config cppnamelint.toml
cppnamelint utility v0.3.1
---------------------------------------------------
 File    = YouPlayGround.cpp
 Config  = cppnamelint.toml
 Checked =     6  [File:0 | Func:  5 | Param:  1 | Var:  0 | Enum:  0 | Struct:  0 | Union:  0 | Class:  0]
 Error   =     1  [File:0 | Func:  0 | Param:  1 | Var:  0 | Enum:  0 | Struct:  0 | Union:  0 | Class:  0]
------------------------------------------------------------
  <  16,   25> Parameter : inputValue (int)
------------------------------------------------------------
```
  
![Failed Case](https://i.imgur.com/N78C0kI.png)


### Others
- Check command with `-verbose` option.
   ![](https://i.imgur.com/jRY40sn.png)
   
- JSON result (Good case)
  ![](https://i.imgur.com/Kp9onEg.png)
  
- JSON result (Bad case)
  ![](https://i.imgur.com/ar3wook.png)
``` json
      [{
        "Checked": {
            "Function": 5,
            "Parameter": 1,
            "Variable": 0
        },
        "Error": {
            "Function": 0,
            "Parameter": 1,
            "Variable": 0
        },
        "ErrorDetailList": [
            {
                "Column": 25,
                "Expected": "",
                "Line": 16,
                "TargetName": "inputValue",
                "Type": 4,
                "TypeName": "int"
            }
        ],
        "File": {
            "Config": "cppnamelint.toml",
            "Source": "C:\\petzone\\cpp-namelint\\sample\\YouPlayGround.cpp"
        }
    }]
```

————————————————————————————————————————————

## ● License
MIT


————————————————————————————————————————————

## ● Author
Douglas Chen <dougpuob@gmail.com>


