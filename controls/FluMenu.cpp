#include "FluMenu.h"
#include "FluDef.h"
#include "../utils/FluIconUtils.h"
#include <QGraphicsDropShadowEffect>
#include "../utils/FluUtils.h"
#include <QPainterPath>
#include <QPainter>
#include <QStyleOption>
#include <QWidgetAction>
#include <QMoveEvent>

FluMenu::FluMenu(QWidget* parent /*= nullptr*/) : QMenu(parent)
{
    setWindowFlags(windowFlags() | Qt::NoDropShadowWindowHint | Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground, true);
    setMouseTracking(true);
    onThemeChanged();
    connect(FluThemeUtils::getUtils(), &FluThemeUtils::themeChanged, this, [=](FluTheme theme) { onThemeChanged(); });
}

FluMenu* FluMenu::fromStandardMenu(QMenu* standardMenu, QWidget* parent /*= nullptr*/)
{
    auto menu = new FluMenu(parent);
    if (!standardMenu)
        return menu;

    menu->setTitle(standardMenu->title());
    const auto standardActions = standardMenu->actions();
    for (auto action : standardActions)
    {
        if (!action)
            continue;

        // 子菜单同样是原生 QMenu，需要递归换成 FluMenu，否则展开时仍是系统样式
        if (auto subMenu = action->menu())
        {
            auto fluentSubMenu = FluMenu::fromStandardMenu(subMenu, menu);
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

void FluMenu::execStandardContextMenu(QWidget* widget, QMenu* standardMenu, const QPoint& globalPos)
{
    auto menu = FluMenu::fromStandardMenu(standardMenu, widget);
    menu->exec(globalPos);
    menu->deleteLater();
}

void FluMenu::addAction(FluAction* action)
{
    QMenu::addAction(action);
}

void FluMenu::mouseMoveEvent(QMouseEvent* e)
{
    QMenu::mouseMoveEvent(e);
}

void FluMenu::paintEvent(QPaintEvent* event)
{
    QMenu::paintEvent(event);
}

void FluMenu::onThemeChanged()
{
    FluStyleSheetUtils::setQssByFileName("FluMenu.qss", this, FluThemeUtils::getUtils()->getTheme());
    for (auto action : actions())
    {
        // 标准右键菜单迁移进来的是原生 QAction（含分隔符），不能当成 FluAction 用
        auto fluAction = qobject_cast<FluAction*>(action);
        if (!fluAction || fluAction->getAwesomeType() == FluAwesomeType::None)
            continue;

        fluAction->setIcon(FluIconUtils::getFluentIcon(fluAction->getAwesomeType(), FluThemeUtils::getUtils()->getTheme()));
    }
}
