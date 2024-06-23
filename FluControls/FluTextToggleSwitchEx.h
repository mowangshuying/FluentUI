#pragma once

#include "FluToggleSwitchEx.h"
#include "FluLabel.h"

#include <QHBoxLayout>

class FluTextToggleSwitchEx : public FluWidget
{
    Q_OBJECT
  public:
    FluTextToggleSwitchEx(QWidget* parent = nullptr) : FluWidget(parent)
    {
        m_hMainLayout = new QHBoxLayout;
        m_hMainLayout->setContentsMargins(0, 0, 0, 0);
        setLayout(m_hMainLayout);

        m_toggleSwithEx = new FluToggleSwitchEx;
        m_textLabel = new FluLabel;
        m_textLabel->setLabelStyle(FluLabelStyle::BodyTextBlockStyle);
        m_textLabel->setWordWrap(true);

        m_hMainLayout->addWidget(m_toggleSwithEx);
        m_hMainLayout->addWidget(m_textLabel);

        setText("on", "off");
        m_textLabel->setText(m_offText);
        connect(m_toggleSwithEx, &FluToggleSwitchEx::toggled, [=](bool bChecked) {
            if (bChecked)
            {
                m_textLabel->setText(m_onText);
            }
            else
            {
                m_textLabel->setText(m_offText);
            }
        });

        FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluTextToggleSwithEx.qss", this);
        connect(FluThemeUtils::getUtils(), &FluThemeUtils::themeChanged, this, [=](FluTheme theme) { onThemeChanged(); });
    }

    void setText(QString onText, QString offText)
    {
        // m_textLabel->setText(text);
        m_onText = onText;
        m_offText = offText;
    }
  public slots:
    void onThemeChanged()
    {
        if (FluThemeUtils::getUtils()->getTheme() == FluTheme::Light)
        {
            FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluTextToggleSwithEx.qss", this);
        }
        else
        {
            FluStyleSheetUitls::setQssByFileName("../StyleSheet/dark/FluTextToggleSwithEx.qss", this);
        }
    }

  protected:
    QString m_onText;
    QString m_offText;

    QHBoxLayout* m_hMainLayout;
    FluToggleSwitchEx* m_toggleSwithEx;
    FluLabel* m_textLabel;
};
