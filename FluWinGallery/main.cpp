#include <QApplication>
#include "../FluControls/FluWidget.h"

#include "FluGalleryWindow.h"
#include <QProcess>
#include <QTranslator>

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    FluLogUtils::__init();
    QTranslator translator;
    if (FluConfigUtils::getUtils()->getLanguage() == "zh-CN")
    {
#ifndef USE_QRC
        bool bLoad = translator.load("../i18n/zh-CN.qm");
#else
        bool bLoad = translator.load(":/i18n/zh-CN.qm");
#endif
        if (bLoad)
        {
            app.installTranslator(&translator);
        }
    }
    else
    {
#ifndef USE_QRC
        bool bLoad = translator.load("../i18n/en-US.qm");
#else
        bool bLoad = translator.load(":/i18n/en-US.qm");
#endif
        if (bLoad)
        {
            app.installTranslator(&translator);
        }
    }

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
