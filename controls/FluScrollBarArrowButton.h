#pragma once

#include <QPushButton>
#include <QPainter>
#include "../Utils/FluUtils.h"

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
    FluScrollBarArrowButton(FluScrollBarArrowButtonType type = FluScrollBarArrowButtonType::ArrowUp, QWidget* parent = nullptr);

    FluAwesomeType getIconTypeByArrowType(FluScrollBarArrowButtonType type);

    void paintEvent(QPaintEvent* event);

  protected:
    FluAwesomeType m_aweSomeType;
};
