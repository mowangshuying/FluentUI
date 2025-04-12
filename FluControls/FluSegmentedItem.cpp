#include "FluSegmentedItem.h"

FluSegmentedItem::FluSegmentedItem(QWidget* parent /*= nullptr*/) : QPushButton(parent)
{
    setFixedHeight(30);
    onThemeChanged();

    connect(this, &FluSegmentedItem::clicked, this, [=]() { emit ItemClicked(this); });

    connect(FluThemeUtils::getUtils(), &FluThemeUtils::themeChanged, [=](FluTheme theme) { onThemeChanged(); });
}

void FluSegmentedItem::onThemeChanged()
{
    if (FluThemeUtils::isLightTheme())
    {
        FluStyleSheetUitls::setQssByFileName(FLURC("StyleSheet/light/FluSegmentedItem.qss"), this);
    }
    else if (FluThemeUtils::isDarkTheme())
    {
        FluStyleSheetUitls::setQssByFileName(FLURC("StyleSheet/dark/FluSegmentedItem.qss"), this);
    }
}
