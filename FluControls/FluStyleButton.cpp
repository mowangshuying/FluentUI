#include "FluStyleButton.h"

FluStyleButton::FluStyleButton(QWidget* parent /*= nullptr*/) : QPushButton(parent)
{
    setFixedSize(200, 30);
    onThemeChanged();
    connect(FluThemeUtils::getUtils(), &FluThemeUtils::themeChanged, this, [=](FluTheme theme) { onThemeChanged(); });
}

void FluStyleButton::onThemeChanged()
{
    FluStyleSheetUitls::setQssByFileName("FluStyleButton.qss", this, FluThemeUtils::getUtils()->getTheme());
}
