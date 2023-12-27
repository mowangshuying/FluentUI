#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "FramelessHelper::FramelessHelperCore" for configuration "Debug"
set_property(TARGET FramelessHelper::FramelessHelperCore APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(FramelessHelper::FramelessHelperCore PROPERTIES
  IMPORTED_IMPLIB_DEBUG "${_IMPORT_PREFIX}/lib/debug/FramelessHelperCore64d.lib"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/bin/debug/FramelessHelperCore64d.dll"
  )

list(APPEND _cmake_import_check_targets FramelessHelper::FramelessHelperCore )
list(APPEND _cmake_import_check_files_for_FramelessHelper::FramelessHelperCore "${_IMPORT_PREFIX}/lib/debug/FramelessHelperCore64d.lib" "${_IMPORT_PREFIX}/bin/debug/FramelessHelperCore64d.dll" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
