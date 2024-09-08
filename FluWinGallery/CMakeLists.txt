cmake_path(GET CMAKE_CURRENT_LIST_DIR FILENAME ModName)
string(REPLACE " " "_" ModName ${ModName})

set(TGT ${ModName})
message("ModName: ${ModName}")

FILE(GLOB DIR_SRCS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
    "*.h"
    "*.cpp"
)

message("add_library(\${TGT} SHARED")
    foreach(f ${DIR_SRCS})
    message("    \"${f}\"")
    endforeach()
message(")")

# qt_add_executable(${TGT}
#     ${DIR_SRCS}
# )
if (${QT_VERSION_MAJOR} LESS 6)
    add_executable(${TGT}
        ${DIR_SRCS}
    )
else()
    qt_add_executable(${TGT}
        ${DIR_SRCS}
    )
endif()

target_link_libraries(${TGT}
    PRIVATE
    FluControls
)

set_target_properties(${TGT} PROPERTIES
    WIN32_EXECUTABLE ON
    MACOSX_BUNDLE ON
)
add_dependencies(${TGT} resource_copy)

include(GNUInstallDirs)
install(TARGETS ${TGT}
  BUNDLE DESTINATION .
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(${QT_VERSION} VERSION_GREATER 6.3.0)
qt_generate_deploy_app_script(
     TARGET ${TGT}
     OUTPUT_SCRIPT deploy_script
     NO_UNSUPPORTED_PLATFORM_ERROR
 )
 install(SCRIPT ${deploy_script})
 endif()
