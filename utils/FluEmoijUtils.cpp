#include "FluEmoijUtils.h"
#include <QPainter>
#include <QtSvg/QSvgRenderer>
#include <QApplication>
#include <QIcon>
#include "FluLogUtils.h"


QPixmap FluEmoijUtils::getSvgPixmap(QString svgPath)
{
    QPixmap pixmap(QSize(30, 30));
    pixmap.fill(Qt::transparent);

    QSvgRenderer renderer(svgPath);

    if (!renderer.isValid())
    {
        return pixmap;
    }

    //if (svgPath.contains("CherryBlossomColor"))
    //{
    //    //LOG_DEBUG << "view Box:" << renderer.viewBox();
    //    LOG_DEBUG << "default Size" << renderer.defaultSize();
    //}

    //LOG_DEBUG << svgPath;
    QPainter painter(&pixmap);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing | QPainter::SmoothPixmapTransform);
    renderer.render(&painter, pixmap.rect());
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
