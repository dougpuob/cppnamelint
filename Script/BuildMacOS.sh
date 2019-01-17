echo "${1}"
if   [ "${1}" == "Release" ] || [ "${1}" == "release" ] || [ "${1}" == "RELEASE" ]; then
    BUILD_TYPE="build=Release"
elif [ "${1}" == "Debug" ]   || [ "${1}" == "debug" ]   || [ "${1}" == "DEBUG" ]; then
    BUILD_TYPE="build=Debug"
else
    UILD_TYPE="build=Release"
fi

python BuildFlow.py lint-format ../Source
python BuildFlow.py proj-create .. ../Build ${BUILD_TYPE}
