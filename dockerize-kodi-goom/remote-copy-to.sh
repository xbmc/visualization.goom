#!/bin/bash

set -u
set -e

declare -r THIS_SCRIPT_PATH="$(cd "$(dirname "$0")" >/dev/null 2>&1 ; pwd -P)"

if [[ "${1}" != "--dry-run" ]]; then
  declare -r DRY_RUN=
else
  declare -r DRY_RUN="--dry-run"
  shift
fi

declare -r REMOTE_HOST=$1
declare -r REMOTE_KODI_BUILD_DIR=$2
declare -r REMOTE_KODI_GOOM_DIR=${REMOTE_KODI_BUILD_DIR}/..

if ! ping -q -c 2 ${REMOTE_HOST} ; then
  echo "Could not connect to remote host \"${REMOTE_HOST}\"."
  exit 1
fi

echo
echo "Rsyncing \"${THIS_SCRIPT_PATH}/../goom-docker-paths.sh\" to \"${REMOTE_HOST}:${REMOTE_KODI_GOOM_DIR}/\""
echo
ssh ${REMOTE_HOST} mkdir -p ${REMOTE_KODI_GOOM_DIR}
rsync ${DRY_RUN} -avh "${THIS_SCRIPT_PATH}/../goom-docker-paths.sh" "${REMOTE_HOST}:${REMOTE_KODI_GOOM_DIR}/"

echo
echo "Rsyncing \"${THIS_SCRIPT_PATH}/\" to \"${REMOTE_HOST}:${REMOTE_KODI_BUILD_DIR}/\""
echo
ssh ${REMOTE_HOST} mkdir -p ${REMOTE_KODI_BUILD_DIR}
rsync ${DRY_RUN} -avh --delete --exclude=remote-copy-to.sh "${THIS_SCRIPT_PATH}/" "${REMOTE_HOST}:${REMOTE_KODI_BUILD_DIR}/"
