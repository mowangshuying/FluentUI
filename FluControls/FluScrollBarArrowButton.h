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
    FluScrollBarArrowButton(FluScrollBarArrowButtonType type = FluScrollBarArrowButtonType::ArrowUp, QWidget* parent = nullptr);

    FluAwesomeType getIconTypeByArrowType(FluScrollBarArrowButtonType type);

    void paintEvent(QPaintEvent* event);

  protected:
    // FluScrollBarArrowButtonType m_arrowType;
    FluAwesomeType m_aweSomeType;
};
