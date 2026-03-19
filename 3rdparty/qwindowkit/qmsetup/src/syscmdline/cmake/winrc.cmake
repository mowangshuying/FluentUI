set(_rc_content "#include <windows.h>

#ifndef VS_VERSION_INFO
#define VS_VERSION_INFO 1
#endif

#define _STRINGIFY(x) #x
#define STRINGIFY(x) _STRINGIFY(x)

VS_VERSION_INFO VERSIONINFO
    FILEVERSION    ${PROJECT_VERSION_MAJOR},${PROJECT_VERSION_MINOR},${PROJECT_VERSION_PATCH},${PROJECT_VERSION_TWEAK}
    PRODUCTVERSION ${PROJECT_VERSION_MAJOR},${PROJECT_VERSION_MINOR},${PROJECT_VERSION_PATCH},${PROJECT_VERSION_TWEAK}
{
    BLOCK \"StringFileInfo\"
    {
       // U.S. English - Windows, Multilingual
       BLOCK \"040904E4\"
       {
          VALUE \"FileDescription\", STRINGIFY(${RC_DESCRIPTION})
          VALUE \"FileVersion\", STRINGIFY(${PROJECT_VERSION})
          VALUE \"ProductName\", STRINGIFY(${PROJECT_NAME})
          VALUE \"ProductVersion\", STRINGIFY(${PROJECT_VERSION})
          VALUE \"LegalCopyright\", STRINGIFY(${RC_COPYRIGHT})
        }
    }
    BLOCK \"VarFileInfo\"
    {
        VALUE \"Translation\", 0x409, 1252 // 1252 = 0x04E4
    }
}")

set(_rc_file ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}_res.rc)
file(WRITE ${_rc_file} ${_rc_content})
target_sources(${PROJECT_NAME} PRIVATE ${_rc_file})