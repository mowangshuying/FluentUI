#pragma once

#include "FluWidget.h"
#include <QHBoxLayout>
#include <QPushButton>
#include <QPainter>
#include <QStyleOption>

#include "../FluUtils/FluUtils.h"
#include "FluCalendarDatePicker.h"
#include "FluCalendarView.h"

class FluCalendarDatePicker : public QPushButton
{
    Q_OBJECT
  public:
    FluCalendarDatePicker(QWidget* parent = nullptr);

    QDate getCurDate();

    void setCurDate(QDate date);

  signals:
    void selectedDate(QDate date);

  public slots:
    void onClicked();

    void onThemeChanged();

  protected:
    QHBoxLayout* m_hMainLayout;
    QPushButton* m_textButton;
    QPushButton* m_iconButton;

    FluCalendarView* m_calendarView;
};
