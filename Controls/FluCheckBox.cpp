#include "FluCheckBox.h"

FluCheckBox::FluCheckBox(QWidget* parent /*= nullptr*/) : QCheckBox(parent)
{
    onThemeChanged();
    connect(FluThemeUtils::getUtils(), &FluThemeUtils::themeChanged, this, [=](FluTheme theme) { onThemeChanged(); });
}

FluCheckBox::FluCheckBox(const QString& text, QWidget* parent /*= nullptr*/) : QCheckBox(text, parent)
{
    onThemeChanged();
    connect(FluThemeUtils::getUtils(), &FluThemeUtils::themeChanged, this, [=](FluTheme theme) { onThemeChanged(); });
}

void FluCheckBox::onThemeChanged()
{
    FluStyleSheetUitls::setQssByFileName("FluCheckBox.qss", this, FluThemeUtils::getUtils()->getTheme());
}
