#!/bin/bash

set -u
set -e

declare -r THIS_SCRIPT_PATH="$(cd "$(dirname "$0")" >/dev/null 2>&1 ; pwd -P)"

source "${THIS_SCRIPT_PATH}/goom-docker-paths.sh"


declare -r KODI_BUILD_ROOT_DIR=$(realpath ${THIS_SCRIPT_PATH}/../xbmc/kodi-build/addons)

declare -r KODI_BUILD_LIB_DIR=${KODI_BUILD_ROOT_DIR}/lib/addons/visualization.goom
if [[ ! -d "${KODI_BUILD_LIB_DIR}" ]]; then
  echo "ERROR: Could not find kodi build lib directory \"${KODI_BUILD_LIB_DIR}\"."
  exit 1
fi
declare -r KODI_BUILD_SHARE_DIR=${KODI_BUILD_ROOT_DIR}/share/kodi/addons/visualization.goom
if [[ ! -d "${KODI_BUILD_SHARE_DIR}" ]]; then
  echo "ERROR: Could not find kodi build share directory \"${KODI_BUILD_SHARE_DIR}\"."
  exit 1
fi
declare -r KODI_BUILD_RESOURCES_DIR=${KODI_BUILD_SHARE_DIR}/resources
if [[ ! -d "${KODI_BUILD_RESOURCES_DIR}" ]]; then
  echo "ERROR: Could not find kodi build resources directory \"${KODI_BUILD_RESOURCES_DIR}\"."
  exit 1
fi


if [[ "${1:-}" == "--dry-run" ]]; then
  declare -r DRY_RUN="--dry-run"
else
  declare -r DRY_RUN=
fi

echo "Installing Goom add-on to Docker files directory \"${KODI_DOCKER_FILES_DIR}\"..."
echo

echo "rsyncing \"${KODI_BUILD_LIB_DIR}/visualization.goom.so.*\" to \"${KODI_DOCKER_FILES_DIR}\"..."
rsync ${DRY_RUN} -avh ${KODI_BUILD_LIB_DIR}/visualization.goom.so.* ${KODI_DOCKER_FILES_DIR}

echo
echo "rsyncing \"${KODI_BUILD_SHARE_DIR}/addon.xml\" to \"${KODI_DOCKER_FILES_DIR}\"..."
rsync ${DRY_RUN} -avh ${KODI_BUILD_SHARE_DIR}/addon.xml ${KODI_DOCKER_FILES_DIR}

echo
echo "rsyncing \"${KODI_BUILD_RESOURCES_DIR}/\" to \"${KODI_DOCKER_RESOURCES_DIR}/\"..."
rsync ${DRY_RUN} --out-format="%n" --itemize-changes -a ${KODI_BUILD_RESOURCES_DIR}/ ${KODI_DOCKER_RESOURCES_DIR}/

echo
