PROJECT(visualization.goom)

CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR})

FIND_PACKAGE(xbmc REQUIRED)
addon_version(visualization.goom GOOM)

FIND_PACKAGE(OpenGL REQUIRED)
FIND_PACKAGE(GLEW REQUIRED)
INCLUDE_DIRECTORIES(${OpenGL_INCLUDE_DIR}
                    ${GLEW_INCLUDE_DIR}
                    ${XBMC_INCLUDE_DIR}
                    ${PROJECT_SOURCE_DIR}/lib/goom2k4-0/src)

INCLUDE(ExternalProject)
ExternalProject_ADD(libgoom SOURCE_DIR ${PROJECT_SOURCE_DIR}/lib/goom2k4-0
                    UPDATE_COMMAND ${PROJECT_SOURCE_DIR}/lib/goom2k4-0/autogen.sh WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/lib/goom2k4-0
                    CONFIGURE_COMMAND ${PROJECT_SOURCE_DIR}/lib/goom2k4-0/configure --disable-shared --enable-static --with-pic --prefix=<INSTALL_DIR>
                    BUILD_COMMAND ${MAKE}
                    INSTALL_COMMAND echo)

SET(SOURCES src/Main.cpp)

SET(DEPLIBS ${OPENGL_LIBRARIES}
            ${GLEW_LIBRARIES}
            ${CMAKE_BINARY_DIR}/libgoom-prefix/src/libgoom-build/src/.libs/libgoom2.a)

build_addon(visualization.goom SOURCES DEPLIBS GOOM_VERSION)
install_addon(visualization.goom ${GOOM_VERSION})

ADD_DEPENDENCIES(visualization.goom libgoom)
