#pragma once

#include <QWidget>
#include <QCheckBox>
#include "../FluUtils/FluUtils.h"

class FluToggleSwitch : public QCheckBox
{
    Q_OBJECT
  public:
    FluToggleSwitch(QWidget* parent = nullptr) : QCheckBox(parent)
    {
        m_onText = "On";
        m_offText = "Off";

        setText(m_offText);
        FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluToggleSwitch.qss", this);
        connect(this, &FluToggleSwitch::clicked, [=](bool bChecked) {
            if (bChecked)
                setText(m_onText);
            else
                setText(m_offText);
        });

        connect(FluThemeUtils::getUtils(), &FluThemeUtils::themeChanged, [=](FluTheme theme) { onThemeChanged(); });
    }

    FluToggleSwitch(QString text, QWidget* parent = nullptr) : QCheckBox(text, parent)
    {
        m_onText = "On";
        m_offText = "Off";

        setText(m_offText);
        FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluToggleSwitch.qss", this);
        connect(this, &FluToggleSwitch::clicked, [=](bool bChecked) {
            if (bChecked)
                setText(m_onText);
            else
                setText(m_offText);
        });

        connect(FluThemeUtils::getUtils(), &FluThemeUtils::themeChanged, [=](FluTheme theme) { onThemeChanged(); });
    }

    void setOnOffText(QString onText, QString offText)
    {
        m_onText = onText;
        m_offText = offText;
    }

  public slots:
    void onThemeChanged()
    {
        if (FluThemeUtils::getUtils()->getTheme() == FluTheme::Light)
        {
            FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluToggleSwitch.qss", this);
        }
        else
        {
            FluStyleSheetUitls::setQssByFileName("../StyleSheet/dark/FluToggleSwitch.qss", this);
        }
    }

  protected:
    QString m_onText;
    QString m_offText;
};
