#include "FluMenu.h"
#include "FluDef.h"
#include "../FluUtils/FluIconUtils.h"
#include <QGraphicsDropShadowEffect>
#include "../FluUtils/FluUtils.h"
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
    FluStyleSheetUitls::setQssByFileName("FluMenu.qss", this, FluThemeUtils::getUtils()->getTheme());
    for (auto action : actions())
    {
        auto fluAction = (FluAction*)action;
        if (fluAction->getAwesomeType() == FluAwesomeType::None)
            continue;

        fluAction->setIcon(FluIconUtils::getFluentIcon(fluAction->getAwesomeType(), FluThemeUtils::getUtils()->getTheme()));
    }
}
