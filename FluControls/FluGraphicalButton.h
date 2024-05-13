#pragma once

#include "../FluUtils/FluUtils.h"
#include "FluDef.h"
#include <QPushButton>

class FluGraphicalButton : public QPushButton
{
    Q_OBJECT
  public:
    FluGraphicalButton(QWidget* parent = nullptr) : QPushButton(parent)
    {
        setFixedSize(50, 50);
        setIconSize(QSize(28, 28));
        // FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluGraphicalButton.qss", this);

        onThemeChanged();
        connect(FluThemeUtils::getUtils(), &FluThemeUtils::themeChanged, [=](FluTheme theme) { onThemeChanged(); });
    }

  public slots:
    void onThemeChanged()
    {
        if (FluThemeUtils::getUtils()->getTheme() == FluTheme::Light)
        {
            FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluGraphicalButton.qss", this);
        }
        else
        {
            FluStyleSheetUitls::setQssByFileName("../StyleSheet/dark/FluGraphicalButton.qss", this);
        }
    }
};
