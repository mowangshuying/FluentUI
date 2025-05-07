include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

if(QMSETUP_STATIC_RUNTIME)
    # To avoid a command execution that can't find the library, we choose to link compiler runtime statically
    if(MINGW)
        add_link_options(-static -static-libgcc -static-libstdc++)
    elseif(MSVC)
        add_compile_options(/MT)
    endif()
endif()

# Get syscmdline
find_package(syscmdline QUIET)

if(NOT TARGET syscmdline::syscmdline)
    set(SYSCMDLINE_INSTALL off)
    add_subdirectory(syscmdline)
endif()

# Add subdirectories
add_subdirectory(corecmd)

# Add headers
set(_corelib_name library)
add_library(${_corelib_name} INTERFACE)
target_include_directories(${_corelib_name} INTERFACE
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../include>"
    "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
    "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/${QMSETUP_INSTALL_NAME}>"
)

install(TARGETS ${_corelib_name}
    EXPORT ${QMSETUP_INSTALL_NAME}Targets
)

if(TRUE)
    # Add install target
    set(_install_dir ${CMAKE_INSTALL_LIBDIR}/cmake/${QMSETUP_INSTALL_NAME})

    # Add version file
    write_basic_package_version_file(
        "${CMAKE_CURRENT_BINARY_DIR}/${QMSETUP_INSTALL_NAME}ConfigVersion.cmake"
        VERSION ${QMSETUP_VERSION}
        COMPATIBILITY AnyNewerVersion
    )

    # Add configuration file
    configure_package_config_file(
        ${CMAKE_CURRENT_LIST_DIR}/${QMSETUP_INSTALL_NAME}Config.cmake.in
        "${CMAKE_CURRENT_BINARY_DIR}/${QMSETUP_INSTALL_NAME}Config.cmake"
        INSTALL_DESTINATION ${_install_dir}
        NO_CHECK_REQUIRED_COMPONENTS_MACRO
    )

    # Install cmake files
    install(FILES
        "${CMAKE_CURRENT_BINARY_DIR}/${QMSETUP_INSTALL_NAME}Config.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/${QMSETUP_INSTALL_NAME}ConfigVersion.cmake"
        DESTINATION ${_install_dir}
    )

    # Install cmake targets files
    install(EXPORT ${QMSETUP_INSTALL_NAME}Targets
        FILE "${QMSETUP_INSTALL_NAME}Targets.cmake"
        NAMESPACE qmsetup::
        DESTINATION ${_install_dir}
    )

    # Install headers
    install(DIRECTORY ../include/
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    )

    # Install cmake modules
    install(DIRECTORY ../cmake/
        DESTINATION ${_install_dir}/cmake
    )
endif()