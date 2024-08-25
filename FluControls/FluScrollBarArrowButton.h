#pragma once

#include <QPushButton>
#include <QPainter>
#include "../FluUtils/FluUtils.h"

enum class FluScrollBarArrowButtonType
{
    ArrowUp,
    ArrowDown,
    ArrowLeft,
    ArrowRight
};

class FluScrollBarArrowButton : public QPushButton
{
    Q_OBJECT
  public:
      FluScrollBarArrowButton(FluScrollBarArrowButtonType type = FluScrollBarArrowButtonType::ArrowUp, QWidget* paernt = nullptr)
      {
      }

      FluAwesomeType getIconTypeByArrowType(FluScrollBarArrowButtonType type)
      {
          switch (type)
          {
          case FluScrollBarArrowButtonType::ArrowUp:
              return FluAwesomeType::ChevronUp;
          case FluScrollBarArrowButtonType::ArrowDown:
              return FluAwesomeType::ChevronDown;
          case FluScrollBarArrowButtonType::ArrowLeft:
              return FluAwesomeType::ChevronLeft;
          case FluScrollBarArrowButtonType::ArrowRight:
              return FluAwesomeType::ChevronRight;
          default:
              return FluAwesomeType::ChevronUp;
          }

          return FluAwesomeType::ChevronUp;
      }

      void paintEvent(QPaintEvent* event)
      {
          QPainter painter(this);
          painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform | QPainter::TextAntialiasing);
          painter.drawPixmap(rect(), FluIconUtils::getFluentIconPixmap(getIconTypeByArrowType(m_arrowType)));

      }
  protected:
      FluScrollBarArrowButtonType m_arrowType;
};
