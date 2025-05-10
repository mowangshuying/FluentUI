
set(FRAMELESSHELPER_BUILD_STATIC ON)
set(FRAMELESSHELPER_BUILD_QUICK OFF)
set(FRAMELESSHELPER_NO_INSTALL ON)
add_subdirectory("framelesshelper-2.5.0")

set(TGT framelesshelper)
add_library(framelesshelper INTERFACE)
target_link_libraries(${TGT}
    INTERFACE
    FramelessHelperCore
    FramelessHelperWidgets
)


set(QWINDOWKIT_BUILD_STATIC ON)
set(QWINDOWKIT_BUILD_QUICK OFF)
set(QWINDOWKIT_INSTALL OFF)
add_subdirectory("qwindowkit-1.3.2")

set(TGT qwindowkit)
add_library(qwindowkit INTERFACE)
target_link_libraries(${TGT}
    INTERFACE
    QWKCore
    QWKWidgets
)

add_subdirectory("qscintilla-2.14.0")
add_subdirectory("qrcode-1.4.0")

