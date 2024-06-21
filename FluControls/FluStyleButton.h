#pragma once

#include "../FluUtils/FluUtils.h"
#include <QPushButton>

class FluStyleButton : public QPushButton
{
    Q_OBJECT
  public:
    FluStyleButton(QWidget* parent = nullptr) : QPushButton(parent)
    {
        setFixedSize(200, 30);
        FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluStyleButton.qss", this);
        connect(FluThemeUtils::getUtils(), &FluThemeUtils::themeChanged, [=](FluTheme theme) { onThemeChanged();
        });
    }

  public slots:
    void onThemeChanged()
    {
        if (FluThemeUtils::getUtils()->getTheme() == FluTheme::Light)
        {
            FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluStyleButton.qss", this);
        }
        else
        {
            FluStyleSheetUitls::setQssByFileName("../StyleSheet/dark/FluStyleButton.qss", this);
        }
    }
};
