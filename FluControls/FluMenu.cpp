#include "FluMenu.h"
#include "FluDef.h"
#include "../FluUtils/FluIconUtils.h"
#include <QGraphicsDropShadowEffect>
#include "../FluUtils/FluUtils.h"
#include <QPainterPath>
#include <QPainter>

#define SHADOW_WIDTH 5

FluMenu::FluMenu(QWidget* parent /*= nullptr*/) : QMenu(parent)
{
    setWindowFlags(windowFlags() | Qt::NoDropShadowWindowHint | Qt::FramelessWindowHint);
    // setAttribute(Qt::WA_TranslucentBackground, true);
    // setContentsMargins(5, 5, 5, 5);
    // setContentsMargins(0, 0, 0, 0);
    FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluMenu.qss", this);
}

void FluMenu::paintEvent(QPaintEvent* event)
{
    //   QMenu::paintEvent(event);
    //  QPainter painter(this);
    //  painter.setRenderHint(QPainter::Antialiasing, true);
    ////  painter.fill(QRect(SHADOW_WIDTH, SHADOW_WIDTH, this->width() - 2 * SHADOW_WIDTH, this->height() - 2 * SHADOW_WIDTH), QBrush(QColor(249, 249, 249)));
    //  QColor color(50, 50, 50, 30);
    //  for (int i = 0; i < SHADOW_WIDTH; i++)
    //  {
    //      color.setAlpha(80 - qSqrt(i) * 40);
    //      painter.setPen(color);
    //      painter.drawRoundedRect(SHADOW_WIDTH - i, SHADOW_WIDTH - i, this->width() - (SHADOW_WIDTH - i) * 2, this->height() - (SHADOW_WIDTH - i) * 2, 4, 4);
    //  }
}
