echo "${1}"
if   [ "${1}" == "Release" ] || [ "${1}" == "release" ] || [ "${1}" == "RELEASE" ]; then
    BUILD_TYPE="--build=Release"
elif [ "${1}" == "Debug" ]   || [ "${1}" == "debug" ]   || [ "${1}" == "DEBUG" ]; then
    BUILD_TYPE="--build=Debug"
else
    BUILD_TYPE=""
fi

python build-flow.py lint  format ../Source
python build-flow.py cmake create .. ../Build ${BUILD_TYPE}