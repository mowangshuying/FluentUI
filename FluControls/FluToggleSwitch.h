#pragma once

#include "FluWidget.h"
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

        m_bEmptyText = false;

        setText(m_offText);
        FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluToggleSwitch.qss", this);
        connect(this, &FluToggleSwitch::clicked, [=](bool bChecked) {
            if (m_bEmptyText)
                return;

            if (bChecked)
                setText(m_onText);
            else
                setText(m_offText);
        });

        connect(FluThemeUtils::getUtils(), &FluThemeUtils::themeChanged, this, [=](FluTheme theme) { onThemeChanged(); });
    }

    FluToggleSwitch(QString text, QWidget* parent = nullptr) : QCheckBox(text, parent)
    {
        m_onText = "On";
        m_offText = "Off";

        setText(m_offText);
        FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluToggleSwitch.qss", this);
        connect(this, &FluToggleSwitch::clicked, [=](bool bChecked) {
            if (m_bEmptyText)
                return;

            if (bChecked)
                setText(m_onText);
            else
                setText(m_offText);
        });

        connect(FluThemeUtils::getUtils(), &FluThemeUtils::themeChanged, this, [=](FluTheme theme) { onThemeChanged(); });
    }

    void setOnOffText(QString onText, QString offText)
    {
        m_onText = onText;
        m_offText = offText;
    }

    void setEmptyText(bool bEmpty)
    {
        m_bEmptyText = bEmpty;
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
    bool m_bEmptyText;
    QString m_onText;
    QString m_offText;
};
