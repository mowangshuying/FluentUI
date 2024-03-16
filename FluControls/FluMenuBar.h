#pragma once

#include <QMenuBar>
#include "../FluUtils/FluUtils.h"
#include <QPainter>
#include <QStyleOption>
#include <QHBoxLayout>
#include <QVBoxLayout>

class FluMenuBar : public QMenuBar
{
    Q_OBJECT
  public:
    FluMenuBar(QWidget* parent = nullptr) : QMenuBar(parent)
    {
        setMouseTracking(true);
        FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluMenuBar.qss", this);
        connect(FluThemeUtils::getUtils(), &FluThemeUtils::themeChanged, [=](FluTheme theme) { onThemeChanged(); });
    }

  public slots:
    void onThemeChanged()
    {
        if (FluThemeUtils::getUtils()->getTheme() == FluTheme::Light)
        {
            FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluMenuBar.qss", this);
        }
        else
        {
            FluStyleSheetUitls::setQssByFileName("../StyleSheet/dark/FluMenuBar.qss", this);
        }
    }
};
