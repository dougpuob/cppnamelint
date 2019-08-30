# **Development for CppNameLint**

## **Requires Common Tools**
  1. git
  2. cmake
  3. python3
  4. python docopt
  5. Compilers
      - Windows : `Visual Studio 2017 Community`
      - Linux : `gcc-8`
      - MacOS : `LLVM-8`

----------

## **Steps to build LLVM**
1. **Fetch source code of LLVM**
   a. `git clone https://github.com/llvm/llvm-project.git llvm-project.git`
   
1. **Configure LLVM**
   a. `cd llvm-project.git`
   b. `git checkout llvmorg-8.0.0`
   c. `mkdir -p build/release`
   d. `cd build/release`
   
1. **Configure LLVM via CMake for WIndows**
	- **Release**
		- **32-bit (293 MB)** :
		```
		cmake -DLLVM_ENABLE_PROJECTS=clang -DCMAKE_BUILD_TYPE=Release -G "Visual Studio 15 2017"        -Thost=x64 ..\llvm`
		 LLVM.sln
		```
		- **64-bit (XXX MB)** :
		```
		cmake -DLLVM_ENABLE_PROJECTS=clang -DCMAKE_BUILD_TYPE=Release -G "Visual Studio 15 2017" -A x64 -Thost=x64 ..\llvm`	
		```
	- **Debug**
		- **32-bit (4.27 GB)**:
		```
        cmake -DLLVM_ENABLE_ABI_BREAKING_CHECKS=0 -DLLVM_ENABLE_PROJECTS=clang -DCMAKE_BUILD_TYPE=Debug -G "Visual Studio 15 2017" -Thost=x64 ..\llvm
		```
		
		- **64-bit (XXXX GB)**:
		```
		cmake -DLLVM_ENABLE_ABI_BREAKING_CHECKS=0 -DLLVM_ENABLE_PROJECTS=clang -DCMAKE_BUILD_TYPE=Debug -G "Visual Studio 15 2017" -Thost=x64 ..\llvm
		```

1. **Configure LLVM via CMake for LInux**
	- **Release**
		- **64-bit (XXXX GB)**:
		```
		export CC=gcc-8
		export CXX=g++-8
		cmake -DCMAKE_BUILD_TYPE=Release -DLLVM_ENABLE_PROJECTS=clang -DLLVM_ENABLE_RTTI=ON -DLLVM_ENABLE_TERMINFO=OFF -G "Unix Makefiles" ../../llvm
		 make
		```
1. **Configure LLVM via CMake for macOS**
	- **Release**
		- **64-bit (XXXX GB)**:
		```
		export CC=clang
		export CXXclang++
		cmake -DLLVM_ENABLE_PROJECTS=clang -DCMAKE_BUILD_TYPE:STRING=Release -DLLVM_ENABLE_RTTI=1 -G "Unix Makefiles" ../../llvm
		make
		```

----------

## **Steps to build CppNameLint (This Project)**
1. `git clone https://github.com/dougpuob/cpp-namelint.git cpp-namelint.git`
1. Set environment variable.
   - **Windows** : `SET NAMELINT_DEVTLS "C:\llvm-project.git"`
   - **Linux**       : `export NAMELINT_DEVTLS "~/llvm-project.git"`
   - **macOS**    : `export NAMELINT_DEVTLS "~/llvm-project.git"`
1. `cd cpp-namelint.git`
1. Config via CMake
   - Windows
     - `BuildWin32.cmd`
     - `BuildWin32.cmd Release`
     - `BuildWin32.cmd Debug`

   - Linux
     - `BuildLinux.sh`
	 - `BuildLinux.sh Release`
	 - `BuildLinux.sh DEbug`

   - MacOS
     - `BuildLinux.sh`
	 - `BuildLinux.sh Release`
	 - `BuildLinux.sh DEbug`

1. Build this project.
   - Windows
    Launch `cpp-namelint.git\Build\win32\cppnamelint.sln`
	
  - Linux
    ```
	cd Script
	./BuildLinux.sh
	cd ../build/release
	make
	```
	
  - macOS
    ```
	cd Script
	./BuildMacOS.sh
	cd ../build/release
	make
	```

----------

## Reference
- https://clang.llvm.org/get_started.html

----------

## Submodules

----------

## License
MIT
