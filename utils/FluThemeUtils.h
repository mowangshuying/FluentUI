#pragma once

#include <QObject>

enum class FluTheme
{
    Light,
    Dark,
    AtomOneDark,
    _END,
};

class FluThemeUtils : public QObject
{
    Q_OBJECT
  private:
    FluThemeUtils(QObject* object = nullptr);

  public:
    FluTheme getTheme();

    void setTheme(FluTheme theme);

    static QString getThemeName();

    static FluThemeUtils* getUtils();

    static bool isLightTheme()
    {
        return getUtils()->getTheme() == FluTheme::Light;
    }

    static bool isDarkTheme()
    {
        return getUtils()->getTheme() == FluTheme::Dark;
    }

    static bool isAtomOneDarkTheme()
    {
        return getUtils()->getTheme() == FluTheme::AtomOneDark;
    }

    static void __init()
    {
        getUtils();
    }

    static void __deInit()
    {
        if (m_themeUtils == nullptr)
            return;
        delete m_themeUtils;
        m_themeUtils = nullptr;
    }

  signals:
    void themeChanged(FluTheme theme);

  protected:
    FluTheme m_theme;

  private:
    static FluThemeUtils* m_themeUtils;
};
