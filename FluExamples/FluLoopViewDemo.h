#pragma once

#include <QWidget>
#include "../FluControls/FluLoopView.h"

class FluLoopViewDemo : public QWidget
{
    Q_OBJECT
  public:
      FluLoopViewDemo(QWidget* parent = nullptr) : QWidget(parent)
      {
          auto loopView = new FluLoopView(this);
          loopView->move(50, 50);
          std::vector<QString> datas;
          for (int i = 0; i < 12; i++)
          {
              QString str = QString::asprintf("%02d", i);
              datas.push_back(str);
          }

          loopView->setAllItems(datas);

          resize(600, 400);
      }
};
