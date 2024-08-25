#pragma once

#include <QScrollArea>

class FluScrollArea : public QScrollArea
{
    Q_OBJECT
  public:
      FluScrollArea(QWidget* parent = nullptr) : QScrollArea(parent)
      {

    }
};
