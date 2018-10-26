# NameLint
The `NameLint` project is an Open Source tool on Windows/Linux/MacOS for checking naming convention which integrates with LLVM's LibTooling as a compiler frontend to retrieve AST from C/C++ source files, then check your naming rules like UpperCamel, LowerCamel, LowerSeperated, and Hungarain, including file name, function name, variable and parameter name.

Provide a TOML format config to customize your own prefix and subfix  string for your projects.

Now the project is still undergoing. If you are interested in the project welcome to join to this project.

`#LLVM` `#Clang` `#LibTooling` `#Compiler` `#Naming` `#NamingConvention` `#Toml` `#NameLint`

----------

## Usage
As an user you can see how to use this tool. What you need with three elements:
1. `NameLint` executable binary file.
2. TOML format configuration file.
3. Your source code files.


### [Options]
`-config=` With a specific configuration file.


### [Example]
**Check with default configuration**
`namelint MyFile.cpp`

**Check with your own configuration**
`namelint MyFile.cpp -config=config.toml`

----------

## Development
### [External Projects]
- **[toml]** https://github.com/toml-lang/toml.git

### [Required Libraries]
- **[LLVM]** https://goo.gl/jtDGMR
- **[GoogleTest]** https://goo.gl/R5N3wk

### [How To Start]
This instructions NOW for Windows, make it work on Linux and MacOS in beta phase.

1. `git clone https://github.com/dougpuob/cpp-namelint.git namelint.git`
2. `cd namelint.git`
3. `git submodule init`
4. `git submodule update`
5. `cd Build`
6. Mouse right-click on file to execute `Cmake.ps1` script wtih **Run with PowerShell**.
7. Launch Build/Win32NT/namelint.sln to build the project on Windows.

----------

## License
MIT