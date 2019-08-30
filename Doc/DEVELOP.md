# **Development for CppNameLint**


https://clang.llvm.org/get_started.html

## **Summary necessaries**
1. git
2. cmake
3. Build environments
   - Windows
     1. Visual Studio 2017 Community

   - Linux
   - MacOS


## **Summary steps for LLVM(clang)**
1. Fetch source code of LLVM(clang).
   1. `git clone https://github.com/llvm/llvm-project.git llvm-project.git`
1. Configure LLVM(clang) project.
   1. `cd llvm-project.git`
   1. `git checkout llvmorg-8.0.0`
   1. `mkdir build/release -p`
   1. `cd build/release`
   1. Config project via CMake:
      - Windows
        - Release
          - 32-bit (293 MB) : `cmake -DLLVM_ENABLE_PROJECTS=clang -DCMAKE_BUILD_TYPE=Release        -G "Visual Studio 15 2017"        -Thost=x64 ..\llvm`
          - 64-bit (XXX MB) : `cmake -DLLVM_ENABLE_PROJECTS=clang -DCMAKE_BUILD_TYPE=Release        -G "Visual Studio 15 2017" -A x64 -Thost=x64 ..\llvm`

        - RelWithDebInfo
          - 32-bit (1.87 GB): `cmake -DLLVM_ENABLE_PROJECTS=clang -DCMAKE_BUILD_TYPE=RelWithDebInfo -G "Visual Studio 15 2017"        -Thost=x64 ..\llvm`
          - 64-bit (XXXX GB): `cmake -DLLVM_ENABLE_PROJECTS=clang -DCMAKE_BUILD_TYPE=RelWithDebInfo -G "Visual Studio 15 2017" -A x64 -Thost=x64 ..\llvm`

        - Debug
          - 32-bit (4.27 GB): `cmake -DLLVM_ENABLE_ABI_BREAKING_CHECKS=0 -DLLVM_ENABLE_PROJECTS=clang -DCMAKE_BUILD_TYPE=Debug -G "Visual Studio 15 2017" -Thost=x64 ..\llvm`
          - 64-bit (XXXX GB): `cmake -DLLVM_ENABLE_ABI_BREAKING_CHECKS=0 -DLLVM_ENABLE_PROJECTS=clang -DCMAKE_BUILD_TYPE=Debug -G "Visual Studio 15 2017" -Thost=x64 ..\llvm`
      - Linux
        - `export CC=gcc-8`
        - `export CXX=g++-8`
        - Release
          - 64-bit (XXXX GB): `cmake -DCMAKE_BUILD_TYPE=Release -DLLVM_ENABLE_PROJECTS=clang -DLLVM_ENABLE_RTTI=ON -DLLVM_ENABLE_TERMINFO=OFF -G "Unix Makefiles" ../../llvm`
        - RelWithDebInfo
        - Debug

      - MacOS
        - `export CC=clang`
        - `export CXX=clang++`
        - Release
          - 64-bit (XXXX GB): `cmake -DLLVM_ENABLE_PROJECTS=clang -DCMAKE_BUILD_TYPE:STRING=Release -DLLVM_ENABLE_RTTI=1 -G "Unix Makefiles" ../../llvm`
        - RelWithDebInfo
        - Debug

1. Build LLVM(clang)
   - Windows
     - Launch `LLVM.sln` project solution file.

   - Linux
     - `make`

   - MacOS
     - `make`


## **Summary steps for Cpp NameLint(This project)**
1. Fetch source code of this project.
   1. `git clone https://github.com/dougpuob/cpp-namelint.git cpp-namelint.git`
   1. `cd cpp-namelint.git/Script`

1. Set environment variable.
   - Windows
     - SET NAMELINT_DEVTLS "C:\working-folder\opensrc\llvm\llvm-project.git--v8.0.0"
     - SET NAMELINT_DEVTLS "D:\devtls\@Win32\3party-lib\msvc2017-32bit\llvm\8.0.0"

   - Linux
     - export NAMELINT_DEVTLS "~/working-folder/opensrc/llvm/llvm-project.git--v8.0.0"
     - export NAMELINT_DEVTLS "~/devtls/@Linux\3party-lib\ubuntu16.4-gcc8-x64\llvm\8.0.0"

   - MacOS
     - export NAMELINT_DEVTLS "~/working-folder/opensrc/llvm/llvm-project.git--v8.0.0"
     - export NAMELINT_DEVTLS "~/devtls/@MacOS\3party-lib\mojave14.0.3-clang8-64bit\llvm\8.0.0"

1. Create this project.
   - Windows
     - `BuildWin32.cmd`
     - `BuildWin32.cmd Release`
     - `BuildWin32.cmd Debug`
     - `BuildWin32.cmd RelWithDebInfo`

   - Linux
     - `make`

   - MacOS
     - `make`

1. Build this project.
   - Windows
    Launch `cpp-namelint.git\Build\win32\cppnamelint.sln`


## **How to start** (as a Developer)
It is a lazy note, if you need to develop NameLint, please contact with me will save your time. I will write a complete manual later.

1. `git clone https://dougpuob@bitbucket.org/dougpuob/cpp-namelint.git cpp-namelint.git`
1. `cd cpp-namelint.git`
1. `git submodule init`
1. `git submodule update`
1. `cd Script`
1. Run BuildWin32.cmd/BuildLinux.sh/BuildMacOS.sh .
1. Build the project(Win32=MSVC, Linux=g++-8, MacOS=clang++).
1. Run TestWin32.cmd/TestLinux.sh


----------

## License
MIT
