#[[
    Warning: This module is private, may be modified or removed in the future, please use with caution.
]] #

include_guard(DIRECTORY)

#[[
    Create the names of output files preserving relative dirs. (Ported from MOC command)

    qm_make_output_file(<infile> <prefix> <ext> <OUT>)

    OUT: output source file paths
#]]
function(qm_make_output_file _infile _prefix _ext _out)
    string(LENGTH ${CMAKE_CURRENT_BINARY_DIR} _binlength)
    string(LENGTH ${_infile} _infileLength)
    set(_checkinfile ${CMAKE_CURRENT_SOURCE_DIR})

    if(_infileLength GREATER _binlength)
        string(SUBSTRING "${_infile}" 0 ${_binlength} _checkinfile)

        if(_checkinfile STREQUAL "${CMAKE_CURRENT_BINARY_DIR}")
            file(RELATIVE_PATH _rel ${CMAKE_CURRENT_BINARY_DIR} ${_infile})
        else()
            file(RELATIVE_PATH _rel ${CMAKE_CURRENT_SOURCE_DIR} ${_infile})
        endif()
    else()
        file(RELATIVE_PATH _rel ${CMAKE_CURRENT_SOURCE_DIR} ${_infile})
    endif()

    if(CMAKE_HOST_WIN32 AND _rel MATCHES "^([a-zA-Z]):(.*)$") # absolute path
        set(_rel "${CMAKE_MATCH_1}_${CMAKE_MATCH_2}")
    endif()

    set(_outfile "${CMAKE_CURRENT_BINARY_DIR}/${_rel}")
    string(REPLACE ".." "__" _outfile ${_outfile})
    get_filename_component(_outpath ${_outfile} PATH)
    get_filename_component(_outfile ${_outfile} NAME_WLE)

    file(MAKE_DIRECTORY ${_outpath})
    set(${_out} ${_outpath}/${_prefix}${_outfile}.${_ext} PARENT_SCOPE)
endfunction()