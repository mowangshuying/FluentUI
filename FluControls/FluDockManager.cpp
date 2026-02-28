#include "FluDockManager.h"

FluDockManager::FluDockManager(QWidget* parent) : CDockManager(parent)
{
    onThemeChanged();
    connect(FluThemeUtils::getUtils(), &FluThemeUtils::themeChanged, this, [=](FluTheme theme) { onThemeChanged(); });
}

// public slots:
void FluDockManager::onThemeChanged()
{
    FluStyleSheetUitls::setQssByFileName("FluDockManager.qss", this, FluThemeUtils::getUtils()->getTheme());
}
