#include "FluPMenu.h"

FluPMenu::FluPMenu(QWidget* parent) : QMenu(parent)
{
    setWindowFlags(Qt::Popup | Qt::FramelessWindowHint | Qt::NoDropShadowWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
    m_style = new FluPMenuStyle(style());
    setStyle(m_style);

    onThemeChanged();
    connect(FluThemeUtils::getUtils(), &FluThemeUtils::themeChanged, this, [=](FluTheme theme) { onThemeChanged(); });
}

FluPMenu::FluPMenu(const QString& title, QWidget* parent) : FluPMenu(parent)
{
    setTitle(title);
}

void FluPMenu::onThemeChanged()
{
    FluStyleSheetUtils::setQssByFileName("FluPMenu.qss", this, FluThemeUtils::getUtils()->getTheme());
}
