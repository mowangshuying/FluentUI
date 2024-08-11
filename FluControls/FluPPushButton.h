#pragma once

#include <QPushButton>
#include <QPainter>
#include <QEvent>

#include "../FluUtils/FluUtils.h"

class FluPPushButton : public QPushButton
{
    Q_OBJECT
  public:
    FluPPushButton(QWidget* parent = nullptr) : QPushButton(parent), m_mouseState(FluMouseState::Normal)
      {
          setMouseTracking(true);
          setFixedHeight(30);

          //updateColorNormal();
          updateColor();
          installEventFilter(this);

          connect(FluThemeUtils::getUtils(), &FluThemeUtils::themeChanged, [=]() { 
              updateColor();
          });
      }

    void updateColor()
    {
        updateColorNormal();
        updateColorHover();
        updateColorPressed();
        update();
      }

      void updateColorNormal()
      {
          if (m_mouseState != FluMouseState::Normal)
              return;

          if (FluThemeUtils::isLightTheme())
          {
              setBackgroundColor(QColor(251, 251, 251));
              setBorderColor(QColor(229, 229, 229));
              setBottomBorderColor(QColor(204, 204, 204));
              setTextColor(Qt::black);
              return;
          }
          
          if (FluThemeUtils::isDarkTheme())
          {
              setBackgroundColor(QColor(45, 45, 45));
              setBorderColor(QColor(53, 53, 53));
              setBottomBorderColor(QColor(48, 48, 48));
              setTextColor(Qt::white);
              return;
          }
      }

      void updateColorHover()
      {
          if (m_mouseState != FluMouseState::Hover)
              return;

          if (FluThemeUtils::isLightTheme())
          {
              setBackgroundColor(QColor(246, 246, 246));
              setBorderColor(QColor(229, 229, 229));
              setBottomBorderColor(QColor(204, 204, 204));
              setTextColor(Qt::black);
              return;
          }

          if (FluThemeUtils::isDarkTheme())
          {
              setBackgroundColor(QColor(50, 50, 50));
              setBorderColor(QColor(53, 53, 53));
              setBottomBorderColor(QColor(48, 48, 48));
              setTextColor(Qt::white);
              return;
          }
      }

      void updateColorPressed()
      {
          if (m_mouseState != FluMouseState::Pressed)
          {
              return;
          }

          if (FluThemeUtils::isLightTheme())
          {
              setBackgroundColor(QColor(245, 245, 245));
              setBorderColor(QColor(229, 229, 229));
              setBottomBorderColor(QColor(229, 229, 229));
              setTextColor(Qt::black);
              return;
          }

          if (FluThemeUtils::isDarkTheme())
          {
              setBackgroundColor(QColor(39, 39, 39));
              setBorderColor(QColor(53, 53, 53));
              setBottomBorderColor(QColor(39, 39, 39));
              setTextColor(Qt::white);
              return;
          }
      }

      QColor getBackgroundColor()
      {
          return m_backgroundColor;
      }

      void setBackgroundColor(QColor color)
      {
          m_backgroundColor = color;
          update();
      }

      QColor getBorderColor()
      {
          return m_borderColor;
      }

      void setBorderColor(QColor color)
      {
          m_borderColor = color;
          update();
      }

      void setBottomBorderColor(QColor color)
      {
          m_bottomBorderColor = color;
          update();
      }

      QColor getTextColor()
      {
          return m_textColor;
          update();
      }

      void setTextColor(QColor color)
      {
           m_textColor = color;
          update();
      }

      void paintEvent(QPaintEvent* event)
      {
          QPainter painter(this);
          painter.setRenderHints(QPainter::SmoothPixmapTransform | QPainter::Antialiasing | QPainter::TextAntialiasing);
          

          QPen pen;
          pen.setWidth(1);
          pen.setColor(m_borderColor);
          painter.setPen(pen);
          painter.setBrush(QBrush(m_backgroundColor));
          QRect backgroundRect = rect();
          painter.drawRoundedRect(backgroundRect, 4, 4);

          pen.setWidth(1);
          pen.setColor(m_bottomBorderColor);
          painter.setPen(pen);
          painter.drawLine(QPoint(2, rect().height()), QPoint(rect().width() - 2, rect().height()));

          pen.setColor(m_textColor);
          painter.setPen(pen);
          painter.drawText(rect(), Qt::AlignCenter, text());
      }

  protected:
      bool eventFilter(QObject* watched, QEvent* event) override
      {   
          bool bFilter = QPushButton::eventFilter(watched, event);

          switch (event->type())
          {
          case QEvent::Enter:
              m_mouseState = FluMouseState::Hover;
              updateColor();
              break;
          case QEvent::Leave:
              m_mouseState = FluMouseState::Normal;
              updateColor();
              break;
          case QEvent::MouseButtonPress:
              m_mouseState = FluMouseState::Pressed;
              updateColor();
              break;
          case QEvent::MouseButtonRelease:
              m_mouseState = FluMouseState::Hover;
              updateColor();
              break;
          default:
              break;
          }

          return bFilter;
      }
  protected:
      QColor m_backgroundColor;
      QColor m_borderColor;
      QColor m_textColor;
      QColor m_bottomBorderColor;

      FluMouseState m_mouseState;
};
