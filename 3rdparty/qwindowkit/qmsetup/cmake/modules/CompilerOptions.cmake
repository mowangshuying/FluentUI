include_guard(DIRECTORY)

#[[
    Disable all possible warnings from the compiler.

    qm_compiler_no_warnings()
]] #
macro(qm_compiler_no_warnings)
    foreach(__lang C CXX)
        if(NOT "x${CMAKE_${__lang}_FLAGS}" STREQUAL "x")
            if(MSVC)
                string(REGEX REPLACE " [/-]W[01234] " " " CMAKE_${__lang}_FLAGS ${CMAKE_${__lang}_FLAGS})
            else()
                string(REGEX REPLACE " -W(all)?(extra)? " " " CMAKE_${__lang}_FLAGS ${CMAKE_${__lang}_FLAGS})
                string(REGEX REPLACE " -[W]?pedantic " " " CMAKE_${__lang}_FLAGS ${CMAKE_${__lang}_FLAGS})
            endif()
        endif()
        string(APPEND CMAKE_${__lang}_FLAGS " -w ")
    endforeach()
    if(MSVC)
        add_compile_definitions(-D_CRT_NON_CONFORMING_SWPRINTFS)
        add_compile_definitions(-D_CRT_SECURE_NO_WARNINGS -D_CRT_SECURE_NO_DEPRECATE)
        add_compile_definitions(-D_CRT_NONSTDC_NO_WARNINGS -D_CRT_NONSTDC_NO_DEPRECATE)
        add_compile_definitions(-D_SCL_SECURE_NO_WARNINGS -D_SCL_SECURE_NO_DEPRECATE)
        add_compile_definitions(-D_SILENCE_ALL_MS_EXT_DEPRECATION_WARNINGS)
    else()
        foreach(__lang C CXX)
            string(APPEND CMAKE_${__lang}_FLAGS " -fpermissive ")
        endforeach()
    endif()
endmacro()

#[[
    Enable all possible warnings from the compiler.

    qm_compiler_max_warnings()
]] #
function(qm_compiler_max_warnings)
    if(MSVC)
        add_compile_options(-W4)
    elseif("x${CMAKE_CXX_COMPILER_ID}" STREQUAL "xClang")
        add_compile_options(-Weverything)
    else()
        add_compile_options(-Wall -Wextra -Wpedantic)
    endif()
endfunction()

#[[
    Treat all warnings as errors.

    qm_compiler_warnings_are_errors()
]] #
function(qm_compiler_warnings_are_errors)
    if(MSVC)
        add_compile_options(-WX)
    else()
        add_compile_options(-Werror)
    endif()
endfunction()

#[[
    Prevent the compiler from receiving unknown parameters.

    qm_compiler_no_unknown_options()
]] #
function(qm_compiler_no_unknown_options)
    if(MSVC)
        if(MSVC_VERSION GREATER_EQUAL 1930) # Visual Studio 2022 version 17.0
            add_compile_options(-options:strict)
        endif()
        add_link_options(-WX)
    endif()
endfunction()

#[[
    Remove all unused code from the final binary.

    qm_compiler_eliminate_dead_code()
]] #
function(qm_compiler_eliminate_dead_code)
    if(MSVC)
        add_compile_options(-Gw -Gy -Zc:inline)
        add_link_options(-OPT:REF -OPT:ICF -OPT:LBR)
    else()
        add_compile_options(-ffunction-sections -fdata-sections)
        if(APPLE)
            add_link_options(-Wl,-dead_strip)
        else()
            add_link_options(-Wl,--as-needed -Wl,--strip-all -Wl,--gc-sections)
        endif()
        if("x${CMAKE_CXX_COMPILER_ID}" STREQUAL "xClang")
            add_link_options(-Wl,--icf=all)
        endif()
    endif()
endfunction()

#[[
    Only export symbols which are marked to be exported, just like MSVC.

    qm_compiler_dont_export_by_default()
]] #
macro(qm_compiler_dont_export_by_default)
    set(CMAKE_C_VISIBILITY_PRESET "hidden")
    set(CMAKE_CXX_VISIBILITY_PRESET "hidden")
    set(CMAKE_VISIBILITY_INLINES_HIDDEN ON)
endmacro()

#[[
    Enable all possible security issue mitigations from your compiler.

    qm_compiler_enable_secure_code()
]] #
macro(qm_compiler_enable_secure_code)
    if(MSVC)
        add_compile_options(-GS -sdl -guard:cf)
        add_link_options(-DYNAMICBASE -FIXED:NO -NXCOMPAT -GUARD:CF)
        if(CMAKE_SIZEOF_VOID_P EQUAL 4)
            add_link_options(-SAFESEH)
        endif()
        if(CMAKE_SIZEOF_VOID_P EQUAL 8)
            add_link_options(-HIGHENTROPYVA)
        endif()
        if(MSVC_VERSION GREATER_EQUAL 1920) # Visual Studio 2019 version 16.0
            add_link_options(-CETCOMPAT)
        endif()
        if(MSVC_VERSION GREATER_EQUAL 1925) # Visual Studio 2019 version 16.5
            add_compile_options(-Qspectre-load)
        elseif(MSVC_VERSION GREATER_EQUAL 1912) # Visual Studio 2017 version 15.5
            add_compile_options(-Qspectre)
        endif()
        if(MSVC_VERSION GREATER_EQUAL 1927) # Visual Studio 2019 version 16.7
            if(CMAKE_SIZEOF_VOID_P EQUAL 8)
                add_compile_options(-guard:ehcont)
                add_link_options(-guard:ehcont)
            endif()
        endif()
        if(MSVC_VERSION GREATER_EQUAL 1930) # Visual Studio 2022 version 17.0
            add_compile_options(-Qspectre-jmp)
        endif()
    elseif(MINGW)
        if("x${CMAKE_CXX_COMPILER_ID}" STREQUAL "xClang")
            add_compile_options(-mguard=cf)
            add_link_options(-mguard=cf)
        else()
        endif()
    else()
        add_compile_options(-mshstk -ftrivial-auto-var-init=pattern
            -fstack-protector-strong -fstack-clash-protection
            -fcf-protection=full)
        add_link_options(-Wl,-z,relro,-z,now)
        if("x${CMAKE_CXX_COMPILER_ID}" STREQUAL "xClang")
            add_compile_options(-mretpoline -mspeculative-load-hardening)
            if(NOT APPLE)
                add_compile_options(-fsanitize=cfi -fsanitize-cfi-cross-dso)
            endif()
        endif()
    endif()
endmacro()

#[[
    Enable all possible Qt coding style policies.

    qm_compiler_enable_strict_qt(
        TARGETS <target1> <target2> ... <targetN>
        [NO_DEPRECATED_API]
        [ALLOW_KEYWORD]
        [ALLOW_UNSAFE_FLAGS]
    )

    NO_DEPRECATED_API: Disable the use of any deprecated Qt APIs. Only has effect since Qt6.
    ALLOW_KEYWORD: Allow the use of the traditional Qt keywords such as "signal" "slot" "emit".
    ALLOW_UNSAFE_FLAGS: Allow the use of the unsafe QFlags (unsafe: can be implicitly cast to and from "int").
]] #
function(qm_compiler_enable_strict_qt)
    cmake_parse_arguments(arg "NO_DEPRECATED_API;ALLOW_KEYWORD;ALLOW_UNSAFE_FLAGS" "" "TARGETS" ${ARGN})
    if(NOT arg_TARGETS)
        message(AUTHOR_WARNING "qm_compiler_enable_strict_qt: you need to specify at least one target!")
        return()
    endif()
    if(arg_UNPARSED_ARGUMENTS)
        message(AUTHOR_WARNING "qm_compiler_enable_strict_qt: Unrecognized arguments: ${arg_UNPARSED_ARGUMENTS}")
    endif()
    foreach(_target IN LISTS arg_TARGETS)
        if(NOT TARGET ${_target})
            message(AUTHOR_WARNING "qm_compiler_enable_strict_qt: ${_target} is not a valid CMake target!")
            continue()
        endif()
        target_compile_definitions(${_target} PRIVATE
            QT_NO_CAST_TO_ASCII
            QT_NO_CAST_FROM_ASCII
            QT_NO_CAST_FROM_BYTEARRAY
            QT_NO_URL_CAST_FROM_STRING
            QT_NO_NARROWING_CONVERSIONS_IN_CONNECT
            QT_NO_JAVA_STYLE_ITERATORS
            QT_NO_FOREACH QT_NO_QFOREACH
            QT_NO_AS_CONST QT_NO_QASCONST
            QT_NO_EXCHANGE QT_NO_QEXCHANGE
            QT_NO_QPAIR
            QT_NO_INTEGRAL_STRINGS
            QT_NO_USING_NAMESPACE
            QT_NO_CONTEXTLESS_CONNECT
            QT_EXPLICIT_QFILE_CONSTRUCTION_FROM_PATH
            QT_USE_NODISCARD_FILE_OPEN
            QT_USE_QSTRINGBUILDER
            QT_USE_FAST_OPERATOR_PLUS
            QT_DEPRECATED_WARNINGS # Have no effect since 5.13
            QT_DEPRECATED_WARNINGS_SINCE=0x0A0000 # Deprecated since 6.5
            QT_WARN_DEPRECATED_UP_TO=0x0A0000 # Available since 6.5
        )
        if(arg_NO_DEPRECATED_API)
            target_compile_definitions(${_target} PRIVATE
                QT_DISABLE_DEPRECATED_BEFORE=0x0A0000 # Deprecated since 6.5
                QT_DISABLE_DEPRECATED_UP_TO=0x0A0000 # Available since 6.5
            )
        endif()
        # On Windows enabling this flag requires us re-compile Qt with this flag enabled,
        # so only enable it on non-Windows platforms.
        if(NOT WIN32)
            target_compile_definitions(${_target} PRIVATE
                QT_STRICT_ITERATORS
            )
        endif()
        # We handle this flag specially because some Qt headers may still use the
        # traditional keywords (especially some private headers).
        if(NOT arg_ALLOW_KEYWORD)
            target_compile_definitions(${_target} PRIVATE
                QT_NO_KEYWORDS
            )
        endif()
        # We handle this flag specially because some Qt headers may still use the
        # unsafe flags (especially some QtQuick headers).
        if(NOT arg_ALLOW_UNSAFE_FLAGS)
            target_compile_definitions(${_target} PRIVATE
                QT_TYPESAFE_FLAGS
            )
        endif()
    endforeach()
endfunction()
