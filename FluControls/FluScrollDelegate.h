#pragma once

#include <QObject>

class FluScrollArea;
class FluScrollBar;

class FluScrollDelegate : public QObject
{
    Q_OBJECT
  public:
      FluScrollDelegate(FluScrollArea* scrollArea = nullptr);
  protected:
    FluScrollArea* m_scrollArea;
    FluScrollBar* m_vScrollBar;
    FluScrollBar* m_hSrollBar;
};
