#!/bin/bash

set -u
set -e

declare -r THIS_SCRIPT_PATH="$(cd "$(dirname "$0")" >/dev/null 2>&1 ; pwd -P)"

source "${THIS_SCRIPT_PATH}/goom-docker-paths.sh"


declare EXTRA_ARGS=""
declare REMOTE_HOST=""

while [[ $# -gt 0 ]]; do
  key="$1"

  case $key in
    --remote-host)
      REMOTE_HOST=${2}
      shift # past argument
      shift # past value
      ;;
    *)
      EXTRA_ARGS="${EXTRA_ARGS}${key} "
      shift # past argument
      ;;
    *)
  esac
done

set -- ${EXTRA_ARGS}
unset EXTRA_ARGS


if [[ "${REMOTE_HOST}" == "" ]] ; then
  echo "Youd need to provide \"--remote-host\"."
  exit 1
fi
if ! ping -q -c 2 ${REMOTE_HOST} ; then
  echo "Could not connect to remote host \"${REMOTE_HOST}\"."
  exit 1
fi

ssh ${REMOTE_HOST} "bash "${REMOTE_KODI_BUILD_DIR}/build-all.sh" --kodi-version ${KODI_VERSION} \
                                                                 --goom-version ${GOOM_VERSION} \
                                                                 --image-os ${KODI_IMAGE_OS_TYPE} \
                                                                 --image-os-version ${KODI_IMAGE_OS_TAG} \
                                                                 --container-home-dir ${KODI_CONTAINER_HOME_DIR} \
                                                                 --docker-files-dir ${KODI_DOCKER_FILES_DIR} \
                                                                 $@"
