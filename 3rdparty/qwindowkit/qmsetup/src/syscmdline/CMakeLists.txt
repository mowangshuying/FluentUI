cmake_minimum_required(VERSION 3.17)

project(syscmdline VERSION 0.0.2.1 LANGUAGES C CXX)

# ----------------------------------
# Build Options
# ----------------------------------
option(SYSCMDLINE_BUILD_STATIC "Build static library" ON)
option(SYSCMDLINE_BUILD_EXAMPLES "Build examples" OFF)
option(SYSCMDLINE_BUILD_TESTS "Build test cases" OFF)
option(SYSCMDLINE_FORCE_VALIDITY_CHECK "Force to enable validity check" OFF)
option(SYSCMDLINE_INSTALL "Install library" ON)

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

if(NOT DEFINED CMAKE_BUILD_SHARE_DIR)
    set(CMAKE_BUILD_SHARE_DIR ${CMAKE_BINARY_DIR}/share)
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

if(SYSCMDLINE_INSTALL)
    include(GNUInstallDirs)
    include(CMakePackageConfigHelpers)
endif()

# ----------------------------------
# Project Variables
# ----------------------------------
set(SYSCMDLINE_VERSION ${PROJECT_VERSION})
set(SYSCMDLINE_INSTALL_NAME ${PROJECT_NAME})

# ----------------------------------
# Main Project
# ----------------------------------
if(TRUE)
    # Add library
    if(SYSCMDLINE_BUILD_STATIC)
        add_library(${PROJECT_NAME} STATIC)
        target_compile_definitions(${PROJECT_NAME} PUBLIC SYSCMDLINE_STATIC)
    else()
        add_library(${PROJECT_NAME} SHARED)
    endif()

    add_library(${PROJECT_NAME}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

    # Add sources
    file(GLOB_RECURSE _src include/syscmdline/*.h src/*.h src/*.cpp)
    target_sources(${PROJECT_NAME} PRIVATE ${_src})

    # Add features
    target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20 cxx_std_17)

    # Add options
    target_compile_definitions(${PROJECT_NAME} PRIVATE SYSCMDLINE_LIBRARY)

    if(SYSCMDLINE_FORCE_VALIDITY_CHECK)
        target_compile_definitions(${PROJECT_NAME} PRIVATE SYSCMDLINE_ENABLE_VALIDITY_CHECK)
    else()
        target_compile_definitions(${PROJECT_NAME} PRIVATE
            "$<$<CONFIG:Debug>:SYSCMDLINE_ENABLE_VALIDITY_CHECK>"
        )
    endif()

    # Include directories
    target_include_directories(${PROJECT_NAME} PUBLIC
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
    )
    target_include_directories(${PROJECT_NAME} PRIVATE include/syscmdline)

    # Add platform specific
    if(WIN32)
        set(RC_DESCRIPTION "C++ Advanced Command Line Parser")
        set(RC_COPYRIGHT "Copyright 2023 SineStriker")
        include("cmake/winrc.cmake")
    endif()

    # if(MSVC)
    # if(${CMAKE_BUILD_TYPE} STREQUAL "Release")
    # target_compile_options(${PROJECT_NAME} PRIVATE /GL /Os)
    # target_link_options(${PROJECT_NAME} PRIVATE /OPT:REF /OPT:ICF /OPT:LBR)
    # endif()
    # endif()
    if(SYSCMDLINE_INSTALL)
        target_include_directories(${PROJECT_NAME} PUBLIC
            "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
        )

        install(TARGETS ${PROJECT_NAME}
            EXPORT ${SYSCMDLINE_INSTALL_NAME}Targets
            RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}" OPTIONAL
            LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}" OPTIONAL
            ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}" OPTIONAL
        )
    endif()
endif()

if(SYSCMDLINE_BUILD_TESTS)
    add_subdirectory(tests)
endif()

if(SYSCMDLINE_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()

if(SYSCMDLINE_INSTALL)
    # Add install target
    set(_install_dir ${CMAKE_INSTALL_LIBDIR}/cmake/${SYSCMDLINE_INSTALL_NAME})

    # Add version file
    write_basic_package_version_file(
        "${CMAKE_CURRENT_BINARY_DIR}/${SYSCMDLINE_INSTALL_NAME}ConfigVersion.cmake"
        VERSION ${PROJECT_VERSION}
        COMPATIBILITY AnyNewerVersion
    )

    # Add configuration file
    configure_package_config_file(
        ${CMAKE_CURRENT_LIST_DIR}/${SYSCMDLINE_INSTALL_NAME}Config.cmake.in
        "${CMAKE_CURRENT_BINARY_DIR}/${SYSCMDLINE_INSTALL_NAME}Config.cmake"
        INSTALL_DESTINATION ${_install_dir}
        NO_CHECK_REQUIRED_COMPONENTS_MACRO
    )

    # Install cmake files
    install(FILES
        "${CMAKE_CURRENT_BINARY_DIR}/${SYSCMDLINE_INSTALL_NAME}Config.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/${SYSCMDLINE_INSTALL_NAME}ConfigVersion.cmake"
        DESTINATION ${_install_dir}
    )

    # Install cmake targets files
    install(EXPORT ${SYSCMDLINE_INSTALL_NAME}Targets
        FILE "${SYSCMDLINE_INSTALL_NAME}Targets.cmake"
        NAMESPACE syscmdline::
        DESTINATION ${_install_dir}
    )

    install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
        FILES_MATCHING PATTERN "*.h"
    )
endif()