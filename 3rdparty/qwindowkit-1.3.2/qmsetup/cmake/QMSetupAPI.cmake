cmake_minimum_required(VERSION 3.19)

#[[
    NOTICE
    --------
    Since Qt official CMake modules sets private header directory variables when you call `find_package(Qt)`
    only if the Qt targets hasn't been defined, if we place `find_package(Qt)` in a function, the variable
    will be cleared while the target remains after the function returns, as a result, we can never get the
    private header directory variables again.

    Therefore, never wrap `find_package(Qt)` in a function, use macro instead, any macros that wraps it also
    shouldn't be wrapped in any function.
]] #
set(QMSETUP_MODULES_DIR ${CMAKE_CURRENT_LIST_DIR})

if(WIN32)
    set(QMSETUP_SHARED_LIBRARY_CATEGORY bin)
    set(QMSETUP_NULL_FILE "NUL")
    set(QMSETUP_REGEX_ABSOLUTE_PATH "^[a-zA-Z]:|\\\\")
else()
    set(QMSETUP_SHARED_LIBRARY_CATEGORY lib)
    set(QMSETUP_NULL_FILE "/dev/null")
    set(QMSETUP_REGEX_ABSOLUTE_PATH "^/")
endif()

set(QMSETUP_IGNORE_STDOUT > ${QMSETUP_NULL_FILE})
set(QMSETUP_IGNORE_STDERR 2> ${QMSETUP_NULL_FILE})
set(QMSETUP_IGNORE_STDOUT_STDERR > ${QMSETUP_NULL_FILE} 2>&1)

if(TARGET qmsetup::corecmd)
    get_target_property(QMSETUP_CORECMD_EXECUTABLE qmsetup::corecmd LOCATION)
else()
    set(QMSETUP_CORECMD_EXECUTABLE)
endif()

if(NOT DEFINED QMSETUP_FIND_QT_ORDER)
    set(QMSETUP_FIND_QT_ORDER Qt6 Qt5)
endif()

include_guard(DIRECTORY)

#[[
    Include modules of this library.

    qm_import(<module...>)
]] #
macro(qm_import)
    foreach(_module ${ARGN})
        if(NOT _module MATCHES "(.+)\\.cmake")
            set(_module "${_module}.cmake")
        endif()

        set(_module_path "${QMSETUP_MODULES_DIR}/modules/${_module}")

        if(NOT EXISTS "${_module_path}")
            message(FATAL_ERROR "qm_import: module \"${_module}\" not found.")
        endif()

        include("${_module_path}")
    endforeach()
endmacro()

#[[
    Include all modules of this library.

    qm_import_all()
]] #
macro(qm_import_all)
    file(GLOB _tmp_modules "${QMSETUP_MODULES_DIR}/modules/*.cmake")

    foreach(_module IN LISTS _tmp_modules)
        include("${_module}")
    endforeach()

    unset(_tmp_modules)
endmacro()

#[[
    Find third-party packages by including scripts in `find-modules`.

    qm_find_package(<module...>)
]] #
macro(qm_find_package)
    foreach(_module ${ARGN})
        if(NOT _module MATCHES "(.+)\\.cmake")
            set(_module "${_module}.cmake")
        endif()

        set(_module_path "${QMSETUP_MODULES_DIR}/find-modules/${_module}")

        # Prepend "Find" to the file name
        if(NOT EXISTS "${_module_path}")
            set(_module_path "${QMSETUP_MODULES_DIR}/find-modules/Find${_module}")
        endif()

        if(NOT EXISTS "${_module_path}")
            message(FATAL_ERROR "qm_find_package: find script \"${_module}\" not found.")
        endif()

        include("${_module_path}")
    endforeach()
endmacro()

#[[
    Parse version and create seq vars with specified prefix.

    qm_parse_version(<prefix> <version>)
]] #
function(qm_parse_version _prefix _version)
    string(REPLACE "." ";" _version_list ${_version})
    list(LENGTH _version_list _version_count)
    list(PREPEND _version_list 0) # Add placeholder

    foreach(_i RANGE 1 4)
        if(_i LESS_EQUAL _version_count)
            list(GET _version_list ${_i} _item)
        else()
            set(_item 0)
        endif()

        set(${_prefix}_${_i} ${_item} PARENT_SCOPE)
    endforeach()
endfunction()

#[[
    Get shorter version number.

    qm_crop_version(<VAR> <version> <count>)
]] #
function(qm_crop_version _var _version _count)
    qm_parse_version(FUNC ${_version})

    set(_list)

    foreach(_i RANGE 1 ${_count})
        list(APPEND _list ${FUNC_${_i}})
    endforeach()

    string(JOIN "." _short_version ${_list})
    set(${_var} ${_short_version} PARENT_SCOPE)
endfunction()

#[[
    Tell if the given paths are same in canonical form.

    qm_paths_equal(<VAR> <path1> <path2>)
]] #
function(qm_paths_equal _out _path1 _path2)
    # cmake_path(NORMAL_PATH) is introduced in CMake 3.20, we don't use it
    # We call `get_filename_component` twice to normalize the paths
    get_filename_component(_path1 ${_path1} ABSOLUTE)
    get_filename_component(_path1 ${_path1} REALPATH)

    get_filename_component(_path2 ${_path2} ABSOLUTE)
    get_filename_component(_path2 ${_path2} REALPATH)

    if(_path1 STREQUAL _path2)
        set(${_out} on PARENT_SCOPE)
    else()
        set(${_out} off PARENT_SCOPE)
    endif()
endfunction()

#[[
    Set value if valid, otherwise use default.

    qm_set_value(<key> <maybe_value...> <default>)
]] #
function(qm_set_value _key)
    set(_args "${ARGN}")
    list(POP_BACK _args _default)

    foreach(_item IN LISTS _args)
        if(${_item})
            set(${_key} ${${_item}} PARENT_SCOPE)
            return()
        endif()
    endforeach()

    set(${_key} ${_default} PARENT_SCOPE)
endfunction()

#[[
    Skip CMAKE_AUTOMOC for sources files or ones in directories.

    qm_skip_automoc(<file/dir...>)
]] #
function(qm_skip_automoc)
    foreach(_item ${ARGN})
        get_filename_component(_item ${_item} ABSOLUTE)

        if(IS_DIRECTORY ${_item})
            file(GLOB _src
                ${_item}/*.h ${_item}/*.hpp
                ${_item}/*.hh ${_item}/*.hxx
                ${_item}/*.cpp ${_item}/*.cxx
                ${_item}/*.c ${_item}/*.cc
                ${_item}/*.m ${_item}/*.mm
            )
            set_source_files_properties(
                ${_src} PROPERTIES SKIP_AUTOMOC ON
            )
        elseif(EXISTS ${_item})
            set_source_files_properties(
                ${_item} PROPERTIES SKIP_AUTOMOC ON
            )
        endif()
    endforeach()
endfunction()

#[[
    Find Qt libraries. Don't wrap it in any functions.

    qm_find_qt(<modules...> [QUIET | REQUIRED | EXACT])
#]]
macro(qm_find_qt)
    set(options QUIET REQUIRED EXACT)
    set(oneValueArgs)
    set(multiValueArgs)
    cmake_parse_arguments(FUNC "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    set(_qm_find_qt_options)

    if(FUNC_QUIET)
        list(APPEND _qm_find_qt_options QUIET)
    elseif(FUNC_REQUIRED)
        list(APPEND _qm_find_qt_options REQUIRED)
    elseif(FUNC_EXACT)
        list(APPEND _qm_find_qt_options EXACT)
    endif()

    if(NOT _qm_find_qt_options)
        set(_qm_find_qt_options REQUIRED)
    endif()

    foreach(_module ${FUNC_UNPARSED_ARGUMENTS})
        if(NOT QT_VERSION_MAJOR)
            find_package(QT NAMES ${QMSETUP_FIND_QT_ORDER} COMPONENTS ${_module} ${_qm_find_qt_options})
        endif()

        if(NOT TARGET Qt${QT_VERSION_MAJOR}::${_module})
            find_package(Qt${QT_VERSION_MAJOR} COMPONENTS ${_module} ${_qm_find_qt_options})
        endif()
    endforeach()

    unset(_qm_find_qt_options)
endmacro()

#[[
    Link Qt libraries. Don't wrap it in any functions.

    qm_link_qt(<target> <scope> <modules...>)
#]]
macro(qm_link_qt _target _scope)
    foreach(_module ${ARGN})
        qm_find_qt(${_module})
        target_link_libraries(${_target} ${_scope} Qt${QT_VERSION_MAJOR}::${_module})
    endforeach()
endmacro()

#[[
    Include Qt private header directories. Don't wrap it in any functions.

    qm_include_qt_private(<target> <scope> <modules...>)
#]]
macro(qm_include_qt_private _target _scope)
    foreach(_module ${ARGN})
        qm_find_qt(${_module}Private QUIET)
        if (TARGET Qt${QT_VERSION_MAJOR}::${_module}Private)
            target_link_libraries(${_target} ${_scope} Qt${QT_VERSION_MAJOR}::${_module}Private)
        else()
            qm_find_qt(${_module})
            target_include_directories(${_target} ${_scope} ${Qt${QT_VERSION_MAJOR}${_module}_PRIVATE_INCLUDE_DIRS})
        endif()
    endforeach()
endmacro()

#[[
    Helper to set or append all kinds of attributes to a target. Don't wrap it in any functions.

    qm_configure_target(<target>
        [SOURCES           <files>]

        [LINKS             <libs>]
        [LINKS_INTERFACE   <libs>]
        [LINKS_PRIVATE     <libs>]

        [INCLUDE           <dirs>]
        [INCLUDE_INTERFACE <dirs>]
        [INCLUDE_PRIVATE   <dirs>]

        [LINKDIR           <dirs>]
        [LINKDIR_INTERFACE <dirs>]
        [LINKDIR_PRIVATE   <dirs>]

        [DEFINES           <defs>]
        [DEFINES_INTERFACE <defs>]
        [DEFINES_PRIVATE   <defs>]

        [FEATURES           <features>]
        [FEATURES_INTERFACE <features>]
        [FEATURES_PRIVATE   <features>]

        [CCFLAGS           <flags>]
        [CCFLAGS_INTERFACE <flags>]
        [CCFLAGS_PUBLIC    <flags>]

        [LDFLAGS           <flags>]
        [LDFLAGS_INTERFACE <flags>]
        [LDFLAGS_PUBLIC    <flags>]

        [QT_LINKS            <modules>]
        [QT_LINKS_INTERFACE  <modules>]
        [QT_LINKS_PRIVATE    <modules>]

        [QT_INCLUDE_PRIVATE  <modules>]

        [SKIP_AUTOMOC   <dir/file...>]
    )

    INCLUDE/LINKDIR: `dir/*` will be expanded to all subdirectories
                     `dir/**` will be expanded to all descendent directories recursively
]] #
macro(qm_configure_target _target)
    set(options)
    set(oneValueArgs)
    set(multiValueArgs
        SOURCES
        LINKS LINKS_PRIVATE
        INCLUDE INCLUDE_PRIVATE
        LINKDIR LINKDIR_PRIVATE
        DEFINES DEFINES_PRIVATE
        FEATURES FEATURES_PRIVATE
        CCFLAGS CCFLAGS_PUBLIC
        LDFLAGS LDFLAGS_PUBLIC
        QT_LINKS QT_LINKS_PRIVATE QT_INCLUDE_PRIVATE
        SKIP_AUTOMOC
    )
    cmake_parse_arguments(FUNC "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    target_sources(${_target} PRIVATE ${FUNC_SOURCES})

    target_link_libraries(${_target} PUBLIC ${FUNC_LINKS})
    target_link_libraries(${_target} PRIVATE ${FUNC_LINKS_PRIVATE})

    if(FUNC_INCLUDE)
        _qm_resolve_dir_helper("${FUNC_INCLUDE}" _temp_dirs)
        target_include_directories(${_target} PUBLIC ${_temp_dirs})
        unset(_temp_dirs)
    endif()

    if(FUNC_INCLUDE_INTERFACE)
        _qm_resolve_dir_helper("${FUNC_INCLUDE_INTERFACE}" _temp_dirs)
        target_include_directories(${_target} INTERFACE ${_temp_dirs})
        unset(_temp_dirs)
    endif()

    if(FUNC_INCLUDE_PRIVATE)
        _qm_resolve_dir_helper("${FUNC_INCLUDE_PRIVATE}" _temp_dirs)
        target_include_directories(${_target} PRIVATE ${_temp_dirs})
        unset(_temp_dirs)
    endif()

    if(FUNC_LINKDIR)
        _qm_resolve_dir_helper("${FUNC_LINKDIR}" _temp_dirs)
        target_link_directories(${_target} PUBLIC ${_temp_dirs})
        unset(_temp_dirs)
    endif()

    if(FUNC_LINKDIR_INTERFACE)
        _qm_resolve_dir_helper("${FUNC_LINKDIR}" _temp_dirs)
        target_link_directories(${_target} INTERFACE ${_temp_dirs})
        unset(_temp_dirs)
    endif()

    if(FUNC_LINKDIR_PRIVATE)
        _qm_resolve_dir_helper("${FUNC_LINKDIR_PRIVATE}" _temp_dirs)
        target_link_directories(${_target} PRIVATE ${_temp_dirs})
        unset(_temp_dirs)
    endif()

    target_compile_definitions(${_target} PUBLIC ${FUNC_DEFINES})
    target_compile_definitions(${_target} INTERFACE ${FUNC_DEFINES_INTERFACE})
    target_compile_definitions(${_target} PRIVATE ${FUNC_DEFINES_PRIVATE})

    target_compile_features(${_target} PUBLIC ${FUNC_FEATURES})
    target_compile_features(${_target} INTERFACE ${FUNC_FEATURES_INTERFACE})
    target_compile_features(${_target} PRIVATE ${FUNC_FEATURES_PRIVATE})

    # CMake won't add language standard flag if the compiler default mode supports the standard,
    # however, if the -std argument is not explicitly specified, the clang language server will
    # not work properly.
    # https://discourse.cmake.org/t/cmake-does-not-set-the-compiler-option-std-to-gnu17-or-c-17-although-i-set-the-target-compile-features-to-cxx-std-17/3299/8
    foreach(_item IN LISTS FUNC_FEATURES FUNC_FEATURES_PRIVATE)
        if(_item MATCHES "cxx_std_(.+)")
            set_property(TARGET APPEND PROPERTY CXX_STANDARD ${CMAKE_MATCH_1})
        elseif(_item MATCHES "c_std_(.+)")
            set_property(TARGET APPEND PROPERTY C_STANDARD ${CMAKE_MATCH_1})
        endif()
    endforeach()

    target_compile_options(${_target} PUBLIC ${FUNC_CCFLAGS_PUBLIC})
    target_compile_options(${_target} INTERFACE ${FUNC_CCFLAGS_INTERFACE})
    target_compile_options(${_target} PRIVATE ${FUNC_CCFLAGS})

    target_link_options(${_target} PUBLIC ${FUNC_LDFLAGS_PUBLIC})
    target_link_options(${_target} INTERFACE ${FUNC_LDFLAGS_INTERFACE})
    target_link_options(${_target} PRIVATE ${FUNC_LDFLAGS})

    qm_link_qt(${_target} PUBLIC ${FUNC_QT_LINKS})
    qm_link_qt(${_target} INTERFACE ${FUNC_QT_LINKS_INTERFACE})
    qm_link_qt(${_target} PRIVATE ${FUNC_QT_LINKS_PRIVATE})

    qm_include_qt_private(${_target} PRIVATE ${FUNC_QT_INCLUDE_PRIVATE})

    if(FUNC_SKIP_AUTOMOC)
        _qm_resolve_file_helper("${FUNC_SKIP_AUTOMOC}" _temp_files)
        qm_skip_automoc(${_temp_files})
        unset(_temp_files)
    endif()
endmacro()

#[[
    Helper to define export macros.

    qm_export_defines(<target>
        [PREFIX     <prefix>]
        [STATIC     <token>]
        [LIBRARY    <token>]
    )
]] #
function(qm_export_defines _target)
    set(options)
    set(oneValueArgs PREFIX STATIC LIBRARY)
    set(multiValueArgs)
    cmake_parse_arguments(FUNC "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    if(NOT FUNC_PREFIX)
        string(TOUPPER ${_target} _prefix)
    else()
        set(_prefix ${FUNC_PREFIX})
    endif()

    qm_set_value(_static_macro FUNC_STATIC ${_prefix}_STATIC)
    qm_set_value(_library_macro FUNC_LIBRARY ${_prefix}_LIBRARY)

    get_target_property(_type ${_target} TYPE)

    if(_type STREQUAL "INTERFACE_LIBRARY")
        return()
    endif()

    if(_type STREQUAL "STATIC_LIBRARY")
        target_compile_definitions(${_target} PUBLIC ${_static_macro})
    endif()

    target_compile_definitions(${_target} PRIVATE ${_library_macro})
endfunction()

#[[
    Attach windows RC file to a target.

    qm_add_win_rc(<target>
        [NAME           name]
        [VERSION        version]
        [DESCRIPTION    desc]
        [COPYRIGHT      copyright]
        [ICON           ico]
        [OUTPUT_DIR     dir]
    )
]] #
function(qm_add_win_rc _target)
    if(NOT WIN32)
        return()
    endif()

    _qm_check_target_type_helper(${_target} _ "EXECUTABLE" "SHARED_LIBRARY")

    set(options)
    set(oneValueArgs NAME VERSION DESCRIPTION COPYRIGHT ICON OUTPUT_DIR)
    set(multiValueArgs)
    cmake_parse_arguments(FUNC "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    qm_set_value(_name FUNC_NAME ${_target})
    qm_set_value(_version FUNC_VERSION PROJECT_VERSION "0.0.0.0")
    qm_set_value(_desc FUNC_DESCRIPTION PROJECT_DESCRIPTION ${_name})
    qm_set_value(_copyright FUNC_COPYRIGHT ${_name})

    qm_parse_version(_ver ${_version})
    set(RC_VERSION ${_ver_1},${_ver_2},${_ver_3},${_ver_4})

    set(RC_APPLICATION_NAME ${_name})
    set(RC_VERSION_STRING ${_version})
    set(RC_DESCRIPTION ${_desc})
    set(RC_COPYRIGHT ${_copyright})

    if(NOT FUNC_ICON)
        set(RC_ICON_COMMENT "//")
        set(RC_ICON_PATH)
    else()
        get_filename_component(RC_ICON_PATH ${FUNC_ICON} ABSOLUTE)
    endif()

    qm_set_value(_out_dir OUTPUT_DIR ${CMAKE_CURRENT_BINARY_DIR})
    set(_out_path "${_out_dir}/${_target}_res.rc")
    configure_file("${QMSETUP_MODULES_DIR}/windows/WinResource.rc.in" ${_out_path} @ONLY)
    target_sources(${_target} PRIVATE ${_out_path})

    if(FUNC_ICON)
        if(${FUNC_ICON} IS_NEWER_THAN ${_out_path})
            file(TOUCH_NOCREATE ${_out_path})
        endif()
    endif()
endfunction()

#[[
    Attach windows RC file to a target, enhanced edition.

    qm_add_win_rc_enhanced(<target>
        [NAME              name]
        [VERSION           version]
        [DESCRIPTION       description]
        [COPYRIGHT         copyright]
        [COMMENTS          comments]
        [COMPANY           company]
        [INTERNAL_NAME     internal name]
        [TRADEMARK         trademark]
        [ORIGINAL_FILENAME original filename]
        [ICONS             icon file paths]
        [OUTPUT_DIR        dir]
    )
]] #
function(qm_add_win_rc_enhanced _target)
    if(NOT WIN32)
        return()
    endif()

    _qm_check_target_type_helper(${_target} _type "EXECUTABLE" "SHARED_LIBRARY")

    set(options)
    set(oneValueArgs
        NAME VERSION DESCRIPTION COPYRIGHT COMMENTS COMPANY
        INTERNAL_NAME TRADEMARK ORIGINAL_FILENAME OUTPUT_DIR
    )
    set(multiValueArgs ICONS)
    cmake_parse_arguments(FUNC "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    qm_set_value(_name FUNC_NAME ${_target})
    qm_set_value(_version FUNC_VERSION PROJECT_VERSION "0.0.0.0")
    qm_set_value(_desc FUNC_DESCRIPTION PROJECT_DESCRIPTION ${_name})
    qm_set_value(_copyright FUNC_COPYRIGHT ${_name})
    qm_set_value(_comments FUNC_COMMENTS "")
    qm_set_value(_company FUNC_COMPANY "")
    qm_set_value(_internal_name FUNC_INTERNAL_NAME "")
    qm_set_value(_trademark FUNC_TRADEMARK "")
    qm_set_value(_original_filename FUNC_ORIGINAL_FILENAME "")

    qm_parse_version(_ver ${_version})
    set(RC_VERSION ${_ver_1},${_ver_2},${_ver_3},${_ver_4})

    set(RC_APPLICATION_NAME ${_name})
    set(RC_VERSION_STRING ${_version})
    set(RC_DESCRIPTION ${_desc})
    set(RC_COPYRIGHT ${_copyright})
    set(RC_COMMENTS ${_comments})
    set(RC_COMPANY ${_company})
    set(RC_INTERNAL_NAME ${_internal_name})
    set(RC_TRADEMARK ${_trademark})
    set(RC_ORIGINAL_FILENAME ${_original_filename})

    set(_file_type)

    if(_type STREQUAL "EXECUTABLE")
        set(_file_type "VFT_APP")
    else()
        set(_file_type "VFT_DLL")
    endif()

    set(RC_FILE_TYPE ${_file_type})

    set(_icons)

    if(FUNC_ICONS)
        set(_index 1)

        foreach(_icon IN LISTS FUNC_ICONS)
            get_filename_component(_icon_path ${_icon} ABSOLUTE)
            string(APPEND _icons "IDI_ICON${_index}    ICON    \"${_icon_path}\"\n")
            math(EXPR _index "${_index} +1")
        endforeach()
    endif()

    set(RC_ICONS ${_icons})

    qm_set_value(_out_dir OUTPUT_DIR ${CMAKE_CURRENT_BINARY_DIR})
    set(_out_path "${_out_dir}/${_target}_res.rc")
    configure_file("${QMSETUP_MODULES_DIR}/windows/WinResource2.rc.in" ${_out_path} @ONLY)
    target_sources(${_target} PRIVATE ${_out_path})

    foreach(_icon IN LISTS FUNC_ICONS)
        if(${_icon} IS_NEWER_THAN ${_out_path})
            file(TOUCH_NOCREATE ${_out_path})
            break()
        endif()
    endforeach()
endfunction()

#[[
    Attach windows manifest file to a target.

    qm_add_win_manifest(<target>
        [NAME           name]
        [VERSION        version]
        [DESCRIPTION    desc]
        [OUTPUT_DIR     dir]
        [UTF8]
        [ADMIN]
    )
]] #
function(qm_add_win_manifest _target)
    if(NOT WIN32)
        return()
    endif()

    _qm_check_target_type_helper(${_target} _ "EXECUTABLE")

    set(options UTF8 ADMIN)
    set(oneValueArgs NAME VERSION DESCRIPTION OUTPUT_DIR)
    set(multiValueArgs)
    cmake_parse_arguments(FUNC "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    qm_set_value(_name FUNC_NAME ${_target})
    qm_set_value(_version FUNC_VERSION PROJECT_VERSION "0.0.0.0")
    qm_set_value(_desc FUNC_DESCRIPTION PROJECT_DESCRIPTION ${_name})

    qm_crop_version(_version ${_version} 4)

    set(MANIFEST_IDENTIFIER ${_name})
    set(MANIFEST_VERSION ${_version})
    set(MANIFEST_DESCRIPTION ${_desc})

    set(MANIFEST_UTF8)

    if(FUNC_UTF8)
        set(MANIFEST_UTF8 "<activeCodePage xmlns=\"http://schemas.microsoft.com/SMI/2019/WindowsSettings\">UTF-8</activeCodePage>")
    endif()

    if(FUNC_ADMIN)
        set(MANIFEST_PRIVILEGES "<requestedExecutionLevel level=\"requireAdministrator\" uiAccess=\"false\" />")
    else()
        set(MANIFEST_PRIVILEGES "<requestedExecutionLevel level=\"asInvoker\" uiAccess=\"false\" />")
    endif()

    qm_set_value(_out_dir OUTPUT_DIR ${CMAKE_CURRENT_BINARY_DIR})
    set(_out_path "${_out_dir}/${_target}_manifest.exe.manifest")
    configure_file("${QMSETUP_MODULES_DIR}/windows/WinManifest.manifest.in" ${_out_path} @ONLY)

    if(MSVC)
        if(CMAKE_GENERATOR MATCHES "Visual Studio")
            # Visual Studio
            target_link_options(${_target} PRIVATE "/manifest" "/manifestinput:${_out_path}")

            # The manifest file contains a UAC field, we should prevent Ninja from embedding the
            # automatically generated UAC field
            target_link_options(${_target} PRIVATE "/manifest" "/manifestuac:no")
        else() # Ninja
            # https://cmake.org/cmake/help/latest/release/3.4.html#other
            # CMake learned to honor *.manifest source files with MSVC tools. Manifest files named as sources
            # of .exe and .dll targets will be merged with linker-generated manifests and embedded in the binary.

            # NOTE: CMake will automatically generate a default manifest file and embed it into the binary file
            # when we are using MSVC toolchain, so it will conflict with the one we embed in the RC file. So in
            # this case, we just follow the CMake documentation, add the manifest file into the sources and let
            # CMake handle it. What's more, CMake can automatically merge all manifest files so we can actually
            # add multiple manifest files, eg. each manifest file contains a separate section.
            target_sources(${_target} PRIVATE ${_out_path})
            target_link_options(${_target} PRIVATE "/manifestuac:no")
        endif()
    else()
        # For non-MSVC toolchains we can only embed the manifest file into the RC file, sadly we have
        # to merge all manifest files into one by ourself if we have multiple of them, but luckily
        # CMake won't embed a default one so we don't need to worry about resource conflicts.
        set(_manifest_rc ${_out_path}.rc)
        file(WRITE ${_manifest_rc} "#include <windows.h>\n\n1 RT_MANIFEST \"${_out_path}\"")
        target_sources(${_target} PRIVATE ${_manifest_rc})
    endif()
endfunction()

#[[
    Add Mac bundle info.

    qm_add_mac_bundle(<target>
        [NAME           <name>]
        [VERSION        <version>]
        [DESCRIPTION    <desc>]
        [COPYRIGHT      <copyright>]
        [ICON           <file>]
    )
]] #
function(qm_add_mac_bundle _target)
    if(NOT APPLE)
        return()
    endif()

    _qm_check_target_type_helper(${_target} _ "EXECUTABLE")

    set(options)
    set(oneValueArgs NAME VERSION DESCRIPTION COPYRIGHT ICON)
    set(multiValueArgs)
    cmake_parse_arguments(FUNC "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    qm_set_value(_app_name FUNC_NAME ${_target})
    qm_set_value(_app_version FUNC_VERSION PROJECT_VERSION "0.0.0.0")
    qm_set_value(_app_desc FUNC_DESCRIPTION PROJECT_DESCRIPTION ${_app_name})
    qm_set_value(_app_copyright FUNC_COPYRIGHT ${_app_name})

    qm_parse_version(_app_version ${_app_version})

    # configure mac plist
    set_target_properties(${_target} PROPERTIES
        MACOSX_BUNDLE TRUE
        MACOSX_BUNDLE_BUNDLE_NAME ${_app_name}
        MACOSX_BUNDLE_EXECUTABLE_NAME ${_app_name}
        MACOSX_BUNDLE_INFO_STRING ${_app_desc}
        MACOSX_BUNDLE_GUI_IDENTIFIER ${_app_name}
        MACOSX_BUNDLE_BUNDLE_VERSION ${_app_version}
        MACOSX_BUNDLE_SHORT_VERSION_STRING ${_app_version_1}.${_app_version_2}
        MACOSX_BUNDLE_COPYRIGHT ${_app_copyright}
    )

    if(FUNC_ICON)
        # And this part tells CMake where to find and install the file itself
        set_source_files_properties(${FUNC_ICON} PROPERTIES
            MACOSX_PACKAGE_LOCATION "Resources"
        )

        # NOTE: Don't include the path in MACOSX_BUNDLE_ICON_FILE -- this is
        # the property added to Info.plist
        get_filename_component(_icns_name ${FUNC_ICON} NAME)

        # configure mac plist
        set_target_properties(${_target} PROPERTIES
            MACOSX_BUNDLE_ICON_FILE ${_icns_name}
        )

        # ICNS icon MUST be added to executable's sources list, for some reason
        # Only apple can do
        target_sources(${_target} PRIVATE ${FUNC_ICON})
    endif()
endfunction()

#[[
    Generate Windows shortcut after building target.

    qm_create_win_shortcut(<target> <dir>
        [OUTPUT_NAME <name]
    )
]] #
function(qm_create_win_shortcut _target _dir)
    if(NOT WIN32)
        return()
    endif()

    set(options)
    set(oneValueArgs OUTPUT_NAME)
    set(multiValueArgs)
    cmake_parse_arguments(FUNC "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    qm_set_value(_output_name FUNC_OUTPUT_NAME $<TARGET_FILE_BASE_NAME:${_target}>)

    set(_vbs_name ${CMAKE_CURRENT_BINARY_DIR}/${_target}_shortcut_$<CONFIG>.vbs)
    set(_vbs_temp ${_vbs_name}.in)

    set(_lnk_path "${_dir}/${_output_name}.lnk")

    set(SHORTCUT_PATH ${_lnk_path})
    set(SHORTCUT_TARGET_PATH $<TARGET_FILE:${_target}>)
    set(SHORTCUT_WORKING_DIRECOTRY $<TARGET_FILE_DIR:${_target}>)
    set(SHORTCUT_DESCRIPTION $<TARGET_FILE_BASE_NAME:${_target}>)
    set(SHORTCUT_ICON_LOCATION $<TARGET_FILE:${_target}>)

    configure_file(
        "${QMSETUP_MODULES_DIR}/windows/WinCreateShortcut.vbs.in"
        ${_vbs_temp}
        @ONLY
    )
    file(GENERATE OUTPUT ${_vbs_name} INPUT ${_vbs_temp})

    add_custom_command(
        TARGET ${_target} POST_BUILD
        COMMAND cscript ${_vbs_name} ${QMSETUP_IGNORE_STDOUT}
        BYPRODUCTS ${_lnk_path}
        VERBATIM
    )
endfunction()

#[[
    Collect targets of given types recursively in a directory.

    qm_collect_targets(<list> [DIRECTORY directory]
                              [EXECUTABLE] [SHARED] [STATIC] [INTERFACE] [UTILITY])

    If one or more types are specified, return targets matching the types.
    If no type is specified, return all targets.
]] #
function(qm_collect_targets _var)
    set(options EXECUTABLE SHARED STATIC INTERFACE UTILITY)
    set(oneValueArgs DIR)
    set(multiValueArgs)
    cmake_parse_arguments(FUNC "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    if(FUNC_DIRECTORY)
        set(_dir ${FUNC_DIRECTORY})
    else()
        set(_dir ${CMAKE_CURRENT_SOURCE_DIR})
    endif()

    set(_tmp_targets)

    macro(_get_targets_recursive _targets _dir)
        get_property(_subdirs DIRECTORY ${_dir} PROPERTY SUBDIRECTORIES)

        foreach(_subdir IN LISTS _subdirs)
            _get_targets_recursive(${_targets} ${_subdir})
        endforeach()

        get_property(_current_targets DIRECTORY ${_dir} PROPERTY BUILDSYSTEM_TARGETS)
        list(APPEND ${_targets} ${_current_targets})
    endmacro()

    # Get targets
    _get_targets_recursive(_tmp_targets ${_dir})
    set(_targets)

    if(NOT FUNC_EXECUTABLE AND NOT FUNC_SHARED AND NOT FUNC_STATIC AND NOT FUNC_INTERFACE AND NOT FUNC_UTILITY)
        set(_targets ${_tmp_targets})
    else()
        # Filter targets
        foreach(_item IN LISTS _tmp_targets)
            get_target_property(_type ${_item} TYPE)

            if(_type STREQUAL "EXECUTABLE")
                if(FUNC_EXECUTABLE)
                    list(APPEND _targets ${_item})
                endif()
            elseif(_type STREQUAL "SHARED_LIBRARY")
                if(FUNC_SHARED)
                    list(APPEND _targets ${_item})
                endif()
            elseif(_type STREQUAL "STATIC_LIBRARY")
                if(FUNC_STATIC)
                    list(APPEND _targets ${_item})
                endif()
            elseif(_type STREQUAL "INTERFACE_LIBRARY")
                if(FUNC_INTERFACE)
                    list(APPEND _targets ${_item})
                endif()
            elseif(_type STREQUAL "UTILITY")
                if(FUNC_UTILITY)
                    list(APPEND _targets ${_item})
                endif()
            endif()
        endforeach()
    endif()

    set(${_var} ${_targets} PARENT_SCOPE)
endfunction()

#[[
    Get subdirectories' names or paths.

    qm_get_subdirs(<list>
        [DIRECTORY dir]
        [EXCLUDE names...]
        [REGEX_INCLUDE exps...]
        [REGEX_EXLCUDE exps...]
        [RELATIVE path]
        [ABSOLUTE]
    )

    If `DIRECTORY` is not specified, consider `CMAKE_CURRENT_SOURCE_DIR`.
    If `RELATIVE` is specified, return paths evaluated as a relative path to it.
    If `ABSOLUTE` is specified, return absolute paths.
    If neither of them is specified, return names.
]] #
function(qm_get_subdirs _var)
    set(options ABSOLUTE)
    set(oneValueArgs DIRECTORY RELATIVE)
    set(multiValueArgs EXCLUDE REGEX_EXLCUDE)
    cmake_parse_arguments(FUNC "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    if(FUNC_DIRECTORY)
        get_filename_component(_dir ${FUNC_DIRECTORY} ABSOLUTE)
    else()
        set(_dir ${CMAKE_CURRENT_SOURCE_DIR})
    endif()

    file(GLOB _subdirs LIST_DIRECTORIES true RELATIVE ${_dir} "${_dir}/*")

    if(FUNC_EXCLUDE)
        foreach(_exclude_dir IN LISTS FUNC_EXCLUDE)
            list(REMOVE_ITEM _subdirs ${_exclude_dir})
        endforeach()
    endif()

    if(FUNC_REGEX_INCLUDE)
        foreach(_exp IN LISTS FUNC_REGEX_INCLUDE)
            list(FILTER _subdirs INCLUDE REGEX ${_exp})
        endforeach()
    endif()

    if(FUNC_REGEX_EXCLUDE)
        foreach(_exp IN LISTS FUNC_REGEX_EXCLUDE)
            list(FILTER _subdirs EXCLUDE REGEX ${_exp})
        endforeach()
    endif()

    set(_res)

    if(FUNC_RELATIVE)
        get_filename_component(_relative ${FUNC_RELATIVE} ABSOLUTE)
    else()
        set(_relative)
    endif()

    foreach(_sub IN LISTS _files)
        if(IS_DIRECTORY ${_dir}/${_sub})
            if(FUNC_ABSOLUTE)
                list(APPEND _res ${_dir}/${_sub})
            elseif(_relative)
                file(RELATIVE_PATH _rel_path ${_relative} ${_dir}/${_sub})
                list(APPEND _res ${_rel_path})
            else()
                list(APPEND _res ${_sub})
            endif()
        endif()
    endforeach()

    set(${_var} ${_res} PARENT_SCOPE)
endfunction()

#[[
    Basic template to install a CMake project.

    qm_basic_install(
        [NAME <name>]
        [VERSION <version>]
        [COMPATIBILITY <compatibility>]
        [INSTALL_DIR <dir>]
        [CONFIG_TEMPLATE <file>]
        [NAMESPACE <namespace>]
        [EXPORT <sets...>]

        [WRITE_VERSION_OPTIONS <options...>]
        [WRITE_CONFIG_OPTIONS <options...>]
    )

    Include `GNUInstallDirs`, `CMakePackageConfigHelpers` before calling this function.
]] #
function(qm_basic_install)
    set(options)
    set(oneValueArgs NAME VERSION COMPATIBILITY INSTALL_DIR CONFIG_TEMPLATE NAMESPACE)
    set(multiValueArgs WRITE_VERSION_OPTIONS WRITE_CONFIG_OPTIONS EXPORT)
    cmake_parse_arguments(FUNC "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    qm_set_value(_lib_dir CMAKE_INSTALL_LIBDIR lib)

    qm_set_value(_name FUNC_NAME PROJECT_NAME "unknown")
    qm_set_value(_version FUNC_VERSION PROJECT_VERSION "0.0.0.0")
    qm_set_value(_compatibility FUNC_COMPATIBILITY AnyNewerVersion)
    qm_set_value(_install_dir FUNC_INSTALL_DIR "${_lib_dir}/cmake/${_name}")
    qm_set_value(_config_template FUNC_CONFIG_TEMPLATE "${CMAKE_CURRENT_LIST_DIR}/${_name}Config.cmake.in")

    set(_namespace)

    if(FUNC_NAMESPACE)
        set(_namespace NAMESPACE ${FUNC_NAMESPACE})
    endif()

    set(_export_files)

    # Install cmake targets files
    foreach(_item IN LISTS FUNC_EXPORT)
        install(EXPORT ${_item}
            FILE "${_item}.cmake"
            DESTINATION ${_install_dir}
            ${_namespace}
        )
        list(APPEND _export_files "${_item}.cmake")
    endforeach()

    # Prepare config template file
    get_filename_component(_config_template ${_config_template} ABSOLUTE)

    if(NOT EXISTS ${_config_template})
        set(_config_content "@PACKAGE_INIT@\n\n")

        foreach(_item IN LISTS _export_files)
            string(APPEND _config_content "include(\"\${CMAKE_CURRENT_LIST_DIR}/${_item}\")\n")
        endforeach()

        set(_config_template "${CMAKE_CURRENT_BINARY_DIR}/${_name}Config.cmake.in")
        file(WRITE ${_config_template} ${_config_content})
    endif()

    # Add version file
    write_basic_package_version_file(
        "${CMAKE_CURRENT_BINARY_DIR}/${_name}ConfigVersion.cmake"
        VERSION ${_version}
        COMPATIBILITY ${_compatibility}
        ${FUNC_WRITE_VERSION_OPTIONS}
    )

    # Add configuration file
    configure_package_config_file(
        ${_config_template}
        "${CMAKE_CURRENT_BINARY_DIR}/${_name}Config.cmake"
        INSTALL_DESTINATION ${_install_dir}
        ${FUNC_WRITE_CONFIG_OPTIONS}
    )

    # Install cmake files
    install(FILES
        "${CMAKE_CURRENT_BINARY_DIR}/${_name}Config.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/${_name}ConfigVersion.cmake"
        DESTINATION ${_install_dir}
    )
endfunction()

# ----------------------------------
# Private functions
# ----------------------------------
macro(_qm_check_target_type_helper _target _type)
    set(_tmp_target_type_list ${ARGN})
    get_target_property(_tmp_target_type ${_target} TYPE)

    if(NOT "${_tmp_target_type}" IN_LIST _tmp_target_type_list)
        return()
    endif()

    set(${_type} ${_tmp_target_type})
    unset(_tmp_target_type)
    unset(_tmp_target_type_list)
endmacro()

function(_qm_resolve_file_helper _dirs _out)
    set(_res)

    foreach(_item ${_dirs})
        if(_item STREQUAL "*")
            set(_cur_dir ".")
            file(GLOB _files LIST_DIRECTORIES true "*")
        elseif(_item STREQUAL "**")
            set(_cur_dir ".")
            file(GLOB_RECURSE _files LIST_DIRECTORIES true "*")
        elseif(_item MATCHES "(.+)[/\\]\\*$")
            set(_cur_dir ${CMAKE_MATCH_1})
            file(GLOB _files LIST_DIRECTORIES true "${_cur_dir}/*")
        elseif(_item MATCHES "(.+)[/\\]\\*\\*$")
            set(_cur_dir ${CMAKE_MATCH_1})
            file(GLOB_RECURSE _files LIST_DIRECTORIES true "${_cur_dir}/*")
        else()
            get_filename_component(_item ${_item} ABSOLUTE)
            list(APPEND _res ${_item})
            continue()
        endif()

        get_filename_component(_cur_dir ${_cur_dir} ABSOLUTE)
        list(APPEND _res ${_cur_dir})

        foreach(_item IN LISTS _files)
            get_filename_component(_item ${_item} ABSOLUTE)
            list(APPEND _res ${_item})
        endforeach()
    endforeach()

    set(${_out} ${_res} PARENT_SCOPE)
endfunction()

function(_qm_resolve_dir_helper _dirs _out)
    set(_files)
    _qm_resolve_file_helper("${_dirs}" _files)

    foreach(_item IN LISTS _files)
        if(IS_DIRECTORY ${_item})
            list(APPEND _res ${_item})
        endif()
    endforeach()

    set(${_out} ${_res} PARENT_SCOPE)
endfunction()