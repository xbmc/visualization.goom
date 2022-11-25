#!/bin/bash

set -e
set -u

declare -r IMAGE_NAME="kodi-nightly:goom-dev"
declare -r CONTAINER_NAME="kodi_goom_dev"
declare -r CONTAINER_HOME_DIR="${HOME}/docker/kodi-nightly"
declare -r CONTAINER_LOG_DIR="${CONTAINER_HOME_DIR}/kodi-log"
declare -r CONTAINER_LOG="${CONTAINER_LOG_DIR}/kodi-docker.log"
declare -r MUSIC_SHARE="/mnt/Music"
declare -r VIDEO_SHARE="/mnt/Video"
declare -r EXTRA_VIDEO_SHARE="/mnt/ub-video"

declare ALL_SHARES="--share=${MUSIC_SHARE} --share=${VIDEO_SHARE}"


declare -r IREXEC_CAPTURES=${CONTAINER_HOME_DIR}/temp/irexec.out
if [[ -d "${EXTRA_VIDEO_SHARE}" ]]; then
    ALL_SHARES="${ALL_SHARES} --share=${EXTRA_VIDEO_SHARE}"
fi

rm -f "${IREXEC_CAPTURES}" |& tee -a "${CONTAINER_LOG}"

declare -r OLD_CORE_PATTERN=$(cat /proc/sys/kernel/core_pattern)
declare -r CORE_PATTERN="/tmp/core.%e.%p"
ulimit -c unlimited
sudo /usr/sbin/sysctl -q -w kernel.core_pattern="${CORE_PATTERN}"


x11docker --runasroot="service lircd start" ${ALL_SHARES} \
          --hostuser=${USER}                              \
		  --network                                       \
		  --pulseaudio                                    \
		  --gpu                                           \
          --home=${CONTAINER_HOME_DIR}                    \
		  --name ${CONTAINER_NAME}                        \
          --                                              \
          --init                                          \
		  --cap-add=SYS_PTRACE                            \
		  --security-opt seccomp=unconfined               \
		  --privileged                                    \
          --ulimit core=-1                                \
          --mount type=bind,source=/tmp/,target=/tmp/     \
          --                                              \
		  ${IMAGE_NAME} |& tee -a "${CONTAINER_LOG}"


if grep KEY_SLEEP "${IREXEC_CAPTURES}" > /dev/null ; then
    >&2 echo "Power off requested. Shutting down now..." |& tee -a "${CONTAINER_LOG}"
    sudo shutdown now
fi

sudo /usr/sbin/sysctl -q -w kernel.core_pattern="${OLD_CORE_PATTERN}"
