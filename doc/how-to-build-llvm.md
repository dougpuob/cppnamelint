# How to build LLVM (Windows/Linux/macOS)

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

## Steps to build LLVM

[https://clang.llvm.org/get_started.html](https://clang.llvm.org/get_started.html)

### 1. **Fetch source code of LLVM**
``` sh
$ git clone [https://github.com/llvm/llvm-project.git](https://github.com/llvm/llvm-project.git) llvm-project.git
$ cd llvm-project.git
$ git checkout llvmorg-11.1.0
$ mkdir -p build
```

### 2. Build for Windows

``` powershell
# Config
cmake -G "Visual Studio 16 2019" -A X64                         `
      -DLLVM_ENABLE_ABI_BREAKING_CHECKS=OFF                     `
      -DLLVM_TARGETS_TO_BUILD="X86"                             `
      -DLLVM_ENABLE_PROJECTS="clang;llvm;clang-tools-extra"     `
      -DCMAKE_BUILD_TYPE=Release                                `
      -DCMAKE_INSTALL_PREFIX="C:\petzone\llvm\llvm-prebuilt\llvmorg-11.1.0-msbuild-vs2019-x64-rel"    `
      ../llvm

# Make
cmake --build . --config Release

# Install
cmake -P cmake_install.cmake
```

### 3. Build for Linux & macOS
``` sh
# Config
cmake -G "Ninja"                              \
      -DLLVM_ENABLE_ABI_BREAKING_CHECKS=OFF   \
      -DLLVM_TARGETS_TO_BUILD="X86"           \
      -DLLVM_ENABLE_PROJECTS="clang;llvm"     \
      -DCMAKE_BUILD_TYPE=Release              \
      -DCMAKE_INSTALL_PREFIX="~\llvm\llvm-prebuilt\llvmorg-11.1.0-ninja-gcc-x64-rel"    \
      ../llvm

# Make
cmake --build . --config Release

# Install
cmake -P cmake_install.cmake
```

➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖

## Reference

- [https://clang.llvm.org/get_started.html](https://clang.llvm.org/get_started.html)

## Submodules

## License

MIT
