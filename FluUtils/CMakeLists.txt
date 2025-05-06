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

if (${QT_VERSION_MAJOR} LESS 6)
    add_library(${TGT}
        STATIC
        ${DIR_SRCS}
    )
else()
    qt_add_library(${TGT}
        STATIC
        ${DIR_SRCS}
    )
endif()

if(USE_QRC)
set(RES_FILES
    "../res/Segoe_Fluent_Icons.ttf"
)
source_group(TREE ${CMAKE_SOURCE_DIR} FILES ${RES_FILES})

qt_add_resources(${TGT} "FluUtilsFonts"
    PREFIX "/"
    BASE ".."
    FILES
    ${RES_FILES}
)
endif()

if (USE_QRC)
    add_definitions(-DUSE_QRC)
endif()

target_link_libraries(${TGT}
    PUBLIC
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Svg
)
