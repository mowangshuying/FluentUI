#pragma once

#include <QPushButton>
#include <QPropertyAnimation>
#include <QGraphicsOpacityEffect>
#include "../FluUtils/FluUtils.h"

class FluScaleButton : public QPushButton
{
    Q_OBJECT
  public:
    FluScaleButton(FluAwesomeType awesomeType, QWidget* parent = nullptr) : QPushButton(parent), m_iconType(awesomeType)
      {
          setFixedSize(30, 30);
          m_bPressed = false;

          m_currentPercentage = 1;
          scaleByPercentage(1);
          initTimer();

          onThemeChanged();
          connect(FluThemeUtils::getUtils(), &FluThemeUtils::themeChanged, this, [=](FluTheme theme) { 
              onThemeChanged();
          });
      }

      void initTimer()
      {

          m_timer = new QTimer(this);
          m_timer->setInterval(20);
          connect(m_timer, &QTimer::timeout, this, [=]() {
              if (m_bPressed)
              {
                  m_currentPercentage -= 0.1;
                  if (m_currentPercentage > 0)
                  {
                      scaleByPercentage(m_currentPercentage);
                  }
                  else
                  {
                      m_timer->stop();
                  }
              }
              else
              {
                  m_currentPercentage += 0.1;
                  if (m_currentPercentage < 1)
                  {
                      scaleByPercentage(m_currentPercentage);
                  }
                  else
                  {
                      m_timer->stop();
                  }
              }

          });
      }

      void scaleByPercentage(float scale)
      {
          int nWH = 18 + 6 * scale;
          setIconSize(QSize(nWH, nWH));
          QPixmap pixmap = FluIconUtils::getFluentIconPixmap(m_iconType, FluThemeUtils::getUtils()->getTheme());
          pixmap = pixmap.scaled(nWH, nWH, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
          setIcon(QIcon(pixmap));
      }

      void mousePressEvent(QMouseEvent* e)
      {
          if (m_bPressed == true)
              return;

          m_bPressed = true;
          m_timer->start();
      }

      void mouseReleaseEvent(QMouseEvent* e)
      {
          m_bPressed = false;
          m_timer->stop();
          m_timer->start();
      }

   public slots:
      void onThemeChanged()
      {
          if (FluThemeUtils::isLightTheme())
          {
              FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluScaleButton.qss", this);
          }
          else
          {
              FluStyleSheetUitls::setQssByFileName("../StyleSheet/dark/FluScaleButton.qss", this);
          }
      }
  protected:
      
      FluAwesomeType m_iconType;
      QTimer* m_timer;
      float m_currentPercentage;
      bool m_bToBig;
      bool m_bPressed;
};
