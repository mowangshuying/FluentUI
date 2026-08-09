#include "FluToggleButton.h"

FluToggleButton::FluToggleButton(QWidget* parent /*= nullptr*/) : QPushButton(parent)
{
    setFixedSize(120, 30);
    m_isToggled = false;
    setProperty("toggled", false);

    connect(this, &FluToggleButton::clicked, this, &FluToggleButton::onToggled);

    onThemeChanged();
    connect(FluThemeUtils::getUtils(), &FluThemeUtils::themeChanged, this, [=](FluTheme theme) { onThemeChanged(); });
}

bool FluToggleButton::getToggled() const
{
    return m_isToggled;
}

void FluToggleButton::setToggled(bool isToggled)
{
    if (m_isToggled == isToggled)
        return;
    m_isToggled = isToggled;
    setProperty("toggled", isToggled);
    style()->polish(this);
    update();
    emit toggledChanged(m_isToggled);
}

void FluToggleButton::onToggled()
{
    setToggled(!m_isToggled);
}

void FluToggleButton::onThemeChanged()
{
    FluStyleSheetUtils::setQssByFileName("FluToggleButton.qss", this, FluThemeUtils::getUtils()->getTheme());
}