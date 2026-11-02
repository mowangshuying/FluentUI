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

        // Swap sub-menus to FluPMenu as well, so an expanded submenu keeps the same custom style
        if (auto subMenu = action->menu())
        {
            auto fluentSubMenu = FluPMenu::fromStandardMenu(subMenu, menu);
            fluentSubMenu->setTitle(action->text());
            action->setMenu(fluentSubMenu);
        }

        // Detach from the native menu first: ~QMenu runs qDeleteAll over the actions in its own
        // list, so reparenting alone is not enough: otherwise deleteLater below would also destroy
        // the actions we just moved over.
        standardMenu->removeAction(action);

        // Then transfer ownership to the Fluent menu explicitly; QMenu::addAction does not
        // guarantee it will reparent the action.
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
