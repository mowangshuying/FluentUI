#pragma once

#include <QObject>

// class FluScrollArea;
class QAbstractScrollArea;
class FluScrollBar;

class FluScrollDelegate : public QObject
{
    Q_OBJECT
  public:
    FluScrollDelegate(QAbstractScrollArea* scrollArea = nullptr);

    FluScrollBar* getVScrollBar();

    FluScrollBar* getHScrollBar();

    bool eventFilter(QObject* watched, QEvent* event);

  protected:
    QAbstractScrollArea* m_scrollArea;
    FluScrollBar* m_vScrollBar;
    FluScrollBar* m_hScrollBar;
};
