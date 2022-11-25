cmake_minimum_required(VERSION 3.15)

project(Goom LANGUAGES CXX)

if (NOT GLM_INCLUDE_DIR)
    message(FATAL_ERROR "\"GLM_INCLUDE_DIR\" must be defined.")
endif ()

if (WIN32)
    add_definitions(-D_WIN32PC)
endif ()

if (DEFINED GOOM_LOGGING)
    MESSAGE(STATUS "Goom: Logging by default is on.")
else ()
    add_definitions(-DNO_LOGGING)
    MESSAGE(STATUS "Goom: Logging turned off.")
endif ()


add_library(goom
            STATIC
            include/goom/goom_config.h
            include/goom/goom_types.h
            src/color/color_data/color_data_maps.cpp
            src/color/color_data/extra_color_groups.cpp
            src/color/color_adjustment.cpp
            src/color/color_maps.cpp
            src/color/color_maps_grid.cpp
            src/color/color_utils.cpp
            src/color/random_color_maps.cpp
            src/color/random_color_maps_groups.cpp
            src/color/random_color_maps_manager.cpp
            src/control/all_standard_visual_fx.cpp
            src/control/goom_all_visual_fx.cpp
            src/control/goom_effects.h
            src/control/goom_events.cpp
            src/control/goom_image_buffers.cpp
            src/control/goom_message_displayer.cpp
            src/control/goom_music_settings_reactor.cpp
            src/control/goom_random_state_handler.cpp
            src/control/goom_sound_events.cpp
            src/control/goom_state_dump.cpp
            src/control/goom_state_handler.cpp
            src/control/goom_state_monitor.cpp
            src/control/goom_states.cpp
            src/control/goom_title_displayer.cpp
            src/control/state_and_filter_consts.h
            src/control/visual_fx_color_maps.h
            src/control/visual_fx_color_matched_sets.cpp
            src/control/visual_fx_weighted_color_maps.cpp
            src/draw/draw_methods.cpp
            src/draw/goom_draw.cpp
            src/draw/goom_draw_to_buffer.cpp
            src/draw/goom_draw_to_container.cpp
            src/draw/goom_draw_to_many.cpp
            src/draw/text_draw.cpp
            src/draw/thick_lines.cpp
            src/filter_fx/after_effects/after_effects.cpp
            src/filter_fx/after_effects/after_effects_states.cpp
            src/filter_fx/after_effects/after_effects_types.h
            src/filter_fx/after_effects/hypercos.cpp
            src/filter_fx/after_effects/image_velocity.cpp
            src/filter_fx/after_effects/noise.cpp
            src/filter_fx/after_effects/planes.cpp
            src/filter_fx/after_effects/rotation.cpp
            src/filter_fx/after_effects/tan_effect.cpp
            src/filter_fx/after_effects/xy_lerp_effect.cpp
            src/filter_fx/after_effects/zoom_vector_after_effects.cpp
            src/filter_fx/filter_effects/amulet.cpp
            src/filter_fx/common_types.h
            src/filter_fx/filter_effects/crystal_ball.cpp
            src/filter_fx/filter_effects/distance_field.cpp
            src/filter_fx/filter_effects/exp_reciprocal.cpp
            src/filter_fx/filter_effects/image_zoom_in_coeffs.cpp
            src/filter_fx/filter_effects/scrunch.cpp
            src/filter_fx/filter_effects/speedway.cpp
            src/filter_fx/filter_effects/uniform_zoom_in_coefficients_effect.h
            src/filter_fx/filter_effects/wave.cpp
            src/filter_fx/filter_effects/y_only.cpp
            src/filter_fx/filter_effects/zoom_in_coefficients_effect_factory.cpp
            src/filter_fx/filter_effects/zoom_vector_effects.cpp
            src/filter_fx/filter_utils/image_displacement.cpp
            src/filter_fx/filter_utils/image_displacement_list.cpp
            src/filter_fx/filter_utils/zoom_coord_transforms.h
            src/filter_fx/filter_utils/zoom_filter_coefficients.h
            src/filter_fx/filter_utils/zoom_transform_buffers.cpp
            src/filter_fx/filter_consts.h
            src/filter_fx/filter_buffer_color_info.cpp
            src/filter_fx/filter_buffers.cpp
            src/filter_fx/filter_buffers_service.cpp
            src/filter_fx/filter_colors_service.cpp
            src/filter_fx/filter_settings_service.cpp
            src/filter_fx/filter_speed.h
            src/filter_fx/filter_zoom_vector.cpp
            src/filter_fx/normalized_coords.h
            src/filter_fx/zoom_in_coefficients_effect.h
            src/filter_fx/zoom_filter_fx.cpp
            src/utils/graphics/bezier_drawer.cpp
            src/utils/graphics/image_bitmaps.cpp
            src/utils/graphics/line_clipper.h
            src/utils/graphics/pixel_utils.h
            src/utils/graphics/small_image_bitmaps.cpp
            src/utils/math/damping_functions.cpp
            src/utils/math/goom_rand.h
            src/utils/math/goom_rand_base.h
            src/utils/math/math20.h
            src/utils/math/misc.h
            src/utils/math/parametric_functions2d.cpp
            src/utils/math/paths.cpp
            src/utils/math/randutils.cpp
            src/utils/math/transform2d.h
            src/utils/text/drawable_text.cpp
            src/utils/adaptive_exposure.cpp
            src/utils/array_utils.h
            src/utils/build_time.cpp
            src/utils/buffer_saver.h
            src/utils/buffer_view.h
            src/utils/date_utils.cpp
            src/utils/enum_utils.h
            src/utils/format_utils.h
            src/utils/logging.cpp
            src/utils/name_value_pairs.cpp
            src/utils/propagate_const.h
            src/utils/step_speed.h
            src/utils/stopwatch.h
            src/utils/strutils.cpp
            src/utils/t_values.cpp
            src/utils/thread_pool.cpp
            src/visual_fx/circles/bitmap_getter_base.h
            src/visual_fx/circles/bitmap_getter.cpp
            src/visual_fx/circles/circle.cpp
            src/visual_fx/circles/circle_params_builder.cpp
            src/visual_fx/circles/circles.cpp
            src/visual_fx/circles/dot_diameters.cpp
            src/visual_fx/circles/dot_paths.cpp
            src/visual_fx/flying_stars/star_drawer.cpp
            src/visual_fx/flying_stars/star_types.cpp
            src/visual_fx/flying_stars/stars.cpp
            src/visual_fx/fx_utils/dot_drawer.cpp
            src/visual_fx/fx_utils/lines.cpp
            src/visual_fx/ifs/colorizer.cpp
            src/visual_fx/ifs/fractal.cpp
            src/visual_fx/ifs/fractal_hits.cpp
            src/visual_fx/ifs/ifs_types.h
            src/visual_fx/ifs/low_density_blurrer.cpp
            src/visual_fx/ifs/similitudes.cpp
            src/visual_fx/lines/line_morph.cpp
            src/visual_fx/lines/line_types.h
            src/visual_fx/shaders/high_contrast.cpp
            src/visual_fx/shaders/hue_shift_lerper.cpp
            src/visual_fx/shapes/bezier_flower.cpp
            src/visual_fx/shapes/shape_parts.cpp
            src/visual_fx/shapes/shape_paths.cpp
            src/visual_fx/shapes/shapes.cpp
            src/visual_fx/tentacles/circles_tentacle_layout.cpp
            src/visual_fx/tentacles/tentacle_driver.cpp
            src/visual_fx/tentacles/tentacle_plotter.cpp
            src/visual_fx/tentacles/tentacle2d.cpp
            src/visual_fx/tentacles/tentacle3d.cpp
            src/visual_fx/tubes/tube_data.cpp
            src/visual_fx/tubes/tubes.cpp
            src/visual_fx/circles_fx.cpp
            src/visual_fx/flying_stars_fx.cpp
            src/visual_fx/fx_helper.h
            src/visual_fx/goom_dots_fx.cpp
            src/visual_fx/goom_visual_fx.h
            src/visual_fx/ifs_dancers_fx.cpp
            src/visual_fx/image_fx.cpp
            src/visual_fx/lines_fx.cpp
            src/visual_fx/shader_fx.cpp
            src/visual_fx/shapes_fx.cpp
            src/visual_fx/tentacles_fx.cpp
            src/visual_fx/tubes_fx.cpp
            src/goom_control.cpp
            src/goom_graphic.cpp
            src/goom_version.cpp
            src/sound_info.cpp
            )

target_include_directories(goom
                           PUBLIC
                           ${GOOM_LIBS_DIR}/src/goom/include
                           ${GOOM_LIBS_DIR}/src/goom/src/utils
                           PRIVATE
                           ${GOOM_LIBS_DIR}/src/goom/include/goom
                           ${GOOM_LIBS_DIR}/src/goom/src
                           )

target_include_directories(goom
                           SYSTEM PRIVATE
                           ${GOOM_LIBS_DIR}/src/bezier/include
                           ${GOOM_LIBS_DIR}/src/vivid/include
                           ${GOOM_LIBS_DIR}/lib/libdivide
                           ${GOOM_LIBS_DIR}/lib/fmt/include
                           ${fmt_SOURCE_DIR}/include
                           ${magic_enum_INCLUDE_DIR}
                           ${FREETYPE_INCLUDE_DIRS}
                           ${GLM_INCLUDE_DIR}
                           )

set_project_warnings(goom)
enable_sanitizers(goom)

set_target_properties(goom
                      PROPERTIES
                      POSITION_INDEPENDENT_CODE ${POS_INDEP_CODE}
                      )

get_target_property(goom_compile_options goom COMPILE_OPTIONS)
get_target_property(goom_compile_features goom COMPILE_FEATURES)

message(STATUS "Goom: C++ standard = \"${CMAKE_CXX_STANDARD}\".")
message(STATUS "Goom: C++ compile features = \"${goom_compile_features}\".")
message(STATUS "Goom: C++ compile options = \"${goom_compile_options}\".")
message(STATUS "Goom: GOOM_LIBS_DIR = \"${GOOM_LIBS_DIR}\".")
message(STATUS "Goom: GLM_INCLUDE_DIR = \"${GLM_INCLUDE_DIR}\".")
message(STATUS "Goom: THIRD_PARTY_INCLUDE_DIR = \"${THIRD_PARTY_INCLUDE_DIR}\".")
message(STATUS "Goom: FREETYPE_INCLUDE_DIRS = \"${FREETYPE_INCLUDE_DIRS}\".")
message(STATUS "Goom: magic_enum_INCLUDE_DIR = \"${magic_enum_INCLUDE_DIR}\".")
message(STATUS "Goom: fmt_SOURCE_DIR = \"${fmt_SOURCE_DIR}\".")
