include_guard(DIRECTORY)

#[[
    Add rules for creating Google Protobuf source files.

    qm_create_protobuf(<OUT>
        INPUT <files...>
        [OUTPUT_DIR <dir>]
        [TARGET <target>]
        [INCLUDE_DIRECTORIES <dirs...>]
        [OPTIONS <options...>]
        [DEPENDS <deps...>]
        [CREATE_ONCE]
    )

    INPUT: source files
    OUTPUT_DIR: output directory

    TARGET: add a custom target to run the generating command

    INCLUDE_DIRECTORIES: extra include directories
    OPTIONS: extra options passed to protobuf compiler
    DEPENDS: dependencies

    CREATE_ONCE: create proto code files at configure phase if not exist

    OUT: output source file paths
#]]
function(qm_create_protobuf _out)
    set(options CREATE_ONCE)
    set(oneValueArgs OUTPUT_DIR TARGET)
    set(multiValueArgs INPUT INCLUDE_DIRECTORIES OPTIONS DEPENDS)
    cmake_parse_arguments(FUNC "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    # Find `protoc`
    if(NOT PROTOC_EXECUTABLE)
        if(NOT TARGET protobuf::protoc)
            message(FATAL_ERROR "qm_create_protobuf: protobuf compiler not found. Add find_package(Protobuf) to CMake to enable.")
        endif()

        get_target_property(PROTOC_EXECUTABLE protobuf::protoc LOCATION)

        if(NOT PROTOC_EXECUTABLE)
            message(FATAL_ERROR "qm_create_protobuf: failed to get the location of `protoc`.")
        endif()

        # Cache value
        set(PROTOC_EXECUTABLE ${PROTOC_EXECUTABLE} PARENT_SCOPE)
    endif()

    if(NOT FUNC_INPUT)
        message(FATAL_ERROR "qm_create_protobuf: INPUT not specified.")
    endif()

    if(FUNC_OUTPUT_DIR)
        get_filename_component(_out_dir ${FUNC_OUTPUT_DIR} ABSOLUTE)
        file(MAKE_DIRECTORY ${_out_dir})
    else()
        set(_out_dir ${CMAKE_CURRENT_BINARY_DIR})
    endif()

    # Collect include paths and out files
    set(_include_options)
    set(_out_files)
    set(_input_names)

    foreach(_item IN LISTS FUNC_INCLUDE_DIRECTORIES)
        get_filename_component(_abs_path ${_item} ABSOLUTE)
        list(APPEND _include_options -I${_abs_path})
    endforeach()

    foreach(_item IN LISTS FUNC_INPUT)
        get_filename_component(_item ${_item} ABSOLUTE)
        get_filename_component(_abs_path ${_item} DIRECTORY)
        list(APPEND _include_options -I${_abs_path})
    endforeach()

    list(REMOVE_DUPLICATES _include_options)

    set(_create_once_warning)
    set(_create_once_warning_printed off)

    # Prepare for create once
    if(FUNC_CREATE_ONCE)
        # Check if options contain generator expressions
        foreach(_opt IN LISTS _include_options LISTS FUNC_OPTIONS)
            string(GENEX_STRIP "${_opt}" _no_genex)

            if(NOT _no_genex STREQUAL _opt)
                set(_create_once_warning "options contain generator expressions, skip generating source file now")
                break()
            endif()
        endforeach()
    endif()

    foreach(_item IN LISTS FUNC_INPUT)
        get_filename_component(_basename ${_item} NAME_WLE)
        list(APPEND _out_files ${_out_dir}/${_basename}.pb.h ${_out_dir}/${_basename}.pb.cc)

        get_filename_component(_name ${_item} NAME)
        list(APPEND _input_names ${_name})

        if(FUNC_CREATE_ONCE AND(NOT EXISTS ${_out_dir}/${_basename}.pb.h OR NOT EXISTS ${_out_dir}/${_basename}.pb.cc))
            if(_create_once_warning)
                if(NOT _create_once_warning_printed)
                    message(WARNING "qm_create_protobuf: ${_create_once_warning}")
                    set(_create_once_warning_printed on)
                endif()
            else()
                get_filename_component(_abs_file ${_item} ABSOLUTE)

                if(NOT EXISTS ${_abs_file})
                    message(WARNING "qm_create_protobuf: input file \"${_name}\" is not available, skip generating source file now")
                else()
                    message(STATUS "Protoc: Generating ${_basename}.pb.h, ${_basename}.pb.cc")
                    execute_process(COMMAND
                        ${PROTOC_EXECUTABLE} --cpp_out=${_out_dir} ${_include_options} ${FUNC_OPTIONS} ${_name}
                    )
                endif()
            endif()
        endif()

        add_custom_command(
            OUTPUT ${_out_dir}/${_basename}.pb.h ${_out_dir}/${_basename}.pb.cc
            COMMAND ${PROTOC_EXECUTABLE} --cpp_out=${_out_dir} ${_include_options} ${FUNC_OPTIONS} ${_name}
            DEPENDS ${_item} ${FUNC_DEPENDS}
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
            VERBATIM
        )
    endforeach()

    if(FUNC_TARGET)
        if(NOT TARGET ${FUNC_TARGET})
            add_custom_target(${FUNC_TARGET})
        endif()

        add_dependencies(${FUNC_TARGET} ${_out_files})
    endif()

    set(${_out} ${_out_files} PARENT_SCOPE)
endfunction()
