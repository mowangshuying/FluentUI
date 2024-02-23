#pragma once

#include <QDateTime>
#include <QObject>
#include <QThread>
#include "../FluUtils/FluUtils.h"


using FluDay = QDate;
using FluMonth = QList<FluDay>;
using FluYear = QList<FluMonth>;
using FluCalendar = QList<FluYear>;

class FluCalendarD
{
  public:
      void init()
      {
          int nLastYear = -1;
          int nLastMonth = -1;
          
          FluMonth month;
          FluYear year;

          FluDay day(1924, 1, 1);

          nLastMonth = 1;
          nLastYear = 1924;

          month.append(day);

          for (int i = 0; ; i++)
          {
              QThread::msleep(100);
              day = day.addDays(1);
              if (day.year() == 2125)
                  break;

              if (day.month() != nLastMonth)
              {
                  nLastMonth = day.month();
                  year.append(month);

                //  LOG_DEBUG << "======================append mouth======================";
                //  LOG_DEBUG << month;
               //   LOG_DEBUG << "======================end======================";

                  month.clear();
                  month.append(day);
              }
              else
              {
                //  LOG_DEBUG << "append day:" << day;
                  month.append(day);
              }

              if (day.year() != nLastYear)
              {
                  nLastYear = day.year();
                  calendar.append(year);

                //  LOG_DEBUG << "======================append year======================";
                //  LOG_DEBUG << year;
               //   LOG_DEBUG << "======================end======================";

                  year.clear();
              }
            //  else
            //  {
                  // year.append(month);
            //  }
          }
      }
  public:
      FluCalendar calendar;
};