#[[
    Warning: This module is private, may be modified or removed in the future, please use with caution.
]] #

if(NOT DEFINED QMSETUP_PACKAGE_BUILD_TYPE)
    set(QMSETUP_PACKAGE_BUILD_TYPE "Release")
endif()

include_guard(DIRECTORY)

#[[
    Install external package at configuration phase.

    qm_install_package(<name>
        [SOURCE_DIR <dir>]
        [BUILD_TREE_DIR <dir>]
        [INSTALL_DIR <dir>]
        [CMAKE_PACKAGE_SUBDIR <subdir>]

        [BUILD_TYPE <type>]
        [CONFIGURE_ARGS <arg...>]
        
        [RESULT_PATH <VAR>]
    )
]] #
function(qm_install_package _name)
    set(options)
    set(oneValueArgs SOURCE_DIR BUILD_TREE_DIR INSTALL_DIR CMAKE_PACKAGE_SUBDIR BUILD_TYPE RESULT_PATH)
    set(multiValueArgs CONFIGURE_ARGS)
    cmake_parse_arguments(FUNC "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    # Directories
    if(NOT FUNC_SOURCE_DIR)
        message(FATAL_ERROR "pre_install_package: SOURCE_DIR is not spefified")
    endif()

    set(_src_dir ${FUNC_SOURCE_DIR})

    if(FUNC_BUILD_TREE_DIR)
        set(_build_tree_dir ${FUNC_BUILD_TREE_DIR})
    else()
        set(_build_tree_dir ${CMAKE_BINARY_DIR}/_build)
    endif()

    if(FUNC_INSTALL_DIR)
        set(_install_dir ${FUNC_INSTALL_DIR})
    else()
        set(_install_dir ${CMAKE_BINARY_DIR}/_install)
    endif()

    if(FUNC_CMAKE_PACKAGE_SUBDIR)
        set(_cmake_subdir ${FUNC_CMAKE_PACKAGE_SUBDIR})
    else()
        include(GNUInstallDirs)
        set(_cmake_subdir "${CMAKE_INSTALL_LIBDIR}/cmake/${_name}")
    endif()

    # Build types
    if(FUNC_BUILD_TYPE)
        set(_build_type -DCMAKE_BUILD_TYPE=${FUNC_BUILD_TYPE})
    elseif(CMAKE_BUILD_TYPE)
        set(_build_type -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE})
    elseif(NOT CMAKE_CONFIGURATION_TYPES)
        set(_build_type -DCMAKE_BUILD_TYPE=${QMSETUP_PACKAGE_BUILD_TYPE})
    else()
        set(_build_type)
    endif()

    if(FUNC_BUILD_TYPE)
        set(_build_types ${FUNC_BUILD_TYPE})
    else()
        set(_build_types ${QMSETUP_PACKAGE_BUILD_TYPE})
    endif()

    # Do it
    set(_install_cmake_dir ${_install_dir}/${_cmake_subdir})
    set(_build_dir ${_build_tree_dir}/${_name})

    if(NOT IS_DIRECTORY ${_install_cmake_dir})
        # Determine generator
        set(_extra_args)

        if(CMAKE_GENERATOR)
            set(_extra_args -G "${CMAKE_GENERATOR}")
        endif()

        if(CMAKE_GENERATOR_PLATFORM)
            set(_extra_args -A "${CMAKE_GENERATOR_PLATFORM}")
        endif()

        # Remove old build directory
        if(IS_DIRECTORY ${_build_dir})
            file(REMOVE_RECURSE ${_build_dir})
        endif()

        file(MAKE_DIRECTORY ${_build_tree_dir})

        # Configure
        message(STATUS "Configuring ${_name}...")
        set(_log_file ${_build_tree_dir}/${_name}_configure.log)
        execute_process(
            COMMAND ${CMAKE_COMMAND} -S ${_src_dir} -B ${_build_dir}
            ${_extra_args} ${_build_type}
            "-DCMAKE_INSTALL_PREFIX=${_install_dir}" ${FUNC_CONFIGURE_ARGS}
            OUTPUT_FILE ${_log_file}
            ERROR_FILE ${_log_file}
            RESULT_VARIABLE _code
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        )

        if(NOT ${_code} EQUAL 0)
            message(FATAL_ERROR "Configure failed, check \"${_log_file}\"")
        endif()

        # Build
        foreach(_item IN LISTS _build_types)
            message(STATUS "Building ${_name} (${_item})...")
            set(_log_file ${_build_tree_dir}/${_name}_build-${_item}.log)
            execute_process(
                COMMAND ${CMAKE_COMMAND} --build ${_build_dir} --config ${_item} --parallel
                OUTPUT_FILE ${_log_file}
                ERROR_FILE ${_log_file}
                RESULT_VARIABLE _code
                WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
            )

            if(NOT ${_code} EQUAL 0)
                message(FATAL_ERROR "Build failed, check \"${_log_file}\"")
            endif()
        endforeach()

        # Install
        foreach(_item IN LISTS _build_types)
            message(STATUS "Installing ${_name} (${_item})...")
            set(_log_file ${_build_tree_dir}/${_name}_install-${_item}.log)
            execute_process(
                COMMAND ${CMAKE_COMMAND} --build ${_build_dir} --config ${_item} --target install
                OUTPUT_FILE ${_log_file}
                ERROR_FILE ${_log_file}
                RESULT_VARIABLE _code
                WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
            )

            if(NOT ${_code} EQUAL 0)
                message(FATAL_ERROR "Install failed, check \"${_log_file}\"")
            endif()
        endforeach()
    endif()

    if(FUNC_RESULT_PATH)
        set(${FUNC_RESULT_PATH} ${_install_cmake_dir} PARENT_SCOPE)
    endif()
endfunction()