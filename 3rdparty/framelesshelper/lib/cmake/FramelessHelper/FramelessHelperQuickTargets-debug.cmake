#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "FramelessHelper::FramelessHelperQuick" for configuration "Debug"
set_property(TARGET FramelessHelper::FramelessHelperQuick APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(FramelessHelper::FramelessHelperQuick PROPERTIES
  IMPORTED_IMPLIB_DEBUG "${_IMPORT_PREFIX}/lib/debug/FramelessHelperQuick64d.lib"
  IMPORTED_LINK_DEPENDENT_LIBRARIES_DEBUG "Qt6::Qml;FramelessHelper::FramelessHelperCore"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/bin/debug/FramelessHelperQuick64d.dll"
  )

list(APPEND _cmake_import_check_targets FramelessHelper::FramelessHelperQuick )
list(APPEND _cmake_import_check_files_for_FramelessHelper::FramelessHelperQuick "${_IMPORT_PREFIX}/lib/debug/FramelessHelperQuick64d.lib" "${_IMPORT_PREFIX}/bin/debug/FramelessHelperQuick64d.dll" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
