function get_this_sourced_script_path()
{
  local dirname=""
  for i in "${BASH_SOURCE[@]}"; do
    dirname=$(dirname $i)
    filename=$(basename $i)
    if [[ "${filename}" == "${GOOM_GET_VARS_SCRIPT_NAME}" ]]; then
      break
    fi
  done

  echo ${dirname}
}

declare -r GOOM_GET_VARS_SCRIPT_NAME="goom-get-vars.sh"
declare -r GOOM_GET_VARS_SCRIPT_PATH=$(get_this_sourced_script_path)

source "${GOOM_GET_VARS_SCRIPT_PATH}/docker-toolchains/build-get-vars.sh"


declare GOOM_VAR_CMD_LINE=""
declare USING_DOCKER="no"
declare USING_CLION="no"
declare DOCKER_OS_TYPE="${DOCKER_BUILD_OS_TYPE}"
declare DOCKER_OS_TAG="${DOCKER_BUILD_OS_TAG}"
declare EXTRA_ARGS=""

while [[ $# -gt 0 ]]; do
  key="$1"

  case $key in
    -b|--build)
      declare -r BUILD_DIRNAME=${2}
      GOOM_VAR_CMD_LINE="${GOOM_VAR_CMD_LINE} --build ${BUILD_DIRNAME}"
      shift # past argument
      shift # past value
      ;;
    -c|--compiler)
      COMPILER=${2}
      GOOM_VAR_CMD_LINE="${GOOM_VAR_CMD_LINE} --compiler ${COMPILER}"
      shift # past argument
      shift # past value
      ;;
    --build-type)
      BUILD_TYPE=${2}
      GOOM_VAR_CMD_LINE="${GOOM_VAR_CMD_LINE} --build-type ${BUILD_TYPE}"
      shift # past argument
      shift # past value
      ;;
    -s|--suffix)
      declare -r BUILD_DIR_SUFFIX=${2}
      GOOM_VAR_CMD_LINE="${GOOM_VAR_CMD_LINE} --suffix ${BUILD_DIR_SUFFIX}"
      shift # past argument
      shift # past value
      ;;
    --docker)
      USING_DOCKER="yes"
      GOOM_VAR_CMD_LINE="${GOOM_VAR_CMD_LINE} --docker"
      shift # past argument
      ;;
    --docker-os-type)
      DOCKER_OS_TYPE=${2}
      GOOM_VAR_CMD_LINE="${GOOM_VAR_CMD_LINE} --docker-os-type ${DOCKER_OS_TYPE}"
      shift # past argument
      shift # past value
      ;;
    --docker-os-tag)
      DOCKER_OS_TAG=${2}
      GOOM_VAR_CMD_LINE="${GOOM_VAR_CMD_LINE} --docker-os-tag ${DOCKER_OS_TAG}"
      shift # past argument
      shift # past value
      ;;
    --clion)
      USING_CLION="yes"
      GOOM_VAR_CMD_LINE="${GOOM_VAR_CMD_LINE} --clion"
      shift # past argument
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


# Compilers
if [[ "${COMPILER:-}" == "" ]]; then
  echo "ERROR: 'COMPILER' must be specified."
  echo
  exit 1
fi
if [[ "${COMPILER}" == "gcc-11" ]]; then
  declare -r C_COMPILER=gcc-11
  declare -r CPP_COMPILER=g++-11
elif [[ "${COMPILER}" == "gcc-12" ]]; then
  declare -r C_COMPILER=gcc-12
  declare -r CPP_COMPILER=g++-12
elif [[ "${COMPILER}" == "clang-13" ]]; then
  declare -r C_COMPILER=clang-13
  declare -r CPP_COMPILER=clang-13
elif [[ "${COMPILER}" == "clang-14" ]]; then
  declare -r C_COMPILER=clang-14
  declare -r CPP_COMPILER=clang-14
elif [[ "${COMPILER}" == "clang-15" ]]; then
  declare -r C_COMPILER=clang-15
  declare -r CPP_COMPILER=clang-15
elif [[ "${COMPILER}" == "clang-16" ]]; then
  declare -r C_COMPILER=clang-16
  declare -r CPP_COMPILER=clang-16
else
  echo "ERROR: Unknown compiler \"${COMPILER}\"."
  echo
  exit 1
fi

# Build type
if [[ "${BUILD_TYPE:-}" == "" ]]; then
  echo "ERROR: 'BUILD_TYPE' must be specified."
  echo
  exit 1
fi
if [[ "${BUILD_TYPE}" == "Debug" ]]; then
  declare -r C_BUILD_TYPE=Debug
elif [[ "${BUILD_TYPE}" == "Release" ]]; then
  declare -r C_BUILD_TYPE=Release
elif [[ "${BUILD_TYPE}" == "RelWithDebInfo" ]]; then
  declare -r C_BUILD_TYPE=RelWithDebInfo
else
  echo "ERROR: Unknown build type \"${BUILD_TYPE}\"."
  echo
  exit 1
fi

# Suffix
if [[ "${BUILD_DIR_SUFFIX:-}" == "" ]]; then
  echo "ERROR: 'BUILD_DIR_SUFFIX' must be specified."
  echo
  exit 1
fi

# Docker
if [[ "${USING_DOCKER}" == "no" ]]; then
  declare DOCKER_PREFIX=""
else
  declare DOCKER_PREFIX="docker-"
fi

declare -r HOST_TIME_ZONE=$(cat /etc/timezone)
declare -r HOST_CCACHE_DIR=${CCACHE_DIR}
declare -r HOST_KODI_ROOT_DIR=$(realpath ${GOOM_GET_VARS_SCRIPT_PATH}/..)
declare -r DOCKER_CCACHE_DIR=/tmp/ccache
declare -r DOCKER_KODI_ROOT_DIR=/tmp/xbmc
declare -r DOCKER_GOOM_BUILD_DIR=/tmp/visualization.goom
declare -r DOCKER_BUILD_IMAGE="$(get_docker_build_image ${DOCKER_OS_TYPE} ${DOCKER_OS_TAG})"

# Clion
if [[ "${USING_CLION}" == "no" ]]; then
  declare CLION_PREFIX=""
else
  declare CLION_PREFIX="clion-"
fi

# Build directory
if [[ "${BUILD_DIRNAME:-}" == "" ]]; then
  declare -r BUILD_DIRNAME=build-${CLION_PREFIX}${DOCKER_PREFIX}${C_COMPILER}-${C_BUILD_TYPE}-${BUILD_DIR_SUFFIX}
fi
if [[ ${BUILD_DIRNAME} != build* ]]; then
  echo "ERROR: Build dirname must start with \"build\". Not this: BUILD_DIRNAME = \"${BUILD_DIRNAME}\""
  exit 1
fi

declare -r BUILD_DIR=${THIS_SCRIPT_PATH}/${BUILD_DIRNAME}


unset DOCKER_PREFIX
unset CLION_PREFIX
