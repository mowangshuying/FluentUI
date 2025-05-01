#include "FluProgressBar.h"

FluProgressBar::FluProgressBar(QWidget* parent /*= nullptr*/) : QProgressBar(parent)
{
    setTextVisible(false);
    onThemeChanged();
    connect(FluThemeUtils::getUtils(), &FluThemeUtils::themeChanged, this, [=](FluTheme theme) { onThemeChanged(); });
}

void FluProgressBar::onThemeChanged()
{
    FluStyleSheetUitls::setQssByFileName("FluProgressBar.qss", this, FluThemeUtils::getUtils()->getTheme());
}
