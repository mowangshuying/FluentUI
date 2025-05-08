!defined(QMAKE_QWK_CORE_INCLUDED, var) {
    QMAKE_QWK_CORE_INCLUDED = 1

    # CMake variables
    QMAKE_QWK_INSTALL_PREFIX = $$PWD/../../..
    QMAKE_QWK_INSTALL_BINDIR = bin
    QMAKE_QWK_INSTALL_LIBDIR = lib
    QMAKE_QWK_INSTALL_INCDIR = include

    # Shared link directory
    QMAKE_QWK_LINK_PATH = "-L$$QMAKE_QWK_INSTALL_PREFIX/$$QMAKE_QWK_INSTALL_LIBDIR"

    # Include directory
    INCLUDEPATH += \
        $$QMAKE_QWK_INSTALL_PREFIX/$$QMAKE_QWK_INSTALL_INCDIR/QWindowKit
    
    CONFIG(debug, debug|release) {
        LIBS = $$QMAKE_QWK_LINK_PATH -lQWKCored $$LIBS
    } else {
        LIBS = $$QMAKE_QWK_LINK_PATH -lQWKCore $$LIBS
    }

    
}
