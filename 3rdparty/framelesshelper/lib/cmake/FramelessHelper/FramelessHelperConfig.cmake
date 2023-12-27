#[[
  MIT License

  Copyright (C) 2021-2023 by wangwenx190 (Yuhang Zhao)

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in
  all copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  SOFTWARE.
]]


####### Expanded from @PACKAGE_INIT@ by configure_package_config_file() #######
####### Any changes to this file will be overwritten by the next CMake run ####
####### The input file was FramelessHelperConfig.cmake.in                            ########

get_filename_component(PACKAGE_PREFIX_DIR "${CMAKE_CURRENT_LIST_DIR}/../../../" ABSOLUTE)

macro(set_and_check _var _file)
  set(${_var} "${_file}")
  if(NOT EXISTS "${_file}")
    message(FATAL_ERROR "File or directory ${_file} referenced by variable ${_var} does not exist !")
  endif()
endmacro()

####################################################################################

set(_FramelessHelper_supported_components Core Widgets Quick)

foreach(_comp ${FramelessHelper_FIND_COMPONENTS})
    if(_comp IN_LIST _FramelessHelper_supported_components)
        set(__target FramelessHelper::${_comp})
        if(TARGET ${__target})
            continue()
        else()
            set(__target_full FramelessHelper${_comp})
            set(__targets_file "${CMAKE_CURRENT_LIST_DIR}/${__target_full}Targets.cmake")
            if(EXISTS "${__targets_file}")
                include("${__targets_file}")
                add_library(${__target} ALIAS FramelessHelper::${__target_full})
            else()
                set(FramelessHelper_FOUND FALSE)
                set(FramelessHelper_NOT_FOUND_MESSAGE "Can't find necessary configuration file for ${__target}, please make sure this component is built successfully and installed properly.")
                break()
            endif()
        endif()
    else()
        set(FramelessHelper_FOUND FALSE)
        set(FramelessHelper_NOT_FOUND_MESSAGE "Unknown component: ${__target}.")
        break()
    endif()
endforeach()

if(NOT DEFINED FramelessHelper_FOUND)
    set(FramelessHelper_FOUND TRUE)
    set(FramelessHelper_VERSION "2.5.0")
    set(FramelessHelper_VERSION_MAJOR "2")
    set(FramelessHelper_VERSION_MINOR "5")
    set(FramelessHelper_VERSION_PATCH "0")
    #set(FramelessHelper_VERSION_TWEAK "")
    set(FramelessHelper_DESCRIPTION "Cross-platform window customization framework for Qt Widgets and Qt Quick.")
    set(FramelessHelper_HOMEPAGE_URL "https://github.com/wangwenx190/framelesshelper/")
    set(FramelessHelper_COMMIT "")
    set(FramelessHelper_COMPILE_DATETIME "")
endif()

include(FeatureSummary)
set_package_properties(FramelessHelper PROPERTIES
    DESCRIPTION "Cross-platform window customization framework for Qt Widgets and Qt Quick."
    URL "https://github.com/wangwenx190/framelesshelper/"
)
