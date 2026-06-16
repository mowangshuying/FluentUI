#include "FluMenuBar.h"

FluMenuBar::FluMenuBar(QWidget* parent /*= nullptr*/) : QMenuBar(parent)
{
    setMouseTracking(true);
    onThemeChanged();
    connect(FluThemeUtils::getUtils(), &FluThemeUtils::themeChanged, this, [=](FluTheme theme) { onThemeChanged(); });
}

void FluMenuBar::onThemeChanged()
{
    FluStyleSheetUitls::setQssByFileName("FluMenuBar.qss", this, FluThemeUtils::getUtils()->getTheme());
}
