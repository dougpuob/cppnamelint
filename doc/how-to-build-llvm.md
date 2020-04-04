# How to build LLVM (Windows/Linux/macOS)

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

## Steps to build LLVM

[https://clang.llvm.org/get_started.html](https://clang.llvm.org/get_started.html)

### 1. **Fetch source code of LLVM**
``` sh
$ git clone [https://github.com/llvm/llvm-project.git](https://github.com/llvm/llvm-project.git) llvm-project.git
$ cd llvm-project.git
$ git checkout llvmorg-8.0.0

# Do the following with Release build
$ mkdir -p build/release
$ cd build/release

# Do the following with Debug build
$ mkdir -p build/debug
$ cd build/debug
```

### 2. Build for Windows

``` sh
################################################################################
# Release                                                                      #
################################################################################
# 32-bit
$ cmake -DLLVM_ENABLE_PROJECTS=clang -DCMAKE_BUILD_TYPE=Release -G "Visual Studio 15 2017" -Thost=x64 ..\llvm

# 64-bit
$ cmake -DLLVM_ENABLE_PROJECTS=clang -DCMAKE_BUILD_TYPE=Release -G "Visual Studio 15 2017" -A x64 -Thost=x64 ..\llvm

################################################################################
# Debug                                                                        #
################################################################################
# 32-bit
$ cmake -DLLVM_ENABLE_ABI_BREAKING_CHECKS=0 -DLLVM_ENABLE_PROJECTS=clang -DCMAKE_BUILD_TYPE=Debug -G "Visual Studio 15 2017" -Thost=x64 ..\llvm

# 64-bit
$ cmake -DLLVM_ENABLE_ABI_BREAKING_CHECKS=0 -DLLVM_ENABLE_PROJECTS=clang -DCMAKE_BUILD_TYPE=Debug -G "Visual Studio 15 2017" -A x64 -Thost=x64 ..\llvm
```

### 3. Build for Linux
``` sh
################################################################################
# Release                                                                      #
################################################################################
# **64-bit**
$ cmake -DCMAKE_BUILD_TYPE=Release -DLLVM_ENABLE_PROJECTS=clang -DLLVM_ENABLE_RTTI=ON -DLLVM_ENABLE_TERMINFO=OFF -G "Unix Makefiles" ../../llvm
```

### 4. Build for macOS
``` sh
################################################################################
# Release                                                                      #
################################################################################
# 64-bit
$ cmake -DLLVM_ENABLE_PROJECTS=clang -DCMAKE_BUILD_TYPE:STRING=Release -DLLVM_ENABLE_RTTI=1 -G "Unix Makefiles" ../../llvm
```

➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖

## Reference

- [https://clang.llvm.org/get_started.html](https://clang.llvm.org/get_started.html)

## Submodules

## License

MIT
