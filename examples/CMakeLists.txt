cmake_path(GET CMAKE_CURRENT_LIST_DIR FILENAME ModName)
string(REPLACE " " "_" ModName ${ModName})

set(TGT ${ModName})
message("ModName: ${ModName}")

FILE(GLOB DIR_SRCS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
    "*.h"
    "*.cpp"
)

message("add_executable(\${TGT} SHARED")
    foreach(f ${DIR_SRCS})
    message("    \"${f}\"")
    endforeach()
message(")")

if (${QT_VERSION_MAJOR} LESS 6)
    add_executable(${TGT}
        ${DIR_SRCS}
     "FluDialogDemo.h")
else()
    qt_add_executable(${TGT}
        ${DIR_SRCS}
    )
endif()


if(USE_QRC)

if(QT_VERSION VERSION_GREATER_EQUAL "6.2")
set(QSS_FILES
    "../stylesheet/dark/FluMenuDemo.qss"
    "../stylesheet/light/FluHNavigationViewDemo.qss"
    "../stylesheet/dark/FluHNavigationViewDemo.qss"
    "../stylesheet/atomOneDark/FluHNavigationViewDemo.qss"
    "../stylesheet/light/FluMenuDemo.qss"
    "../stylesheet/light/FluTemplateDemo.qss"
    "../stylesheet/dark/FluTemplateDemo.qss"
    "../stylesheet/atomOneDark/FluTemplateDemo.qss"
    "../stylesheet/dark/FluMainWidgetDemo.qss"
    "../stylesheet/light/FluMainWidgetDemo.qss"
    # "../stylesheet/light/FluADSDemo.qss"
    # "../stylesheet/dark/FluADSDemo.qss"
    # "../stylesheet/atomOneDark/FluADSDemo.qss"
)
source_group(TREE ${CMAKE_SOURCE_DIR} FILES ${QSS_FILES})

qt_add_resources(${TGT} "ExamplesQss"
    PREFIX "/"
    BASE ".."
    FILES
    ${QSS_FILES}
)
flu_qrc_lowopt(ExamplesQss)
else()
target_sources(${TGT} PUBLIC ExamplesQss.qrc)
endif()

endif() ### end for use qrc

if (USE_QRC)
    add_definitions(-DUSE_QRC)
endif()


if(QT_VERSION VERSION_GREATER_EQUAL "6.2")
target_link_libraries(${TGT}
    PRIVATE
    FluentUI::Controls
    qscintilla
    qrcode
    Qt${QT_VERSION_MAJOR}::Charts
    Qt${QT_VERSION_MAJOR}::Core5Compat
    qtadvanceddocking-qt6
)

else()
target_link_libraries(${TGT}
    PRIVATE
    FluentUI::Controls
    qscintilla
    qrcode
    Qt${QT_VERSION_MAJOR}::Charts
    qtadvanceddocking-qt5
)
endif()