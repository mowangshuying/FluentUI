#pragma once

#include <QSlider>

#include "../FluUtils/FluUtils.h"

class FluSlider : public QSlider
{
    Q_OBJECT
  public:
    FluSlider(QWidget* parent = nullptr) : QSlider(parent)
    {
        FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluSlider.qss", this);
        connect(FluThemeUtils::getUtils(), &FluThemeUtils::themeChanged, this, [=](FluTheme theme) { onThemeChanged(); });
    }

    FluSlider(Qt::Orientation orientation, QWidget* parent = nullptr) : QSlider(orientation, parent)
    {
        FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluSlider.qss", this);
        connect(FluThemeUtils::getUtils(), &FluThemeUtils::themeChanged, this, [=](FluTheme theme) { onThemeChanged(); });
    }

  public slots:
    void onThemeChanged()
    {
        if (FluThemeUtils::isLightTheme())
        {
            FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluSlider.qss", this);
        }
        else
        {
            FluStyleSheetUitls::setQssByFileName("../StyleSheet/dark/FluSlider.qss", this);
        }
    }
};
