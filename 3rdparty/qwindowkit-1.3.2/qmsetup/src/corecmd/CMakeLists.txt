project(qmcorecmd VERSION ${QMSETUP_VERSION})

string(TIMESTAMP _year "%Y")
set(RC_COPYRIGHT "Copyright 2023-${_year} Stdware Collections")
set(RC_DESCRIPTION "QMSetup Core Utility Command")

set(_src
    main.cpp
    sha-256.h
    sha-256.cpp
    utils.h
    utils.cpp
)

if(WIN32)
    list(APPEND _src utils_win.cpp)
else()
    list(APPEND _src utils_unix.cpp)
endif()

add_executable(${PROJECT_NAME} ${_src})
target_link_libraries(${PROJECT_NAME} PRIVATE syscmdline::syscmdline)

# Add features
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20 cxx_std_17)
set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_EXTENSIONS OFF
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

if(WIN32)
    target_link_libraries(${PROJECT_NAME} PRIVATE shlwapi)
    target_compile_definitions(${PROJECT_NAME} PRIVATE _CRT_SECURE_NO_WARNINGS)
endif()

if(WIN32)
    qm_add_win_rc(${PROJECT_NAME}
        COPYRIGHT ${RC_COPYRIGHT}
        DESCRIPTION ${RC_DESCRIPTION}
    )

    # Make sure Windows UAC does not believe it is an installer
    qm_add_win_manifest(${PROJECT_NAME}
        DESCRIPTION ${RC_DESCRIPTION}
    )
endif()

target_compile_definitions(${PROJECT_NAME} PRIVATE TOOL_DESC="${RC_DESCRIPTION}, Version ${QMSETUP_VERSION}")
target_compile_definitions(${PROJECT_NAME} PRIVATE TOOL_COPYRIGHT="${RC_COPYRIGHT}, checkout https://github.com/stdware/qmsetup")
target_compile_definitions(${PROJECT_NAME} PRIVATE TOOL_VERSION="${QMSETUP_VERSION}")

set_target_properties(${PROJECT_NAME} PROPERTIES EXPORT_NAME corecmd)

# Vcpkg requires the binary to be installed in "tools/${PORT}" directory
if(QMSETUP_VCPKG_TOOLS_HINT)
    set(_tools_dir tools/${QMSETUP_INSTALL_NAME})
else()
    set(_tools_dir ${CMAKE_INSTALL_BINDIR})
endif()

install(TARGETS ${PROJECT_NAME}
    EXPORT ${QMSETUP_INSTALL_NAME}Targets
    RUNTIME DESTINATION "${_tools_dir}" OPTIONAL
    LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}" OPTIONAL
    ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}" OPTIONAL
)

# Check patchelf
if (NOT WIN32 AND NOT APPLE)
    execute_process(
        COMMAND patchelf --version
        OUTPUT_VARIABLE _patchelf_version_output
        ERROR_QUIET
        OUTPUT_STRIP_TRAILING_WHITESPACE
    )

    if(NOT "${_patchelf_version_output}" MATCHES "patchelf")
        message(WARNING "Patchelf not found, the deploy feature won't work.")
    else()
        string(REGEX REPLACE "patchelf (.+)" "\\1" _patchelf_version ${_patchelf_version_output})
        message(STATUS "Found patchelf, version ${_patchelf_version}")
    endif()
endif()