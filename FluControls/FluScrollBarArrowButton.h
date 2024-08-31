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
    FluScrollBarArrowButton(FluScrollBarArrowButtonType type = FluScrollBarArrowButtonType::ArrowUp, QWidget* parent = nullptr) : QPushButton(parent)
    {
        m_aweSomeType = getIconTypeByArrowType(type);
        setFixedSize(12, 12);
    }

    FluAwesomeType getIconTypeByArrowType(FluScrollBarArrowButtonType type)
    {
        switch (type)
        {
            case FluScrollBarArrowButtonType::ArrowUp:
                return FluAwesomeType::CaretSolidUp;
            case FluScrollBarArrowButtonType::ArrowDown:
                return FluAwesomeType::CaretSolidDown;
            case FluScrollBarArrowButtonType::ArrowLeft:
                return FluAwesomeType::CaretSolidLeft;
            case FluScrollBarArrowButtonType::ArrowRight:
                return FluAwesomeType::CaretSolidRight;
            default:
                return FluAwesomeType::CaretSolidUp;
        }

        return FluAwesomeType::CaretSolidUp;
    }

    void paintEvent(QPaintEvent* event)
    {
        QPainter painter(this);
        painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform | QPainter::TextAntialiasing);
        painter.drawPixmap(rect(), FluIconUtils::getFluentIconPixmap(m_aweSomeType, FluThemeUtils::getUtils()->getTheme()));
    }

  protected:
    // FluScrollBarArrowButtonType m_arrowType;
    FluAwesomeType m_aweSomeType;
};
