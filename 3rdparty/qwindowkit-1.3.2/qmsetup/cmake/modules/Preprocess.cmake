#[[
    Warning: This module depends on `qmcorecmd` after installation.
]] #
if(NOT QMSETUP_CORECMD_EXECUTABLE)
    message(FATAL_ERROR "QMSETUP_CORECMD_EXECUTABLE not defined. Add find_package(qmsetup) to CMake first.")
endif()

if(NOT DEFINED QMSETUP_DEFINITION_NUMERICAL)
    set(QMSETUP_DEFINITION_NUMERICAL off)
endif()

if(NOT DEFINED QMSETUP_DEFINITION_SCOPE)
    set(QMSETUP_DEFINITION_SCOPE)
endif()

if(NOT DEFINED QMSETUP_DEFINITION_PROPERTY)
    set(QMSETUP_DEFINITION_PROPERTY)
endif()

if(NOT DEFINED QMSETUP_SYNC_INCLUDE_STANDARD)
    set(QMSETUP_SYNC_INCLUDE_STANDARD on)
endif()

include_guard(DIRECTORY)

#[[
    Generate indirect reference files for header files to make the include statements more orderly.
    The generated file has the same timestamp as the source file.

    qm_sync_include(<src> <dest>
        [STANDARD] [NO_STANDARD] [NO_ALL]
        [INCLUDE <expr> <sub> ...]
        [EXCLUDE <expr...>]
        [INSTALL_DIR <dir>]
        [FORCE] [VERBOSE]
    )

    STANDARD: Enable standard public-private pattern, can be forced to enable by enabling `QMSETUP_SYNC_INCLUDE_STANDARD`
    NO_STANDARD: Disable standard public-private pattern, enable it to override `QMSETUP_SYNC_INCLUDE_STANDARD`
#]]
function(qm_sync_include _src_dir _dest_dir)
    set(options FORCE VERBOSE NO_STANDARD NO_ALL)
    set(oneValueArgs INSTALL_DIR)
    set(multiValueArgs INCLUDE EXCLUDE)
    cmake_parse_arguments(FUNC "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    if(NOT IS_ABSOLUTE ${_src_dir})
        get_filename_component(_src_dir ${_src_dir} ABSOLUTE)
    else()
        string(REPLACE "\\" "/" _src_dir ${_src_dir})
    endif()

    if(NOT IS_ABSOLUTE ${_dest_dir})
        get_filename_component(_dest_dir ${_dest_dir} ABSOLUTE)
    else()
        string(REPLACE "\\" "/" _dest_dir ${_dest_dir})
    endif()

    if(IS_DIRECTORY ${_src_dir})
        file(GLOB_RECURSE header_files ${_src_dir}/*.h ${_src_dir}/*.hpp)

        set(_args)

        if(FUNC_STANDARD OR(QMSETUP_SYNC_INCLUDE_STANDARD AND NOT FUNC_NO_STANDARD))
            list(APPEND _args -s)
        endif()

        if(FUNC_NO_ALL)
            list(APPEND _args -n)
        endif()

        set(_even off)

        foreach(_item IN LISTS FUNC_INCLUDE)
            if(_even)
                set(_even off)
                list(APPEND _args ${_item})
            else()
                set(_even on)
                list(APPEND _args -i ${_item})
            endif()
        endforeach()

        foreach(_item IN LISTS FUNC_EXCLUDE)
            list(APPEND _args -e ${_item})
        endforeach()

        if(FUNC_VERBOSE)
            list(APPEND _args -V)
        endif()

        if(FUNC_FORCE OR NOT EXISTS ${_dest_dir})
            if(EXISTS ${_dest_dir})
                file(REMOVE_RECURSE ${_dest_dir})
            endif()

            execute_process(
                COMMAND ${QMSETUP_CORECMD_EXECUTABLE} incsync ${_args} ${_src_dir} ${_dest_dir}
                WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                COMMAND_ERROR_IS_FATAL ANY
            )
        endif()

        if(FUNC_INSTALL_DIR)
            set(_install_dir ${FUNC_INSTALL_DIR})
            set(_args_quoted)

            foreach(_item IN LISTS _args)
                set(_args_quoted "${_args_quoted}\"${_item}\" ")
            endforeach()

            # Get command output only and use file(INSTALL) to install files
            install(CODE "
                get_filename_component(_install_dir \"${_install_dir}\" ABSOLUTE BASE_DIR \${CMAKE_INSTALL_PREFIX})
        
                execute_process(
                    COMMAND \"${QMSETUP_CORECMD_EXECUTABLE}\" incsync -d 
                        ${_args_quoted} \"${_src_dir}\" \${_install_dir}
                    WORKING_DIRECTORY \"${CMAKE_CURRENT_SOURCE_DIR}\"
                    OUTPUT_VARIABLE _output_contents
                    OUTPUT_STRIP_TRAILING_WHITESPACE
                    COMMAND_ERROR_IS_FATAL ANY
                )
                string(REPLACE \"\\n\" \";\" _lines \"\${_output_contents}\")

                foreach(_line IN LISTS _lines)
                    string(REGEX MATCH \"from \\\"([^\\\"]*)\\\" to \\\"([^\\\"]*)\\\"\" _ \${_line})
                    get_filename_component(_target_path \${CMAKE_MATCH_2} DIRECTORY)
                    file(INSTALL \${CMAKE_MATCH_1} DESTINATION \${_target_path})
                endforeach()
            ")
        endif()
    else()
        message(FATAL_ERROR "qm_sync_include: source directory doesn't exist.")
    endif()
endfunction()

#[[
    Add a definition to a property scope.

    qm_add_definition( <key | key=value> | <key> <value>
        [GLOBAL | TARGET <target> | SOURCE <file> | DIRECTORY <dir>]
        [PROPERTY <prop>]

        [CONDITION <cond...>]
        [STRING_LITERAL] [NO_KEYWORD]
        [NUMERICAL] [CLASSICAL]
    )

    STRING_LITERAL: Force quotes on values
    NO_KEYWORD: Treat any keyword as string
    NUMERICAL: Use 1/-1 as defined/undefined, can be forced to enable by enabling `QMSETUP_DEFINITION_NUMERICAL`
    CLASSICAL: Use classical definition, enable it to override `QMSETUP_DEFINITION_NUMERICAL`
]] #
function(qm_add_definition _first)
    set(options STRING_LITERAL NO_KEYWORD NUMERICAL CLASSICAL)
    set(oneValueArgs TARGET SOURCE DIRECTORY PROPERTY)
    set(multiValueArgs CONDITION)
    cmake_parse_arguments(FUNC "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    set(_result)
    set(_is_pair off)
    set(_defined off)

    set(_list ${_first} ${FUNC_UNPARSED_ARGUMENTS})
    list(LENGTH _list _len)

    set(_cond on)
    set(_numerical off)

    if(NOT FUNC_CLASSICAL AND(QMSETUP_DEFINITION_NUMERICAL OR FUNC_NUMERICAL))
        set(_numerical on)
    endif()

    if(FUNC_CONDITION)
        if(NOT(${FUNC_CONDITION}))
            set(_cond off)
        endif()
    elseif(DEFINED FUNC_CONDITION)
        set(_cond off)
    endif()

    if(_len EQUAL 1)
        set(_result ${_list})
        set(_defined on)

        if(NOT _cond)
            set(_defined off)
        endif()
    elseif(_len EQUAL 2)
        # Get key
        list(POP_FRONT _list _key)
        list(POP_FRONT _list _val)

        if(FUNC_STRING_LITERAL AND NOT ${_val} MATCHES "\".+\"")
            set(_val "\"${_val}\"")
        endif()

        # Boolean
        string(TOLOWER ${_val} _val_lower)

        if(NOT FUNC_NO_KEYWORD AND(${_val_lower} STREQUAL "off" OR ${_val_lower} STREQUAL "false"))
            set(_result ${_key})
            set(_defined off)

            if(NOT _cond)
                set(_defined on)
            endif()
        elseif(NOT FUNC_NO_KEYWORD AND(${_val_lower} STREQUAL "on" OR ${_val_lower} STREQUAL "true"))
            set(_result ${_key})
            set(_defined on)

            if(NOT _cond)
                set(_defined off)
            endif()
        else()
            set(_result "${_key}=${_val}")
            set(_is_pair on)
            set(_defined on)

            if(NOT _cond)
                set(_defined off)
            endif()
        endif()
    else()
        message(FATAL_ERROR "qm_add_definition: called with incorrect number of arguments")
    endif()

    if(_numerical AND NOT _is_pair)
        if(_defined)
            set(_result "${_result}=1")
        else()
            set(_result "${_result}=-1")
        endif()
    elseif(NOT _defined)
        return()
    endif()

    _qm_calc_property_scope_helper(_scope _prop)
    set_property(${_scope} APPEND PROPERTY ${_prop} "${_result}")
endfunction()

#[[
    Remove a definition from a property scope.

    qm_remove_definition(<key>
        [GLOBAL | TARGET <target> | SOURCE <file> | DIRECTORY <dir>]
        [PROPERTY <prop>]
    )
]] #
function(qm_remove_definition _key)
    set(options)
    set(oneValueArgs TARGET PROPERTY)
    set(multiValueArgs)
    cmake_parse_arguments(FUNC "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    if(FUNC_TARGET)
        get_target_property(_definitions ${FUNC_TARGET} ${_prop})
    else()
        get_property(_definitions GLOBAL PROPERTY ${_prop})
    endif()

    # Filter
    list(FILTER _definitions EXCLUDE REGEX "^${_key}(=.*)?$")

    _qm_calc_property_scope_helper(_scope _prop)
    set_property(${_scope} PROPERTY ${_prop} "${_definitions}")
endfunction()

#[[
    Generate a configuration header of a property scope. If the configuration has not changed,
    the generated file's timestemp will not be updated when you reconfigure it.

    qm_generate_config(<file>
        [GLOBAL | TARGET <target> | SOURCE <file> | DIRECTORY <dir>]
        [PROPERTY <prop>]

        [PROJECT_NAME <name>]
        [WARNING_FILE <file>]
        [NO_WARNING]
        [NO_HASH]
    )
]] #
function(qm_generate_config _file)
    set(options NO_WARNING NO_HASH)
    set(oneValueArgs TARGET PROPERTY PROJECT_NAME WARNING_FILE)
    set(multiValueArgs)
    cmake_parse_arguments(FUNC "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    _qm_calc_property_scope_helper(_scope _prop)
    get_property(_definitions ${_scope} PROPERTY ${_prop})

    if(NOT _definitions)
        set(_definitions) # May be _-NOTFOUND
    endif()

    _qm_generate_config_helper()
endfunction()

#[[
    Generate build info information header.

    qm_generate_build_info(<file>
        [ROOT_DIRECTORY <dir>]
        [PREFIX <prefix>]
        
        [YEAR] [TIME]

        [WARNING_FILE <file>]
        [NO_WARNING]
        [NO_HASH]
        [REQUIRED]
    )

    file: Output file

    ROOT_DIRECTORY: Repository root directory (CMake will try to run `git` at this directory)
    PREFIX: Macros prefix, default to the upper case of  `PROJECT_NAME`
    REQUIRED: Abort if there's any error with git
]] #
function(qm_generate_build_info _file)
    set(options NO_WARNING NO_HASH YEAR TIME REQUIRED)
    set(oneValueArgs ROOT_DIRECTORY PREFIX WARNING_FILE)
    set(multiValueArgs)
    cmake_parse_arguments(FUNC "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    if(FUNC_PREFIX)
        set(_prefix ${FUNC_PREFIX})
    else()
        string(TOUPPER "${PROJECT_NAME}" _prefix)
    endif()

    set(_dir)
    qm_set_value(_dir FUNC_ROOT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

    set(_git_branch "unknown")
    set(_git_hash "unknown")
    set(_git_commit_time "unknown")
    set(_git_commit_author "unknown")
    set(_git_commit_email "unknown")

    # Check `git` command
    if(NOT GIT_EXECUTABLE)
        find_package(Git)

        if(NOT Git_FOUND)
            if(FUNC_REQUIRED)
                message(FATAL_ERROR "Git not found")
            endif()
        endif()
    endif()

    if(GIT_EXECUTABLE)
        # Branch
        execute_process(
            COMMAND ${GIT_EXECUTABLE} symbolic-ref --short -q HEAD
            OUTPUT_VARIABLE _temp
            ERROR_VARIABLE _err
            OUTPUT_STRIP_TRAILING_WHITESPACE
            ERROR_STRIP_TRAILING_WHITESPACE
            ERROR_QUIET
            WORKING_DIRECTORY ${_dir}
            RESULT_VARIABLE _code
        )

        if(_code EQUAL 0)
            set(_git_branch ${_temp})
        elseif(FUNC_REQUIRED)
            message(FATAL_ERROR "Error running git symbolic-ref: ${_err}")
        endif()

        # Hash
        execute_process(
            COMMAND ${GIT_EXECUTABLE} log -1 "--pretty=format:%H;%aI;%aN;%aE" # Use `;` as separator
            OUTPUT_VARIABLE _temp
            ERROR_VARIABLE _err
            OUTPUT_STRIP_TRAILING_WHITESPACE
            ERROR_STRIP_TRAILING_WHITESPACE
            ERROR_QUIET
            WORKING_DIRECTORY ${_dir}
            RESULT_VARIABLE _code
        )

        if(_code EQUAL 0)
            list(GET _temp 0 _git_hash)
            list(GET _temp 1 _git_commit_time)
            list(GET _temp 2 _git_commit_author)
            list(GET _temp 3 _git_commit_email)
        elseif(FUNC_REQUIRED)
            message(FATAL_ERROR "Error running git log: ${_err}")
        endif()
    endif()

    qm_set_value(_system_name CMAKE_SYSTEM_NAME unknown)
    qm_set_value(_system_version CMAKE_SYSTEM_VERSION unknown)
    qm_set_value(_system_processor CMAKE_SYSTEM_PROCESSOR unknown)

    qm_set_value(_host_system_name CMAKE_HOST_SYSTEM_NAME unknown)
    qm_set_value(_host_system_version CMAKE_HOST_SYSTEM_VERSION unknown)
    qm_set_value(_host_system_processor CMAKE_HOST_SYSTEM_PROCESSOR unknown)

    qm_set_value(_compiler_name CMAKE_CXX_COMPILER_ID unknown)
    qm_set_value(_compiler_version CMAKE_CXX_COMPILER_VERSION unknown)
    qm_set_value(_compiler_arch CMAKE_CXX_COMPILER_ARCHITECTURE_ID unknown)
    qm_set_value(_compiler_abi CMAKE_CXX_COMPILER_ABI unknown)

    set(_definitions)

    set(_has_time off)

    # year
    if(FUNC_YEAR)
        string(TIMESTAMP _build_year "%Y")
        list(APPEND _definitions ${_prefix}_BUILD_YEAR=\"${_build_year}\")
        set(_has_time on)
    endif()

    # time
    if(FUNC_TIME)
        string(TIMESTAMP _build_time "%Y/%m/%d %H:%M:%S")
        list(APPEND _definitions ${_prefix}_BUILD_TIME=\"${_build_time}\")
        set(_has_time on)
    endif()

    if(_has_time)
        list(APPEND _definitions "%")
    endif()

    # system
    list(APPEND _definitions ${_prefix}_SYSTEM_NAME=\"${_system_name}\")
    list(APPEND _definitions ${_prefix}_SYSTEM_VERSION=\"${_system_version}\")
    list(APPEND _definitions ${_prefix}_SYSTEM_PROCESSOR=\"${_system_processor}\")

    list(APPEND _definitions ${_prefix}_HOST_SYSTEM_NAME=\"${_host_system_name}\")
    list(APPEND _definitions ${_prefix}_HOST_SYSTEM_VERSION=\"${_host_system_version}\")
    list(APPEND _definitions ${_prefix}_HOST_SYSTEM_PROCESSOR=\"${_host_system_processor}\")

    list(APPEND _definitions "%")

    # compiler
    list(APPEND _definitions ${_prefix}_COMPILER_ID=\"${_compiler_name}\")
    list(APPEND _definitions ${_prefix}_COMPILER_VERSION=\"${_compiler_version}\")
    list(APPEND _definitions ${_prefix}_COMPILER_ARCH=\"${_compiler_arch}\")
    list(APPEND _definitions ${_prefix}_COMPILER_ABI=\"${_compiler_abi}\")

    list(APPEND _definitions "%")

    # build time (deprecated)
    # list(APPEND _definitions ${_prefix}_BUILD_DATE_TIME=\"${_build_time}\")
    # list(APPEND _definitions ${_prefix}_BUILD_YEAR=\"${_build_year}\")

    # list(APPEND _definitions "%")

    # git info
    list(APPEND _definitions ${_prefix}_GIT_BRANCH=\"${_git_branch}\")
    list(APPEND _definitions ${_prefix}_GIT_LAST_COMMIT_HASH=\"${_git_hash}\")
    list(APPEND _definitions ${_prefix}_GIT_LAST_COMMIT_TIME=\"${_git_commit_time}\")
    list(APPEND _definitions ${_prefix}_GIT_LAST_COMMIT_AUTHOR=\"${_git_commit_author}\")
    list(APPEND _definitions ${_prefix}_GIT_LAST_COMMIT_EMAIL=\"${_git_commit_email}\")

    _qm_generate_config_helper()
endfunction()

# ----------------------------------
# Private functions
# ----------------------------------
function(_qm_calc_property_scope_helper _scope _prop)
    if(FUNC_TARGET)
        set(_scope TARGET ${FUNC_TARGET})
    elseif(FUNC_SOURCE)
        set(_scope SOURCE ${FUNC__SOURCE})
    elseif(FUNC_DIRECTORY)
        set(_scope DIRECTORY ${FUNC_DIRECTORY})
    elseif(FUNC_GLOBAL)
        set(_scope GLOBAL)
    elseif(QMSETUP_DEFINITION_SCOPE)
        set(_scope ${QMSETUP_DEFINITION_SCOPE})
    else()
        set(_scope GLOBAL)
    endif()

    qm_set_value(_prop FUNC_PROPERTY QMSETUP_DEFINITION_PROPERTY "CONFIG_DEFINITIONS")

    set(_scope ${_scope} PARENT_SCOPE)
    set(_prop ${_prop} PARENT_SCOPE)
endfunction()

function(_qm_generate_config_helper)
    set(_args)

    foreach(_item IN LISTS _definitions)
        list(APPEND _args "-D${_item}")
    endforeach()

    list(APPEND _args ${_file})

    if(NOT FUNC_NO_WARNING)
        list(APPEND _args "-w" ${FUNC_WARNING_FILE})
    endif()

    if(FUNC_PROJECT_NAME)
        list(APPEND _args "-p" ${FUNC_PROJECT_NAME})
    endif()

    if(FUNC_NO_HASH)
        list(APPEND _args "-f")
    endif()

    execute_process(COMMAND ${QMSETUP_CORECMD_EXECUTABLE} configure ${_args}
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        COMMAND_ERROR_IS_FATAL ANY
    )
endfunction()
