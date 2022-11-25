#!/bin/bash

set -u
set -e

declare -r GOOM_DUMPS_DIR="${HOME}/docker/kodi-nightly/.kodi/userdata/addon_data/visualization.goom/goom_dumps"
declare -r MOVE_TO_DIR="/tmp/goom_dumps_too_small"
declare -r MIN_LINE_COUNT=2000

if [[ ! -d "${GOOM_DUMPS_DIR}" ]]; then
  echo "ERROR: Could not find goom dumps directory \"${GOOM_DUMPS_DIR}\"."
  exit 1
fi

mkdir -p "${MOVE_TO_DIR}"
if [[ ! -d "${MOVE_TO_DIR}" ]]; then
  echo "ERROR: Could not find goom dumps move to directory \"${MOVE_TO_DIR}\"."
  exit 1
fi

for dir in ${GOOM_DUMPS_DIR}/*/ ; do
    LINE_COUNT=$(wc -l < "${dir}/blocky_wavy_effects.dat")
    if (( LINE_COUNT < MIN_LINE_COUNT )) ; then
        mv -v "${dir}" "${MOVE_TO_DIR}"
    fi
done
