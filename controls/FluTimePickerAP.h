#pragma once

#include "../Utils/FluUtils.h"
#include <QPushButton>
#include "FluWidget.h"
#include <QHBoxLayout>
#include <QVBoxLayout>

#include <QStyleOption>
#include <QPainter>

#include "FluTimePickerAPView.h"

class FluTimePickerAP : public FluWidget
{
    Q_OBJECT
  public:
    FluTimePickerAP(QWidget* parent = nullptr);

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
    QPushButton* m_apButton;

    FluTimePickerAPView* m_timerPickerApView;
};
