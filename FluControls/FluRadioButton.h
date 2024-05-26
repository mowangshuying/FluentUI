#pragma once

#include <QRadioButton>
#include "../FluUtils/FluUtils.h"
#include <QProxyStyle>
#include <QPainter>
#include <QStyleOptionButton>

class FluRadioButton : public QRadioButton
{
    Q_OBJECT
  public:
    explicit FluRadioButton(QWidget* parent = nullptr) : QRadioButton(parent)
    {
        FluStyleSheetUitls::setQssByFileName(":/StyleSheet/light/FluRadioButton.qss", this);
        connect(FluThemeUtils::getUtils(), &FluThemeUtils::themeChanged, this, [=](FluTheme theme) { onThemeChanged(); });
    }

    explicit FluRadioButton(const QString& text, QWidget* parent = nullptr) : QRadioButton(text, parent)
    {
        FluStyleSheetUitls::setQssByFileName(":/StyleSheet/light/FluRadioButton.qss", this);
        connect(FluThemeUtils::getUtils(), &FluThemeUtils::themeChanged, this, [=](FluTheme theme) { onThemeChanged(); });
    }

  public slots:
    void onThemeChanged()
    {
        if (FluThemeUtils::getUtils()->getTheme() == FluTheme::Light)
        {
            FluStyleSheetUitls::setQssByFileName(":/StyleSheet/light/FluRadioButton.qss", this);
        }
        else
        {
            FluStyleSheetUitls::setQssByFileName(":/StyleSheet/dark/FluRadioButton.qss", this);
        }
    }
};
