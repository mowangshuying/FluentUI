#include "FluPushButton.h"

FluPushButton::FluPushButton(QWidget *parent /*= nullptr*/) : QPushButton(parent)
{
    setFixedSize(200, 30);
    onThemeChanged();
    connect(FluThemeUtils::getUtils(), &FluThemeUtils::themeChanged, this, [=](FluTheme theme) { onThemeChanged(); });
}

FluPushButton::FluPushButton(const QString &text, QWidget *parent /*= nullptr*/) : FluPushButton(parent)
{
    setText(text);
}

void FluPushButton::onThemeChanged()
{
    if (FluThemeUtils::isLightTheme())
    {
        FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluPushButton.qss", this);
    }
    else
    {
        FluStyleSheetUitls::setQssByFileName("../StyleSheet/dark/FluPushButton.qss", this);
    }
}
