#pragma once

#include <QSettings>
#include "FluThemeUtils.h"

class FluConfigUtils : public QObject
{
  public:
    FluConfigUtils(QObject* parent = nullptr);

    ~FluConfigUtils();

    FluTheme getTheme();

    void setTheme(FluTheme theme);

  protected:
    QSettings* m_settings;

    // public:
    //     FluTheme m_theme; // the theme
};
