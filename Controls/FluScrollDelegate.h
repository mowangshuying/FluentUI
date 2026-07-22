#pragma once

#include <QObject>

class QAbstractScrollArea;
class FluScrollBar;

class FluScrollDelegate : public QObject
{
    Q_OBJECT
  public:
    FluScrollDelegate(QAbstractScrollArea* scrollArea = nullptr);

    FluScrollBar* getVerticalScrollBar();

    FluScrollBar* getHorizontalScrollBar();

    bool eventFilter(QObject* watched, QEvent* event);

  protected:
    QAbstractScrollArea* m_scrollArea;
    FluScrollBar* m_verticalScrollBar;
    FluScrollBar* m_horizontalScrollBar;
};
