#include "FluProgressBarPage.h"

FluProgressBarPage::FluProgressBarPage(QWidget* parent /*= nullptr*/) : FluAEmptyPage(parent)
{
    m_mainLayout->setAlignment(Qt::AlignTop);
    m_titleLabel->setText(tr("ProgressBar"));
    m_infoLabel->setText(
        tr("The ProgressBar has two different visual representations.\nIndeterminate - shows that a task is ongoing, but doesn't block user interaction.\nDeterminate - show how much progress has been made on a kknown amount of work."));

    // Determinate example
    auto displayBox1 = new FluDisplayBox;
    displayBox1->setTitle(tr("A determinate progress bar."));
    displayBox1->getCodeExpander()->setCodeByPath("../code/ProgressBarPageCode1.md");
    displayBox1->setBodyWidgetFixedHeight(96);

    auto progressBar1 = new FluProgressBar(displayBox1);
    progressBar1->move(50, 70);
    progressBar1->setValue(75);
    progressBar1->setFixedWidth(150);

    m_scrollView->getMainLayout()->addWidget(displayBox1, 0, Qt::AlignTop);

    // Indeterminate example
    auto displayBox2 = new FluDisplayBox;
    displayBox2->setTitle(tr("An indeterminate progress bar."));
    displayBox2->getCodeExpander()->setCodeByPath("../code/ProgressBarPageCode2.md");
    displayBox2->setBodyWidgetFixedHeight(96);

    auto progressBar2 = new FluProgressBar(displayBox2);
    progressBar2->move(50, 70);
    progressBar2->setFixedWidth(150);
    progressBar2->setWorking(true);

    m_scrollView->getMainLayout()->addWidget(displayBox2, 0, Qt::AlignTop);

    onThemeChanged();
}

void FluProgressBarPage::onThemeChanged()
{
    FluStyleSheetUtils::setQssByFileName("FluProgressBarPage.qss", this, FluThemeUtils::getUtils()->getTheme());
}
