#include "FluPMenu.h"

namespace
{
// Qt builds its standard text-editing context menus from platform theme icons, whose
// freedesktop names are still carried by the resulting QIcon (see QIcon::name()). Those themes
// only ship 16/24/48/128 px variants, while FluPMenuStyle asks every menu icon for a fixed
// square pixmap of m_menuItemIconWH (20 px) and ignores pixelMetric(PM_SmallIconSize), which
// this style reports as 0. A 20 px request against a 16/24 px source is resampled into a
// non-square bitmap (measured: 15x20 for edit-undo, 13x20 for edit-cut, 19x20 for
// edit-select-all) and drawn as a flat single-colour silhouette, so a standard menu taken over
// by fromStandardMenu looks visibly different from a hand-built Fluent menu, whose actions use
// square icon-font glyphs. Map the well-known theme names onto the matching Fluent glyph so
// both construction paths render the same artwork.
FluAwesomeType fluentIconTypeForThemeIconName(const QString& themeName)
{
    static const struct Entry
    {
        const char* themeName;
        FluAwesomeType awesomeType;
    } table[] = {
        {"edit-undo", FluAwesomeType::Undo},
        {"edit-redo", FluAwesomeType::Redo},
        {"edit-cut", FluAwesomeType::Cut},
        {"edit-copy", FluAwesomeType::Copy},
        {"edit-paste", FluAwesomeType::Paste},
        {"edit-delete", FluAwesomeType::Delete},
        {"edit-clear", FluAwesomeType::Clear},
        {"edit-select-all", FluAwesomeType::SelectAll},
        {"edit-find", FluAwesomeType::Search},
        {"edit-find-replace", FluAwesomeType::Search},
        {"format-text-bold", FluAwesomeType::Bold},
        {"format-text-italic", FluAwesomeType::Italic},
        {"format-text-underline", FluAwesomeType::Underline},
        {"tools-check-spelling", FluAwesomeType::Spelling},
        {"object-select", FluAwesomeType::Accept},
        {"list-add", FluAwesomeType::Add},
        {"list-remove", FluAwesomeType::Remove},
    };

    for (const Entry& entry : table)
    {
        if (themeName == QLatin1String(entry.themeName))
            return entry.awesomeType;
    }
    return FluAwesomeType::None;
}
} // namespace

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

        // Replace a leftover platform theme icon with the matching Fluent glyph, but only when
        // the icon still carries a freedesktop theme name: an icon the application set by hand
        // has no theme name and must be left exactly as it is.
        const QIcon actionIcon = action->icon();
        if (!actionIcon.isNull() && !actionIcon.name().isEmpty())
        {
            const FluAwesomeType awesomeType = fluentIconTypeForThemeIconName(actionIcon.name());
            if (awesomeType != FluAwesomeType::None)
                action->setIcon(FluIconUtils::getFluentIcon(awesomeType, FluThemeUtils::getUtils()->getTheme()));
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
