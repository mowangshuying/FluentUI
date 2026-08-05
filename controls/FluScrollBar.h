#pragma once

#include <QApplication>
#include <QWidget>
#include <QEvent>
#include <QWheelEvent>
#include "FluScrollBarTrunk.h"
// #include "FluScrollbarHandle.h"
#include <QResizeEvent>
#include "FluScrollBarArrowButton.h"
#include <QScrollBar>
#include <QAbstractScrollArea>
#include "FluWidget.h"
#include <QPropertyAnimation>
#include <QGraphicsOpacityEffect>
#include <QTimer>

class FluScrollArea;
class FluScrollBarHandle;

class FluScrollBar : public FluWidget
{
    Q_OBJECT
    Q_PROPERTY(int value READ getValue WRITE setValue)
    Q_PROPERTY(QColor trunkBackgroundColor READ getTrunkBackgroundColor WRITE setTrunkBackgroundColor)
    Q_PROPERTY(QColor handleBackgroundColor READ getHandleBackgroundColor WRITE setHandleBackgroundColor)
    Q_PROPERTY(QColor handleHoverColor READ getHandleHoverColor WRITE setHandleHoverColor)
  public:
    FluScrollBar(Qt::Orientation orientation, QAbstractScrollArea* scrollArea = nullptr);

    Qt::Orientation getOrientation();

    int getMaxValue();

    int getMinValue();

    void setRangeValue(int minValue, int maxValue);

    void scrollCurrentValue(int value);

    void scrollBy(int delta);

    void animateToValue(int targetValue, int duration = 200, QEasingCurve::Type curve = QEasingCurve::OutCubic);

    int getValue();

    void setValue(int value);

    int getPadding();

    void setPadding(int padding);

    int getPageStep();

    void setPageStep(int pageStep);

    int getTrunkLen();

    bool atTrunk(const QPoint& pos);

    int getSlideWayLen();

    void setHideScrollBar(bool isHideScrollBar);

    bool isHideScrollBar();

    void adjustScrollBarPosAndSize(QSize scrollAreaSize);

    QScrollBar* getOriginalScrollBar();

    void hideOriginalScrollBar();

    void adjustHandlePos();

    void adjustHandleSize();

    QColor getTrunkBackgroundColor();

    void setTrunkBackgroundColor(QColor color);

    QColor getHandleBackgroundColor();

    void setHandleBackgroundColor(QColor color);

    QColor getHandleHoverColor();

    void setHandleHoverColor(QColor color);

  public:
    bool eventFilter(QObject* watched, QEvent* event);

    void enterEvent(QEnterEvent* event);

    void leaveEvent(QEvent* event);

    void resizeEvent(QResizeEvent* event);

    void mouseMoveEvent(QMouseEvent* event);

    void mousePressEvent(QMouseEvent* event);

    void mouseReleaseEvent(QMouseEvent* event);

    void wheelEvent(QWheelEvent* event);
  signals:
    void valueRangeChanged(int minValue, int maxValue);
    void valueChanged(int value);
  public slots:
    void OnPageUp();

    void OnPageDown();

    // void onCurrentValueChanged(int value);

    void expand();

    void collapse();

    void onOpacityAnimationChanged(const QVariant& value);

    void onThemeChanged();

    void onTimerTimeout();

    void onAutoHideTimeout();

    void onContentScrolled();

    void fadeIn();

  protected:
    QAbstractScrollArea* m_scrollArea;
    FluScrollBarTrunk* m_scrollBarTrunk;
    FluScrollBarHandle* m_scrollBarHandle;

    QScrollBar* m_scrollBar;

    Qt::Orientation m_orientation;

    QTimer* m_timer;
    int m_pendingAction;  // 0=none, 1=expand, 2=collapse
    QPropertyAnimation* m_valueAnimation;

    int m_maxValue;
    int m_minValue;
    int m_value;

    int m_padding;

    int m_pageStep;

    bool m_isExpanded;
    bool m_isEnter;

    QPoint m_pressedPoint;
    bool m_isPressed;

    bool m_isHideScrollBar;

    // C. Auto-hide + fade
    QTimer* m_autoHideTimer;
    QPropertyAnimation* m_fadeAnimation;
    QGraphicsOpacityEffect* m_opaEffect;
    bool m_isFaded;

  protected:
    void setMaxValue(int value);

    void setMinValue(int value);
};
