#pragma once

#include "FluAEmptyPage.h"
#include "../FluControls/FluDisplayBox.h"
#include "../FluControls/FluRepeatButton.h"
#include "../FluUtils/FluUtils.h"
#include "../FluControls/FluVScrollView.h"

class FluRepeatButtonPage : public FluAEmptyPage
{
    Q_OBJECT
  public:
    FluRepeatButtonPage(QWidget* parent = nullptr) : FluAEmptyPage(parent)
    {
        m_mainLayout->setAlignment(Qt::AlignTop);
        m_titleLabel->setText("RepeatButtonPage");
        m_infoLabel->setText("The RepeatButton control is like a standard button, except that the Click event occurs continuously while the user presses the RepeatButton.");
        FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluRepeatButtonPage.qss", this);

        auto displayBox = new FluDisplayBox;
        displayBox->setTitle("A simple RepeatButton with text context.");

        displayBox->getCodeExpander()->setCodeByPath("../code/RepeatButtonPageCode1");
        displayBox->setBodyWidgetFixedHeight(64);

        auto repeatButton = new FluRepeatButton;
        repeatButton->setFixedSize(120, 30);
        repeatButton->setText("Click and hold");
        displayBox->getBodyLayout()->addWidget(repeatButton);
        m_vScrollView->getMainLayout()->addWidget(displayBox, 0, Qt::AlignTop);

        connect(FluThemeUtils::getUtils(), &FluThemeUtils::themeChanged, [=](FluTheme theme) { onThemeChanged(); });
    }

  public slots:
    void onThemeChanged()
    {
        if (FluThemeUtils::getUtils()->getTheme() == FluTheme::Light)
        {
            FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluRepeatButtonPage.qss", this);
        }
        else
        {
            FluStyleSheetUitls::setQssByFileName("../StyleSheet/dark/FluRepeatButtonPage.qss", this);
        }
    }
};
