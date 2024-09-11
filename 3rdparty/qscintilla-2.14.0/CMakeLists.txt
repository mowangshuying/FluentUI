cmake_minimum_required(VERSION 3.20)

project(qscintilla
    VERSION "2.14.0"
    DESCRIPTION "QScintilla - a Port to Qt v5 and Qt v6 of Scintilla."
    HOMEPAGE_URL "https://qscintilla.com/"
)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Gui Widgets PrintSupport Concurrent Network)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Gui Widgets PrintSupport Concurrent Network)

aux_source_directory(${PROJECT_SOURCE_DIR}/src SRC)
aux_source_directory(${PROJECT_SOURCE_DIR}/scintilla/lexers SRC)
aux_source_directory(${PROJECT_SOURCE_DIR}/scintilla/lexlib SRC)
aux_source_directory(${PROJECT_SOURCE_DIR}/scintilla/src SRC)
aux_source_directory(${PROJECT_SOURCE_DIR}/scintilla/boostregex SRC)

file(GLOB MOC_HEADER ${PROJECT_SOURCE_DIR}/src/Qsci/*.h)
add_library(${PROJECT_NAME} STATIC ${SRC} ${MOC_HEADER})

target_compile_definitions(${PROJECT_NAME} PRIVATE SCINTILLA_QT SCI_LEXER INCLUDE_DEPRECATED_FEATURES)
target_include_directories(${PROJECT_NAME} PRIVATE
    ${PROJECT_SOURCE_DIR}/scintilla/lexlib
    ${PROJECT_SOURCE_DIR}/scintilla/boostregex
)

target_include_directories(${PROJECT_NAME} PUBLIC
    ${PROJECT_SOURCE_DIR}/src
    ${PROJECT_SOURCE_DIR}/src/Qsci
    ${PROJECT_SOURCE_DIR}/scintilla/src
    ${PROJECT_SOURCE_DIR}/scintilla/include)

target_link_libraries(${PROJECT_NAME} Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Gui Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Concurrent Qt${QT_VERSION_MAJOR}::Network Qt${QT_VERSION_MAJOR}::PrintSupport)

if("${CMAKE_BUILD_TYPE}" STREQUAL "Release")
    set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "qscintilla")
else()
    set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "qscintillad")
endif()

