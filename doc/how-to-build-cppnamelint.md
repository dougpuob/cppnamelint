# How to build Cpp-NameLint (This project)

This project is integrated with Azure DevOps, so you can read `azure-pipelines.yml` to now how to build. Another way is read the following content.

Attention! before continue, this project is based on LLVM's libtooling library, so you have prepare library binary files for it. There are two ways:
1. Download from my cloud (contact me, I will send you the links. I will pack it later because I am planing to use `LLVMConfig.cmake`)
2. Build LLVM youself. (how-to-build-llvm.md)
 
➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖
## Requires Common Tools

1. git
2. cmake
3. python3
4. Compilers
    - Windows: Visual Studio 2017 Community
    - Linux : gcc-8
    - MacOS : llvm-8

➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖
## Prepare essentials

1. **Git clone project to your local**
`$ git clone https://github.com/dougpuob/cpp-namelint.git cpp-namelint.git`

2. **Set environment variable**  
   - **Windows** : $ SET LLVM_DIR_CPPNAMELINT    "C:\llvm-project.git"
   - **Linux**   : $ export LLVM_DIR_CPPNAMELINT "~/llvm-project.git"
   - **macOS**   : $ export LLVM_DIR_CPPNAMELINT "~/llvm-project.git"

➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖
## Build this project
### Windows
   1. `$ cd cpp-namelint.git/script`  
   1. `$ powershell.exe "./build-bin-win32.ps1"` or `./build-bin-win32-dbg.ps1"` for debugging.  
   1. Launch & build `build\windows\cppnamelint.sln`.

### Linux
   1. `$ cd cpp-namelint.git/script`  
   1. `$ build-bin-linux.sh` 
   1. `$ cd cpp-namelint.git/build/linux`
   1. `$ make`

### macOS
   1. `$ cd cpp-namelint.git/script`  
   1. `$ build-bin-macos.sh`
   1. `$ cd cpp-namelint.git/build/macos`
   1. `$ make`

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
