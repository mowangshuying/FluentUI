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
