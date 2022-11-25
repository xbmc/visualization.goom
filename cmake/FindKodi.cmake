message("<FindKodi.cmake>")

if ((CMAKE_CXX_COMPILER_ID MATCHES ".*MSVC")
     AND ((GOOM_BUILD_DIR MATCHES ".*jenkins.*") OR (GOOM_BUILD_DIR MATCHES ".*workspace.*")))
    set(KODI_BINARY_ADDONS_ROOT_DIR "${GOOM_BUILD_DIR}/../../..")
    cmake_path(NORMAL_PATH KODI_BINARY_ADDONS_ROOT_DIR OUTPUT_VARIABLE KODI_BINARY_ADDONS_ROOT_DIR)
    set(EXPECTED_KODI_CONFIG_DIR "${KODI_BINARY_ADDONS_ROOT_DIR}/cmake/addons/output/lib")
else ()
    set(EXPECTED_KODI_CONFIG_DIR "${GOOM_BUILD_DIR}")
endif ()

file(GLOB_RECURSE KODI_CONFIG_DIR LIST_DIRECTORIES False "${EXPECTED_KODI_CONFIG_DIR}/*/KodiConfig.cmake" NO_CACHE)
get_filename_component(KODI_CONFIG_DIR "${KODI_CONFIG_DIR}" DIRECTORY)
if (NOT KODI_CONFIG_DIR)
    message(STATUS "GOOM_BUILD_DIR = \"${GOOM_BUILD_DIR}\".")
    message(STATUS "EXPECTED_KODI_CONFIG_DIR = \"${EXPECTED_KODI_CONFIG_DIR}\".")
    set(EXPECTED_KODI_CONFIG_DIR "/usr")
    message(WARNING "Could not find \"KodiConfig.cmake\" under goom build directory. Resetting to \"${EXPECTED_KODI_CONFIG_DIR}\".")
endif ()

# Hack to handle 'Debian' builds where 'KodiConfig.cmake' is not under build directory but
# can be found under '/usr'

file(GLOB_RECURSE KODI_CONFIG_DIR LIST_DIRECTORIES False "${EXPECTED_KODI_CONFIG_DIR}/*/KodiConfig.cmake" NO_CACHE)
get_filename_component(KODI_CONFIG_DIR "${KODI_CONFIG_DIR}" DIRECTORY)
if (NOT KODI_CONFIG_DIR)
    message(STATUS "GOOM_BUILD_DIR = \"${GOOM_BUILD_DIR}\".")
    message(STATUS "EXPECTED_KODI_CONFIG_DIR = \"${EXPECTED_KODI_CONFIG_DIR}\".")
    message(FATAL_ERROR "Could not find \"KodiConfig.cmake\" under goom build directory.")
endif ()

set(CMAKE_FIND_DEBUG_MODE FALSE)
find_package(Kodi PATHS "${KODI_CONFIG_DIR}" NO_DEFAULT_PATH REQUIRED CONFIG)

# Provides KODI_INCLUDE_DIR but it's out by one!
set(KODI_FIXED_INCLUDE_DIR ${KODI_INCLUDE_DIR}/..)
