#include <QApplication>
#include "../FluControls/FluWidget.h"

#include "FluGalleryWindow.h"
#include <QProcess>
#include <QTranslator>

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    FluLogUtils::__init();

    // load qm
    static QTranslator translator;
    bool bLoad = translator.load("../i18n/zh-cn.qm");
    LOG_DEBUG << "Load:" << bLoad;
    app.installTranslator(&translator);

    FluGalleryWindow w;
    w.show();

    int nExec = app.exec();
    if (nExec == 931)
    {
        QProcess::startDetached(qApp->applicationFilePath());
        return nExec;
    }

    return nExec;
}
