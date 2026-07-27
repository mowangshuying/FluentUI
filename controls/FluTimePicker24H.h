#pragma once

#include "../Utils/FluUtils.h"
#include <QPushButton>
#include "FluWidget.h"
#include <QHBoxLayout>
#include <QVBoxLayout>

#include <QStyleOption>
#include <QPainter>

#include "FluTimePicker24HView.h"

class FluTimePicker24H : public FluWidget
{
    Q_OBJECT
  public:
    FluTimePicker24H(QWidget* parent = nullptr);

    void mouseReleaseEvent(QMouseEvent* event);

    void paintEvent(QPaintEvent* event);
  signals:
    void clicked();
  public slots:
    void onThemeChanged();

  protected:
    QHBoxLayout* m_mainLayout;
    QPushButton* m_hourButton;
    QPushButton* m_minuteButton;

    FluTimePicker24HView* m_timerPicker24HView;
};
