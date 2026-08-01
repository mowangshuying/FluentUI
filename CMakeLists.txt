cmake_minimum_required(VERSION 3.20)

project(FluentUI VERSION 1.0.8 LANGUAGES CXX)


option(USE_QRC "Build With qrc" TRUE)
option(BUILD_GALLERY "Build Gallery" TRUE)
option(BUILD_PYTHON_BINDINGS "Build Python bindings for PySide6" OFF)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/bin")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "${PROJECT_BINARY_DIR}/bin")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE "${PROJECT_BINARY_DIR}/bin")


find_package(QT NAMES Qt5 Qt6 REQUIRED COMPONENTS Core)
if(QT_VERSION VERSION_GREATER_EQUAL "6.2")
find_package(QT NAMES Qt6 REQUIRED COMPONENTS Widgets Svg Charts Core5Compat)
find_package(Qt6 REQUIRED COMPONENTS Widgets Svg Charts Core5Compat)
if (USE_QRC)
if (MSVC_IDE)
	message(STATUS "Qt6Widgets_LIBRARIES: ${Qt6Widgets_LIBRARIES}")
	get_target_property(V_LOCATION ${Qt6Widgets_LIBRARIES} IMPORTED_LOCATION)
	message(STATUS "V_LOCATION: ${V_LOCATION}")
	cmake_path(GET V_LOCATION PARENT_PATH V_RUN_PATH)
	message(STATUS "V_RUN_PATH: ${V_RUN_PATH}")
	set(CMAKE_VS_DEBUGGER_ENVIRONMENT "PATH=%PATH%;${V_RUN_PATH}")
	message(STATUS "CMAKE_VS_DEBUGGER_ENVIRONMENT: ${CMAKE_VS_DEBUGGER_ENVIRONMENT}")
endif()
endif()
else()
find_package(QT NAMES Qt5 REQUIRED COMPONENTS Widgets Svg Charts)
find_package(Qt5 REQUIRED COMPONENTS Widgets Svg Charts)
endif()



# qt_standard_project_setup()

# Generated Qt resource files (qrc_*.cpp) are huge data-only translation units
# (qrc_UtilsEmoijs.cpp is ~100 MB). Compiling them at -O2/-O3 can exhaust
# memory on CI runners, so compile them with no optimization instead.
function(flu_qrc_lowopt resource_name)
    set_source_files_properties(
        "${CMAKE_CURRENT_BINARY_DIR}/qrc_${resource_name}.cpp"
        "${CMAKE_CURRENT_BINARY_DIR}/.qt/rcc/qrc_${resource_name}.cpp"
        PROPERTIES
        COMPILE_OPTIONS "$<$<CXX_COMPILER_ID:MSVC>:/Od>$<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-O0>"
    )
endfunction()

# Third-party libraries: build as static
set(FRAMELESSHELPER_BUILD_STATIC ON CACHE BOOL "" FORCE)
set(FRAMELESSHELPER_BUILD_QUICK OFF CACHE BOOL "" FORCE)
set(QWINDOWKIT_BUILD_STATIC ON CACHE BOOL "" FORCE)
set(BUILD_STATIC ON CACHE BOOL "" FORCE)  # Qt-Advanced-Docking-System

add_subdirectory("3rdparty")
add_subdirectory("controls")
add_subdirectory("examples")

add_subdirectory("utils")

if (BUILD_GALLERY)
add_subdirectory("gallery")
endif()

if (BUILD_PYTHON_BINDINGS)
add_subdirectory("bindings/PySide6")
endif()

# add_subdirectory("res")
# add_subdirectory("stylesheet")

if (NOT USE_QRC)
add_custom_target(resource_copy
    COMMAND ${CMAKE_COMMAND} -E copy_directory_if_different
    ${CMAKE_CURRENT_SOURCE_DIR}/res
    ${PROJECT_BINARY_DIR}/res
    COMMAND ${CMAKE_COMMAND} -E copy_directory_if_different
    ${CMAKE_CURRENT_SOURCE_DIR}/stylesheet
    ${PROJECT_BINARY_DIR}/stylesheet
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

install(DIRECTORY stylesheet
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
endif()

set(CPACK_PACKAGE_FILE_NAME "Gallery")
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
