#include "FluMenu.h"
#include "FluDef.h"
#include "../FluUtils/FluIconUtils.h"
#include <QGraphicsDropShadowEffect>
#include "../FluUtils/FluUtils.h"
#include <QPainterPath>
#include <QPainter>

FluMenu::FluMenu(QWidget* parent /*= nullptr*/) : QMenu(parent)
{
    setWindowFlags(windowFlags() | Qt::FramelessWindowHint | Qt::NoDropShadowWindowHint);
    setAttribute(Qt::WA_TranslucentBackground, true);
    FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluMenu.qss", this);
}

void FluMenu::paintEvent(QPaintEvent* event)
{
    QMenu::paintEvent(event);
}
