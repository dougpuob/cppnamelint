#!/bin/bash

export CC="gcc"
export CXX="g++"
echo CC  =$CC 
echo CXX =$CXX

echo "${1}"

if   [ "${1}" == "Release" ] || [ "${1}" == "release" ] || [ "${1}" == "RELEASE" ]; then
    BUILD_TYPE="Release"
elif [ "${1}" == "Debug" ]   || [ "${1}" == "debug" ]   || [ "${1}" == "DEBUG" ]; then
    BUILD_TYPE="Debug"
else
    BUILD_TYPE="Release"
fi

git submodule init
git submodule update

git submodule init
git submodule update

pip3 --version
if [ "$?"!="0" ]; then    
    sudo apt-get install python3-pip
fi
pip3 install docopt

cmake --version
if [ "$?"!="0" ]; then    
    sudo apt-get install cmake
fi

${CC} --version
if [ "$?"!="0" ]; then    
    sudo apt-get install ${CC}
fi

${CXX} --version
if [ "$?"!="0" ]; then    
    sudo apt-get install ${CXX}
fi

# export NAMELINT_LLVM_LIB=~/my-data/my-cloud/@mydata/software/data/devtls/my-devtls/@Linux/3party-lib/ubuntu18.04.2-gcc8-x64/llvm
python3 BuildFlow.py lint-format ../Source
python3 BuildFlow.py proj-create .. ../Build ${BUILD_TYPE}

