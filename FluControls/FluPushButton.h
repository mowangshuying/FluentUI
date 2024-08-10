#pragma once

#include <QPaintEvent>
#include <QPainter>
#include <QPushButton>

#include "../FluUtils/FluUtils.h"

class FluPushButton : public QPushButton
{
    Q_OBJECT
  public:
    FluPushButton(QWidget *parent = nullptr) : QPushButton(parent)
    {
        setFixedSize(200, 30);
        // setFixedHeight(30);
        FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluPushButton.qss", this);
        if (FluThemeUtils::isDarkTheme())
        {
            FluStyleSheetUitls::setQssByFileName("../StyleSheet/dark/FluPushButton.qss", this);
        }
        connect(FluThemeUtils::getUtils(), &FluThemeUtils::themeChanged, this, [=](FluTheme theme) { onThemeChanged(); });
    }
    explicit FluPushButton(const QString &text, QWidget *parent = nullptr) : FluPushButton(parent) {
        setText(text);
    }
  public slots:
    void onThemeChanged()
    {
        if (FluThemeUtils::isLightTheme())
        {
            FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluPushButton.qss", this);
        }
        else
        {
            FluStyleSheetUitls::setQssByFileName("../StyleSheet/dark/FluPushButton.qss", this);
        }
    }

  protected:
};