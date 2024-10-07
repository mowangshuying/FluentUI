#include "FluProgressBarDemo.h"

FluProgressBarDemo::FluProgressBarDemo(QWidget* parent /*= nullptr*/) : FluWidget(parent)
{
    auto progressBar = new FluProgressBar(this);
    progressBar->move(50, 50);
    progressBar->setValue(75);
    progressBar->setFixedWidth(150);

    resize(600, 400);
}
