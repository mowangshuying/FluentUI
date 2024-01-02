#include <QApplication>
#include <QWidget>

#include "FluGalleryWindow.h"
#include "../FluUtils/FluLogUtils.h"

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    FluLogUtils::__init();
    FluGalleryWindow w;
    w.show();

    return app.exec();
}
