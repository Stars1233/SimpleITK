#!/usr/bin/env bash

set -ex

export ITK_GLOBAL_DEFAULT_NUMBER_OF_THREADS=2

echo "COREBINARYDIRECTORY: ${COREBINARYDIRECTORY}"
echo "CTEST_SOURCE_DIRECTORY: ${CTEST_SOURCE_DIRECTORY}"

which python
python --version
PYTHON_VERSION=$(python -c 'import sys;print ("{0}{1}".format(sys.version_info[0], sys.version_info[1]))')

# Detect OS
OS_NAME=$(uname -s)

# Detect version (for macOS)
if [ "$OS_NAME" == "Darwin" ]; then
    OS_ARCH=$(uname -m)
    if [ "$OS_ARCH" == "x86_64" ]; then
        OS_VERSION="10.9"
    elif [ "$OS_ARCH" == "arm64" ]; then
        OS_VERSION="11.0"
    else
        echo "Unsupported architecture: $OS_ARCH"
        exit 1
    fi
    SIMPLEITK_PYTHON_PLAT_NAME="macosx-$OS_VERSION-$OS_ARCH"
else
    echo "Unsupported OS: $OS_NAME"
    exit 1
fi

read -r -d '' CTEST_CACHE << EOM || true
CMAKE_PREFIX_PATH:PATH=${COREBINARYDIRECTORY}
CMAKE_CXX_VISIBILITY_PRESET:STRING=hidden
CMAKE_VISIBILITY_INLINES_HIDDEN:BOOL=ON
CMAKE_OSX_DEPLOYMENT_TARGET=$OS_VERSION
SWIG_EXECUTABLE:FILEPATH=${COREBINARYDIRECTORY}/Swig/bin/swig
BUILD_EXAMPLES:BOOL=ON
BUILD_TESTING:BOOL=ON
SimpleITK_PYTHON_PLAT_NAME:STRING=$SIMPLEITK_PYTHON_PLAT_NAME
SimpleITK_BUILD_DISTRIBUTE:BOOL=ON
SimpleITK_PYTHON_WHEEL:BOOL=1
SimpleITK_BUILD_STRIP:BOOL=1
Python_EXECUTABLE:FILEPATH=$(which python)
SimpleITK_PYTHON_USE_LIMITED_API:BOOL=${USE_LIMITED_API}
EOM

export CTEST_CACHE
export CTEST_BINARY_DIRECTORY="${GITHUB_WORKSPACE}/py${PYTHON_VERSION}"

ctest -D dashboard_source_config_dir="Wrapping/Python" \
      -D "dashboard_track:STRING=Package" \
      -D "CTEST_BUILD_NAME:STRING=${RUNNER_NAME}-${GITHUB_JOB}-py${PYTHON_VERSION}" \
      -S "${CTEST_SOURCE_DIRECTORY}/.github/workflows/github_actions.cmake" -VV -j 2

cmake --build "${CTEST_BINARY_DIRECTORY}" --target dist


mkdir -p "${GITHUB_WORKSPACE}/artifacts"
find ${CTEST_BINARY_DIRECTORY} -iname "simpleitk*.whl" -exec cp -v {} "${GITHUB_WORKSPACE}/artifacts" \;
