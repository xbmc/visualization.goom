cmake_minimum_required( VERSION 3.14 FATAL_ERROR )

project( vivid_tests 
    VERSION 1.1.0
    LANGUAGES CXX
)

add_executable( vivid_tests
    test_main.cpp
    test_conversion_manual.cpp
    test_profiles.cpp
    test_wrapping.cpp
    # test_conversion_fuzzy.cpp	# requires Qt
)

target_compile_options ( vivid_tests
        PRIVATE
        -Wall -Wextra -pedantic -Wno-effc++ -Wno-sign-conversion
        )

target_include_directories( vivid_tests
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        # Need this '..' hack here. Not nice!
        SYSTEM ${GLM_INCLUDE_DIR}/..
)

set_target_properties( vivid_tests
    PROPERTIES
        CXX_STANDARD 14
)

target_link_libraries( vivid_tests
    PRIVATE
        libs::vivid
)
