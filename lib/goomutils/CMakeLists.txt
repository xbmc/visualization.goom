cmake_minimum_required(VERSION 3.12)

project(GoomUtils LANGUAGES CXX)

##set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address")
#set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fsanitize=address")
#set(CMAKE_MODULE_LINKER_FLAGS "${CMAKE_MODULE_LINKER_FLAGS} -fsanitize=address")

if(WIN32)
    add_definitions(-D_WIN32PC)
endif()

add_library(goomutils
    STATIC
        src/color_data_maps.cpp
        src/colormaps.cpp
        src/colorutils.cpp
        src/extra_color_groups.cpp
        src/goomrand.cpp
        src/graphics/honeycomb.cpp
        src/graphics/image_bitmaps.cpp
        src/graphics/small_image_bitmaps.cpp
        src/logging.cpp
        src/mathutils.cpp
        src/random_colormaps.cpp
        src/random_colormaps_manager.cpp
        src/strutils.cpp
        src/t_values.cpp
        src/thread_pool.cpp
        src/graphics/turtle.cpp
)

#set_source_files_properties(src/colormaps.cpp PROPERTIES COMPILE_FLAGS -fsanitize=address)

target_include_directories(goomutils
    PUBLIC
        ${LIBS_DIR}/goom/include
        ${LIBS_DIR}/goomutils/include
    PRIVATE
        ${LIBS_DIR}/goomutils/include/goomutils
)
target_include_directories(goomutils
    SYSTEM PRIVATE
        ${LIBS_DIR}/vivid/include
        ${LIBS_DIR}/fmt/include
        ${LIBS_DIR}/magic_enum/include
        # Need this '..' hack here. Not nice!
        SYSTEM ${GLM_INCLUDE_DIR}/..
)

set_target_properties(goomutils
    PROPERTIES
        CXX_STANDARD ${CPP_STANDARD}
        POSITION_INDEPENDENT_CODE ON
)

message(STATUS "Goom Utils C++ standard = \"${CPP_STANDARD}\".")
