#!/bin/bash

set -u
set -e

declare -r THIS_SCRIPT_PATH="$(cd "$(dirname "$0")" >/dev/null 2>&1 ; pwd -P)"


declare -r KODI_BUILD_DIR=$(realpath ${THIS_SCRIPT_PATH}/../xbmc/kodi-build/addons/visualization.goom)
if [[ ! -d "${KODI_BUILD_DIR}" ]]; then
  echo "ERROR: Could not find kodi build directory \"${KODI_BUILD_DIR}\"."
  exit 1
fi

declare -r KODI_LIB_DIR=/usr/lib/x86_64-linux-gnu/kodi/addons/visualization.goom
if [[ ! -d "${KODI_LIB_DIR}" ]]; then
  echo "ERROR: Could not find kodi lib directory \"${KODI_LIB_DIR}\"."
  exit 1
fi

declare -r KODI_RESOURCES_DIR=/usr/share/kodi/addons/visualization.goom
if [[ ! -d "${KODI_RESOURCES_DIR}" ]]; then
  echo "ERROR: Could not find kodi resources directory \"${KODI_RESOURCES_DIR}\"."
  exit 1
fi

sudo cp -pv ${KODI_BUILD_DIR}/visualization.goom.so.* ${KODI_LIB_DIR}

echo
sudo cp -pv ${KODI_BUILD_DIR}/addon.xml ${KODI_RESOURCES_DIR}

echo
echo "rsyncing \"${KODI_BUILD_DIR}/resources/\" to \"${KODI_RESOURCES_DIR}/resources/\"..."
sudo rsync --out-format="%n" --itemize-changes -a ${KODI_BUILD_DIR}/resources/ ${KODI_RESOURCES_DIR}/resources/
