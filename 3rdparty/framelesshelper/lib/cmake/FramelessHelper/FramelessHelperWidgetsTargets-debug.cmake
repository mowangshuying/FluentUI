#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "FramelessHelper::FramelessHelperWidgets" for configuration "Debug"
set_property(TARGET FramelessHelper::FramelessHelperWidgets APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(FramelessHelper::FramelessHelperWidgets PROPERTIES
  IMPORTED_IMPLIB_DEBUG "${_IMPORT_PREFIX}/lib/debug/FramelessHelperWidgets64d.lib"
  IMPORTED_LINK_DEPENDENT_LIBRARIES_DEBUG "Qt6::Widgets;FramelessHelper::FramelessHelperCore"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/bin/debug/FramelessHelperWidgets64d.dll"
  )

list(APPEND _cmake_import_check_targets FramelessHelper::FramelessHelperWidgets )
list(APPEND _cmake_import_check_files_for_FramelessHelper::FramelessHelperWidgets "${_IMPORT_PREFIX}/lib/debug/FramelessHelperWidgets64d.lib" "${_IMPORT_PREFIX}/bin/debug/FramelessHelperWidgets64d.dll" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
