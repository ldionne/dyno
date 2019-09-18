#!/usr/bin/env bash

set -e

DYNO_ROOT="$(git rev-parse --show-toplevel)"
BUILD_DIR="${DYNO_ROOT}/dependencies/build"
INSTALL_DIR="${DYNO_ROOT}/dependencies/install"

rm -rf "${INSTALL_DIR}" "${BUILD_DIR}"
mkdir -p "${INSTALL_DIR}" "${BUILD_DIR}"
cd "${BUILD_DIR}"

if [[ $# -ge 0 && "$1" == "--minimal" ]]; then
  shift
  cmake "${DYNO_ROOT}/dependencies" -DCMAKE_INSTALL_PREFIX="${INSTALL_DIR}" -DMINIMAL="true" "${@}"
else
  cmake "${DYNO_ROOT}/dependencies" -DCMAKE_INSTALL_PREFIX="${INSTALL_DIR}" "${@}"
fi

cmake --build "${BUILD_DIR}"

echo "************************************************************************"
echo "When setting up Dyno, you should add '${INSTALL_DIR}' to 'CMAKE_PREFIX_PATH'"
echo "************************************************************************"
