# MIT License
# Copyright (c) 2023 SineStriker

# Description:
# Copy file or directory to destination if different.
# Mainly use `file(INSTALL)` to implement.

# Usage:
# cmake
# -D src=<files/dirs...>
# -D dest=<dir>
# [-D dest_base=<dir>]
# [-D args=<args...>]
# -P copy.cmake

# Check required arguments
if(NOT src)
    message(FATAL_ERROR "src not defined.")
endif()

if(NOT dest)
    message(FATAL_ERROR "dest not defined.")
endif()

# Calculate destination
if(dest_base)
    set(_dest_base ${dest_base})
else()
    set(_dest_base ${CMAKE_BINARY_DIR})
endif()

get_filename_component(_dest ${dest} ABSOLUTE BASE_DIR ${_dest_base})

# Copy
foreach(_file IN LISTS src)
    # Avoid using `get_filename_component` to keep the trailing slash
    set(_path ${_file})

    if(NOT IS_ABSOLUTE ${_path})
        set(_path "${CMAKE_BINARY_DIR}/${_path}")
    endif()

    if(IS_DIRECTORY ${_path})
        file(INSTALL DESTINATION ${_dest}
            TYPE DIRECTORY
            FILES ${_path}
            ${args}
        )
    else()
        set(_paths)

        if(${_path} MATCHES "\\*\\*")
            file(GLOB_RECURSE _paths ${_path})
        else()
            file(GLOB _paths ${_path})
        endif()

        file(INSTALL DESTINATION ${_dest}
            TYPE FILE
            FILES ${_paths}
            ${args}
        )
    endif()
endforeach()
