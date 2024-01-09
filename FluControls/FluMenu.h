#pragma once

#include <QMenu>

class FluMenu : public QMenu
{
    Q_OBJECT
  public:
      
      FluMenu(QWidget* parent = nullptr);

      void paintEvent(QPaintEvent* event);
};
