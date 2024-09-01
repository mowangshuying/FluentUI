#pragma once

#include "FluWidget.h"
#include <QPushButton>
#include "FluWidget.h"
#include <QHBoxLayout>
#include <QVBoxLayout>

#include <QStyleOption>
#include <QPainter>

#include "FluDatePickerView.h"

class FluDatePicker : public FluWidget
{
    Q_OBJECT
  public:
    FluDatePicker(QWidget* parent = nullptr);

    void mouseReleaseEvent(QMouseEvent* event);

    void paintEvent(QPaintEvent* event);
  signals:
    void clicked();
  public slots:
    void onThemeChanged();

  protected:
    QHBoxLayout* m_hMainLayout;
    QPushButton* m_monthBtn;
    QPushButton* m_dayBtn;
    QPushButton* m_yearBtn;

    FluDatePickerView* m_datePickerView;
};
