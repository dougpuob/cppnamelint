# CMake 尋找 LLVMConfig.cmake

▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬

Build folder 裡可以找到兩個 `LLVMConfig.cmake` 檔案，第一個是「決對路徑」、第二個是「變數路徑」、第三個是「安裝路徑」。我把 LLVM repo 放在 `/home/dougpuob/llvm-project.git` 為例子：

1. **決對路徑**
/home/dougpuob/llvm-project.git/build/release/lib/cmake/llvm/LLVMConfig.cmake

2. **變數路徑 (**LLVM_CMAKE_DIR**)**
/home/dougpuob/llvm-project.git/build/release/cmake/modules/CMakeFiles/LLVMConfig.cmake

3. **預設安裝路徑** 
/usr/local/lib/cmake/llvm

---

▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬

如果你已經自行建置完成 LLVM，無論是否安裝在自己的系統中，你可以這樣子做

    # 為實驗專案建一個目錄(hellollvm)：
    cd ~/hellollvm/
    ls 
    CMakeFiles.txt
    main.cpp
    mkdir build
    cd build
    # 接著下面三種方法，透過 CMake 連結 LLVM libraries：
    

1. **沒安裝(決對路徑)**

        export LLVM_DIR=/home/dougpuob/llvm-project.git/build/release
        cmake ..

2. **沒安裝(變數路徑)**

        export LLVM_CMAKE_DIR=/home/dougpuob/llvm-project.git/build/release/cmake/modules/CMakeFiles
        cmake ..

3. **已經安裝 (LLVM預設目錄** `/usr/local/lib/cmake/llvm` **)**

        export LLVM_DIR=/usr/local/lib/cmake/llvm
        cmake ..

也就是說，`find_package((LLVM REQUIRED CONFIG)` 會在下面幾個的目錄中尋找 `LLVMConfig.cmake` 檔案：

1. LLVM_DIR
2. LLVM_CMAKE_DIR
3. /usr/local/lib/cmake/llvm

▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬

## Resource

[main.cpp](CMake%20LLVMConfig%20cmake/main.cpp)

[CMakeLists.txt](CMake%20LLVMConfig%20cmake/CMakeLists.txt)

▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬

## **Reference**

1. [https://lowlevelbits.org/building-an-llvm-based-tool.-lessons-learned/](https://lowlevelbits.org/building-an-llvm-based-tool.-lessons-learned/)
2. [https://github.com/llvm/llvm-project/blob/master/llvm/docs/CMake.rst](https://github.com/llvm/llvm-project/blob/master/llvm/docs/CMake.rst)
