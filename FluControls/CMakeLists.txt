cmake_path(GET CMAKE_CURRENT_LIST_DIR FILENAME ModName)
string(REPLACE " " "_" ModName ${ModName})

set(TGT ${ModName})
message("ModName: ${ModName}")

FILE(GLOB DIR_SRCS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
    "*.h"
    "*.cpp"
)

message("qt_add_library(\${TGT} STATIC")
    foreach(f ${DIR_SRCS})
    message("    \"${f}\"")
    endforeach()
message(")")

qt_add_library(${TGT}
    STATIC 
    ${DIR_SRCS}
)

target_link_libraries(${TGT}
    PRIVATE
    framelesshelper
    Qt6::Widgets
)
