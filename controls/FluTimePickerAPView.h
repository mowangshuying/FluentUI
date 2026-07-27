#pragma once

#include "FluWidget.h"
#include "FluLoopView.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "../Utils/FluUtils.h"
#include <QPushButton>
#include <QPainter>
#include <QStyleOption>
#include "FluAmPmView.h"
#include "FluHSplitLine.h"
#include "FluVSplitLine.h"
#include "FluTimePickerViewMask.h"
#include <QFrame>
#include <QGraphicsDropShadowEffect>
#include <QApplication>
#include <QWheelEvent>

class FluTimePickerAPView : public FluWidget
{
    Q_OBJECT
    Q_PROPERTY(QColor maskBackgroundColorEx READ getMaskBackgroundColorEx WRITE setMaskBackgroundColorEx)
    Q_PROPERTY(QColor maskTextColorEx READ getMaskTextColorEx WRITE setMaskTextColorEx)
  public:
    FluTimePickerAPView(QWidget* parent = nullptr);

    void setMaskBackgroundColorEx(QColor color)
    {
        m_mask->setBackgroundColorEx(color);
    }
    QColor getMaskBackgroundColorEx()
    {
        return m_mask->getBackgroundColorEx();
    }

    void setMaskTextColorEx(QColor color)
    {
        m_mask->setTextColorEx(color);
    }
    QColor getMaskTextColorEx()
    {
        return m_mask->getTextColorEx();
    }

    int getHour();

    int getMinute();

    void setHour(int hour);

    void setMinute(int minute);

    bool isAm();

    void setAm(bool isAm);

    void updateTime();

    void setShadowEffect();

    void paintEvent(QPaintEvent* event);

    void showEvent(QShowEvent* event);

    void resizeEvent(QResizeEvent* event);
  signals:
    void clickedOk();
    void clickedCancel();
  public slots:
    void onThemeChanged();

  protected:
    QFrame* m_mainView;
    QHBoxLayout* m_mainViewLayout;
    QGraphicsDropShadowEffect* m_shadowEffect;

    QVBoxLayout* m_mainLayout;
    QHBoxLayout* m_viewLayout;
    QHBoxLayout* m_buttonLayout;

    FluTimePickerViewMask* m_mask;

    FluLoopView* m_hourView;
    FluLoopView* m_minuteView;
    FluAmPmView* m_ampmView;

    QPushButton* m_okButton;
    QPushButton* m_cancelButton;

    int m_hour;
    int m_minute;
    bool m_isAm;

    bool m_isFirstShow;
};
