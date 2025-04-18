cmake_minimum_required(VERSION 3.20)

project(FluWinGallery VERSION 0.4.0 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/bin")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "${PROJECT_BINARY_DIR}/bin")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE "${PROJECT_BINARY_DIR}/bin")

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Svg)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Svg)
# qt_standard_project_setup()

add_subdirectory("3rdparty")
add_subdirectory("FluControls")
add_subdirectory("FluExamples")
add_subdirectory("FluIconTool")
add_subdirectory("FluUtils")
add_subdirectory("FluWinGallery")
# add_subdirectory("res")
# add_subdirectory("StyleSheet")

add_custom_target(resource_copy
    COMMAND ${CMAKE_COMMAND} -E copy_directory_if_different
    ${CMAKE_CURRENT_SOURCE_DIR}/res
    ${PROJECT_BINARY_DIR}/res
    COMMAND ${CMAKE_COMMAND} -E copy_directory_if_different
    ${CMAKE_CURRENT_SOURCE_DIR}/StyleSheet
    ${PROJECT_BINARY_DIR}/StyleSheet
    COMMAND ${CMAKE_COMMAND} -E copy_directory_if_different
    ${CMAKE_CURRENT_SOURCE_DIR}/code
    ${PROJECT_BINARY_DIR}/code
    COMMAND ${CMAKE_COMMAND} -E copy_directory_if_different
    ${CMAKE_CURRENT_SOURCE_DIR}/i18n
    ${PROJECT_BINARY_DIR}/i18n
    COMMAND ${CMAKE_COMMAND} -E copy_directory_if_different
    ${CMAKE_CURRENT_SOURCE_DIR}/config
    ${PROJECT_BINARY_DIR}/config
)

install(DIRECTORY res
    DESTINATION .
)

install(DIRECTORY StyleSheet
    DESTINATION .
)

install(DIRECTORY code
    DESTINATION .
)

install(DIRECTORY config
    DESTINATION .
)

install(DIRECTORY i18n
    DESTINATION .
)

set(CPACK_PACKAGE_FILE_NAME "FluGalleryWin64Msvc")
set(CPACK_INCLUDE_TOPLEVEL_DIRECTORY OFF)

include(InstallRequiredSystemLibraries)
set(CPACK_GENERATOR "ZIP")
include(CPack)

message(STATUS "Configuration Options Summary --
    Target system:          ${CMAKE_SYSTEM}
    Compiler:
        Build type:         ${CMAKE_BUILD_TYPE}
        C compiler:         ${CMAKE_C_COMPILER}
        Qt version:         ${QT_DEFAULT_MAJOR_VERSION}
        Qt toolchain:       ${QT_QMAKE_EXECUTABLE}")
