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
#include <QStackedLayout>

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

      FluPushButton* getYearMonthBtn()
      {
          return m_yearMonthBtn;
      }

      FluIconButton* getNextBtn()
      {
          return m_nextBtn;
      }

      FluIconButton* getPreBtn()
      {
          return m_preBtn;
      }

      void setYearMonth(int nYear, int nMonth)
      {
          const QList<QString> monthTexts = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
          QString yearMonthText = QString::asprintf("%s %d", monthTexts.at(nMonth - 1).toStdString().data(), nYear);
          m_yearMonthBtn->setText(yearMonthText);
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
          //m_curMonth = QDate(nYear, nMonth, 1);

          QDate today = QDate::currentDate();
          if (nYear < 1924 || nYear > 2124)
              return;

          if (nMonth < 0 || nMonth > 12)
              return;

          if (nYear == 1924 && nMonth == 1)
          {
              QDate date(1924, 1, 1);
              int day = date.dayOfWeek();
              
              // get day
              for (int i = 0; i < 42; i++)
              {
                  int j = i + day;
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

              return;
          }

          if (nYear == 2024 && nMonth == 12)
          {
              return;
          }

          //QDate date(1900, 12, 24);
          
          QDate date(nYear, nMonth, 1);
          int day = date.dayOfWeek();

          for (int i = day; i > 0; i--)
          {
              date = date.addDays(-1);
              QString dayText = QString::asprintf("%d", date.day());
              getLabel(i-1)->setText(dayText);
              getLabel(i-1)->setProperty("curMonth", false);
          }

          date = QDate(nYear, nMonth, 1);
          for (int i = 0; i < 42; i++)
          {
              int j = i + day;
              if (j >= 42)
                  break;

              QString dayText = QString::asprintf("%d", date.day());
              getLabel(j)->setText(dayText);

              getLabel(j)->setProperty("curMonth", true);
              if (date.month() != nMonth)
              {
                  getLabel(j)->setProperty("curMonth", false);
              }

              if (date == today)
              {
                  getLabel(j)->setProperty("today", true);
              }

              date = date.addDays(1);
          }
     }

     void setCurMonth(int nYear, int nMonth)
     {
          m_curMonth = QDate(nYear, nMonth, 1);
     }

     QDate getCurMonth()
     {
          return m_curMonth;
     }

     void setCurMonth(QDate curMonth)
     {
          LOG_DEBUG << "setCurMonth:" << curMonth;
          m_curMonth = curMonth;
          emit curMonthChanged();
     }

     QDate getNextMonth()
     {
          return m_curMonth.addMonths(1);
     }

     QDate getPreMonth()
     {
          return m_curMonth.addMonths(-1);
     }
   
   signals:
     void curMonthChanged();
   protected:
     QGridLayout* m_gMainLayout;
     QList<QLabel*> m_labelList;
     FluCalendar m_calendar;
     
     QDate m_curMonth;
};

class FluCalendarSelectDayView : public QWidget
{
    Q_OBJECT
   public:
       FluCalendarSelectDayView(QWidget* parent = nullptr) : QWidget(parent)
       {
          m_vMainLayout = new QVBoxLayout;
          m_vMainLayout->setContentsMargins(0, 0, 0, 0);
          m_vMainLayout->setSpacing(0);
          setLayout(m_vMainLayout);

           auto weekTitle = new FluCalendarViewWeakTitle;
           m_vMainLayout->addWidget(weekTitle);
           //m_vMainLayout->addStretch();

           auto monthView = new FluCalendarMonthView;
           m_vMainLayout->addWidget(monthView);
          
           QDate curDate = QDate::currentDate();
           monthView->setDateByYearMonth(curDate.year(), curDate.month());
           monthView->setCurMonth(curDate.year(), curDate.month());
           //title->setYearMonth(curDate.year(), curDate.month());

          //setFixedHeight(270);
       }

  public:
       QVBoxLayout* m_vMainLayout;
};

class FluCalendarSelectMonthView : public QWidget
{
   public:
       FluCalendarSelectMonthView(QWidget* parent = nullptr) : QWidget(parent)
       {
          m_gMainLayout = new QGridLayout;
          m_gMainLayout->setContentsMargins(10, 0, 10, 0);
          m_gMainLayout->setSpacing(0);
          m_gMainLayout->setVerticalSpacing(5);
          setLayout(m_gMainLayout);

          QList<QString> monthTexts = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
          for (int i = 0; i < 4; i++)
          {
              for (int j = 0; j < 4; j++)
              {
                  QLabel* label = new QLabel;
                  label->setObjectName("label");
                  label->setFixedSize(50, 50);

                  label->setText(monthTexts.at((i*4 + j) % 12));
                  label->setAlignment(Qt::AlignCenter);
                  label->setProperty("today", false);

                  m_labelList.append(label);
                  m_gMainLayout->addWidget(label, i, j);
              }
          }

          setFixedHeight(300);
          FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluCalendarSelectMonthView.qss", this);
       }
  protected:
       QGridLayout* m_gMainLayout;
       QList<QLabel*> m_labelList;
       QDate m_curYear;
};

class FluCalendarSelectYearView : public QWidget
{
   public:
    FluCalendarSelectYearView(QWidget* parent = nullptr) : QWidget(parent)
    {
          m_gMainLayout = new QGridLayout;
          m_gMainLayout->setContentsMargins(10, 0, 10, 0);
          m_gMainLayout->setSpacing(0);
          m_gMainLayout->setVerticalSpacing(5);
          setLayout(m_gMainLayout);
           
          for (int i = 0; i < 4; i++)
          {
              for (int j = 0; j < 4; j++)
              {
                  QLabel* label = new QLabel;
                  label->setObjectName("label");
                  label->setFixedSize(50, 50);
                  
                  label->setText(QString::asprintf("%d", i * 4 + j + 1));
                  label->setAlignment(Qt::AlignCenter);
                  label->setProperty("today", false);

                  //    if (i * 7 + j == 15)
                  //        label->setProperty("today", true);

                  m_labelList.append(label);
                  m_gMainLayout->addWidget(label, i, j);
              }
          }

          setFixedHeight(300);
          FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluCalendarSelectYearView.qss", this);
    }

   
   protected:
     QGridLayout* m_gMainLayout;
     QList<QLabel*> m_labelList;
     QDate m_curYear;
};

enum FluCalendarViewState
{
    FluCVS_SelectDayView,
    FluCVS_SelectMonthView,
    FluCVS_SelectYearView,
};

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


           m_sLayout = new QStackedLayout;
           m_vMainLayout->addLayout(m_sLayout);

          //auto weekTitle = new FluCalendarViewWeakTitle;
          // m_vMainLayout->addWidget(weekTitle);
          // m_vMainLayout->addStretch();

           // auto monthView = new FluCalendarMonthView;
           // m_vMainLayout->addWidget(monthView);
           // 
           // QDate curDate = QDate::currentDate();
           // monthView->setDateByYearMonth(curDate.year(), curDate.month());
           // monthView->setCurMonth(curDate.year(), curDate.month());
           // title->setYearMonth(curDate.year(), curDate.month());

           //setFixedSize(300, 360);

           //connect(title->getNextBtn(), &FluIconButton::clicked, [=](bool bClicked){
           //    QDate nextMonth = monthView->getNextMonth();
           //    monthView->setDateByYearMonth(nextMonth.year(), nextMonth.month());
           //    monthView->setCurMonth(nextMonth);
           //    });

           //connect(title->getPreBtn(), &FluIconButton::clicked, [=](bool bClicked) {
           //    QDate preMonth = monthView->getPreMonth();
           //    monthView->setDateByYearMonth(preMonth.year(), preMonth.month());
           //    monthView->setCurMonth(preMonth);
           //});

           //connect(monthView, &FluCalendarMonthView::curMonthChanged, [=]() { 
           //    QDate curMonth = monthView->getCurMonth();
           //    title->setYearMonth(curMonth.year(), curMonth.month());
           //    });

           m_selectDayView = new FluCalendarSelectDayView(this);
           m_sLayout->addWidget(m_selectDayView);

           m_selectMonthView = new FluCalendarSelectMonthView(this);
           m_sLayout->addWidget(m_selectMonthView);

           m_selectYearView = new FluCalendarSelectYearView(this);
           m_sLayout->addWidget(m_selectYearView);

           m_viewState = FluCVS_SelectDayView;
           connect(title->getYearMonthBtn(), &FluPushButton::clicked, [=](bool bClicked) { 
               switch (m_viewState)
               {
                   case FluCVS_SelectDayView:
                       switchSelectMonthView();
                       m_viewState = FluCVS_SelectMonthView;
                       break;
                   case FluCVS_SelectMonthView:
                       switchSelectYearView();
                       m_viewState = FluCVS_SelectYearView;
                       break;
                   case FluCVS_SelectYearView:
                       break;
                   default:
                       break;
               }
               });
           FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluCalendarView.qss", this);
	  }

      void switchSelectViewState(FluCalendarViewState state)
      {
           switch (state)
           {
              case FluCVS_SelectDayView:
                  switchSelectDayView();
                  break;
              case FluCVS_SelectMonthView:
                  switchSelectMonthView();
                  break;
              case FluCVS_SelectYearView:
                  switchSelectYearView();
                  break;
              default:
                  break;
           }
      }

      void switchSelectDayView()
      {
           m_sLayout->setCurrentWidget(m_selectDayView);
      }

      void switchSelectMonthView()
      {
           m_sLayout->setCurrentWidget(m_selectMonthView);
      }

      void switchSelectYearView()
      {
           m_sLayout->setCurrentWidget(m_selectYearView);
      }

	  void paintEvent(QPaintEvent* event)
      {
           QStyleOption opt;
           opt.initFrom(this);
           QPainter painter(this);
           style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
      }

  protected:
      QDate m_curDate;
      FluCalendarViewState m_viewState;

      QVBoxLayout* m_vMainLayout;
      QStackedLayout* m_sLayout;

      FluCalendarSelectDayView *m_selectDayView;
      FluCalendarSelectMonthView* m_selectMonthView;
      FluCalendarSelectYearView* m_selectYearView;
};
