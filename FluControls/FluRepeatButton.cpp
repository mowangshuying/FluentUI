#include "FluRepeatButton.h"

FluRepeatButton::FluRepeatButton(QWidget* parent /*= nullptr*/) : QPushButton(parent)
{
    m_nClickedCount = 0;
    setFixedSize(200, 30);
    connect(this, &FluRepeatButton::clicked, [=](bool bChecked) { m_nClickedCount++; });
    onThemeChanged();
    connect(FluThemeUtils::getUtils(), &FluThemeUtils::themeChanged, this, [=](FluTheme theme) { onThemeChanged(); });
}

void FluRepeatButton::setClickCount(int nCount)
{
    m_nClickedCount = nCount;
    emit clickedCountChanged(nCount);
}

int FluRepeatButton::getClickCount()
{
    return m_nClickedCount;
}

void FluRepeatButton::onThemeChanged()
{
    if (FluThemeUtils::isLightTheme())
    {
        FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluRepeatButton.qss", this);
    }
    else
    {
        FluStyleSheetUitls::setQssByFileName("../StyleSheet/dark/FluRepeatButton.qss", this);
    }
}
