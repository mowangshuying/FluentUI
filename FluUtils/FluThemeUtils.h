#pragma once

#include <QObject>

enum class FluTheme
{
    Light,
    Dark,
};

class FluThemeUtils : public QObject
{
  public:
      FluThemeUtils(QObject* object = nullptr) : QObject(object)
      {
          m_theme = FluTheme::Light;
      }

      FluTheme getTheme()
      {
          return m_theme;
      }

      void setTheme(FluTheme theme)
      {
          m_theme = theme;
          emit themeChanged(m_theme);
      }

signals:
      void themeChanged(FluTheme theme);

protected:
      FluTheme m_theme;
};
