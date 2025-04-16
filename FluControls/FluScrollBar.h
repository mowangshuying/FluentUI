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

class FluScrollArea;
class FluScrollBarHandle;

class FluScrollBar : public FluWidget
{
    Q_OBJECT
    Q_PROPERTY(int value READ getCurrentValue WRITE setCurrrentValue)
    Q_PROPERTY(QColor trunkBackgroundColor READ getTrunkBackgoundColor WRITE setTrunkBackgoundColor)
    Q_PROPERTY(QColor handleBackgroundColor READ getHandleBackgroundColor WRITE setHandleBackgroundColor)
  public:
    FluScrollBar(Qt::Orientation orientation, QAbstractScrollArea* scrollArea = nullptr);

    Qt::Orientation getOrientation();

    int getMaxValue();

    void setMaxValue(int nValue);

    int getMinValue();

    void setMinValue(int nValue);

    void setRangeValue(int nMinValue, int nMaxValue);

    int getCurrentValue();

    void setCurrrentValue(int nValue);

    void scrollCurrentValue(int nValue);

    int getPadding();

    void setPadding(int nPadding);

    int getPageStep();

    void setPageStep(int nPageStep);

    int getTrunkLen();

    bool atTrunk(const QPoint& pos);

    int getSlideWayLen();

    void setHideScrollBar(bool bHideScrollBar);

    bool isHideScrollBar();

    void adjustScrollBarPosAndSize(QSize scrollAreaSize);

    QScrollBar* getOriginalScrollBar();

    void hideOriginalScrollBar();

    void adjustHandlePos();

    void adjustHandleSize();

    QColor getTrunkBackgoundColor();

    void setTrunkBackgoundColor(QColor color);

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
    void valueRangeChanged(int nMinValue, int nMaxValue);
    void currentValueChanged(int nValue);
  public slots:
    void OnPageUp();

    void OnPageDown();

    void onCurrentValueChanged(int nValue);

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

    int m_nMaxValue;
    int m_nMinValue;
    int m_nCurrentValue;

    int m_nPadding;

    int m_nPageStep;

    bool m_bExpanded;
    bool m_bEnter;

    QPoint m_pressedPoint;
    bool m_bPressed;

    bool m_bHideScrollBar;
};
