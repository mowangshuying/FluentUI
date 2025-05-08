#[[
    Warning: This module depends on `qmcorecmd` after installation.
]] #
if(NOT QMSETUP_CORECMD_EXECUTABLE)
    message(FATAL_ERROR "QMSETUP_CORECMD_EXECUTABLE not defined. Add find_package(qmsetup) to CMake first.")
endif()

if(NOT DEFINED QMSETUP_APPLOCAL_DEPS_PATHS)
    set(QMSETUP_APPLOCAL_DEPS_PATHS)
endif()

if(NOT DEFINED QMSETUP_APPLOCAL_DEPS_PATHS_DEBUG)
    set(QMSETUP_APPLOCAL_DEPS_PATHS_DEBUG ${QMSETUP_APPLOCAL_DEPS_PATHS})
endif()

if(NOT DEFINED QMSETUP_APPLOCAL_DEPS_PATHS_RELEASE)
    set(QMSETUP_APPLOCAL_DEPS_PATHS_RELEASE ${QMSETUP_APPLOCAL_DEPS_PATHS})
endif()

if(NOT DEFINED QMSETUP_APPLOCAL_DEPS_PATHS_RELWITHDEBINFO)
    set(QMSETUP_APPLOCAL_DEPS_PATHS_RELWITHDEBINFO ${QMSETUP_APPLOCAL_DEPS_PATHS_RELEASE})
endif()

if(NOT DEFINED QMSETUP_APPLOCAL_DEPS_PATHS_MINSIZEREL)
    set(QMSETUP_APPLOCAL_DEPS_PATHS_MINSIZEREL ${QMSETUP_APPLOCAL_DEPS_PATHS_RELEASE})
endif()

include_guard(DIRECTORY)

#[[
    Record searching paths for Windows Executables, must be called before calling `qm_win_applocal_deps`
    or `qm_deploy_directory` if your project supports Windows.

    WARNING: This function is deprecated.

    qm_win_record_deps(<target>)
]] #
function(qm_win_record_deps _target)
    if(NOT WIN32)
        return()
    endif()

    set(_paths)
    get_target_property(_link_libraries ${_target} LINK_LIBRARIES)

    foreach(_item IN LISTS _link_libraries)
        if(NOT TARGET ${_item})
            continue()
        endif()

        get_target_property(_imported ${_item} IMPORTED)

        if(_imported)
            get_target_property(_path ${_item} LOCATION)

            if(NOT _path OR NOT ${_path} MATCHES "\\.dll$")
                continue()
            endif()

            set(_path "$<TARGET_PROPERTY:${_item},LOCATION_$<CONFIG>>")
        else()
            get_target_property(_type ${_item} TYPE)

            if(NOT ${_type} MATCHES "SHARED_LIBRARY")
                continue()
            endif()

            set(_path "$<TARGET_FILE:${_item}>")
        endif()

        list(APPEND _paths ${_path})
    endforeach()

    if(NOT _paths)
        return()
    endif()

    set(_deps_file "${CMAKE_CURRENT_BINARY_DIR}/${_target}_deps_$<CONFIG>.txt")
    file(GENERATE OUTPUT ${_deps_file} CONTENT "$<JOIN:${_paths},\n>")
    set_target_properties(${_target} PROPERTIES QMSETUP_DEPENDENCIES_FILE ${_deps_file})
endfunction()

#[[
    Automatically copy dependencies for Windows Executables after build.

    qm_win_applocal_deps(<target>
        [CUSTOM_TARGET <target>]
        [FORCE] [VERBOSE]
        [EXTRA_SEARCHING_PATHS <path...>]
        [EXTRA_TARGETS <target...>]
        [OUTPUT_DIR <dir>]
        [EXCLUDE <pattern...>]
    )
]] #
function(qm_win_applocal_deps _target)
    if(NOT WIN32)
        return()
    endif()

    set(options FORCE VERBOSE)
    set(oneValueArgs TARGET CUSTOM_TARGET OUTPUT_DIR)
    set(multiValueArgs EXTRA_SEARCHING_PATHS EXTRA_TARGETS EXCLUDE)
    cmake_parse_arguments(FUNC "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    # Get output directory and deploy target
    set(_out_dir)
    set(_deploy_target)

    if(FUNC_CUSTOM_TARGET)
        set(_deploy_target ${FUNC_CUSTOM_TARGET})

        if(NOT TARGET ${_deploy_target})
            add_custom_target(${_deploy_target})
        endif()
    else()
        set(_deploy_target ${_target})
    endif()

    if(FUNC_OUTPUT_DIR)
        set(_out_dir ${FUNC_OUTPUT_DIR})
    else()
        set(_out_dir "$<TARGET_FILE_DIR:${_target}>")
    endif()

    if(NOT _out_dir)
        message(FATAL_ERROR "qm_win_applocal_deps: cannot determine output directory.")
    endif()

    # Get dep files
    set(_dep_files)
    _qm_win_get_all_dep_files(_dep_files ${_target})

    foreach(_item IN LISTS FUNC_EXTRA_TARGETS)
        _qm_win_get_all_dep_files(_dep_files ${_item})
    endforeach()

    # Prepare command
    set(_args)

    if(FUNC_FORCE)
        list(APPEND _args -f)
    endif()

    if(FUNC_VERBOSE)
        list(APPEND _args -V)
    endif()

    # Add extra searching paths
    foreach(_item IN LISTS FUNC_EXTRA_SEARCHING_PATHS)
        list(APPEND _args "-L${_item}")
    endforeach()

    # Add global extra searching paths
    if(CMAKE_BUILD_TYPE)
        string(TOUPPER ${CMAKE_BUILD_TYPE} _build_type_upper)

        if(QMSETUP_APPLOCAL_DEPS_PATHS_${_build_type_upper})
            foreach(_item IN LISTS QMSETUP_APPLOCAL_DEPS_PATHS_${_build_type_upper})
                get_filename_component(_item ${_item} ABSOLUTE BASE_DIR ${CMAKE_SOURCE_DIR})
                list(APPEND _args "-L${_item}")
            endforeach()
        elseif(QMSETUP_APPLOCAL_DEPS_PATHS)
            foreach(_item IN LISTS QMSETUP_APPLOCAL_DEPS_PATHS)
                get_filename_component(_item ${_item} ABSOLUTE BASE_DIR ${CMAKE_SOURCE_DIR})
                list(APPEND _args "-L${_item}")
            endforeach()
        endif()
    else()
        foreach(_item IN LISTS QMSETUP_APPLOCAL_DEPS_PATHS)
            get_filename_component(_item ${_item} ABSOLUTE BASE_DIR ${CMAKE_SOURCE_DIR})
            list(APPEND _args "-L${_item}")
        endforeach()
    endif()

    foreach(_item IN LISTS _dep_files)
        list(APPEND _args "-@${_item}")
    endforeach()

    foreach(_item IN LISTS FUNC_EXCLUDE)
        list(APPEND _args -e ${_item})
    endforeach()

    list(APPEND _args "$<TARGET_FILE:${_target}>")

    add_custom_command(TARGET ${_deploy_target} POST_BUILD
        COMMAND ${QMSETUP_CORECMD_EXECUTABLE} deploy ${_args}
        WORKING_DIRECTORY ${_out_dir}
        VERBATIM
    )
endfunction()

#[[
    Add deploy command when install project, not available in debug mode.

    qm_deploy_directory(<install_dir>
        [FORCE] [STANDARD] [VERBOSE]
        [LIBRARY_DIR <dir>]
        [EXTRA_LIBRARIES <path>...]
        [EXTRA_PLUGIN_PATHS <path>...]
        [EXTRA_SEARCHING_PATHS <path>...]

        [PLUGINS <plugin>...]
        [PLUGIN_DIR <dir>]

        [QML <qml>...]
        [QML_DIR <dir>]

        [WIN_TARGETS <target>...]

        [COMMENT <comment>]
    )

    PLUGINS: Qt plugins, in format of `<category>/<name>`
    PLUGIN_DIR: Qt plugins destination
    EXTRA_PLUGIN_PATHS: Extra Qt plugins searching paths
    QML: Qt qml directories
    QML_DIR: Qt qml destination
    LIBRARY_DIR: Library destination
    EXTRA_LIBRARIES： Extra library names list to deploy
    EXTRA_SEARCHING_PATHS: Extra library searching paths
]] #
function(qm_deploy_directory _install_dir)
    set(options FORCE STANDARD VERBOSE)
    set(oneValueArgs LIBRARY_DIR PLUGIN_DIR QML_DIR COMMENT)
    set(multiValueArgs EXTRA_PLUGIN_PATHS PLUGINS QML WIN_TARGETS EXTRA_SEARCHING_PATHS EXTRA_LIBRARIES)
    cmake_parse_arguments(FUNC "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    # Get qmake
    if((FUNC_PLUGINS OR FUNC_QML) AND NOT DEFINED QT_QMAKE_EXECUTABLE)
        if(TARGET Qt${QT_VERSION_MAJOR}::qmake)
            _get_executable_location(Qt${QT_VERSION_MAJOR}::qmake QT_QMAKE_EXECUTABLE)
        elseif((FUNC_PLUGINS AND NOT FUNC_EXTRA_PLUGIN_PATHS) OR FUNC_QML)
            message(FATAL_ERROR "qm_deploy_directory: qmake not defined. Add find_package(Qt5 COMPONENTS Core) to CMake to enable.")
        endif()
    endif()

    # Set values
    qm_set_value(_lib_dir FUNC_LIBRARY_DIR "${_install_dir}/${QMSETUP_SHARED_LIBRARY_CATEGORY}")
    qm_set_value(_plugin_dir FUNC_PLUGIN_DIR "${_install_dir}/plugins")
    qm_set_value(_qml_dir FUNC_QML_DIR "${_install_dir}/qml")

    # Prepare commands
    set(_args
        -i "${_install_dir}"
        -m "${QMSETUP_CORECMD_EXECUTABLE}"
        --plugindir "${_plugin_dir}"
        --libdir "${_lib_dir}"
        --qmldir "${_qml_dir}"
    )
    set(_searching_paths)

    if(QT_QMAKE_EXECUTABLE)
        list(APPEND _args --qmake "${QT_QMAKE_EXECUTABLE}")
    endif()

    # Add Qt plugins
    foreach(_item IN LISTS FUNC_PLUGINS)
        list(APPEND _args --plugin "${_item}")
    endforeach()

    # Add QML modules
    foreach(_item IN LISTS FUNC_QML)
        list(APPEND _args --qml "${_item}")
    endforeach()

    # Add extra plugin paths
    foreach(_item IN LISTS FUNC_EXTRA_PLUGIN_PATHS)
        list(APPEND _args --extra "${_item}")
    endforeach()

    # Add extra searching paths
    foreach(_item IN LISTS FUNC_EXTRA_SEARCHING_PATHS)
        get_filename_component(_item ${_item} ABSOLUTE)
        list(APPEND _searching_paths ${_item})
    endforeach()

    # Add global extra searching paths
    if(CMAKE_BUILD_TYPE)
        string(TOUPPER ${CMAKE_BUILD_TYPE} _build_type_upper)

        if(QMSETUP_APPLOCAL_DEPS_PATHS_${_build_type_upper})
            foreach(_item IN LISTS QMSETUP_APPLOCAL_DEPS_PATHS_${_build_type_upper})
                get_filename_component(_item ${_item} ABSOLUTE BASE_DIR ${CMAKE_SOURCE_DIR})
                list(APPEND _searching_paths ${_item})
            endforeach()
        elseif(QMSETUP_APPLOCAL_DEPS_PATHS)
            foreach(_item IN LISTS QMSETUP_APPLOCAL_DEPS_PATHS)
                get_filename_component(_item ${_item} ABSOLUTE BASE_DIR ${CMAKE_SOURCE_DIR})
                list(APPEND _searching_paths ${_item})
            endforeach()
        endif()
    else()
        foreach(_item IN LISTS QMSETUP_APPLOCAL_DEPS_PATHS)
            get_filename_component(_item ${_item} ABSOLUTE BASE_DIR ${CMAKE_SOURCE_DIR})
            list(APPEND _searching_paths ${_item})
        endforeach()
    endif()

    foreach(_item IN LISTS _searching_paths)
        list(APPEND _args -L "${_item}")
    endforeach()

    if(WIN32)
        set(_dep_files)

        if(FUNC_WIN_TARGETS)
            _qm_win_get_all_dep_files(_dep_files ${FUNC_WIN_TARGETS})
        endif()

        foreach(_item IN LISTS _dep_files)
            list(APPEND _args -@ "${_item}")
        endforeach()

        set(_script_quoted "cmd /c \"${QMSETUP_MODULES_DIR}/scripts/windeps.bat\"")
    else()
        set(_script_quoted "bash \"${QMSETUP_MODULES_DIR}/scripts/unixdeps.sh\"")
    endif()

    # Add extra libraries
    foreach(_item IN LISTS _searching_paths)
        foreach(_lib IN LISTS FUNC_EXTRA_LIBRARIES)
            set(_path "${_item}/${_lib}")

            if((EXISTS ${_path}) AND(NOT IS_DIRECTORY ${_path}))
                list(APPEND _args --copy ${_path} ${_lib_dir})
            endif()
        endforeach()
    endforeach()

    # Add options
    if(FUNC_FORCE)
        list(APPEND _args "-f")
    endif()

    if(FUNC_STANDARD)
        list(APPEND _args "-s")
    endif()

    if(FUNC_VERBOSE)
        list(APPEND _args "-V")
    endif()

    set(_args_quoted)

    foreach(_item IN LISTS _args)
        set(_args_quoted "${_args_quoted}\"${_item}\" ")
    endforeach()

    set(_comment_code)

    if(FUNC_COMMENT)
        set(_comment_code "message(STATUS \"${FUNC_COMMENT}\")")
    endif()

    # Add install command
    install(CODE "
        ${_comment_code}
        execute_process(
            COMMAND ${_script_quoted} ${_args_quoted}
            WORKING_DIRECTORY \"${_install_dir}\"
            COMMAND_ERROR_IS_FATAL ANY
        )
    ")
endfunction()

# ----------------------------------
# Private functions
# ----------------------------------
function(_qm_win_get_all_dep_files _out)
    # Get searching paths
    macro(get_recursive_dynamic_dependencies _current_target _result)
        get_target_property(_deps ${_current_target} LINK_LIBRARIES)

        if(_deps)
            foreach(_dep IN LISTS _deps)
                if(NOT TARGET ${_dep})
                    continue()
                endif()

                get_target_property(_type ${_dep} TYPE)

                if(_type STREQUAL "SHARED_LIBRARY")
                    list(APPEND ${_result} ${_dep})
                endif()

                get_recursive_dynamic_dependencies(${_dep} ${_result})
            endforeach()
        endif()
    endmacro()

    set(_visited_targets ${ARGN})

    foreach(_target ${ARGN})
        set(_all_deps)
        get_recursive_dynamic_dependencies(${_target} _all_deps)

        foreach(_cur_dep IN LISTS _all_deps)
            if(${_cur_dep} IN_LIST _visited_targets)
                continue()
            endif()

            list(APPEND _visited_targets ${_cur_dep})
        endforeach()
    endforeach()

    set(_dep_files)

    foreach(_target IN LISTS _visited_targets)
        # Add file
        get_target_property(_file ${_target} QMSETUP_DEPENDENCIES_FILE)

        if(NOT _file)
            continue()
        endif()

        list(APPEND _dep_files ${_file})
    endforeach()

    set(${_out} ${_dep_files} PARENT_SCOPE)
endfunction()

function(_get_executable_location _target _var)
    get_target_property(_path ${_target} IMPORTED_LOCATION)

    if(NOT _path)
        get_target_property(_path ${_target} IMPORTED_LOCATION_RELEASE)
    endif()

    if(NOT _path)
        get_target_property(_path ${_target} IMPORTED_LOCATION_MINSIZEREL)
    endif()

    if(NOT _path)
        get_target_property(_path ${_target} IMPORTED_LOCATION_RELWITHDEBINFO)
    endif()

    if(NOT _path)
        get_target_property(_path ${_target} IMPORTED_LOCATION_DEBUG)
    endif()

    if(NOT _path)
        message(FATAL_ERROR "Could not find imported location of target: ${_target}")
    endif()

    set(${_var} ${_path} PARENT_SCOPE)
endfunction()