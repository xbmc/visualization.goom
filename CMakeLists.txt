cmake_minimum_required(VERSION 3.12)

project(visualization.goom)

set(CPP_STANDARD 14)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR})

if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
  # Kodi Windows build uses Visual Studio 2017 which calls C++17 attributes errors instead of warnings.
  # Force C++17 to get it to build properly.
  set(CPP_STANDARD 17)
  set(CMAKE_COMMON_CXX_WARNINGS /W2)
  # Windows linker seems to be broken - possibly with multi-threading.
  set(POS_INDEP_CODE "OFF")
else()
  set(CMAKE_COMMON_CXX_WARNINGS -Wall -Wextra -Weffc++ -Wsign-conversion -pedantic)
  if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang" OR CMAKE_CXX_COMPILER_ID STREQUAL "AppleClang")
    set(CMAKE_COMMON_CXX_WARNINGS ${CMAKE_COMMON_CXX_WARNINGS} -Wno-c++17-extensions)
  endif()
  set(POS_INDEP_CODE "ON")
endif()

set(CMAKE_CXX_STANDARD ${CPP_STANDARD})
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(Kodi REQUIRED)
find_package(glm REQUIRED)

if(NOT WIN32 AND (APP_RENDER_SYSTEM STREQUAL "gl" OR NOT APP_RENDER_SYSTEM))
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

find_package(Freetype)
if (FREETYPE_FOUND)
  message(STATUS "Found FreeType package - using supplied include directories.")
else()
  message(WARNING "Could not find FreeType package - disabling Freetype.")
  add_definitions(-DNO_FREETYPE_INSTALLED)
endif ()

set(LIBS_DIR ${CMAKE_SOURCE_DIR}/lib)

message(STATUS "CMAKE_CXX_COMPILER_ID = \"${CMAKE_CXX_COMPILER_ID}\".")
message(STATUS "CMAKE_CXX_COMPILER_VERSION = \"${CMAKE_CXX_COMPILER_VERSION}\".")
message(STATUS "CMAKE_MODULE_PATH = \"${CMAKE_MODULE_PATH}\".")
message(STATUS "LIBS_DIR = \"${LIBS_DIR}\".")
message(STATUS "FREETYPE_INCLUDE_DIRS = \"${FREETYPE_INCLUDE_DIRS}\".")
message(STATUS "GLM_INCLUDE_DIR = \"${GLM_INCLUDE_DIR}\".")
message(STATUS "KODI_INCLUDE_DIR = \"${KODI_INCLUDE_DIR}\".")
message(STATUS "Main C++ standard = \"${CPP_STANDARD}\".")
message(STATUS "C++ standard required = \"${CMAKE_CXX_STANDARD_REQUIRED}\".")
message(STATUS "C++ extensions = \"${CMAKE_CXX_EXTENSIONS}\".")
message(STATUS "C Compile features = \"${COMMON_C_COMPILE_FEATURES}\".")
message(STATUS "C++ Compile features = \"${COMMON_CXX_COMPILE_FEATURES}\".")
message(STATUS "C warnings = \"${CMAKE_COMMON_C_WARNINGS}\".")
message(STATUS "C++ warnings = \"${CMAKE_COMMON_CXX_WARNINGS}\".")

add_compile_options(${CMAKE_COMMON_C_WARNINGS})
add_compile_options(${CMAKE_COMMON_CXX_WARNINGS})

add_subdirectory(lib)

include_directories(${LIBS_DIR}/goom/include
                    ${LIBS_DIR}/goom/goomutils/include
                    ${LIBS_DIR}
                    SYSTEM ${LIBS_DIR}/vivid/include
                    SYSTEM ${LIBS_DIR}/fmt/include
                    SYSTEM ${FREETYPE_INCLUDE_DIRS}
                    # Need this '..' hack here. Not nice!
                    SYSTEM ${GLM_INCLUDE_DIR}/..
                    SYSTEM ${KODI_INCLUDE_DIR})

set(GOOM_SOURCES src/Main.cpp)
set(GOOM_HEADERS src/CircularBuffer.h
                 src/Main.h)

if ($ENV{DO_TESTING})
  set (TESTING ON)
  include(../visualization.goom.testing/goom_testing)
endif()

list(APPEND DEPLIBS goom goomutils vivid)

set(CMAKE_CXX_STANDARD ${CPP_STANDARD})
build_addon(visualization.goom GOOM DEPLIBS)

include(CPack)
