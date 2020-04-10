#!/bin/bash

export CC="gcc"
export CXX="g++"
echo CC  =$CC
echo CXX =$CXX


pushd ..
git submodule init
git submodule update
popd


echo "============================================================"
echo Generate makefile via cmake
echo "============================================================"
ROOT_DIR=..
BUILD_DIR=../build/linux
BUILD_TYPE=Release
mkdir -p ${BUILD_DIR}


# export NAMELINT_LLVM_LIB=~/my-data/my-cloud/@mydata/software/data/devtls/my-devtls/@Linux/3party-lib/ubuntu18.04.2-gcc8-x64/llvm
python3 ./cppnamelint.py bldgcfg ${ROOT_DIR} ${BUILD_DIR} ${BUILD_TYPE}
