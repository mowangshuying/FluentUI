#include "FluProgressBarDemo.h"

FluProgressBarDemo::FluProgressBarDemo(QWidget* parent /*= nullptr*/) : FluTemplateDemo(parent)
{
    auto vLayout = new QVBoxLayout(this);
    m_contentLayout->addLayout(vLayout);


    vLayout->addSpacing(100);
    // Determinate bar
    auto progressBar1 = new FluProgressBar(this);
    progressBar1->setValue(75);
    progressBar1->setFixedWidth(300);
    vLayout->addWidget(progressBar1);

    vLayout->addSpacing(100);

     //Indeterminate bar
    auto progressBar2 = new FluProgressBar(this);
    progressBar2->setFixedWidth(300);
    progressBar2->setValue(20);
    progressBar2->setWorking(true);
    vLayout->addWidget(progressBar2);

    vLayout->addStretch();


    resize(600, 400);
}
