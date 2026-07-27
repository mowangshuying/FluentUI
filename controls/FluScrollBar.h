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

class FluScrollArea;
class FluScrollBarHandle;

class FluScrollBar : public FluWidget
{
    Q_OBJECT
    Q_PROPERTY(int value READ getValue WRITE setValue)
    Q_PROPERTY(QColor trunkBackgroundColor READ getTrunkBackgroundColor WRITE setTrunkBackgroundColor)
    Q_PROPERTY(QColor handleBackgroundColor READ getHandleBackgroundColor WRITE setHandleBackgroundColor)
  public:
    FluScrollBar(Qt::Orientation orientation, QAbstractScrollArea* scrollArea = nullptr);

    Qt::Orientation getOrientation();

    int getMaxValue();

    void setMaxValue(int value);

    int getMinValue();

    void setMinValue(int value);

    void setRangeValue(int minValue, int maxValue);

    int getCurrentValue();

    void setCurrentValue(int value);

    void scrollCurrentValue(int value);

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
    void currentValueChanged(int value);
  public slots:
    void OnPageUp();

    void OnPageDown();

    // void onCurrentValueChanged(int value);

    void expand();

    void collapse();

    void onOpacityAnimationChanged(const QVariant& value);

    void onThemeChanged();

  protected:
    QAbstractScrollArea* m_scrollArea;
    FluScrollBarTrunk* m_scrollBarTrunk;
    FluScrollBarHandle* m_scrollBarHandle;

    QScrollBar* m_scrollBar;

    Qt::Orientation m_orientation;

    QTimer* m_timer;
    QPropertyAnimation* m_valueAnimation;

    int m_maxValue;
    int m_minValue;
    int m_currentValue;
    int m_value;  // use for animation; update current value;

    int m_padding;

    int m_pageStep;

    bool m_isExpanded;
    bool m_isEnter;

    QPoint m_pressedPoint;
    bool m_isPressed;

    bool m_isHideScrollBar;
};
