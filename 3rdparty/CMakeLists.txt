
set(FRAMELESSHELPER_BUILD_STATIC ON)
set(FRAMELESSHELPER_BUILD_QUICK OFF)
add_subdirectory("framelesshelper-2.5.0")

set(TGT framelesshelper)
add_library(framelesshelper INTERFACE)
target_link_libraries(${TGT}
    INTERFACE
    FramelessHelperCore
    FramelessHelperWidgets
)
