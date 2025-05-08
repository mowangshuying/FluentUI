!defined(QMAKE_QWK_WIDGETS_INCLUDED, var) {
    QMAKE_QWK_WIDGETS_INCLUDED = 1

    include($$PWD/QWKCore.pri)

    CONFIG(debug, debug|release) {
        LIBS = $$QMAKE_QWK_LINK_PATH -lQWKWidgetsd $$LIBS
    } else {
        LIBS = $$QMAKE_QWK_LINK_PATH -lQWKWidgets $$LIBS
    }

    
}
