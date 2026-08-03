#include "FluTabWidget.h"

FluTabWidget::FluTabWidget(QWidget *parent /*= nullptr*/) : QTabWidget(parent)
{
    onThemeChanged();
    connect(FluThemeUtils::getUtils(), &FluThemeUtils::themeChanged, this, [=](FluTheme theme) { onThemeChanged(); });
}

void FluTabWidget::onThemeChanged()
{
    FluStyleSheetUtils::setQssByFileName("FluTabWidget.qss", this, FluThemeUtils::getUtils()->getTheme());
}
