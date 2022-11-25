cmake_minimum_required( VERSION 3.15 FATAL_ERROR )

project( vivid
    VERSION 2.2.2
    DESCRIPTION "A simple-to-use cpp color library"
    HOMEPAGE_URL "https://github.com/gurki/vivid"
    LANGUAGES CXX
)

#find_package( glm REQUIRED )
#message(STATUS "glm included")
if (NOT GLM_INCLUDE_DIR)
    message(FATAL_ERROR "\"GLM_INCLUDE_DIR\" must be defined." )
endif()


add_library( ${PROJECT_NAME} STATIC
    src/adobe.cpp
    src/color.cpp
    src/colormap.cpp
    src/hex.cpp
    src/hsl.cpp
    src/hsv.cpp
    src/index.cpp
    src/interpolation.cpp
    src/lab.cpp
    src/lch.cpp
    src/lrgb.cpp
    src/name.cpp
    src/oklab.cpp
    src/rgb.cpp
    src/rgb32.cpp
    src/rgb8.cpp
    src/srgb.cpp
    src/types.cpp
    src/utility.cpp
    src/xyz.cpp
)

add_library(libs::vivid ALIAS vivid)

if(NOT CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    set(CMAKE_COMMON_CXX_WARNINGS ${CMAKE_COMMON_CXX_WARNINGS} -Wno-effc++ -Wno-sign-conversion)
endif()

target_compile_options( vivid
    PRIVATE
        ${CMAKE_COMMON_CXX_WARNINGS}
)

target_compile_features( ${PROJECT_NAME}
    PUBLIC
        cxx_std_17  #  std::optional, nested namespaces
    PRIVATE
        cxx_auto_type
        cxx_defaulted_functions
        cxx_lambdas
        cxx_range_for
        cxx_trailing_return_types
        cxx_unicode_literals
        cxx_inline_namespaces
)

target_include_directories( ${PROJECT_NAME}
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${GLM_INCLUDE_DIR}
)

enable_sanitizers(${PROJECT_NAME})

set_target_properties( ${PROJECT_NAME}
    PROPERTIES
        POSITION_INDEPENDENT_CODE ${POS_INDEP_CODE}
)

# Disable examples and tests for now - Android and Apple builds failing.
if(OFF)
    message(STATUS "Building Vivid examples and tests.")
    add_subdirectory(examples)
    add_subdirectory(tests)
endif()

get_target_property(vivid_compile_options  vivid COMPILE_OPTIONS)
get_target_property(vivid_compile_features vivid COMPILE_FEATURES)

message(STATUS "Vivid: C++ standard = \"${CMAKE_CXX_STANDARD}\".")
message(STATUS "Vivid: C++ compile features = \"${vivid_compile_features}\".")
message(STATUS "Vivid: C++ compile options = \"${vivid_compile_options}\".")
message(STATUS "Vivid: GLM_INCLUDE_DIR = \"${GLM_INCLUDE_DIR}\".")
