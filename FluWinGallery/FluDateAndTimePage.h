#pragma once

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QStyleOption>
#include <QPainter>

#include "FluATitlePage.h"
#include "../FluControls/FluFWScrollView.h"
#include "../FluUtils/FluUtils.h"
#include "../FluControls/FluHCard.h"

class FluDateAndTimePage : public FluATitlePage
{
    Q_OBJECT
  public:
      FluDateAndTimePage(QWidget* parent = nullptr) : FluATitlePage(parent)
      {
          m_vMainLayout->setContentsMargins(35, 35, 0, 35);
          m_titleLabel->setText("Date & Time");

          auto calendarDatePickerCard = new FluHCard(QPixmap("../res/ControlImages/CalendarDatePicker.png"), "CalendarDatePicker", "A control that lets users pick a date value using a calendar.");
          getFWScrollView()->getMainLayout()->addWidget(calendarDatePickerCard);

          auto calendarView = new FluHCard(QPixmap("../res/ControlImages/CalendarView.png"), "CalendarView", "A control that presents aa calendar for a user to choose a date from.");
          getFWScrollView()->getMainLayout()->addWidget(calendarView);

          auto datePickerCard = new FluHCard(QPixmap("../res/ControlImages/DatePicker.png"), "DatePicker", "A control that lets a user pick a date value.");
          getFWScrollView()->getMainLayout()->addWidget(datePickerCard);

          auto timePickerCard = new FluHCard(QPixmap("../res/ControlImages/TimePicker.png"), "TimePicker", "A configurable control that lets a user pick a time value.");
          getFWScrollView()->getMainLayout()->addWidget(timePickerCard);

          FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluDateAndTimePage.qss", this);
          connect(FluThemeUtils::getUtils(), &FluThemeUtils::themeChanged, [=](FluTheme theme) { onThemeChanged(); });
      }

       public slots:
      void onThemeChanged()
      {
          if (FluThemeUtils::getUtils()->getTheme() == FluTheme::Light)
          {
              FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluDateAndTimePage.qss", this);
          }
          else
          {
              FluStyleSheetUitls::setQssByFileName("../StyleSheet/dark/FluDateAndTimePage.qss", this);
          }
      }
};
