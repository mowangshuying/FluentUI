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
    FluStyleSheetUitls::setQssByFileName("FluSegmentedItem.qss", this, FluThemeUtils::getUtils()->getTheme());
}
