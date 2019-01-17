#!/bin/bash

export CC="gcc-8"
export CXX="g++-8"
echo CC  =$CC
echo CXX =$CC

echo "${1}"

if   [ "${1}" == "Release" ] || [ "${1}" == "release" ] || [ "${1}" == "RELEASE" ]; then
    BUILD_TYPE="build=Release"
elif [ "${1}" == "Debug" ]   || [ "${1}" == "debug" ]   || [ "${1}" == "DEBUG" ]; then
    BUILD_TYPE="build=Debug"
else
    BUILD_TYPE=""
fi


python3 BuildFlow.py lint-format ../Source
python3 BuildFlow.py proj-create .. ../Build ${BUILD_TYPE}

