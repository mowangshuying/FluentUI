#include "FluPushButton.h"

FluPushButton::FluPushButton(QWidget *parent /*= nullptr*/) : QPushButton(parent)
{
    setPill(false);
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
    FluStyleSheetUitls::setQssByFileName("FluPushButton.qss", this, FluThemeUtils::getUtils()->getTheme());
}
