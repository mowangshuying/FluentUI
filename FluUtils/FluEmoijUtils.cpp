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

QPixmap FluEmoijUtils::getSvgPixmap(FluEmoijType type)
{
    // #ifndef USE_QRC
    QString typeName = EnumTypeToQString(type);
    typeName += ".svg";

    QString svgPath = "";
#ifndef USE_QRC
    svgPath = "../res/Emoij/" + typeName;
#else
    svgPath = ":/res/Emoij/" + typeName;
#endif

    // #endif
    return FluEmoijUtils::getSvgPixmap(svgPath);
}

QIcon FluEmoijUtils::getSvgIcon(QString svgPath)
{
    return QIcon(getSvgPixmap(svgPath));
}

QIcon FluEmoijUtils::getSvgIcon(FluEmoijType type)
{
    return QIcon(FluEmoijUtils::getSvgPixmap(type));
}
