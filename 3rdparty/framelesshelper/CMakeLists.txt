set(TGT framelesshelper)

if (WIN32)
    add_library(${TGT}_Core SHARED IMPORTED GLOBAL)
    set_target_properties(${TGT}_Core PROPERTIES
        IMPORTED_IMPLIB_DEBUG "${CMAKE_CURRENT_LIST_DIR}/lib/debug/FramelessHelperCore64d.lib"
        IMPORTED_IMPLIB_RELEASE "${CMAKE_CURRENT_LIST_DIR}/lib/release/FramelessHelperCore64.lib"
        IMPORTED_LOCATION_DEBUG "${CMAKE_CURRENT_LIST_DIR}/bin/debug/FramelessHelperCore64d.dll"
        IMPORTED_LOCATION_RELEASE "${CMAKE_CURRENT_LIST_DIR}/bin/release/FramelessHelperCore64.dll"
    )

    add_library(${TGT}_Widgets SHARED IMPORTED GLOBAL)
    set_target_properties(${TGT}_Widgets PROPERTIES
        IMPORTED_IMPLIB_DEBUG "${CMAKE_CURRENT_LIST_DIR}/lib/debug/FramelessHelperWidgets64d.lib"
        IMPORTED_IMPLIB_RELEASE "${CMAKE_CURRENT_LIST_DIR}/lib/release/FramelessHelperWidgets64.lib"
        IMPORTED_LOCATION_DEBUG "${CMAKE_CURRENT_LIST_DIR}/bin/debug/FramelessHelperWidgets64d.dll"
        IMPORTED_LOCATION_RELEASE "${CMAKE_CURRENT_LIST_DIR}/bin/release/FramelessHelperWidgets64.dll"
    )
else()
    add_library(${TGT}_Core UNKNOWN IMPORTED GLOBAL)
    set_target_properties(${TGT}_Core PROPERTIES
        IMPORTED_LOCATION_DEBUG "${CMAKE_CURRENT_LIST_DIR}/lib/debug/FramelessHelperCore64d.lib"
        IMPORTED_LOCATION_RELEASE "${CMAKE_CURRENT_LIST_DIR}/lib/release/FramelessHelperCore64.lib"
    )

    add_library(${TGT}_Widgets UNKNOWN IMPORTED GLOBAL)
    set_target_properties(${TGT}_Widgets PROPERTIES
        IMPORTED_LOCATION_DEBUG "${CMAKE_CURRENT_LIST_DIR}/lib/debug/FramelessHelperWidgets64d.lib"
        IMPORTED_LOCATION_RELEASE "${CMAKE_CURRENT_LIST_DIR}/lib/release/FramelessHelperWidgets64.lib"
    )
endif()

if(NOT CMAKE_BUILD_TYPE)
    set(PATH_CONFIG "DEBUG")
elseif(${CMAKE_BUILD_TYPE} STREQUAL "Release" OR ${CMAKE_BUILD_TYPE} STREQUAL "RelWithDebInfo" OR ${CMAKE_BUILD_TYPE} STREQUAL "MinSizeRel")
    set(PATH_CONFIG "RELEASE")
else()
    set(PATH_CONFIG "DEBUG")
endif()

get_target_property(CORE_PATH ${TGT}_Core IMPORTED_LOCATION_${PATH_CONFIG})
cmake_path(GET CORE_PATH FILENAME CORE_PATH_FILE)
message(STATUS "CORE_PATH: ${PATH_CONFIG}, ${CORE_PATH}, ${CORE_PATH_FILE}")
get_target_property(WIDGETS_PATH ${TGT}_Widgets IMPORTED_LOCATION_${PATH_CONFIG})
cmake_path(GET WIDGETS_PATH FILENAME WIDGETS_PATH_FILE)
message(STATUS "WIDGETS_PATH: ${PATH_CONFIG}, ${WIDGETS_PATH}, ${WIDGETS_PATH_FILE}")

add_custom_command(OUTPUT "${PROJECT_BINARY_DIR}/bin/${CORE_PATH_FILE}"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "${CORE_PATH}"
    "${PROJECT_BINARY_DIR}/bin"
)

add_custom_command(OUTPUT "${PROJECT_BINARY_DIR}/bin/${WIDGETS_PATH_FILE}"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "${WIDGETS_PATH}"
    "${PROJECT_BINARY_DIR}/bin"
)

add_custom_target(${TGT}_AutoCopy
    DEPENDS
    "${PROJECT_BINARY_DIR}/bin/${CORE_PATH_FILE}"
    "${PROJECT_BINARY_DIR}/bin/${WIDGETS_PATH_FILE}"
)

add_library(${TGT} INTERFACE)
target_include_directories(${TGT}
    SYSTEM INTERFACE
    "${CMAKE_CURRENT_LIST_DIR}/include"
)

target_link_libraries(${TGT}
    INTERFACE
    ${TGT}_Core
    ${TGT}_Widgets
)

add_dependencies(${TGT}
    ${TGT}_AutoCopy
)

install(PROGRAMS
    "bin/debug/FramelessHelperCore64d.dll"
    "bin/debug/FramelessHelperWidgets64d.dll"
    DESTINATION bin
    CONFIGURATIONS DEBUG
)

install(PROGRAMS
    "bin/release/FramelessHelperCore64.dll"
    "bin/release/FramelessHelperWidgets64.dll"
    DESTINATION bin
    CONFIGURATIONS RELEASE
)
