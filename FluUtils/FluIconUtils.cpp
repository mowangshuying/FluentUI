#include "FluIconUtils.h"
#include "../FluControls/FluDef.h"
#include <QFontDatabase>
#include <QPainter>

FluIconUtils::FluIconUtils()
{
    int fontId = QFontDatabase::addApplicationFont("../res/Segoe_Fluent_Icons.ttf");
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

QPixmap FluIconUtils::getFluentIconPixmap(FluAwesomeType nType)
{
    return getFluentIconPixmap(nType, QColor(30, 30, 30));
}

QPixmap FluIconUtils::getFluentIconPixmap(FluAwesomeType nType, QColor penColor)
{
    QFont tmpFont = getInstance()->m_fluentFont;
    tmpFont.setPixelSize(20);

    QPixmap tmpPixMap(30, 30);
    tmpPixMap.fill(Qt::transparent);
    QPainter painter;
    painter.begin(&tmpPixMap);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
    painter.setPen(penColor);
    //   painter.setBrush(Qt::black);
    tmpFont.setPointSize(15);
    painter.setFont(tmpFont);
    painter.drawText(tmpPixMap.rect(), Qt::AlignCenter, QChar((int)nType));
    painter.end();
    // tmpPixMap.save("tmp.png");
    return tmpPixMap;
}

QIcon FluIconUtils::getFluentIcon(FluAwesomeType nType)
{
    return QIcon(getFluentIconPixmap(nType));
}

QIcon FluIconUtils::getFluentIcon(FluAwesomeType nType, QColor penColor)
{
    return QIcon(getFluentIconPixmap(nType, penColor));
}

void FluIconUtils::saveFluentPng(FluAwesomeType nType, QString filename)
{
    auto pixmap = getFluentIconPixmap(nType);
    pixmap.save(filename);
}
