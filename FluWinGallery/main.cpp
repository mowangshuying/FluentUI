#include <QApplication>
#include "../FluControls/FluWidget.h"

#include "FluGalleryWindow.h"
#include <QProcess>

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    FluLogUtils::__init();
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
