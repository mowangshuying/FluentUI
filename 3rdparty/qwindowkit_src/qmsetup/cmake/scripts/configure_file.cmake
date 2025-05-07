# MIT License
# Copyright (c) 2023 SineStriker

# Description:
# Command that executes `configure_file`.

# Usage:
# cmake
# -D input=<file>
# -D output=<file>
# -D force=TRUE/FALSE
# [-D args=<args...>]
# -P configure_file.cmake

if(force AND EXISTS ${_output})
    file(REMOVE ${_output})
endif()

configure_file(${input} ${output} ${args})