#!/bin/bash

set -u
set -e

declare -r THIS_SCRIPT_PATH="$(cd "$(dirname "$0")" >/dev/null 2>&1 ; pwd -P)"


pushd ${THIS_SCRIPT_PATH} > /dev/null

echo "------------------------"
bash goom-docker-install-to.sh
sleep 2

echo "------------------------"
bash goom-docker-build.sh $@
sleep 2

echo "------------------------"
bash goom-docker-run.sh $@

popd > /dev/null
