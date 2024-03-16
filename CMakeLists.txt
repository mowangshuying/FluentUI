cmake_minimum_required(VERSION 3.20)

project(FluWinGallery VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)
qt_standard_project_setup()

add_subdirectory("3rdparty")
add_subdirectory("FluControls")
add_subdirectory("FluExamples")
add_subdirectory("FluIconTool")
add_subdirectory("FluUtils")
add_subdirectory("FluWinGallery")
add_subdirectory("res")
add_subdirectory("StyleSheet")
