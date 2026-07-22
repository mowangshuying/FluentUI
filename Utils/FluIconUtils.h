#pragma once

#include <QFont>
#include <QIcon>
#include <QPixmap>

#include "../Controls/FluDef.h"
#include "../Utils/FluThemeUtils.h"

#define FluGetIcon(type) FluIconUtils::GetFluentIcon(type)
#define FluGetIconPixmap(type) FluIconUtils::GetFluentIconPixmap(type)

class FluIconUtils
{
  private:
    FluIconUtils();
    ~FluIconUtils();

  public:
    static FluIconUtils *getInstance();
    static QPixmap getFluentIconPixmap(FluAwesomeType type);
    static QIcon getFluentIcon(FluAwesomeType type);

    static QPixmap getFluentIconPixmap(FluAwesomeType type, FluTheme theme);
    static QPixmap getFluentIconPixmap(FluAwesomeType type, FluTheme theme, int w, int h);
    static QIcon getFluentIcon(FluAwesomeType type, FluTheme theme);
    static QIcon getFluentIcon(FluAwesomeType type, FluTheme theme, int w, int h);

    static QPixmap getFluentIconPixmap(FluAwesomeType type, QColor penColor, int w, int h);
    static QPixmap getFluentIconPixmap(FluAwesomeType type, QColor penColor);
    static QIcon getFluentIcon(FluAwesomeType type, QColor penColor);

    static void saveFluentPng(FluAwesomeType type, FluTheme theme, QString filename);

    static QPixmap getSvgPixmap(QString svgPath);
    static QIcon getSvgIcon(QString svgPath);

    static QPixmap getPixmap(QString path)
    {
#ifndef USE_QRC
        return QPixmap(path);
#else
        path = path.replace("../res/", ":/res/");
        return QPixmap(path);
#endif
    }

  private:
    QFont m_fluentFont;
};
