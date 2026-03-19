
set(FRAMELESSHELPER_BUILD_STATIC ON)
set(FRAMELESSHELPER_BUILD_QUICK OFF)
set(FRAMELESSHELPER_NO_INSTALL ON)
add_subdirectory("framelesshelper")

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
add_subdirectory("qwindowkit")

set(TGT qwindowkit)
add_library(qwindowkit INTERFACE)
target_link_libraries(${TGT}
    INTERFACE
    QWKCore
    QWKWidgets
)

add_subdirectory("qscintilla")
add_subdirectory("qrcode")
add_subdirectory("cmark")
add_subdirectory("Qt-Advanced-Docking-System")

