#include "FluIconUtils.h"
#include "../FluControls/FluDef.h"
#include <QFontDatabase>
#include <QPainter>
#include <QtSvg/QSvgRenderer>
#include <QApplication>

FluIconUtils::FluIconUtils()
{
    int fontId = QFontDatabase::addApplicationFont("../res/Segoe_Fluent_Icons.ttf");
    QStringList fontFamilies = QFontDatabase::applicationFontFamilies(fontId);
    m_fluentFont.setFamily(fontFamilies.at(0));

   // QApplication::setFont(m_fluentFont);
}

FluIconUtils::~FluIconUtils()
{
}

FluIconUtils *FluIconUtils::getInstance()
{
    static FluIconUtils utils;
    return &utils;
}

QPixmap FluIconUtils::getFluentIconPixmap(FluAwesomeType nType)
{
    //  return getFluentIconPixmap(nType, QColor(255, 255, 255));
    return getFluentIconPixmap(nType, QColor(8, 8, 8));
}

QPixmap FluIconUtils::getFluentIconPixmap(FluAwesomeType nType, QColor penColor, int w, int h)
{
    // return QPixmap();
    QFont tmpFont = getInstance()->m_fluentFont;
    tmpFont.setPixelSize(15);

    QPixmap tmpPixMap(w, h);
    tmpPixMap.fill(Qt::transparent);
    QPainter painter;
    painter.begin(&tmpPixMap);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
    painter.setPen(penColor);
    tmpFont.setPointSize(15);
    painter.setFont(tmpFont);
    painter.drawText(tmpPixMap.rect(), Qt::AlignCenter, QChar((unsigned int)nType));
    painter.end();
    // tmpPixMap.save("tmp.png");
    return tmpPixMap;
}

QPixmap FluIconUtils::getFluentIconPixmap(FluAwesomeType nType, QColor penColor)
{
    return getFluentIconPixmap(nType, penColor, 30, 30);
}

QIcon FluIconUtils::getFluentIcon(FluAwesomeType nType)
{
    return QIcon(getFluentIconPixmap(nType));
}

QPixmap FluIconUtils::getFluentIconPixmap(FluAwesomeType nType, FluTheme theme)
{
    if (theme == FluTheme::Light)
        return FluIconUtils::getFluentIconPixmap(nType, QColor(8, 8, 8));

    if (theme == FluTheme::Dark)
        return FluIconUtils::getFluentIconPixmap(nType, QColor(239, 239, 239));

    return FluIconUtils::getFluentIconPixmap(nType, QColor(8, 8, 8));
}

QIcon FluIconUtils::getFluentIcon(FluAwesomeType nType, FluTheme theme)
{
    return QIcon(getFluentIconPixmap(nType, theme));
}

QIcon FluIconUtils::getFluentIcon(FluAwesomeType nType, QColor penColor)
{
    return QIcon(getFluentIconPixmap(nType, penColor));
}

void FluIconUtils::saveFluentPng(FluAwesomeType nType, FluTheme theme, QString filename)
{
    auto pixmap = getFluentIconPixmap(nType, theme);
    pixmap.save(filename);
}

QPixmap FluIconUtils::getSvgPixmap(QString svgPath)
{
    QPixmap pixmap(QSize(30, 30));
    pixmap.fill(Qt::transparent);
    QPainter painter(&pixmap);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing | QPainter::SmoothPixmapTransform);
    QSvgRenderer renderer(svgPath);
    renderer.render(&painter);
    return pixmap;
}

QIcon FluIconUtils::getSvgIcon(QString svgPath)
{
    return QIcon(getSvgPixmap(svgPath));
}
