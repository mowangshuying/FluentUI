#include "FluProgressBarDemo.h"

FluProgressBarDemo::FluProgressBarDemo(QWidget* parent /*= nullptr*/) : FluTemplateDemo(parent)
{
    // Determinate bar
    auto progressBar = new FluProgressBar(this);
    progressBar->move(50, 50);
    progressBar->setValue(75);
    progressBar->setFixedWidth(150);

    // Indeterminate bar
    auto progressBar2 = new FluProgressBar(this);
    progressBar2->move(50, 100);
    progressBar2->setFixedWidth(150);
    progressBar2->setWorking(true);

    resize(600, 400);
}
