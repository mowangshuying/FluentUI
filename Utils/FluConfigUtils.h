#pragma once

#include <QSettings>
#include "FluThemeUtils.h"

class FluConfigUtils : public QObject
{
  protected:
    FluConfigUtils(QObject* parent = nullptr);
    ~FluConfigUtils();

  public:
    static FluConfigUtils* getUtils()
    {
        if (m_configUtils == nullptr)
            m_configUtils = new FluConfigUtils();
        return m_configUtils;
    }

    FluTheme getTheme();

    void setTheme(FluTheme theme);

    QString getLanguage();

    void setLanguage(QString language);

    int getNavWidth();

    void setNavWidth(int width);

    int getNavStyle();

    void setNavStyle(int style);

    bool getViewCollapsed();

    void setViewCollapsed(bool collapsed);

    QSettings* getSettings();

  protected:
    QSettings* m_settings;

    // public:
    //     FluTheme m_theme; // the theme
    static FluConfigUtils* m_configUtils;
};
