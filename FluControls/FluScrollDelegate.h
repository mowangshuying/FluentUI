#pragma once

#include <QObject>

class FluScrollArea;
class FluScrollBar;

class FluScrollDelegate : public QObject
{
    Q_OBJECT
  public:
      FluScrollDelegate(FluScrollArea* scrollArea = nullptr);

      FluScrollBar* getVScrollBar()
      {
          return m_vScrollBar;
      }

      FluScrollBar* getHScrollBar()
      {
          return m_hScrollBar;
      }

      bool eventFilter(QObject* watched, QEvent* event);
  protected:
    FluScrollArea* m_scrollArea;
    FluScrollBar* m_vScrollBar;
    FluScrollBar* m_hScrollBar;
};
