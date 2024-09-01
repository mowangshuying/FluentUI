#include "FluCheckBox.h"

FluCheckBox::FluCheckBox(QWidget* parent /*= nullptr*/) : QCheckBox(parent)
{
    FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluCheckBox.qss", this);
    connect(FluThemeUtils::getUtils(), &FluThemeUtils::themeChanged, this, [=](FluTheme theme) { onThemeChanged(); });
}

FluCheckBox::FluCheckBox(const QString& text, QWidget* parent /*= nullptr*/) : QCheckBox(text, parent)
{
    FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluCheckBox.qss", this);
    connect(FluThemeUtils::getUtils(), &FluThemeUtils::themeChanged, this, [=](FluTheme theme) { onThemeChanged(); });
}

void FluCheckBox::onThemeChanged()
{
    if (FluThemeUtils::isLightTheme())
    {
        FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluCheckBox.qss", this);
    }
    else
    {
        FluStyleSheetUitls::setQssByFileName("../StyleSheet/dark/FluCheckBox.qss", this);
    }
}
