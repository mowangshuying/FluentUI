set(TGT framelesshelper)

# add_library(${TGT} UNKNOWN IMPORTED GLOBAL)
# set_target_properties(${TGT} PROPERTIES
#     INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_CURRENT_LIST_DIR}/include"
#     # IMPORTED_IMPLIB_DEBUG "${CMAKE_CURRENT_LIST_DIR}/lib/debug/FramelessHelperCore64d.lib"
#     # IMPORTED_IMPLIB_RELEASE "${CMAKE_CURRENT_LIST_DIR}/lib/release/FramelessHelperCore64.lib"
#     # IMPORTED_LOCATION_DEBUG "${CMAKE_CURRENT_LIST_DIR}/bin/debug/FramelessHelperCore64d.dll"
#     # IMPORTED_LOCATION_RELEASE "${CMAKE_CURRENT_LIST_DIR}/bin/release/FramelessHelperCore64.dll"
#     IMPORTED_LOCATION_DEBUG "${CMAKE_CURRENT_LIST_DIR}/lib/debug/FramelessHelperCore64d.lib,${CMAKE_CURRENT_LIST_DIR}/lib/debug/FramelessHelperWidgets64d.lib"
#     IMPORTED_LOCATION_RELEASE "${CMAKE_CURRENT_LIST_DIR}/lib/release/FramelessHelperCore64.lib"
# )

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
