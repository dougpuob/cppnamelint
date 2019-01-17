# NameLint
The `NameLint` C/C++ naming convention checking tool which can run on Windows/Linux/MacOS for name of files, functions, variable, and paramters. This project is based on LLVM's LibTooling as a compiler frontend to retrieve AST from C/C++ source files, then check your naming rules like UpperCamel, LowerCamel, LowerSeperated, and Hungarain.

1. File target for C/C++ source code.
1. Cross platform on Windows/Linux/macOS.
1. String target for files, functions, variables, and parameters.
1. Config file format with TOML.1.
1. Naming rule with UpperCamel, LowerCamel, LowerSeperated, and Hungarain.

`#LLVM` `#Clang` `#LibTooling` `#Compiler` `#Naming` `#NamingConvention` `#Toml` `#NameLint`

----------

## Usage
```
NameLint utility v0.0.1

  Usage:
    namelint check <file> [--config=<file>] [--log=<file>]
    namelint test   [-a | --all] [-u | --unittest]
    namelint config [--config=<file>]
    namelint --help
    namelint --version

  Options:
    --config=<file>   [default: namelint.toml]
    --log=<file>      [default: namelint.log]
```

### Examples
1. `namelint check InputFile.cpp --config=Config.toml`


----------

### [How To Start]
This instructions NOW for Windows, make it work on Linux and MacOS in beta phase.

1. `git clone https://github.com/dougpuob/cpp-namelint.git namelint.git`
1. `cd namelint.git`
1. `git submodule init`
1. `git submodule update`
1. `cd Script`
1. Run BuildWin32.cmd/BuildLinux.sh/BuildMacOS.sh .


----------

## License
MIT