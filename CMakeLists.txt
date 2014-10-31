project(visualization.goom)

cmake_minimum_required(VERSION 2.6)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR})

find_package(kodi REQUIRED)

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
include_directories(${OpenGL_INCLUDE_DIR}
                    ${GLEW_INCLUDE_DIRS}
                    ${KODI_INCLUDE_DIR}
                    ${PROJECT_SOURCE_DIR}/lib/goom2k4-0/src)

include(ExternalProject)
set(update_command "")
if(BOOTSTRAP_IN_TREE OR NOT DEFINED BOOTSTRAP_IN_TREE)
  set(update_command UPDATE_COMMAND autoreconf -vif WORKING_DIRECTORY <SOURCE_DIR>)
endif()
externalproject_add(libgoom SOURCE_DIR ${PROJECT_SOURCE_DIR}/lib/goom2k4-0
                    "${update_command}"
                    CONFIGURE_COMMAND ${PROJECT_SOURCE_DIR}/lib/goom2k4-0/configure --disable-shared --enable-static --with-pic --prefix=<INSTALL_DIR>
                    BUILD_COMMAND ${MAKE}
                    INSTALL_COMMAND "")

set(GOOM_SOURCES src/Main.cpp)

set(DEPLIBS ${OPENGL_LIBRARIES}
            ${GLEW_LIBRARIES}
            ${CMAKE_BINARY_DIR}/libgoom-prefix/src/libgoom-build/src/.libs/libgoom2.a)

build_addon(visualization.goom GOOM DEPLIBS)

add_dependencies(visualization.goom libgoom)
include(CPack)

