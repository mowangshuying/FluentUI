#include "FluIconUtils.h"
#include "../Controls/FluDef.h"
#include <QFontDatabase>
#include <QPainter>
#include <QtSvg/QSvgRenderer>
#include <QApplication>

FluIconUtils::FluIconUtils()
{
#ifndef USE_QRC
    int fontId = QFontDatabase::addApplicationFont("../res/Segoe_Fluent_Icons.ttf");
#else
    int fontId = QFontDatabase::addApplicationFont(":/res/Segoe_Fluent_Icons.ttf");
#endif
    QStringList fontFamilies = QFontDatabase::applicationFontFamilies(fontId);
    m_fluentFont.setFamily(fontFamilies.at(0));
}

FluIconUtils::~FluIconUtils()
{
}

FluIconUtils *FluIconUtils::getInstance()
{
    static FluIconUtils utils;
    return &utils;
}

QPixmap FluIconUtils::getFluentIconPixmap(FluAwesomeType type)
{
    return getFluentIconPixmap(type, QColor(8, 8, 8));
}

QPixmap FluIconUtils::getFluentIconPixmap(FluAwesomeType type, QColor penColor, int w, int h)
{
    QFont tempFont = getInstance()->m_fluentFont;
    tempFont.setPixelSize(qMin(w, h) * 0.7);

    QPixmap tempPixmap(w, h);
    tempPixmap.fill(Qt::transparent);
    QPainter painter;
    painter.begin(&tempPixmap);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing | QPainter::SmoothPixmapTransform);
    painter.setPen(penColor);
    painter.setFont(tempFont);
    painter.drawText(tempPixmap.rect(), Qt::AlignCenter, QChar((unsigned int)type));
    painter.end();
    return tempPixmap;
}

QPixmap FluIconUtils::getFluentIconPixmap(FluAwesomeType type, QColor penColor)
{
    return getFluentIconPixmap(type, penColor, 30, 30);
}

QIcon FluIconUtils::getFluentIcon(FluAwesomeType type)
{
    return QIcon(getFluentIconPixmap(type));
}

QPixmap FluIconUtils::getFluentIconPixmap(FluAwesomeType type, FluTheme theme)
{
    if (theme == FluTheme::Light)
        return FluIconUtils::getFluentIconPixmap(type, QColor(8, 8, 8));

    if (theme == FluTheme::Dark)
        return FluIconUtils::getFluentIconPixmap(type, QColor(239, 239, 239));

    if (theme == FluTheme::AtomOneDark)
        return FluIconUtils::getFluentIconPixmap(type, QColor(Qt::white));

    return FluIconUtils::getFluentIconPixmap(type, QColor(8, 8, 8));
}

QPixmap FluIconUtils::getFluentIconPixmap(FluAwesomeType type, FluTheme theme, int w, int h)
{
    if (theme == FluTheme::Light)
        return FluIconUtils::getFluentIconPixmap(type, QColor(8, 8, 8), w, h);

    if (theme == FluTheme::Dark)
        return FluIconUtils::getFluentIconPixmap(type, QColor(239, 239, 239), w, h);

    if (theme == FluTheme::AtomOneDark)
        return FluIconUtils::getFluentIconPixmap(type, QColor(Qt::white), w, h);

    return FluIconUtils::getFluentIconPixmap(type, QColor(8, 8, 8), w, h);
}

QIcon FluIconUtils::getFluentIcon(FluAwesomeType type, FluTheme theme)
{
    return QIcon(getFluentIconPixmap(type, theme));
}

QIcon FluIconUtils::getFluentIcon(FluAwesomeType type, FluTheme theme, int w, int h)
{
    return QIcon(getFluentIconPixmap(type, theme, w, h));
}

QIcon FluIconUtils::getFluentIcon(FluAwesomeType type, QColor penColor)
{
    return QIcon(getFluentIconPixmap(type, penColor));
}

void FluIconUtils::saveFluentPng(FluAwesomeType type, FluTheme theme, QString filename)
{
    auto pixmap = getFluentIconPixmap(type, theme);
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
