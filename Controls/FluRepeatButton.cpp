#include "FluRepeatButton.h"

FluRepeatButton::FluRepeatButton(QWidget* parent /*= nullptr*/) : QPushButton(parent)
{
    m_clickedCount = 0;
    setFixedSize(200, 30);
    connect(this, &FluRepeatButton::clicked, [=](bool isChecked) { m_clickedCount++; });
    onThemeChanged();
    connect(FluThemeUtils::getUtils(), &FluThemeUtils::themeChanged, this, [=](FluTheme theme) { onThemeChanged(); });
}

void FluRepeatButton::setClickCount(int count)
{
    m_clickedCount = count;
    emit clickedCountChanged(count);
}

int FluRepeatButton::getClickCount()
{
    return m_clickedCount;
}

void FluRepeatButton::onThemeChanged()
{
    FluStyleSheetUtils::setQssByFileName("FluRepeatButton.qss", this, FluThemeUtils::getUtils()->getTheme());
}
