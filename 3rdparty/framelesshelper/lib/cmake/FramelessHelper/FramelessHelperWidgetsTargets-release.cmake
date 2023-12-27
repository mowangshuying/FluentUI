#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "FramelessHelper::FramelessHelperWidgets" for configuration "Release"
set_property(TARGET FramelessHelper::FramelessHelperWidgets APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(FramelessHelper::FramelessHelperWidgets PROPERTIES
  IMPORTED_IMPLIB_RELEASE "${_IMPORT_PREFIX}/lib/release/FramelessHelperWidgets64.lib"
  IMPORTED_LINK_DEPENDENT_LIBRARIES_RELEASE "Qt6::Widgets;FramelessHelper::FramelessHelperCore"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/bin/release/FramelessHelperWidgets64.dll"
  )

list(APPEND _cmake_import_check_targets FramelessHelper::FramelessHelperWidgets )
list(APPEND _cmake_import_check_files_for_FramelessHelper::FramelessHelperWidgets "${_IMPORT_PREFIX}/lib/release/FramelessHelperWidgets64.lib" "${_IMPORT_PREFIX}/bin/release/FramelessHelperWidgets64.dll" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
