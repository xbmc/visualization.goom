function get_docker_build_image()
{
    local -r os_type="$1"
    local -r os_tag="$2"

    echo "cpp-toolchain/${os_type}-${os_tag}:1.1"
}

declare -r DOCKER_BUILD_OS_TYPE=debian
declare -r DOCKER_BUILD_OS_TAG=bookworm
