export CC=clang
export CXX=clang++


echo "${1}"
if   [ "${1}" == "Release" ] || [ "${1}" == "release" ] || [ "${1}" == "RELEASE" ]; then
    BUILD_TYPE="Release"
elif [ "${1}" == "Debug" ]   || [ "${1}" == "debug" ]   || [ "${1}" == "DEBUG" ]; then
    BUILD_TYPE="Debug"
else
    UILD_TYPE="Release"
fi


git submodule init
git submodule update


python BuildFlow.py lint-format ../Source
python BuildFlow.py proj-create .. ../Build ${BUILD_TYPE}
