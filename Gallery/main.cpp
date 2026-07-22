#include <QApplication>
#include "../Controls/FluWidget.h"

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
        FluTranslatorUtils::installTranslator(&app, "Controls.zh-CN");
        FluTranslatorUtils::installTranslator(&app, "Gallery.zh-CN");
    }

    FluGalleryWindow w;
    w.show();

    int exec = app.exec();
    if (exec == 931)
    {
        QProcess::startDetached(qApp->applicationFilePath());
        return exec;
    }

    return exec;
}
