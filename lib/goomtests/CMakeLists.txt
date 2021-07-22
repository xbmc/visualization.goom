cmake_minimum_required(VERSION 3.12)

project(GoomTests LANGUAGES CXX)

##set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address")
#set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fsanitize=address")
#set(CMAKE_MODULE_LINKER_FLAGS "${CMAKE_MODULE_LINKER_FLAGS} -fsanitize=address")

if(WIN32)
    add_definitions(-D_WIN32PC)
endif()

find_package(Threads)

add_executable(goomtests
    src/test_main.cpp
    src/test_colorutils.cpp
    src/test_goomrand.cpp
    src/test_mathutils.cpp
    src/test_parallel_utils.cpp
    src/test_strutils.cpp
)

target_link_libraries(goomtests
    PRIVATE
        goom
        goomutils
        vivid
        ${CMAKE_THREAD_LIBS_INIT}
)

target_include_directories(goomtests
    PRIVATE 
        ${LIBS_DIR}/catch2/include
        ${LIBS_DIR}/goom/include/goom  
        ${LIBS_DIR}/goomutils/include/goomutils
)  
target_include_directories(goomtests
    SYSTEM PRIVATE 
        ${LIBS_DIR}/fmt/include
        ${LIBS_DIR}/magic_enum/include
        # Need this '..' hack here. Not nice!
        SYSTEM ${GLM_INCLUDE_DIR}/..
)

set_target_properties(goomtests
    PROPERTIES
        CXX_STANDARD ${CPP_STANDARD}
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${PROJECT_NAME}/bin
)

message(STATUS "Goom Tests C++ standard = \"${CPP_STANDARD}\".")
