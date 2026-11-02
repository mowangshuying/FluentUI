#include "FluPMenu.h"

FluPMenu::FluPMenu(QWidget* parent) : QMenu(parent)
{
    setWindowFlags(Qt::Popup | Qt::FramelessWindowHint | Qt::NoDropShadowWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
    // QProxyStyle adopts the base style it is given by reparenting it to itself. Here style() is
    // the shared QStyleSheetStyle inherited from the parent widget, not something this menu owns,
    // so letting the proxy adopt it puts that shared style in the popup's QObject tree: destroying
    // the menu destroys the style every other widget in the window still points at, leaving them
    // with a dangling style pointer. Hand it back to its original parentless state after
    // construction and let QWidgetPrivate keep managing its lifetime.
    QStyle *inheritedStyle = style();
    m_style = new FluPMenuStyle(inheritedStyle);
    setStyle(m_style);
    if (inheritedStyle && inheritedStyle->parent() == m_style)
        inheritedStyle->setParent(nullptr);

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
