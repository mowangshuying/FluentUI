#pragma once

#include <QSlider>
#include <QEvent>
#include <QPropertyAnimation>

#include "../utils/FluUtils.h"

class QLabel;

class FluSlider : public QSlider
{
    Q_OBJECT
    Q_PROPERTY(qreal handleScale READ handleScale WRITE setHandleScale)
    Q_PROPERTY(int animValue READ animValue WRITE setAnimValue)
  public:
    FluSlider(QWidget* parent = nullptr);
    FluSlider(Qt::Orientation orientation, QWidget* parent = nullptr);
    ~FluSlider() override;

    void setTooltipEnabled(bool enable);
    bool isTooltipEnabled() const;

    void setTickMarkEnabled(bool enable);
    bool isTickMarkEnabled() const;
    void setTickMarkInterval(int interval);
    int getTickMarkInterval() const;

    qreal handleScale() const;
    void setHandleScale(qreal scale);

    void setReadOnly(bool readOnly);
    bool isReadOnly() const;

    int animValue() const;
    void setAnimValue(int v);

  protected:
    void paintEvent(QPaintEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void keyPressEvent(QKeyEvent* event) override;
    void enterEvent(QEnterEvent* event) override;
    void leaveEvent(QEvent* event) override;
    void onThemeChanged();

  private:
    void showValueTooltip();
    void hideValueTooltip();
    void updateTooltipStyle();
    void animateHandleTo(qreal target);
    void animateToValue(int target);

  private:
    // Tooltip state
    bool m_tooltipEnabled = true;
    bool m_dragging = false;
    int m_lastValue = -1;
    QLabel* m_valueTooltip = nullptr;

    // Tick mark state
    bool m_tickMarkEnabled = false;
    int m_tickMarkInterval = 10;

    // Handle animation state
    qreal m_handleScale = 1.0;
    QPropertyAnimation* m_scaleAnim = nullptr;
    bool m_hovered = false;
    bool m_pressed = false;

    // Read-only state
    bool m_readOnly = false;

    // Value jump animation state
    QPropertyAnimation* m_valueAnim = nullptr;
    int m_animValue = 0;
    bool m_animatingValue = false;

    // Click vs drag distinction
    QPoint m_pressMousePos;                    // Mouse position when pressed
    int m_pressValue = 0;                      // Value when pressed
    bool m_isClickOnly = false;                // True if press without significant movement
    static constexpr int kClickThreshold = 4;  // Pixel threshold to distinguish click vs drag
};
