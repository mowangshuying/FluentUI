#pragma once

#include "../FluUtils/FluUtils.h"
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
    QHBoxLayout* m_hMainLayout;
    QPushButton* m_hourBtn;
    QPushButton* m_minuteBtn;
    QPushButton* m_apBtn;

    FluTimePickerAPView* m_timerPickerApView;
};
