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

qt_add_executable(${TGT}
    ${DIR_SRCS}
)

target_link_libraries(${TGT}
    PRIVATE
    FluControls
    Qt${QT_VERSION_MAJOR}::StateMachine
)
