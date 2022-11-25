#!/bin/bash

set -u
set -o pipefail

declare -r LOG_DIR=${HOME}/kodi-log
declare -r KODI_DOCKER_LOG=${LOG_DIR}/kodi-docker.log
declare -r IREXEC_CAPTURES=${HOME}/temp/irexec.out
# Set the following to redirect irexec logs
declare -r IREXEC_LOG_DIR=${LOG_DIR}

log()
{
  local -r date_str=$(date +"%m-%d-%y %T")
  { >&2 echo "${date_str} $1 " ; } |& tee -a "${KODI_DOCKER_LOG}"
}

get_kodi_pid()
{
  pidof "kodi.bin"
}

stop_kodi()
{
  local -r exit_code=$?

  if [[ "$(get_kodi_pid)" == "" ]]; then
    log "Kodi is not running. Exiting with return code '${exit_code}'." ; exit ${exit_code}
  fi

  log "Stopping Kodi..."
  kodi-send --action="Quit"

  local -r timeout=10
  local timer=0

  while [[ ${timer} -lt ${timeout} && "$(get_kodi_pid)" != "" ]]; do
    log "waiting for Kodi to terminate: ($((timeout - timer)) seconds to go)"
    timer=$((timer+1))
    sleep 1
  done

  if [[ "$(get_kodi_pid)" == "" ]]; then
    log 'Kodi terminated successfully.' ; exit 1
  fi

  log "WARNING: Could not stop Kodi after $timeout seconds."
}


mkdir -p "${LOG_DIR}"
mkdir -p "${HOME}/temp"

trap stop_kodi EXIT

declare -r KODI_OUTPUT=/tmp/kodi-standalone.output

# Run irexec to echo any 'KEY_SLEEP" presses to a signal file.
log "Starting irexec..."
rm -f "${IREXEC_CAPTURES}"
XDG_CACHE_HOME=${IREXEC_LOG_DIR} irexec /etc/lirc/irexec.lircrc > "${IREXEC_CAPTURES}" &

log "Starting Kodi standalone..."
kodi-standalone |& tee ${KODI_OUTPUT}
declare RET_CODE=$?

log "Kodi exited with exit code ${RET_CODE}."

if grep -i "Crash report available" "${KODI_OUTPUT}" ; then
  log "Kodi has a 'Crash report'."
  exit 1
fi
