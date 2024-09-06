#pragma once

#include <QPushButton>
#include <QPainter>
#include <QEvent>

#include "../FluUtils/FluUtils.h"

class FluPPushButton : public QPushButton
{
    Q_OBJECT
  public:
    FluPPushButton(QWidget* parent = nullptr);

    void updateColor();

    void updateColorNormal();

    void updateColorHover();

    void updateColorPressed();

    QColor getBackgroundColor();

    void setBackgroundColor(QColor color);

    QColor getBorderColor();

    void setBorderColor(QColor color);

    void setBottomBorderColor(QColor color);

    QColor getTextColor();

    void setTextColor(QColor color);

    void paintEvent(QPaintEvent* event);

  protected:
    bool eventFilter(QObject* watched, QEvent* event) override;

  protected:
    QColor m_backgroundColor;
    QColor m_borderColor;
    QColor m_textColor;
    QColor m_bottomBorderColor;

    FluMouseState m_mouseState;
};
