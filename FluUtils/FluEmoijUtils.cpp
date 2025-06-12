#include "FluEmoijUtils.h"
#include <QPainter>
#include <QtSvg/QSvgRenderer>
#include <QApplication>
#include <QIcon>

QPixmap FluEmoijUtils::getSvgPixmap(QString svgPath)
{
    QPixmap pixmap(QSize(30, 30));
    pixmap.fill(Qt::transparent);
    QPainter painter(&pixmap);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing | QPainter::SmoothPixmapTransform);
    QSvgRenderer renderer(svgPath);
    renderer.render(&painter);
    return pixmap;
}

QIcon FluEmoijUtils::getSvgIcon(QString svgPath)
{
    return QIcon(getSvgPixmap(svgPath));
}
