#include "FluTextToggleSwitchEx.h"

FluTextToggleSwitchEx::FluTextToggleSwitchEx(QWidget* parent /*= nullptr*/) : FluWidget(parent)
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

void FluTextToggleSwitchEx::setText(QString onText, QString offText)
{
    // m_textLabel->setText(text);
    m_onText = onText;
    m_offText = offText;
}

void FluTextToggleSwitchEx::onThemeChanged()
{
    if (FluThemeUtils::isLightTheme())
    {
        FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluTextToggleSwithEx.qss", this);
    }
    else
    {
        FluStyleSheetUitls::setQssByFileName("../StyleSheet/dark/FluTextToggleSwithEx.qss", this);
    }
}
