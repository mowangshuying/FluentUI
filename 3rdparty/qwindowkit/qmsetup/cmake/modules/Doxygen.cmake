include_guard(DIRECTORY)

#[[
    Add Doxygen documentation generating target.

    qm_setup_doxygen(<target>
        [NAME           <name>]
        [VERSION        <version>]
        [DESCRIPTION    <desc>]
        [LOGO           <file>]
        [MDFILE         <file>]
        [OUTPUT_DIR     <dir>]
        [INSTALL_DIR    <dir>]

        [TAGFILES           <file> ...]
        [GENERATE_TAGFILE   <file>]
        
        [INPUT                  <file> ...]
        [INCLUDE_DIRECTORIES    <dir> ...]
        [COMPILE_DEFINITIONS    <NAME=VALUE> ...]
        [TARGETS                <target> ...]
        [ENVIRONMENT_EXPORTS    <key> ...]
        [NO_EXPAND_MACROS       <macro> ...]
        [DEPENDS                <dependency> ...]
    )
]] #
function(qm_setup_doxygen _target)
    set(options)
    set(oneValueArgs NAME VERSION DESCRIPTION LOGO MDFILE OUTPUT_DIR INSTALL_DIR GENERATE_TAGFILE)
    set(multiValueArgs INPUT TAGFILES INCLUDE_DIRECTORIES COMPILE_DEFINITIONS TARGETS ENVIRONMENT_EXPORTS
        NO_EXPAND_MACROS DEPENDS
    )
    cmake_parse_arguments(FUNC "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    if(NOT DOXYGEN_EXECUTABLE)
        message(FATAL_ERROR "qm_setup_doxygen: DOXYGEN_EXECUTABLE not defined. Add find_package(Doxygen) to CMake to enable.")
    endif()

    set(DOXYGEN_FILE_DIR ${QMSETUP_MODULES_DIR}/doxygen)

    if(FUNC_NAME)
        set(_name ${FUNC_NAME})
    else()
        set(_name ${PROJECT_NAME})
    endif()

    if(FUNC_VERSION)
        set(_version ${FUNC_VERSION})
    else()
        set(_version ${PROJECT_VERSION})
    endif()

    if(FUNC_DESCRIPTION)
        set(_desc ${FUNC_DESCRIPTION})
    elseif(PROJECT_DESCRIPTION)
        set(_desc ${PROJECT_DESCRIPTION})
    else()
        set(_desc ${_name})
    endif()

    if(FUNC_LOGO)
        set(_logo ${FUNC_LOGO})
    else()
        set(_logo)
    endif()

    if(FUNC_MDFILE)
        set(_mdfile ${FUNC_MDFILE})
    else()
        set(_mdfile)
    endif()

    if(FUNC_GENERATE_TAGFILE)
        set(_tagfile ${FUNC_GENERATE_TAGFILE})
    else()
        set(_tagfile)
    endif()

    set(_sep " \\\n    ")

    # Generate include file
    set(_doxy_includes "${CMAKE_CURRENT_BINARY_DIR}/cmake/doxygen_${_target}_$<CONFIG>.inc")
    set(_doxy_output_dir "${CMAKE_CURRENT_BINARY_DIR}/doxygen_${_target}")

    set(_input "")
    set(_tagfiles "")
    set(_includes "")
    set(_defines "")
    set(_no_expand "")

    if(FUNC_INPUT)
        set(_input "INPUT = $<JOIN:${FUNC_INPUT},${_sep}>\n\n")
    else()
        set(_input "INPUT = \n\n")
    endif()

    if(FUNC_TAGFILES)
        set(_tagfiles "TAGFILES = $<JOIN:${FUNC_TAGFILES},${_sep}>\n\n")
    else()
        set(_tagfiles "TAGFILES = \n\n")
    endif()

    if(FUNC_INCLUDE_DIRECTORIES)
        set(_includes "INCLUDE_PATH = $<JOIN:${FUNC_INCLUDE_DIRECTORIES},${_sep}>\n\n")
    else()
        set(_includes "INCLUDE_PATH = \n\n")
    endif()

    if(FUNC_COMPILE_DEFINITIONS)
        set(_defines "PREDEFINED = $<JOIN:${FUNC_COMPILE_DEFINITIONS},${_sep}>\n\n")
    else()
        set(_defines "PREDEFINED = \n\n")
    endif()

    if(FUNC_NO_EXPAND_MACROS)
        set(_temp_list)

        foreach(_item IN LISTS FUNC_NO_EXPAND_MACROS)
            list(APPEND _temp_list "${_item}=")
        endforeach()

        set(_no_expand "PREDEFINED += $<JOIN:${_temp_list},${_sep}>\n\n")
        unset(_temp_list)
    endif()

    # Extra
    set(_extra_arguments)

    if(FUNC_TARGETS)
        foreach(item IN LISTS FUNC_TARGETS)
            set(_extra_arguments
                "${_extra_arguments}INCLUDE_PATH += $<JOIN:$<TARGET_PROPERTY:${item},INCLUDE_DIRECTORIES>,${_sep}>\n\n")
            set(_extra_arguments
                "${_extra_arguments}PREDEFINED += $<JOIN:$<TARGET_PROPERTY:${item},COMPILE_DEFINITIONS>,${_sep}>\n\n")
        endforeach()
    endif()

    if(FUNC_OUTPUT_DIR)
        set(_doxy_output_dir ${FUNC_OUTPUT_DIR})
    endif()

    if(_mdfile)
        set(_extra_arguments "${_extra_arguments}INPUT += ${_mdfile}\n\n")
    endif()

    file(GENERATE
        OUTPUT "${_doxy_includes}"
        CONTENT "${_input}${_tagfiles}${_includes}${_defines}${_extra_arguments}${_no_expand}"
    )

    set(_env)

    foreach(_export IN LISTS FUNC_ENVIRONMENT_EXPORTS)
        if(NOT DEFINED "${_export}")
            message(FATAL_ERROR "qm_setup_doxygen: ${_export} is not known when trying to export it.")
        endif()

        list(APPEND _env "${_export}=${${_export}}")
    endforeach()

    list(APPEND _env "DOXY_FILE_DIR=${DOXYGEN_FILE_DIR}")
    list(APPEND _env "DOXY_INCLUDE_FILE=${_doxy_includes}")

    list(APPEND _env "DOXY_PROJECT_NAME=${_name}")
    list(APPEND _env "DOXY_PROJECT_VERSION=${_version}")
    list(APPEND _env "DOXY_PROJECT_BRIEF=${_desc}")
    list(APPEND _env "DOXY_PROJECT_LOGO=${_logo}")
    list(APPEND _env "DOXY_MAINPAGE_MD_FILE=${_mdfile}")

    set(_build_command "${CMAKE_COMMAND}" "-E" "env"
        ${_env}
        "DOXY_OUTPUT_DIR=${_doxy_output_dir}"
        "DOXY_GENERATE_TAGFILE=${_tagfile}"
        "${DOXYGEN_EXECUTABLE}"
        "${DOXYGEN_FILE_DIR}/Doxyfile"
    )

    if(FUNC_DEPENDS)
        set(_dependencies DEPENDS ${FUNC_DEPENDS})
    endif()

    if(_tagfile)
        get_filename_component(_tagfile_dir ${_tagfile} ABSOLUTE)
        get_filename_component(_tagfile_dir ${_tagfile_dir} DIRECTORY)
        set(_make_tagfile_dir_cmd COMMAND ${CMAKE_COMMAND} -E make_directory ${_tagfile_dir})
    else()
        set(_make_tagfile_dir_cmd)
    endif()

    add_custom_target(${_target}
        COMMAND ${CMAKE_COMMAND} -E make_directory ${_doxy_output_dir}
        ${_make_tagfile_dir_cmd}
        COMMAND ${_build_command}
        COMMENT "Building HTML documentation"
        WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
        VERBATIM
        ${_dependencies}
    )

    if(FUNC_INSTALL_DIR)
        set(_install_dir ${FUNC_INSTALL_DIR})

        if(_tagfile)
            get_filename_component(_name ${_tagfile} NAME)
            set(_install_tagfile ${_name})
        else()
            set(_install_tagfile)
        endif()

        set(_install_command "${CMAKE_COMMAND}" "-E" "env"
            ${_env}
            "DOXY_OUTPUT_DIR=\${_install_dir}"
            "DOXY_GENERATE_TAGFILE=\${_install_dir}/${_install_tagfile}"
            "${DOXYGEN_EXECUTABLE}"
            "${DOXYGEN_FILE_DIR}/Doxyfile"
        )

        set(_install_command_quoted)

        foreach(_item IN LISTS _install_command)
            set(_install_command_quoted "${_install_command_quoted}\"${_item}\" ")
        endforeach()

        install(CODE "
            message(STATUS \"Installing HTML documentation\")
            get_filename_component(_install_dir \"${_install_dir}\" ABSOLUTE BASE_DIR \${CMAKE_INSTALL_PREFIX})
            file(MAKE_DIRECTORY \${_install_dir})
            execute_process(
                COMMAND ${_install_command_quoted}
                WORKING_DIRECTORY \"${CMAKE_CURRENT_SOURCE_DIR}\"
                OUTPUT_QUIET
            )
        ")
    endif()
endfunction()