#!/bin/bash

set -u
set -e

declare -r THIS_SCRIPT_PATH="$(cd "$(dirname "$0")" >/dev/null 2>&1 ; pwd -P)"

source "${THIS_SCRIPT_PATH}/goom-image-funcs.sh"


declare IS_USER_ADDON="no"
declare NO_CACHE=""

while [[ $# -gt 0 ]]; do
  key="$1"

  case $key in
    --no-cache)
      NO_CACHE="--no-cache"
      shift # past argument
      ;;
    --user-addon)
      IS_USER_ADDON="yes"
      shift # past argument
      ;;
    --kodi-version)
      declare -r KODI_VERSION=$2
      shift # past argument
      shift # past value
      ;;
    --goom-version)
      declare -r GOOM_VERSION=$2
      shift # past argument
      shift # past value
      ;;
    --image-os)
      declare -r KODI_IMAGE_OS_TYPE=$2
      shift # past argument
      shift # past value
      ;;
    --image-os-version)
      declare -r KODI_IMAGE_OS_TAG=$2
      shift # past argument
      shift # past value
      ;;
    --container-home-dir)
      declare -r KODI_CONTAINER_HOME_DIR=$2
      shift # past argument
      shift # past value
      ;;
    --docker-files-dir)
      declare -r KODI_DOCKER_FILES_DIR=$2
      shift # past argument
      shift # past value
      ;;
    *)
      echo "ERROR: Unknown command line argument: $key"
      exit 1
      ;;
    *)
  esac
done

if [[ "${KODI_VERSION:-}" == "" ]]; then
  echo "ERROR: Kodi version not specified."
  exit 1
fi
if [[ "${GOOM_VERSION:-}" == "" ]]; then
  echo "ERROR: Goom version not specified."
  exit 1
fi
if [[ "${KODI_IMAGE_OS_TYPE:-}" == "" ]]; then
  echo "ERROR: OS image type not specified."
  exit 1
fi
if [[ "${KODI_IMAGE_OS_TAG:-}" == "" ]]; then
  echo "ERROR: OS image tag not specified."
  exit 1
fi
if [[ "${KODI_CONTAINER_HOME_DIR:-}" == "" ]]; then
  echo "ERROR: Container home directory not specified."
  exit 1
fi
if [[ "${KODI_DOCKER_FILES_DIR:-}" == "" ]]; then
  echo "ERROR: Docker files directory not specified."
  exit 1
fi


function copy_user_addon_files()
{
  if [[ "${IS_USER_ADDON}" == "no" ]]; then
    echo
    echo "Installing the system goom add-on, so removing all user add-on files from \"${CONTAINER_GOOM_ADDON_DIR}\"..."
    if [[ -d "${CONTAINER_GOOM_ADDON_DIR}" ]]; then
        rm -r "${CONTAINER_GOOM_ADDON_DIR}"
    fi
  else
    echo
    echo "Copying required goom user add-on files from \"${KODI_DOCKER_FILES_DIR}\" to \"${CONTAINER_GOOM_ADDON_DIR}\"..."

    mkdir -p "${CONTAINER_GOOM_ADDON_DIR}"
    echo
    echo "rsyncing \"${KODI_DOCKER_FILES_DIR}/visualization.goom.so.${GOOM_VERSION}\" to \"${CONTAINER_GOOM_ADDON_DIR}\""
    rsync -avh "${KODI_DOCKER_FILES_DIR}/visualization.goom.so.${GOOM_VERSION}" "${CONTAINER_GOOM_ADDON_DIR}"
    echo
    echo "rsyncing \"${KODI_DOCKER_FILES_DIR}/addon.xml\" to \"${CONTAINER_GOOM_ADDON_DIR}\""
    rsync -avh "${KODI_DOCKER_FILES_DIR}/addon.xml" "${CONTAINER_GOOM_ADDON_DIR}/addon.xml"
    echo
    echo "rsyncing \"${KODI_DOCKER_FILES_DIR}/resources/\" to \"${CONTAINER_GOOM_ADDON_DIR}resources/\""
    rsync --delete --out-format="%n" --itemize-changes -a "${KODI_DOCKER_FILES_DIR}/resources/" "${CONTAINER_GOOM_ADDON_DIR}/resources/"
  fi
}

declare -r KODI_GOOM_IMAGE="$(get_kodi_goom_image_name ${KODI_IMAGE_OS_TYPE} ${KODI_IMAGE_OS_TAG} ${KODI_VERSION})"
declare -r CONTAINER_GOOM_ADDON_DIR="${KODI_CONTAINER_HOME_DIR}/.kodi/addons/visualization.goom"

if [[ "${KODI_VERSION}" == "matrix" ]]; then
  declare -r KODI_PPA="ppa:team-xbmc/ppa"
elif [[ "${KODI_VERSION}" == "nightly" ]]; then
  declare -r KODI_PPA="ppa:team-xbmc/xbmc-nightly"
else
  echo "ERROR: Unknown Kodi version: \"${KODI_VERSION}\"."
  exit 1
fi

if [[ "${IS_USER_ADDON}" == "no" ]]; then
  # Copy add-ons to Kodi system directories.
  declare -r KODI_GOOM_LIB_DIR=/usr/lib/x86_64-linux-gnu/kodi/addons/visualization.goom
  declare -r KODI_GOOM_ADDON_DIR=/usr/share/kodi/addons/visualization.goom
else
  # Copying files to "/tmp" in Docker means the files will be lost when the container starts.
  # We want this for user add-on files because they are copied seperately to the Kodi home
  # add-ons directory and we don't want them in the Kodi system directories.
  declare -r KODI_GOOM_LIB_DIR=/tmp
  declare -r KODI_GOOM_ADDON_DIR=/tmp
fi

if [[ "${KODI_IMAGE_OS_TAG}" != "impish" ]]; then
  declare -r END_OF_LIFE="no"
else
  declare -r END_OF_LIFE="yes"
fi


pushd "${THIS_SCRIPT_PATH}" > /dev/null

if [[ "${NO_CACHE}" == "" ]]; then
  echo "Building Goom Docker image \"${KODI_GOOM_IMAGE}\"..."
  echo
else
  echo "Building Goom Docker image \"${KODI_GOOM_IMAGE}\" with \"${NO_CACHE}\"..."
  echo
fi

declare -r BUILD_ARGS="--build-arg OS_TYPE=${KODI_IMAGE_OS_TYPE}             \
                       --build-arg OS_TAG=${KODI_IMAGE_OS_TAG}               \
                       --build-arg KODI_PPA=${KODI_PPA}                      \
                       --build-arg END_OF_LIFE=${END_OF_LIFE}                \
                       --build-arg GOOM_VERSION=${GOOM_VERSION}              \
                       --build-arg KODI_GOOM_LIB_DIR=${KODI_GOOM_LIB_DIR}    \
                       --build-arg KODI_GOOM_ADDON_DIR=${KODI_GOOM_ADDON_DIR}"

docker build ${NO_CACHE} -t ${KODI_GOOM_IMAGE} ${BUILD_ARGS} -f Dockerfile .

docker system prune -f

copy_user_addon_files


popd > /dev/null

echo
echo "Sucessfully built \"${KODI_GOOM_IMAGE}\"."
echo
