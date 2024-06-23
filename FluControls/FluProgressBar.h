#pragma once

#include <QProgressBar>
#include "../FluUtils/FluUtils.h"

class FluProgressBar : public QProgressBar
{
    Q_OBJECT
  public:
    FluProgressBar(QWidget* parent = nullptr) : QProgressBar(parent)
    {
        setTextVisible(true);
        FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluProgressBar.qss", this);
        connect(FluThemeUtils::getUtils(), &FluThemeUtils::themeChanged, this, [=](FluTheme theme) { onThemeChanged(); });
    }

  public slots:
    void onThemeChanged()
    {
        if (FluThemeUtils::getUtils()->getTheme() == FluTheme::Light)
        {
            FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluProgressBar.qss", this);
        }
        else
        {
            FluStyleSheetUitls::setQssByFileName("../StyleSheet/dark/FluProgressBar.qss", this);
        }
    }

  protected:
};
