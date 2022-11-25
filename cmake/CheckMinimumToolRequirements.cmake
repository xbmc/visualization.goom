# Check minimum compiler versions.
if (CMAKE_CXX_COMPILER_ID MATCHES ".*Clang")
    # Older clangs don't like some variations of "Circle(Circle&&) noexcept = default"
    if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
        set(MIN_COMPILER_VERSION 13)
    elseif (CMAKE_CXX_COMPILER_ID STREQUAL "AppleClang")
        set(MIN_COMPILER_VERSION 13)
    endif ()
elseif (CMAKE_CXX_COMPILER_ID MATCHES ".*GNU")
    set(MIN_COMPILER_VERSION 9)
elseif (CMAKE_CXX_COMPILER_ID MATCHES ".*MSVC")
    set(MIN_COMPILER_VERSION 19.0)
endif()

if (CMAKE_CXX_COMPILER_VERSION VERSION_LESS ${MIN_COMPILER_VERSION})
    message(FATAL_ERROR "${CMAKE_CXX_COMPILER_ID} version = '${CMAKE_CXX_COMPILER_VERSION}'. Minimum acceptable version is '${MIN_COMPILER_VERSION}'.")
endif ()

# Check the minimum standard.
set(MIN_CXX_STANDARD 17)
if (CMAKE_CXX_STANDARD VERSION_LESS ${MIN_CXX_STANDARD})
    message(FATAL_ERROR "CMAKE_CXX_STANDARD = '${CMAKE_CXX_STANDARD}'. Minimum acceptable standard is '${MIN_CXX_STANDARD}'.")
endif ()

if (NOT CMAKE_CXX_STANDARD_REQUIRED)
    message(FATAL_ERROR "CMAKE_CXX_STANDARD_REQUIRED should be set to 'ON'.")
endif ()
# TODO. Can't get "if (NOT CMAKE_CXX_EXTENSIONS)" to work!
if (NOT ${CMAKE_CXX_EXTENSIONS} STREQUAL OFF)
    message(FATAL_ERROR "CMAKE_CXX_EXTENSIONS should be set to 'OFF'. Currently set to '${CMAKE_CXX_EXTENSIONS}'.")
endif ()

# Don't trust older build environments yet.
include(CheckIncludeFileCXX)
CHECK_INCLUDE_FILE_CXX(optional OPTIONAL_INCLUDE)
if (NOT OPTIONAL_INCLUDE)
    message(FATAL_ERROR "Could not find C++17 'optional' header. Is libc++ up to date?")
endif ()
CHECK_INCLUDE_FILE_CXX(filesystem FILESYSTEM_INCLUDE)
if (NOT FILESYSTEM_INCLUDE)
    message(FATAL_ERROR "Could not find C++17 'filesystem' header. Is libc++ up to date?")
endif ()

# Check minimum Window SDK
if (WIN32)
    if (NOT CMAKE_VS_WINDOWS_TARGET_PLATFORM_VERSION)
        message(WARNING "Windows SDK is not defined. Cannot tell if it's too old.")
    else ()
        set(MINIMUM_SDK_VERSION "10.0.17763.0")
        if (CMAKE_VS_WINDOWS_TARGET_PLATFORM_VERSION VERSION_LESS ${MINIMUM_SDK_VERSION})
            message(FATAL_ERROR "Windows SDK too old: installed \"${CMAKE_VS_WINDOWS_TARGET_PLATFORM_VERSION}\" < minimum \"${MINIMUM_SDK_VERSION}\"")
        endif ()
    endif ()
endif ()
