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

FluPMenu* FluPMenu::fromStandardMenu(QMenu* standardMenu, QWidget* parent /*= nullptr*/)
{
    auto menu = new FluPMenu(parent);
    if (!standardMenu)
        return menu;

    menu->setTitle(standardMenu->title());
    const auto standardActions = standardMenu->actions();
    for (auto action : standardActions)
    {
        if (!action)
            continue;

        // 子菜单同样换成 FluPMenu，保证展开时仍是同一套自绘样式
        if (auto subMenu = action->menu())
        {
            auto fluentSubMenu = FluPMenu::fromStandardMenu(subMenu, menu);
            fluentSubMenu->setTitle(action->text());
            action->setMenu(fluentSubMenu);
        }

        // 先从原生菜单里摘走：QMenu 析构会 qDeleteAll 自己列表中的 action，
        // 只改父对象不够，否则下面 deleteLater 时会把迁过来的 action 一起删掉
        standardMenu->removeAction(action);

        // 再把 ownership 显式转到 Fluent 菜单，QMenu::addAction 不保证会重新设父
        action->setParent(menu);
        menu->QMenu::addAction(action);
    }

    standardMenu->deleteLater();
    return menu;
}

void FluPMenu::execStandardContextMenu(QWidget* widget, QMenu* standardMenu, const QPoint& globalPos)
{
    auto menu = FluPMenu::fromStandardMenu(standardMenu, widget);
    menu->exec(globalPos);
    menu->deleteLater();
}

void FluPMenu::onThemeChanged()
{
    FluStyleSheetUtils::setQssByFileName("FluPMenu.qss", this, FluThemeUtils::getUtils()->getTheme());
}
