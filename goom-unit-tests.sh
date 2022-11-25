#!/bin/bash

set -u

declare -r THIS_SCRIPT_PATH="$(cd "$(dirname "$0")" >/dev/null 2>&1 ; pwd -P)"

source "${THIS_SCRIPT_PATH}/goom-get-vars.sh"


if [[ ! -d "${BUILD_DIR}" ]]; then
  echo "ERROR: Could not find build directory \"${BUILD_DIR}\"."
  exit 1
fi

declare -r TEST_DIR=${BUILD_DIR}

echo "Using TEST_DIR \"${TEST_DIR}\"."
echo

ctest --verbose --test-dir "${TEST_DIR}"
if [[ $? == 0 ]]; then
  exit 0
fi


declare -r RERUN_OPTS="--rerun-failed --output-on-failure"

ctest ${RERUN_OPTS} --verbose --test-dir "${TEST_DIR}"
