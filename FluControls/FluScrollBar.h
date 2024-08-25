#pragma once

#include <QWidget>
class FluScrollArea;

class FluScrollBar : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(int value READ getValue WRITE setValue)
  public:
      FluScrollBar(Qt::Orientation orientation, FluScrollArea* scrollArea = nullptr);
};
