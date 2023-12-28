#include "../FluUtils/FluIconUtils.h"
#include "FluIconToolWidget.h"
#include <QApplication>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    FluIconToolWidget w;
    w.show();

    return app.exec();
}