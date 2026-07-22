#include "FluTextToggleSwitchEx.h"

FluTextToggleSwitchEx::FluTextToggleSwitchEx(QWidget* parent /*= nullptr*/) : FluWidget(parent)
{
    m_hMainLayout = new QHBoxLayout;
    m_hMainLayout->setContentsMargins(0, 0, 0, 0);
    setLayout(m_hMainLayout);

    m_toggleSwitchEx = new FluToggleSwitchEx;
    m_textLabel = new FluLabel;
    m_textLabel->setLabelStyle(FluLabelStyle::BodyTextBlockStyle);
    m_textLabel->setWordWrap(true);

    m_hMainLayout->addWidget(m_toggleSwitchEx);
    m_hMainLayout->addWidget(m_textLabel);

    setText(tr("on"), tr("off"));
    m_textLabel->setText(m_offText);
    connect(m_toggleSwitchEx, &FluToggleSwitchEx::toggled, [=](bool bChecked) {
        if (bChecked)
        {
            m_textLabel->setText(m_onText);
        }
        else
        {
            m_textLabel->setText(m_offText);
        }

        emit stateChanged(bChecked);
    });

    onThemeChanged();
}

void FluTextToggleSwitchEx::setText(QString onText, QString offText)
{
    // m_textLabel->setText(text);
    m_onText = onText;
    m_offText = offText;
}

void FluTextToggleSwitchEx::setChecked(bool checked)
{
    m_toggleSwitchEx->setChecked(checked);
}

void FluTextToggleSwitchEx::onThemeChanged()
{
    // FluStyleSheetUtils::setQssByFileName("FluTextToggleSwithEx.qss", this, FluThemeUtils::getUtils()->getTheme());
}
