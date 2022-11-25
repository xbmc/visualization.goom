cmake_minimum_required(VERSION 3.15)

project(GoomTests LANGUAGES CXX)

set(GOOM_LIB_TESTS_NAME goom_lib_tests)

if (WIN32)
    add_definitions(-D_WIN32PC)
endif ()

find_package(Threads)

add_executable(${GOOM_LIB_TESTS_NAME}
               src/test_main.cpp
               src/test_pixels.cpp
               src/color/test_color_maps_grids.cpp
               src/color/test_color_utils.cpp
               src/draw/test_draw.cpp
               src/filters/test_filter_buffers.cpp
               src/filters/test_filter_colors_service.cpp
               src/filters/test_filter_zoom_vector.cpp
               src/filters/test_normalized_coords.cpp
               src/sound/test_sound_info.cpp
               src/utils/math/test_goom_rand.cpp
               src/utils/math/test_misc.cpp
               src/utils/math/test_randutils.cpp
               src/utils/test_enum_utils.cpp
               src/utils/test_parallel_utils.cpp
               src/utils/test_strutils.cpp
               src/utils/test_t_values.cpp
               src/visual_fx/test_filter_fx.cpp
               )

target_link_libraries(${GOOM_LIB_TESTS_NAME}
                      PRIVATE
                      goom
                      vivid
                      Catch2::Catch2
                      ${CMAKE_THREAD_LIBS_INIT}
                      m
                      pthread
                      stdc++
                      )

target_include_directories(${GOOM_LIB_TESTS_NAME}
                           PRIVATE
                           ${GOOM_LIBS_DIR}/src/goom/include
                           ${GOOM_LIBS_DIR}/src/goom/include/goom
                           ${GOOM_LIBS_DIR}/src/goom/src
                           )
target_include_directories(${GOOM_LIB_TESTS_NAME}
                           SYSTEM PRIVATE
                           ${GOOM_LIBS_DIR}/lib/libdivide
                           ${fmt_SOURCE_DIR}/include
                           ${magic_enum_INCLUDE_DIR}
                           )

set_project_warnings(${GOOM_LIB_TESTS_NAME})
enable_sanitizers(${GOOM_LIB_TESTS_NAME})
configure_linker(${GOOM_LIB_TESTS_NAME})

#catch_discover_tests(${GOOM_LIB_TESTS_NAME})
add_test(NAME ${GOOM_LIB_TESTS_NAME}
         COMMAND ${GOOM_LIB_TESTS_NAME})

get_target_property(${GOOM_LIB_TESTS_NAME} ${GOOM_LIB_TESTS_NAME} COMPILE_OPTIONS)
get_target_property(${GOOM_LIB_TESTS_NAME} ${GOOM_LIB_TESTS_NAME} COMPILE_FEATURES)
get_target_property(${GOOM_LIB_TESTS_NAME} ${GOOM_LIB_TESTS_NAME} LINK_OPTIONS)

message(STATUS "Goom Lib Tests: C++ standard = \"${CMAKE_CXX_STANDARD}\".")
message(STATUS "Goom Lib Tests: C++ compile features = \"${${GOOM_LIB_TESTS_NAME}_compile_features}\".")
message(STATUS "Goom Lib Tests: C++ compile options = \"${${GOOM_LIB_TESTS_NAME}_compile_options}\".")
message(STATUS "Goom Lib Tests: C++ link options = \"${${GOOM_LIB_TESTS_NAME}_link_options}\".")
