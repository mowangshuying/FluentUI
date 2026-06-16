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
    FluStyleSheetUitls::setQssByFileName("FluRepeatButton.qss", this, FluThemeUtils::getUtils()->getTheme());
}
