#include "FluRadioButton.h"

FluRadioButton::FluRadioButton(QWidget* parent /*= nullptr*/) : QRadioButton(parent)
{
    onThemeChanged();
    connect(FluThemeUtils::getUtils(), &FluThemeUtils::themeChanged, this, [=](FluTheme theme) { onThemeChanged(); });
}

FluRadioButton::FluRadioButton(const QString& text, QWidget* parent /*= nullptr*/) : QRadioButton(text, parent)
{
    onThemeChanged();
    connect(FluThemeUtils::getUtils(), &FluThemeUtils::themeChanged, this, [=](FluTheme theme) { onThemeChanged(); });
}

void FluRadioButton::onThemeChanged()
{
    FluStyleSheetUtils::setQssByFileName("FluRadioButton.qss", this, FluThemeUtils::getUtils()->getTheme());
}
