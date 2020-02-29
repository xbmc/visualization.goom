cmake_minimum_required(VERSION 3.5)
project(goom)

if(WIN32)
 add_definitions(-D_WIN32PC)
endif()

set(GOOM_SOURCES src/goomsl_yacc.c
                 src/goomsl_lex.c
                 src/goomsl_lex.l
                 src/goomsl.c
                 src/goomsl_hash.c
                 src/goomsl_heap.c
                 src/goom_tools.c
                 src/config_param.c
                 src/convolve_fx.c
                 src/filters.c
                 src/flying_stars_fx.c
                 src/gfontlib.c
                 src/gfontrle.c
                 src/goom_core.c
                 src/graphic.c
                 src/ifs.c
                 src/lines.c
                 src/mathtools.c
                 src/mmx.c
                 src/sound_tester.c
                 src/surf3d.c
                 src/tentacle3d.c
                 src/plugin_info.c
                 src/v3d.c
                 src/drawmethods.c
                 src/cpu_info.c
                 src/xmmx.c)

set(GOOM_HEADERS src/goom.h
                 src/goom_plugin_info.h
                 src/goom_typedefs.h
                 src/goom_graphic.h
                 src/goom_config_param.h
                 src/goom_visual_fx.h
                 src/goom_filters.h
                 src/goom_tools.h
                 src/goomsl.h
                 src/goomsl_hash.h
                 src/goomsl_heap.h
                 src/goom_tools.h
                 src/goom_config.h
                 src/tentacle3d.h
                 src/mmx.h
                 src/xmmx.h)

add_library(goom STATIC ${GOOM_SOURCES} ${GOOM_HEADERS})
set_property(TARGET goom PROPERTY POSITION_INDEPENDENT_CODE ON)
set_property(TARGET goom PROPERTY C_STANDARD 11)
