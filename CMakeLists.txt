cmake_minimum_required(VERSION 3.5)
project(visualization.goom)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR})

find_package(Kodi REQUIRED)

set(APP_RENDER_SYSTEM "gles")

if(APP_RENDER_SYSTEM STREQUAL "gl" OR NOT APP_RENDER_SYSTEM)
  find_package(OpenGl REQUIRED)
  set(DEPLIBS ${OPENGL_LIBRARIES})
  set(includes ${OPENGL_INCLUDE_DIR})
  add_definitions(${OPENGL_DEFINITIONS})
else()
  find_package(OpenGLES REQUIRED)
  set(DEPLIBS ${OPENGLES_LIBRARIES})
  set(includes ${OPENGLES_INCLUDE_DIR})
  add_definitions(${OPENGLES_DEFINITIONS})
endif()

add_subdirectory(lib/goom2k4-0)

include_directories(${includes}
                    ${KODI_INCLUDE_DIR}/.. # Hack way with "/..", need bigger Kodi cmake rework to match right include ways (becomes done in future)
                    ${PROJECT_SOURCE_DIR}/lib
                    ${PROJECT_SOURCE_DIR}/lib/goom2k4-0/src)

set(GOOM_SOURCES src/Main.cpp
                 src/workers.cpp)

set(GOOM_HEADERS src/buffer_savers.hpp
                 src/goom_config.h
                 src/tsqueue.hpp
                 src/workers.hpp)

list(APPEND DEPLIBS goom)

build_addon(visualization.goom GOOM DEPLIBS)

include(CPack)
