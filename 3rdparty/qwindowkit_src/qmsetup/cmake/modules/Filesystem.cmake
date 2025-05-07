if(NOT DEFINED QMSETUP_MODULES_DIR)
    include("${CMAKE_CURRENT_LIST_DIR}/../QMSetupAPI.cmake")
endif()

include_guard(DIRECTORY)

#[[
    Initialize the build output directories of targets and resources.

    qm_init_directories()
]] #
macro(qm_init_directories)
    if(NOT DEFINED QMSETUP_BUILD_DIR)
        set(QMSETUP_BUILD_DIR "${CMAKE_BINARY_DIR}/out-$<LOWER_CASE:${CMAKE_SYSTEM_PROCESSOR}>-$<CONFIG>")
    endif()

    if(NOT DEFINED CMAKE_RUNTIME_OUTPUT_DIRECTORY)
        set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${QMSETUP_BUILD_DIR}/bin)
    endif()

    if(NOT DEFINED CMAKE_LIBRARY_OUTPUT_DIRECTORY)
        set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${QMSETUP_BUILD_DIR}/lib)
    endif()

    if(NOT DEFINED CMAKE_ARCHIVE_OUTPUT_DIRECTORY)
        set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${QMSETUP_BUILD_DIR}/lib)
    endif()

    if(NOT DEFINED CMAKE_BUILD_SHARE_DIR)
        set(CMAKE_BUILD_SHARE_DIR ${QMSETUP_BUILD_DIR}/share)
    endif()
endmacro()

#[[
    Add a resources copying command for whole project.

    qm_add_copy_command(<target>
        [CUSTOM_TARGET <target>]
        [EXTRA_ARGS <args...>]
        [DEPENDS <targets...>]
        [VERBOSE] [SKIP_BUILD] [SKIP_INSTALL]

        SOURCES <file/dir...> [DESTINATION <dir>] [INSTALL_DIR <dir>]
    )

    CUSTOM_TARGET: Use a custom target to control the copy command
    EXTRA_ARGS: Extra arguments to pass to file(INSTALL) statement
    DEPENDS: Targets that the copy command depends

    SOURCES: Source files or directories, directories ending with "/" will have their contents copied
    DESTINATION: Copy the source file to the destination path. If the given value is a relative path, 
                 the base directory depends on the type of the target
                    - `$<TARGET_FILE_DIR>`: real target
                    - `QMSETUP_BUILD_DIR`: custom target
    INSTALL_DIR: Install the source files into a subdirectory in the given path. The subdirectory is the
                 relative path from the `QMSETUP_BUILD_DIR` to `DESTINATION`.
]] #
function(qm_add_copy_command _target)
    set(options VERBOSE SKIP_BUILD SKIP_INSTALL)
    set(oneValueArgs CUSTOM_TARGET DESTINATION INSTALL_DIR)
    set(multiValueArgs SOURCES EXTRA_ARGS DEPENDS)
    cmake_parse_arguments(FUNC "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    if(NOT FUNC_SOURCES)
        message(FATAL_ERROR "qm_add_copy_command: SOURCES not specified.")
    endif()

    if(NOT TARGET ${_target})
        add_custom_target(${_target})
    endif()

    # Determine destination
    set(_dest)
    qm_set_value(_dest FUNC_DESTINATION .)

    # Determine destination base directory
    set(_dest_base)
    get_target_property(_type ${_target} TYPE)

    if(_type STREQUAL "UTILITY")
        qm_set_value(_dest_base QMSETUP_BUILD_DIR ${CMAKE_CURRENT_SOURCE_DIR})
    else()
        set(_dest_base "$<TARGET_FILE_DIR:${_target}>")
    endif()

    # Set deploy target
    if(FUNC_CUSTOM_TARGET)
        set(_deploy_target ${FUNC_CUSTOM_TARGET})

        if(NOT TARGET ${_deploy_target})
            add_custom_target(${_deploy_target})
        endif()
    else()
        set(_deploy_target ${_target})
    endif()

    if(FUNC_DEPENDS)
        add_dependencies(${_deploy_target} ${FUNC_DEPENDS})
    endif()

    # Prepare arguments
    set(_extra_args)
    set(_ignore_stdout)

    if(FUNC_EXTRA_ARGS)
        list(APPEND _extra_args -D "args=${FUNC_EXTRA_ARGS}")
    endif()

    if(NOT FUNC_VERBOSE)
        set(_ignore_stdout ${QMSETUP_IGNORE_STDOUT})
    endif()

    if(NOT FUNC_SKIP_BUILD)
        # Build phase
        add_custom_command(TARGET ${_deploy_target} POST_BUILD
            COMMAND ${CMAKE_COMMAND}
            -D "src=${FUNC_SOURCES}"
            -D "dest=${_dest}"
            -D "dest_base=${_dest_base}"
            ${_extra_args}
            -P "${QMSETUP_MODULES_DIR}/scripts/copy.cmake" ${_ignore_stdout}
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
            VERBATIM
        )
    endif()

    if(FUNC_INSTALL_DIR AND NOT FUNC_SKIP_INSTALL)
        if(NOT QMSETUP_BUILD_DIR)
            message(FATAL_ERROR "qm_add_copy_command: `QMSETUP_BUILD_DIR` not defined, the install directory cannot be determined.")
        endif()

        # Install phase
        install(CODE "
            set(_src \"${FUNC_SOURCES}\")
            set(_extra_args \"${FUNC_EXTRA_ARGS}\")

            # Calculate the relative path from build phase destination to build directory
            get_filename_component(_build_dir \"${_dest}\" ABSOLUTE BASE_DIR \"${_dest_base}\")
            file(RELATIVE_PATH _rel_path \"${QMSETUP_BUILD_DIR}\" \${_build_dir})

            # Calculate real install directory
            get_filename_component(_dest \"${FUNC_INSTALL_DIR}/\${_rel_path}\" ABSOLUTE BASE_DIR \${CMAKE_INSTALL_PREFIX})
    
            foreach(_file \${_src})
                # Avoid using `get_filename_component` to keep the trailing slash
                set(_path \${_file})
                if (NOT IS_ABSOLUTE \${_path})
                    set(_path \"${CMAKE_CURRENT_SOURCE_DIR}/\${_path}\")
                endif()
    
                if(IS_DIRECTORY \${_path})
                    set(_type DIRECTORY)
                else()
                    set(_type FILE)
                endif()
    
                file(INSTALL DESTINATION \"\${_dest}\"
                    TYPE \${_type}
                    FILES \${_path}
                    \${_extra_args}
                )
            endforeach()
        ")
    endif()
endfunction()