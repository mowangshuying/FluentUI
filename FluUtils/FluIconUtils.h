#pragma once

#include <QFont>
#include <QIcon>
#include <QPixmap>

#include "../FluControls/FluDef.h"
#include "../FluUtils/FluThemeUtils.h"

#define FluGetIcon(nType) FluIconUtils::GetFluentIcon(nType)
#define FluGetIconPixmap(nType) FluIconUtils::GetFluentIconPixmap(nType)

class FluIconUtils
{
  private:
    FluIconUtils();
    ~FluIconUtils();

  public:
    static FluIconUtils *getInstance();
    static QPixmap getFluentIconPixmap(FluAwesomeType nType);
    static QIcon getFluentIcon(FluAwesomeType nType);

    static QPixmap getFluentIconPixmap(FluAwesomeType nType, FluTheme theme);
    static QPixmap getFluentIconPixmap(FluAwesomeType nType, FluTheme theme, int w, int h);
    static QIcon getFluentIcon(FluAwesomeType nType, FluTheme theme);
    static QIcon getFluentIcon(FluAwesomeType nType, FluTheme theme, int w, int h);

    static QPixmap getFluentIconPixmap(FluAwesomeType nType, QColor penColor, int w, int h);
    static QPixmap getFluentIconPixmap(FluAwesomeType nType, QColor penColor);
    static QIcon getFluentIcon(FluAwesomeType nType, QColor penColor);

    static void saveFluentPng(FluAwesomeType nType, FluTheme theme, QString filename);

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
