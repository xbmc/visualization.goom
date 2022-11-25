#!/bin/bash

set -u
set -e

declare -r THIS_SCRIPT_PATH="$(cd "$(dirname "$0")" >/dev/null 2>&1 ; pwd -P)"

source "${THIS_SCRIPT_PATH}/goom-get-vars.sh"


docker run --rm                                                \
           -e TZ=${HOST_TIME_ZONE}                             \
           -e CCACHE_DIR=${DOCKER_CCACHE_DIR}                  \
           -v ${HOST_CCACHE_DIR}:${DOCKER_CCACHE_DIR}          \
           -v ${HOST_KODI_ROOT_DIR}:${DOCKER_KODI_ROOT_DIR}    \
           -v ${THIS_SCRIPT_PATH}:${DOCKER_GOOM_BUILD_DIR}     \
           -t ${DOCKER_BUILD_IMAGE}                            \
           bash -c "cd ${DOCKER_GOOM_BUILD_DIR} &&             \
                    ${DOCKER_GOOM_BUILD_DIR}/goom-configure.sh \
                      --docker                                 \
                      --docker-os-type ${DOCKER_OS_TYPE}       \
                      --docker-os-tag ${DOCKER_OS_TAG}         \
                      --compiler ${COMPILER}                   \
                      --build-type ${BUILD_TYPE}               \
                      --suffix ${BUILD_DIR_SUFFIX}             \
                      --kodi-root-dir ${DOCKER_KODI_ROOT_DIR}"
