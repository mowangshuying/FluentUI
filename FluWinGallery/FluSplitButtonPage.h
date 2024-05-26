#pragma once

#include "FluAEmptyPage.h"
#include "../FluControls/FluSplitButton.h"
#include "../FluUtils/FluUtils.h"
#include "../FluControls/FluColorFlyout.h"
#include "../FluControls/FluDisplayBox.h"
#include "../FluControls/FluVScrollView.h"

class FluSplitButtonPage : public FluAEmptyPage
{
    Q_OBJECT
  public:
    FluSplitButtonPage(QWidget* parent = nullptr) : FluAEmptyPage(parent)
    {
        m_mainLayout->setAlignment(Qt::AlignTop);
        m_titleLabel->setText("SplitButton");
        m_infoLabel->setText("The splitButton is a dropdown button, but with an addition execution hit target.");

        addSplitButtonWithText();

        FluStyleSheetUitls::setQssByFileName(":/StyleSheet/light/FluSplitButtonPage.qss", this);

        // connect(FluThemeUtils::getUtils(), &FluThemeUtils::themeChanged, [=](FluTheme theme) { onThemeChanged(); }); { onThemeChanged(); });
    }

    void addSplitButtonWithText()
    {
        auto displayBox = new FluDisplayBox;
        displayBox->setTitle("A SplitButton with text.");
        displayBox->getCodeExpander()->setCodeByPath(":/code/SplitButtonPageCode1.md");

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
        displayBox->getCodeExpander()->setCodeByPath(":/code/SplitButtonPageCode1.md");
        m_vScrollView->getMainLayout()->addWidget(displayBox, 0, Qt::AlignTop);
    }
  public slots:
    void onThemeChanged()
    {
        if (FluThemeUtils::getUtils()->getTheme() == FluTheme::Light)
        {
            FluStyleSheetUitls::setQssByFileName(":/StyleSheet/light/FluSplitButtonPage.qss", this);
        }
        else
        {
            FluStyleSheetUitls::setQssByFileName(":/StyleSheet/dark/FluSplitButtonPage.qss", this);
        }
    }
};
