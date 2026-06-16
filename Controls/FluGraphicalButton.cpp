#include "FluGraphicalButton.h"

FluGraphicalButton::FluGraphicalButton(QWidget* parent /*= nullptr*/) : QPushButton(parent)
{
    setFixedSize(50, 50);
    setIconSize(QSize(28, 28));

    onThemeChanged();
    connect(FluThemeUtils::getUtils(), &FluThemeUtils::themeChanged, this, [=](FluTheme theme) { onThemeChanged(); });
}

void FluGraphicalButton::onThemeChanged()
{
    FluStyleSheetUitls::setQssByFileName("FluGraphicalButton.qss", this, FluThemeUtils::getUtils()->getTheme());
}
