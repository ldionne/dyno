#!/usr/bin/env bash

set -e

CMAKE_BINARY_DIR="${PWD}/build"
CMAKE_INSTALL_PREFIX="${PWD}/install"
CMAKE_SOURCE_DIR="${PWD}"

rm -rf "${CMAKE_INSTALL_PREFIX}" "${CMAKE_BINARY_DIR}"
mkdir -p "${CMAKE_INSTALL_PREFIX}" "${CMAKE_BINARY_DIR}"
cd "${CMAKE_BINARY_DIR}"

if [[ $# -ge 0 && "$1" == "--minimal" ]]; then
  shift
  cmake "${CMAKE_SOURCE_DIR}" -DCMAKE_INSTALL_PREFIX="${CMAKE_INSTALL_PREFIX}" -DMINIMAL="true" "${@}"
else
  cmake "${CMAKE_SOURCE_DIR}" -DCMAKE_INSTALL_PREFIX="${CMAKE_INSTALL_PREFIX}" "${@}"
fi

cmake --build "${CMAKE_BINARY_DIR}"

echo "************************************************************************"
echo "When setting up Dyno, you should add '${CMAKE_INSTALL_PREFIX}' to 'CMAKE_PREFIX_PATH'"
echo "************************************************************************"
