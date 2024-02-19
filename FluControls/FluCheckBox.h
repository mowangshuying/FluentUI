#pragma once

#include <QCheckBox>
#include "../FluUtils/FluUtils.h"

class FluCheckBox : public QCheckBox
{
    Q_OBJECT
  public:
    explicit FluCheckBox(QWidget* parent = nullptr) : QCheckBox(parent)
    {
        FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluCheckBox.qss", this);
        connect(FluThemeUtils::getUtils(), &FluThemeUtils::themeChanged, [=](FluTheme theme) { onThemeChanged(); });
    }

    explicit FluCheckBox(const QString& text, QWidget* parent = nullptr) : QCheckBox(text, parent)
    {
        FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluCheckBox.qss", this);
        connect(FluThemeUtils::getUtils(), &FluThemeUtils::themeChanged, [=](FluTheme theme) { onThemeChanged(); });
    }

  public slots:
    void onThemeChanged()
    {
        if (FluThemeUtils::getUtils()->getTheme() == FluTheme::Light)
        {
            FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluCheckBox.qss", this);
        }
        else
        {
            FluStyleSheetUitls::setQssByFileName("../StyleSheet/dark/FluCheckBox.qss", this);
        }
    }
};
