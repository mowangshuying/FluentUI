include_guard(DIRECTORY)

#[[
    Add qt translation target.

    qm_add_translation(<target>
        [LOCALES locales]
        [PREFIX prefix]
        [SOURCES files... | DIRECTORIES dirs... | TARGETS targets... | TS_FILES files...]
        [TS_DIR dir]
        [QM_DIR dir]
        [TS_OPTIONS options...]
        [QM_OPTIONS options...]
        [TS_DEPENDS targets...]
        [QM_DEPENDS targets...]
        [CREATE_ONCE]
    )

    Arguments:
        LOCALES: language names, e.g. zh_CN en_US, must specify if SOURCES or TARGETS is specified
        PREFIX: translation file prefix, default to target name

        SOURCES: source files
        DIRECTORIES: source directories
        TARGETS: target names, the source files of which will be collected
        TS_FILES: ts file names, add the specified ts file

        TS_DIR: ts files destination, default to `CMAKE_CURRENT_SOURCE_DIR`
        QM_DIR: qm files destination, default to `CMAKE_CURRENT_BINARY_DIR`

        TS_DEPENDS: add lupdate task as a dependency to the given targets
        QM_DEPENDS: add lrelease task as a dependency to the given targets

        CREATE_ONCE: create translations at configure phase if not exist
    
]] #
function(qm_add_translation _target)
    set(options CREATE_ONCE)
    set(oneValueArgs PREFIX TS_DIR QM_DIR)
    set(multiValueArgs LOCALES SOURCES DIRECTORIES TARGETS TS_FILES TS_OPTIONS QM_OPTIONS TS_DEPENDS QM_DEPENDS)
    cmake_parse_arguments(FUNC "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    # Get linguist tools
    if(NOT TARGET Qt${QT_VERSION_MAJOR}::lupdate OR NOT TARGET Qt${QT_VERSION_MAJOR}::lrelease)
        message(FATAL_ERROR "qm_add_translation: linguist tools not defined. Add find_package(Qt5 COMPONENTS LinguistTools) to CMake to enable.")
    endif()

    set(_src_files)
    set(_include_dirs)

    # Collect source files
    if(FUNC_SOURCES)
        list(APPEND _src_files ${FUNC_SOURCES})
    endif()

    # Collect source files
    if(FUNC_TARGETS)
        foreach(_item IN LISTS FUNC_TARGETS)
            get_target_property(_type ${_item} TYPE)

            if((_type STREQUAL "UTILITY") OR(_type STREQUAL "INTERFACE_LIBRARY"))
                continue()
            endif()

            set(_tmp_files)
            get_target_property(_tmp_files ${_item} SOURCES)
            list(FILTER _tmp_files INCLUDE REGEX ".+\\.(h|hh|hpp|hxx|c|cc|cpp|cxx|m|mm)$")
            list(FILTER _tmp_files EXCLUDE REGEX "^(qasc|moc)_.+")

            # Need to convert to absolute path
            get_target_property(_target_dir ${_item} SOURCE_DIR)

            foreach(_file IN LISTS _tmp_files)
                get_filename_component(_abs_file ${_file} ABSOLUTE BASE_DIR ${_target_dir})
                list(APPEND _src_files ${_abs_file})
            endforeach()

            unset(_tmp_files)

            get_target_property(_tmp_dirs ${_item} INCLUDE_DIRECTORIES)
            list(APPEND _include_dirs ${_tmp_dirs})
        endforeach()
    endif()

    # Collect source directories
    if(FUNC_DIRECTORIES)
        foreach(_item IN LISTS FUNC_DIRECTORIES)
            file(GLOB _tmp
                ${_item}/*.h ${_item}/*.hpp
                ${_item}/*.hh ${_item}/*.hxx
                ${_item}/*.cpp ${_item}/*.cxx
                ${_item}/*.c ${_item}/*.cc
                ${_item}/*.m ${_item}/*.mm
            )
            list(APPEND _src_files ${_tmp})
        endforeach()
    endif()

    if(_src_files)
        if(NOT FUNC_LOCALES)
            message(FATAL_ERROR "qm_add_translation: source files collected but LOCALES not specified!")
        endif()
    elseif(NOT FUNC_TS_FILES)
        message(FATAL_ERROR "qm_add_translation: no source files or ts files collected!")
    endif()

    add_custom_target(${_target})

    set(_qm_depends)

    if(FUNC_TS_OPTIONS)
        set(_ts_options ${FUNC_TS_OPTIONS})
    endif()

    if(FUNC_QM_OPTIONS)
        set(_qm_options ${FUNC_QM_OPTIONS})
    endif()

    if(_src_files)
        if(FUNC_PREFIX)
            set(_prefix ${FUNC_PREFIX})
        else()
            set(_prefix ${_target})
        endif()

        if(FUNC_TS_DIR)
            set(_ts_dir ${FUNC_TS_DIR})
        else()
            set(_ts_dir ${CMAKE_CURRENT_SOURCE_DIR})
        endif()

        set(_ts_files)

        foreach(_loc IN LISTS FUNC_LOCALES)
            list(APPEND _ts_files ${_ts_dir}/${_prefix}_${_loc}.ts)
        endforeach()

        # Include options
        set(_include_options)

        foreach(_inc IN LISTS _include_dirs)
            list(APPEND _include_options "-I${_inc}")
        endforeach()

        # May be an lupdate bug, so we skip passing include directories
        # list(APPEND _ts_options ${_include_options})
        if(_ts_options)
            list(PREPEND _ts_options OPTIONS)
        endif()

        set(_create_once)

        if(FUNC_CREATE_ONCE)
            set(_create_once CREATE_ONCE)
        endif()

        _qm_add_lupdate_target(${_target}_lupdate
            INPUT ${_src_files}
            OUTPUT ${_ts_files}
            ${_ts_options}
            ${_create_once}
        )

        # Add update dependencies
        # add_dependencies(${_target} ${_target}_lupdate)
        foreach(_item IN LISTS FUNC_TS_DEPENDS)
            add_dependencies(${_item} ${_target}_lupdate)
        endforeach()

    # list(APPEND _qm_depends DEPENDS ${_target}_lupdate)
    else()
        if(FUNC_PREFIX)
            message(WARNING "qm_add_translation: no source files collected, PREFIX ignored")
        endif()

        if(FUNC_TS_DIR)
            message(WARNING "qm_add_translation: no source files collected, TS_DIR ignored")
        endif()

        if(FUNC_TS_DEPENDS)
            message(WARNING "qm_add_translation: no source files collected, TS_DEPENDS ignored")
        endif()
    endif()

    if(FUNC_QM_DIR)
        set(_qm_dir ${FUNC_QM_DIR})
    else()
        set(_qm_dir ${CMAKE_CURRENT_BINARY_DIR})
    endif()

    set(_qm_target)

    if(_qm_options)
        list(PREPEND _qm_options OPTIONS)
    endif()

    _qm_add_lrelease_target(${_target}_lrelease
        INPUT ${_ts_files} ${FUNC_TS_FILES}
        DESTINATION ${_qm_dir}
        ${_qm_options}
        ${_qm_depends}
    )

    add_dependencies(${_target} ${_target}_lrelease)

    # Add release dependencies
    if(FUNC_TARGETS)
        foreach(_item IN LISTS FUNC_TARGETS)
            add_dependencies(${_item} ${_target}_lrelease)
        endforeach()
    endif()

    foreach(_item IN LISTS FUNC_QM_DEPENDS)
        add_dependencies(${_item} ${_target}_lrelease)
    endforeach()
endfunction()

# ----------------------------------
# Private functions
# ----------------------------------
# Input: cxx source files
# Output: target ts files
function(_qm_add_lupdate_target _target)
    set(options CREATE_ONCE)
    set(oneValueArgs)
    set(multiValueArgs INPUT OUTPUT OPTIONS DEPENDS)

    cmake_parse_arguments(_LUPDATE "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})
    set(_lupdate_deps ${_LUPDATE_DEPENDS})

    set(_my_sources ${_LUPDATE_INPUT})
    set(_my_tsfiles ${_LUPDATE_OUTPUT})

    add_custom_target(${_target} DEPENDS ${_lupdate_deps})
    _get_executable_location(Qt${QT_VERSION_MAJOR}::lupdate _lupdate_exe)

    set(_create_once_warning)
    set(_create_once_warning_printed off)

    # Prepare for create once
    if(_LUPDATE_CREATE_ONCE)
        # Check if all src files are available
        foreach(_file IN LISTS _my_sources)
            get_filename_component(_abs_file ${_file} ABSOLUTE)

            if(NOT EXISTS ${_abs_file})
                get_filename_component(_file ${_file} NAME)
                set(_create_once_warning "source file \"${_file}\" is not available, skip generating ts file now")
                break()
            endif()
        endforeach()

        # Check if options contain generator expressions
        if(NOT _create_once_warning)
            foreach(_opt IN LISTS _LUPDATE_OPTIONS)
                string(GENEX_STRIP "${_opt}" _no_genex)

                if(NOT _no_genex STREQUAL _opt)
                    set(_create_once_warning "lupdate options contain generator expressions, skip generating ts file now")
                    break()
                endif()
            endforeach()
        endif()
    endif()

    foreach(_ts_file IN LISTS _my_tsfiles)
        # make a list file to call lupdate on, so we don't make our commands too
        # long for some systems
        get_filename_component(_ts_name ${_ts_file} NAME)
        set(_ts_lst_file "${CMAKE_CURRENT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/${_ts_name}_lst_file")
        set(_lst_file_srcs)

        foreach(_lst_file_src IN LISTS _my_sources)
            set(_lst_file_srcs "${_lst_file_src}\n${_lst_file_srcs}")
        endforeach()

        get_directory_property(_inc_DIRS INCLUDE_DIRECTORIES)

        foreach(_pro_include IN LISTS _inc_DIRS)
            get_filename_component(_abs_include "${_pro_include}" ABSOLUTE)
            set(_lst_file_srcs "-I${_pro_include}\n${_lst_file_srcs}")
        endforeach()

        file(WRITE ${_ts_lst_file} "${_lst_file_srcs}")

        get_filename_component(_ts_abs ${_ts_file} ABSOLUTE)

        if(_LUPDATE_CREATE_ONCE AND NOT EXISTS ${_ts_abs})
            if(_create_once_warning)
                if(NOT _create_once_warning_printed)
                    message(WARNING "qm_add_translation: ${_create_once_warning}")
                    set(_create_once_warning_printed on)
                endif()
            else()
                message(STATUS "Lupdate: Generating ${_ts_name}")
                get_filename_component(_abs_file ${_ts_file} ABSOLUTE)
                get_filename_component(_dir ${_abs_file} DIRECTORY)
                file(MAKE_DIRECTORY ${_dir})
                execute_process(
                    COMMAND ${_lupdate_exe} ${_LUPDATE_OPTIONS} "@${_ts_lst_file}" -ts ${_ts_file}
                    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                    OUTPUT_QUIET
                    COMMAND_ERROR_IS_FATAL ANY
                )
            endif()
        endif()

        add_custom_command(
            TARGET ${_target}
            COMMAND ${_lupdate_exe}
            ARGS ${_LUPDATE_OPTIONS} "@${_ts_lst_file}" -ts ${_ts_file}
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
            DEPENDS ${_my_sources}
            BYPRODUCTS ${_ts_lst_file}
            VERBATIM
        )
    endforeach()
endfunction()

# Input: ts files
# Output: list to append qm files
function(_qm_add_lrelease_target _target)
    set(options)
    set(oneValueArgs DESTINATION OUTPUT)
    set(multiValueArgs INPUT OPTIONS DEPENDS)

    cmake_parse_arguments(_LRELEASE "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})
    set(_lrelease_files ${_LRELEASE_INPUT})
    set(_lrelease_deps ${_LRELEASE_DEPENDS})

    _get_executable_location(Qt${QT_VERSION_MAJOR}::lrelease _lrelease_exe)

    set(_qm_files)

    foreach(_file IN LISTS _lrelease_files)
        get_filename_component(_abs_FILE ${_file} ABSOLUTE)
        get_filename_component(_qm_file ${_file} NAME)

        # everything before the last dot has to be considered the file name (including other dots)
        string(REGEX REPLACE "\\.[^.]*$" "" FILE_NAME ${_qm_file})
        get_source_file_property(output_location ${_abs_FILE} OUTPUT_LOCATION)

        if(output_location)
            set(_out_dir ${output_location})
        elseif(_LRELEASE_DESTINATION)
            set(_out_dir ${_LRELEASE_DESTINATION})
        else()
            set(_out_dir ${CMAKE_CURRENT_BINARY_DIR})
        endif()

        set(_qm_file "${_out_dir}/${FILE_NAME}.qm")

        add_custom_command(
            OUTPUT ${_qm_file}
            COMMAND ${CMAKE_COMMAND} -E make_directory ${_out_dir}
            COMMAND ${_lrelease_exe} ARGS ${_LRELEASE_OPTIONS} ${_abs_FILE} -qm ${_qm_file}
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
            DEPENDS ${_lrelease_files}
            VERBATIM
        )

        list(APPEND _qm_files ${_qm_file})
    endforeach()

    add_custom_target(${_target} ALL DEPENDS ${_lrelease_deps} ${_qm_files})

    if(_LRELEASE_OUTPUT)
        set(${_LRELEASE_OUTPUT} ${_qm_files} PARENT_SCOPE)
    endif()
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