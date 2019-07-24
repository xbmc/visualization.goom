project(visualization.goom)

cmake_minimum_required(VERSION 3.3)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR})

enable_language(CXX)

find_package(Kodi REQUIRED)

find_package(OpenGL REQUIRED)
set(DEPLIBS ${OPENGL_LIBRARIES})
set(includes ${OPENGL_INCLUDE_DIR})
add_definitions(${OPENGL_DEFINITIONS})

if(NOT OPENGL_FOUND)
  message(FATAL_ERROR "No rendering API found. Bailing")
endif()

include_directories(${includes}
                    ${KODI_INCLUDE_DIR}/.. # Hack way with "/..", need bigger Kodi cmake rework to match right include ways (becomes done in future)
                    ${PROJECT_SOURCE_DIR}/lib
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

set(GOOM_SOURCES src/Main.cpp src/workers.cpp)

set(DEPLIBS ${OPENGL_LIBRARIES}
            ${CMAKE_BINARY_DIR}/libgoom-prefix/src/libgoom-build/src/.libs/libgoom2.a)

build_addon(visualization.goom GOOM DEPLIBS)

add_dependencies(visualization.goom libgoom)

include(CPack)
