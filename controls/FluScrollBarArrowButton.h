#pragma once

#include <QPushButton>
#include <QPainter>
#include "../utils/FluUtils.h"

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
    Q_PROPERTY(QColor normalColor READ getNormalColor WRITE setNormalColor)
    Q_PROPERTY(QColor hoverColor READ getHoverColor WRITE setHoverColor)
    Q_PROPERTY(QColor boundaryColor READ getBoundaryColor WRITE setBoundaryColor)
  public:
    FluScrollBarArrowButton(FluScrollBarArrowButtonType type = FluScrollBarArrowButtonType::ArrowUp, QWidget* parent = nullptr);

    FluAwesomeType getIconTypeByArrowType(FluScrollBarArrowButtonType type);

    void setAtBoundary(bool atBoundary);
    bool isAtBoundary() const;

    QColor getNormalColor() const;
    void setNormalColor(QColor color);

    QColor getHoverColor() const;
    void setHoverColor(QColor color);

    QColor getBoundaryColor() const;
    void setBoundaryColor(QColor color);

    void paintEvent(QPaintEvent* event);

  protected:
    void enterEvent(QEnterEvent* event) override;
    void leaveEvent(QEvent* event) override;

  protected:
    FluAwesomeType m_aweSomeType;
    bool m_isHovered = false;
    bool m_isAtBoundary = false;
    QColor m_normalColor;
    QColor m_hoverColor;
    QColor m_boundaryColor;
};
