# How to build CppNameLint (This project)

This project is based on LLVM's libtooling library, so you have to build llvm first. Then it uses CMake's find_package() function to find LLVM library, this means you don't need to specific libraries in CMakeLists.txt file, all depend on `LLVMConfig.cmake` and `ClangConfig.cmake` files.

Understand it more details, please read `CMakeLists.txt` and `azure-pipelines.yml`.
 
➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖
## Requires Common Tools

1. git
2. cmake
3. ninja
4. python3
5. Compilers
    - Windows: Visual Studio 2019 Community
    - Linux : gcc
    - MacOS : clang


➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖
## Build this project
### Windows
``` powershell
git clone https://github.com/dougpuob/cpp-namelint.git cppnamelint.git
cd cppnamelint.git
git submodule init
git submodule update

mkdir build
cd build
cmake .. -DLLVM_INSTALL_DIR="C:\petzone\llvm\llvm-prebuilt\llvmorg-11.1.0-msbuild-vs2019-x64-rel"
cmake --build . --config Release
```

### Linux & macOS
``` bash
git clone https://github.com/dougpuob/cpp-namelint.git cppnamelint.git
cd cppnamelint.git
git submodule init
git submodule update

mkdir build
cd build
cmake .. -DLLVM_INSTALL_DIR="~\llvm\llvm-prebuilt\llvmorg-11.1.0-ninja-gcc-x64-rel"
cmake --build . --config Release
```

➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖
## Pack & Test this project
### Windows
   1. `$ cd cpp-namelint.git/script`  
   1. `$ powershell.exe "./build-pack-win32.ps1"`.  
   1. `cd release`
   1. `$ powershell.exe  "./build-test-win32.ps1"`

### Linux & macOS
   1. `$ cd cpp-namelint.git/script`  
   1. `$ build-pack-linux.sh`
   1. `cd release`
   1. `$ build-test-linux.sh`
   
➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖
