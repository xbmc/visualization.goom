#!/bin/bash

set -u
set -e

declare -r THIS_SCRIPT_PATH="$(cd "$(dirname "$0")" >/dev/null 2>&1 ; pwd -P)"

source "${THIS_SCRIPT_PATH}/goom-docker-paths.sh"


bash "${DOCKERIZE_KODI_DIR}/build-all.sh" --kodi-version ${KODI_VERSION} \
                                          --goom-version ${GOOM_VERSION} \
                                          --image-os ${KODI_IMAGE_OS_TYPE} \
                                          --image-os-version ${KODI_IMAGE_OS_TAG} \
                                          --container-home-dir ${KODI_CONTAINER_HOME_DIR} \
                                          --docker-files-dir ${KODI_DOCKER_FILES_DIR} \
                                          $@
