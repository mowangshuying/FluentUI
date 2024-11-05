#include "FluProgressRingPage.h"

FluProgressRingPage::FluProgressRingPage(QWidget* parent /*= nullptr*/) : FluAEmptyPage(parent)
{
    m_mainLayout->setAlignment(Qt::AlignTop);
    m_titleLabel->setText("ProgressRing");
    // m_subTitleLabel->setText("CppQtFluentUi888::FluProgressRing");

    m_infoLabel->setText("The ProgressRing has two different visual representations.\nIndeterminate - shows that a task is ongoing.but blocks user interaction.\nDeterminate - shows how much progress has been made on a known amount of work.");

    addIndeterminateProgressRing();

    addIndeterminateRing();

    addBusyRing();

    FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluProgressRingPage.qss", this);
}

void FluProgressRingPage::addIndeterminateProgressRing()
{
    auto displayBox = new FluDisplayBoxEx;
    displayBox->getBodyContentLayout()->setAlignment(Qt::AlignTop);
    displayBox->getBodyRightLayout()->setAlignment(Qt::AlignTop);
    displayBox->setTitle("An indeterminate progress ring.");
    displayBox->getCodeExpander()->setCodeByPath("../code/ProgressRingPageCode1.md");
    displayBox->setBodyWidgetFixedHeight(96);

    auto hBoxLayout = new QHBoxLayout;
    hBoxLayout->setContentsMargins(0, 0, 0, 0);
    // hBoxLayout->setAlignment(Qt::AlignVCenter | Qt::AlignLeft);

    auto progressRing1 = new FluProgressRing;
    progressRing1->setWorking(true);

    auto progressRing2 = new FluProgressRing;
    progressRing2->setFixedSize(30, 30);
    progressRing2->setWorking(true);

    auto progressRing3 = new FluProgressRing;
    progressRing3->setFixedSize(25, 25);
    progressRing3->setWorking(true);

    hBoxLayout->addWidget(progressRing1);
    hBoxLayout->addWidget(progressRing2);
    hBoxLayout->addWidget(progressRing3);
    displayBox->getBodyContentLayout()->addLayout(hBoxLayout);

    auto progressOptionsLabel = new FluLabel(FluLabelStyle::CaptionTextBlockSylte);
    progressOptionsLabel->setText("Track Background color");

    auto comboBox = new FluComboBoxEx;
    comboBox->addItem("Transparent");
    comboBox->addItem("LightGray");
    connect(comboBox, &FluComboBoxEx::currentIndexChanged, [=](int index) {
        if (index == 0)
        {
            progressRing1->setTransparentTrack(true);
            progressRing2->setTransparentTrack(true);
            progressRing3->setTransparentTrack(true);
        }
        else
        {
            progressRing1->setTransparentTrack(false);
            progressRing2->setTransparentTrack(false);
            progressRing3->setTransparentTrack(false);
        }
    });

    //  displayBox->getBodyContentLayout()->addWidget(progressRing1);
    displayBox->getBodyRightLayout()->addWidget(progressOptionsLabel, 0, Qt::AlignTop);
    displayBox->getBodyRightLayout()->addWidget(comboBox, 0, Qt::AlignTop);

    m_vScrollView->getMainLayout()->addWidget(displayBox, 0, Qt::AlignTop);
}

void FluProgressRingPage::addIndeterminateRing()
{
    auto displayBox = new FluDisplayBox;
    displayBox->setTitle("An indeterminate ring.");
    displayBox->getCodeExpander()->setCodeByPath("../code/ProgressRingPageCode2.md");
    displayBox->setBodyWidgetFixedHeight(96);

    auto progressRing = new FluProgressRing(displayBox);
    progressRing->move(50, 50);
    progressRing->setShowText(true);
    // progressRing->setCurValue(85);

    QTimer* timer = new QTimer(this);
    timer->setInterval(100);
    timer->start();

    m_nTimes = 0;
    connect(timer, &QTimer::timeout, [=]() {
        m_nTimes++;
        m_nTimes = m_nTimes %= 100;
        progressRing->setCurValue(m_nTimes);
    });

    // displayBox1->getBodyLayout()->addWidget(checkBox);
    m_vScrollView->getMainLayout()->addWidget(displayBox, 0, Qt::AlignTop);
}

void FluProgressRingPage::addBusyRing()
{
    auto displayBox = new FluDisplayBox;
    displayBox->setTitle("An busy ring.");
    displayBox->getCodeExpander()->setCodeByPath("../code/ProgressRingPageCode3.md");
    displayBox->setBodyWidgetFixedHeight(96);

    auto busyRing = new FluBusyProgressRing(displayBox);
    busyRing->move(50, 50);

    // displayBox1->getBodyLayout()->addWidget(checkBox);
    m_vScrollView->getMainLayout()->addWidget(displayBox, 0, Qt::AlignTop);
}

void FluProgressRingPage::onThemeChanged()
{
    if (FluThemeUtils::isLightTheme())
    {
        FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluProgressRingPage.qss", this);
    }
    else
    {
        FluStyleSheetUitls::setQssByFileName("../StyleSheet/dark/FluProgressRingPage.qss", this);
    }
}
