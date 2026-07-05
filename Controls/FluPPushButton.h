#pragma once

#include <QPushButton>
#include <QPainter>
#include <QEvent>

#include "../Utils/FluUtils.h"

class FluPPushButton : public QPushButton
{
    Q_OBJECT
    Q_PROPERTY(QColor ppBackgroundColor READ getBackgroundColor WRITE setBackgroundColor)
    Q_PROPERTY(QColor ppBorderColor READ getBorderColor WRITE setBorderColor)
    Q_PROPERTY(QColor ppBottomBorderColor READ getBottomBorderColor WRITE setBottomBorderColor)
    Q_PROPERTY(QColor ppTextColor READ getTextColor WRITE setTextColor)
  public:
    FluPPushButton(QWidget* parent = nullptr);

    QColor getBackgroundColor();

    void setBackgroundColor(QColor color);

    QColor getBorderColor();

    void setBorderColor(QColor color);

    QColor getBottomBorderColor();
    void setBottomBorderColor(QColor color);

    QColor getTextColor();

    void setTextColor(QColor color);

    void paintEvent(QPaintEvent* event);

  protected:
    bool eventFilter(QObject* watched, QEvent* event) override;
  public slots:
    void onThemeChanged();
  protected:
    QColor m_backgroundColor;
    QColor m_borderColor;
    QColor m_textColor;
    QColor m_bottomBorderColor;

    FluPPUtils::PPMouseState m_mouseState;
};
