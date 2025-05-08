!defined(QMAKE_QWK_QUICK_INCLUDED, var) {
    QMAKE_QWK_QUICK_INCLUDED = 1

    include($$PWD/QWKCore.pri)

    CONFIG(debug, debug|release) {
        LIBS = $$QMAKE_QWK_LINK_PATH -lQWKQuickd $$LIBS
    } else {
        LIBS = $$QMAKE_QWK_LINK_PATH -lQWKQuick $$LIBS
    }

    
}
