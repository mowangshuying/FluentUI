cmake_minimum_required(VERSION 3.19)

project(qmsetup VERSION 0.1.1.1)

# ----------------------------------
# Configure Options
# ----------------------------------
option(QMSETUP_VCPKG_TOOLS_HINT "Install executables to tools directory" OFF)
option(QMSETUP_STATIC_RUNTIME "Static link runtime libraries on Windows" ON)

# ----------------------------------
# CMake Settings
# ----------------------------------
if(NOT DEFINED CMAKE_RUNTIME_OUTPUT_DIRECTORY)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
endif()

if(NOT DEFINED CMAKE_LIBRARY_OUTPUT_DIRECTORY)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
endif()

if(NOT DEFINED CMAKE_ARCHIVE_OUTPUT_DIRECTORY)
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
endif()

if(MSVC)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /manifest:no")
    set(CMAKE_MODULE_LINKER_FLAGS "${CMAKE_MODULE_LINKER_FLAGS} /manifest:no")
    set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} /manifest:no")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /utf-8")

    if(NOT DEFINED CMAKE_DEBUG_POSTFIX)
        set(CMAKE_DEBUG_POSTFIX "d")
    endif()
endif()

# ----------------------------------
# Project Variables
# ----------------------------------
set(QMSETUP_VERSION ${PROJECT_VERSION})
set(QMSETUP_INSTALL_NAME ${PROJECT_NAME})
set(QMSETUP_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})

include(cmake/QMSetupAPI.cmake)

add_subdirectory(src)