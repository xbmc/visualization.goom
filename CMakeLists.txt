project(visualization.goom)

cmake_minimum_required(VERSION 2.6)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR})

find_package(Kodi REQUIRED)

if(APP_RENDER_SYSTEM STREQUAL "gl" OR NOT APP_RENDER_SYSTEM)
  find_package(OpenGL REQUIRED)
  set(DEPLIBS ${OPENGL_LIBRARIES})
  set(includes ${OPENGL_INCLUDE_DIR})
  add_definitions(-DHAS_OPENGL)
elseif(APP_RENDER_SYSTEM STREQUAL "gles")
  find_package(OpenGLES2 REQUIRED)
  set(DEPLIBS ${OPENGLES2_LIBRARIES})
  set(includes ${OPENGLES2_INCLUDE_DIR})
  add_definitions(-DHAS_GLES2)
endif()

include_directories(${includes}
                    ${KODI_INCLUDE_DIR}/.. # Hack way with "/..", need bigger Kodi cmake rework to match right include ways (becomes done in future)
                    ${PROJECT_SOURCE_DIR}/lib/goom2k4-0/src)

include(ExternalProject)
externalproject_add(libgoom SOURCE_DIR ${PROJECT_SOURCE_DIR}/lib/goom2k4-0
                    CONFIGURE_COMMAND cd <SOURCE_DIR> && autoreconf -vif && cd <BINARY_DIR> && ${PROJECT_SOURCE_DIR}/lib/goom2k4-0/configure --disable-shared --enable-static --with-pic --prefix=<INSTALL_DIR>
                    BUILD_COMMAND ${MAKE}
                    INSTALL_COMMAND "")

set(GOOM_SOURCES src/Main.cpp
                 src/shaders/GUIShader.cpp
                 src/shaders/Matrix.cpp
                 src/shaders/Shader.cpp)

set(GOOM_HEADERS src/goom_config.h
                 src/shaders/GUIShader.h
                 src/shaders/Matrix.h
                 src/shaders/Shader.h)

list(APPEND DEPLIBS ${CMAKE_BINARY_DIR}/libgoom-prefix/src/libgoom-build/src/.libs/libgoom2.a)

build_addon(visualization.goom GOOM DEPLIBS)

add_dependencies(visualization.goom libgoom)
include(CPack)
