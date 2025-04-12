#include "FluProgressBarPage.h"

FluProgressBarPage::FluProgressBarPage(QWidget* parent /*= nullptr*/) : FluAEmptyPage(parent)
{
    m_mainLayout->setAlignment(Qt::AlignTop);
    m_titleLabel->setText(tr("ProgressBar"));
    m_infoLabel->setText(
        tr("The ProgressBar has two different visual representations.\nIndeterminate - shows that a task is ongoing, but doesn't block user interaction.\nDeterminate - show how much progress has been made on a kknown amount of work."));

    auto displayBox1 = new FluDisplayBox;
    displayBox1->setTitle(tr("An indeterminate progress ring."));
    displayBox1->getCodeExpander()->setCodeByPath(FLURC("code/ProgressBarPageCode1.md"));
    displayBox1->setBodyWidgetFixedHeight(96);

    auto progressBar1 = new FluProgressBar(displayBox1);
    progressBar1->move(50, 70);
    progressBar1->setValue(75);
    progressBar1->setFixedWidth(150);

    // progressRing1->setWorking(true);

    m_vScrollView->getMainLayout()->addWidget(displayBox1, 0, Qt::AlignTop);
    onThemeChanged();
}

void FluProgressBarPage::onThemeChanged()
{
    if (FluThemeUtils::isLightTheme())
    {
        FluStyleSheetUitls::setQssByFileName(FLURC("StyleSheet/light/FluProgressBarPage.qss"), this);
    }
    else
    {
        FluStyleSheetUitls::setQssByFileName(FLURC("StyleSheet/dark/FluProgressBarPage.qss"), this);
    }
}
