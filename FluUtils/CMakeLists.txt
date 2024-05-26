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

qt_add_library(${TGT}
    STATIC
    ${DIR_SRCS}
)
qt_add_resources(${TGT} "flu_utils_fonts"
    PREFIX "/"
    BASE ".."
    FILES
    "../res/Segoe_Fluent_Icons.ttf"
)

target_link_libraries(${TGT}
    PUBLIC
    Qt6::Widgets
    Qt6::Svg
)
