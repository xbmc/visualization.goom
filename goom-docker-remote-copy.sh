#!/bin/bash

set -e
set -u

declare -r THIS_SCRIPT_PATH="$(cd "$(dirname "$0")" >/dev/null 2>&1 ; pwd -P)"

source "${THIS_SCRIPT_PATH}/goom-docker-paths.sh"


bash ${DOCKERIZE_KODI_DIR}/remote-copy-to.sh $@ "${REMOTE_KODI_BUILD_DIR}"
