#!/bin/bash

set -e
set -u

declare -r THIS_SCRIPT_PATH="$(cd "$(dirname "$0")" >/dev/null 2>&1 ; pwd -P)"

source "${THIS_SCRIPT_PATH}/goom-docker-paths.sh"


declare KODI_CONTAINER_HOME_DIR_TO_USE="${KODI_CONTAINER_HOME_DIR}"

while [[ $# -gt 0 ]]; do
  key="$1"

  case $key in
    --kodi-home-dir)
      declare KODI_CONTAINER_HOME_DIR_TO_USE=${2}
      shift # past argument
      shift # past value
      ;;
    --user-addon)
      # Ignore
      shift # past argument
      ;;
    --no-cache)
      # Ignore
      shift # past argument
      ;;
    *)
      echo "Unknown option \"${key}\"."
      echo
      exit 1
      ;;
    *)    # unknown option
  esac
done


if [[ ! -d "${KODI_CONTAINER_HOME_DIR_TO_USE}" ]]; then
  mkdir -p "${KODI_CONTAINER_HOME_DIR_TO_USE}"
  if [[ ! -d "${KODI_CONTAINER_HOME_DIR_TO_USE}" ]]; then
    echo "ERROR: Could not create Kodi Docker home directory: \"${KODI_CONTAINER_HOME_DIR_TO_USE}\"."
    exit 1
  fi
  echo
  echo "NOTE: Created empty Kodi Docker home directory: \"${KODI_CONTAINER_HOME_DIR_TO_USE}\"."
fi

if [[ ! -d "${KODI_CONTAINER_HOME_DIR_TO_USE}" ]]; then
  echo "ERROR: Could not find Kodi container home directory: \"${KODI_CONTAINER_HOME_DIR_TO_USE}\"."
  exit 1
fi
if [[ ! -d "${MUSIC_SHARE}" ]]; then
  echo "ERROR: Could not find music directory: \"${MUSIC_SHARE}\"."
  exit 1
fi

declare -r IREXEC_CAPTURES=${KODI_CONTAINER_HOME_DIR_TO_USE}/temp/irexec.out
rm -f "${IREXEC_CAPTURES}"

echo "Running Goom using Docker image \"${KODI_GOOM_IMAGE}\"..."

declare -r OLD_CORE_PATTERN=$(cat /proc/sys/kernel/core_pattern)
declare -r CORE_PATTERN="/tmp/core.%e.%p"
echo
echo "Setting linux 'core' pattern: \"${CORE_PATTERN}\"."
ulimit -c unlimited
sudo /usr/sbin/sysctl -q -w kernel.core_pattern="${CORE_PATTERN}"

declare -r TIME_ZONE=$(readlink /etc/localtime | sed 's#.*/zoneinfo/##')

echo
x11docker -q                                          \
          --share=${MUSIC_SHARE}                      \
          --runasroot="service lircd start"           \
          --name ${KODI_CONTAINER_NAME}               \
          --hostuser=${USER}                          \
          --network                                   \
          --pulseaudio                                \
          --gpu                                       \
          --home=${KODI_CONTAINER_HOME_DIR_TO_USE}    \
          --                                          \
          --init                                      \
          --privileged                                \
          --ulimit core=-1                            \
          --mount type=bind,source=/tmp/,target=/tmp/ \
          -e "TZ=${TIME_ZONE}"                        \
          --                                          \
          ${KODI_GOOM_IMAGE}

echo "x11docker return code = $?"

sudo /usr/sbin/sysctl -q -w kernel.core_pattern="${OLD_CORE_PATTERN}"

echo
