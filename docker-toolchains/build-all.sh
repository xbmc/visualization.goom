#!/bin/bash

set -u
set -e

declare -r THIS_SCRIPT_PATH="$(cd "$(dirname "$0")" >/dev/null 2>&1 ; pwd -P)"

source "${THIS_SCRIPT_PATH}/build-get-vars.sh"


declare NO_CACHE=""
declare DOCKER_OS_TYPE="${DOCKER_BUILD_OS_TYPE}"
declare DOCKER_OS_TAG="${DOCKER_BUILD_OS_TAG}"

while [[ $# -gt 0 ]]; do
  key="$1"

  case $key in
    --no-cache)
      NO_CACHE="--no-cache"
      shift # past argument
      ;;
    --docker-os-type)
      DOCKER_OS_TYPE=${2}
      shift # past argument
      shift # past value
      ;;
    --docker-os-tag)
      DOCKER_OS_TAG=${2}
      shift # past argument
      shift # past value
      ;;
    *)
      echo "Unknown option \"${key}\"."
      echo
      exit 1
      ;;
    *)    # unknown option
  esac
done


declare -r BUILD_CLANG_VER="15"
declare -r BUILD_IMAGE="$(get_docker_build_image ${DOCKER_OS_TYPE} ${DOCKER_OS_TAG})"


if [[ "${NO_CACHE}" == "" ]]; then
  echo "Building \"${BUILD_IMAGE}\"..."
  echo
else
  echo "Building \"${BUILD_IMAGE}\" with \"${NO_CACHE}\"..."
  echo
fi

pushd "${THIS_SCRIPT_PATH}" > /dev/null

declare -r BUILD_ARGS="--build-arg OS_TYPE=${DOCKER_OS_TYPE} \
                       --build-arg OS_TAG=${DOCKER_OS_TAG}   \
                       --build-arg CLANG_VER=${BUILD_CLANG_VER} \
                       --build-arg UID=$(id -u)"

docker build ${NO_CACHE} ${BUILD_ARGS} -t ${BUILD_IMAGE} -f Dockerfile .

docker system prune -f

popd > /dev/null

