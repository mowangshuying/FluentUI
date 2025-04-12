#include "FluSplitButtonPage.h"

FluSplitButtonPage::FluSplitButtonPage(QWidget* parent /*= nullptr*/) : FluAEmptyPage(parent)
{
    m_mainLayout->setAlignment(Qt::AlignTop);
    m_titleLabel->setText(tr("SplitButton"));
    m_infoLabel->setText(tr("The splitButton is a dropdown button, but with an addition execution hit target."));

    addSplitButtonWithText();

    FluStyleSheetUitls::setQssByFileName(FLURC("StyleSheet/light/FluSplitButtonPage.qss"), this);
}

void FluSplitButtonPage::addSplitButtonWithText()
{
    auto displayBox = new FluDisplayBox;
    displayBox->setTitle(tr("A SplitButton with text."));
    displayBox->getCodeExpander()->setCodeByPath(FLURC("code/SplitButtonPageCode1.md"));

    auto splitButton = new FluSplitButton(this);
    splitButton->setText("Choose Color.");
    // splitButton->move(50, 50);
    splitButton->setFixedSize(130, 30);

    // the FluColorFlyout.
    FluColorFlyout* colorLayout = new FluColorFlyout(splitButton);

    auto colorBtn00 = new FluColorButton(QColor(255, 0, 0));
    colorLayout->addColorButton(colorBtn00, 0, 0);

    auto colorBtn01 = new FluColorButton(QColor(255, 165, 0));
    colorLayout->addColorButton(colorBtn01, 0, 1);

    auto colorBtn02 = new FluColorButton(QColor(255, 255, 0));
    colorLayout->addColorButton(colorBtn02, 0, 2);

    auto colorBtn10 = new FluColorButton(QColor(0, 128, 0));
    colorLayout->addColorButton(colorBtn10, 1, 0);

    auto colorBtn11 = new FluColorButton(QColor(75, 0, 130));
    colorLayout->addColorButton(colorBtn11, 1, 1);

    auto colorBtn12 = new FluColorButton(QColor(238, 130, 238));
    colorLayout->addColorButton(colorBtn12, 1, 2);

    auto colorBtn20 = new FluColorButton(QColor(128, 128, 128));
    colorLayout->addColorButton(colorBtn20, 2, 0);

    connect(colorLayout, &FluColorFlyout::colorChanged, [=](QColor color) { LOG_DEBUG << "color: rgb(" << color.red() << "," << color.green() << "," << color.blue() << ")."; });

    connect(splitButton, &FluSplitButton::clicked, [=]() { colorLayout->show(); });

    displayBox->getBodyLayout()->addWidget(splitButton);
    displayBox->getCodeExpander()->setCodeByPath(FLURC("code/SplitButtonPageCode1.md"));
    m_vScrollView->getMainLayout()->addWidget(displayBox, 0, Qt::AlignTop);
}

void FluSplitButtonPage::onThemeChanged()
{
    if (FluThemeUtils::isLightTheme())
    {
        FluStyleSheetUitls::setQssByFileName(FLURC("StyleSheet/light/FluSplitButtonPage.qss"), this);
    }
    else
    {
        FluStyleSheetUitls::setQssByFileName(FLURC("StyleSheet/dark/FluSplitButtonPage.qss"), this);
    }
}
