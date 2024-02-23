#pragma once

#include <QCalendarWidget>
#include <QWidget>
#include "../FluUtils/FluUtils.h"
#include <QPainter>
#include <QStyleOption>
#include <QPushButton>
#include <QHBoxLayout>
#include "FluPushButton.h"
#include "FluIconButton.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QGridLayout>
#include <QScrollArea>
#include "FluCalendarData.h"
#include <QScrollBar>

class FluCalendarViewTitle : public QWidget
{
    Q_OBJECT
  public:
      FluCalendarViewTitle(QWidget* parent = nullptr) : QWidget(parent)
      {
          m_hMainLayout = new QHBoxLayout;
          setLayout(m_hMainLayout);

          m_yearMonthBtn = new FluPushButton;
          m_yearMonthBtn->setText("January 2000");
          m_hMainLayout->addWidget(m_yearMonthBtn);

          m_preBtn = new FluIconButton(FluAwesomeType::CaretSolidUp);
          m_nextBtn = new FluIconButton(FluAwesomeType::CaretSolidDown);

          m_hMainLayout->addWidget(m_preBtn);
          m_hMainLayout->addWidget(m_nextBtn);

          m_yearMonthBtn->setObjectName("yearMonthBtn");
          m_preBtn->setObjectName("preBtn");
          m_nextBtn->setObjectName("nextBtn");

          setFixedHeight(50);

          FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluCalendarViewTitle.qss", m_yearMonthBtn);
          FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluCalendarViewTitle.qss", m_preBtn);
          FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluCalendarViewTitle.qss", m_nextBtn);
          FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluCalendarViewTitle.qss", this);
      }

      void paintEvent(QPaintEvent* event)
      {
          QStyleOption opt;
          opt.initFrom(this);
          QPainter painter(this);
          style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
      }

  protected:
      FluPushButton* m_yearMonthBtn;
      FluIconButton* m_preBtn;
      FluIconButton* m_nextBtn;

      QHBoxLayout* m_hMainLayout;

      
};

class FluCalendarViewWeakTitle : public QWidget
{
    public:
      FluCalendarViewWeakTitle(QWidget* parent = nullptr) : QWidget(parent)
      {
          //QLabel* m_label = new QLabel("Su");
          m_hMainLayout = new QHBoxLayout;
          m_hMainLayout->setContentsMargins(10, 0, 10, 0);
          m_hMainLayout->setSpacing(0);
          setLayout(m_hMainLayout);

          QList<QString> weekTexts = {"Su", "Mo", "Tu", "We", "Th", "Fr", "Sa"};
          for (int i = 0; i < weekTexts.size(); i++)
          {
              QLabel* label = new QLabel;
              //label->setFixedWidth(40);
              label->setFixedSize(40, 40);
              label->setObjectName("label");
              label->setAlignment(Qt::AlignCenter);
              label->setText(weekTexts.at(i));

              m_hMainLayout->addWidget(label);
          }

          setFixedHeight(30);
          FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluCalendarViewWeakTitle.qss", this);
      }

      void paintEvent(QPaintEvent* event)
      {
          QStyleOption opt;
          opt.initFrom(this);
          QPainter painter(this);
          style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
      }

  protected:
      QHBoxLayout* m_hMainLayout;
};

class FluCalendarMonthView : public QWidget
{
    Q_OBJECT
 public:
     FluCalendarMonthView(QWidget* parent = nullptr) : QWidget(parent)
     {
          m_gMainLayout = new QGridLayout;
          m_gMainLayout->setContentsMargins(10, 0, 10, 0);
          m_gMainLayout->setSpacing(0);
          m_gMainLayout->setVerticalSpacing(5);
          setLayout(m_gMainLayout);

          for (int i = 0; i < 6; i++)
          {
              for (int j = 0; j < 7; j++)
              {
                  QLabel* label = new QLabel;
                  label->setObjectName("label");
                  label->setFixedSize(40, 40);
              //    label->setText(QString::asprintf("%d", i * 7 + j));
                  label->setAlignment(Qt::AlignCenter);
                  label->setProperty("today", false);

              //    if (i * 7 + j == 15)
              //        label->setProperty("today", true);

                  m_labelList.append(label);
                  m_gMainLayout->addWidget(label, i, j);
              }
          }

          //m_calendar.init();

          setFixedHeight(270);
          FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluCalendarMonthView.qss", this);
     }

     //void setLabelText(int nIndex, QString text)
    // {
    //      //m_gMainLayout->itemAt(nIndex);
    //      m_labelList.at(nIndex)->setText(text);
    // }

     QLabel* getLabel(int nIndex)
     {
          return m_labelList.at(nIndex);
     }

     //FluMonth getMonth(int nYear, int nMonth)
     //{
     //     return m_calendar.years[nYear].at(nMonth);
     //}

     void setDateByYearMonth(int nYear, int nMonth)
     {
          //QDate date = QDate::currentDate();
          if (nYear == 1924 && nMonth == 1)
          {
              QDate date(1924, 1, 1);
              int day = date.dayOfWeek();
              
              // get day
              for (int i = 0; i < 42; i++)
              {
                  int j = i + 2;
                  if (j >= 42)
                      break;

                  QString dayText = QString::asprintf("%d", date.day());
                  getLabel(j)->setText(dayText);

                  getLabel(j)->setProperty("curMonth", true);
                  if (date.month() != nMonth)
                  {
                      getLabel(j)->setProperty("curMonth", false);
                  }

                  date = date.addDays(1);
              }
          }
     }

   protected:
     QGridLayout* m_gMainLayout;
     QList<QLabel*> m_labelList;
     FluCalendar m_calendar;
};

//class FluCalendarMonthScrollView : public QScrollArea
//{
//    Q_OBJECT
//   public:
//       FluCalendarMonthScrollView(QWidget* parent = nullptr) : QScrollArea(parent)
//       {
//          setWidgetResizable(true);
//          setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
//          verticalScrollBar()->setSingleStep(10);
//          m_contextWidget = new QWidget(this);
//          setWidget(m_contextWidget);
//          m_vMainLayout = new QVBoxLayout(m_contextWidget);
//          m_vMainLayout->setContentsMargins(0, 0, 0, 0);
//          m_contextWidget->setObjectName("contextWidget");
//
//          FluCalendarD calendarD;
//          calendarD.init();
//
//          QList<FluDay> dayList;
//          for (int i = 0; i < calendarD.calendar.size(); i++)
//          {
//              FluYear year = calendarD.calendar.at(i);
//              for (int j = 0; j < year.size(); j++)
//              {
//                  FluMonth month = year.at(j);
//                  for (int k = 0; k < month.size(); k++)
//                  {
//                      dayList.append(month.at(k));
//                  }
//              }
//          }
//
//
//          
//       //   auto monthView = new FluCalendarMonthView;
//       //   m_vMainLayout->addWidget(monthView);
//
//          FluCalendarMonthView* monthView = nullptr;
//          for (int i = 0; i < dayList.size(); i++)
//          {
//              int j = i + 6;
//
//              if (j == 6 || j % 42 == 0)
//              {
//                  //if (i >= 42)
//                  //    break;
//
//                  monthView = new FluCalendarMonthView;
//                  m_vMainLayout->addWidget(monthView);
//              }
//
//              QString dayText = QString::asprintf("%d", dayList.at(i).day());
//              monthView->setLabelText(j % 42, dayText);
//          }
//
//
//          FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluCalendarMonthScrollView.qss", this);
//       }
//
//     protected:
//       QWidget* m_contextWidget;
//       QVBoxLayout* m_vMainLayout;
//};

class FluCalendarView : public QWidget
{
	Q_OBJECT
  public:
	  FluCalendarView(QWidget* parent = nullptr) : QWidget(parent)
	  {
           m_vMainLayout = new QVBoxLayout;
           m_vMainLayout->setContentsMargins(0, 0, 0, 0);
           m_vMainLayout->setSpacing(0);

           setLayout(m_vMainLayout);

           auto title = new FluCalendarViewTitle;
           m_vMainLayout->addWidget(title);

           auto weekTitle = new FluCalendarViewWeakTitle;
           m_vMainLayout->addWidget(weekTitle);
          // m_vMainLayout->addStretch();

            auto monthView = new FluCalendarMonthView;
            m_vMainLayout->addWidget(monthView);
            monthView->setDateByYearMonth(1924, 1);

           //auto monthScrollView = new FluCalendarMonthScrollView;
           //m_vMainLayout->addWidget(monthScrollView);

           setFixedSize(300, 360);
           FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluCalendarView.qss", this);
	  }

	  void paintEvent(QPaintEvent* event)
      {
           QStyleOption opt;
           opt.initFrom(this);
           QPainter painter(this);
           style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
      }

  protected:
      QVBoxLayout* m_vMainLayout;
};
