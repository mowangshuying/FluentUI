#pragma once

#include <QLineEdit>

#include "../FluControls/FluLineEdit.h"

class FluLineEditDemo : public QWidget
{
    Q_OBJECT
  public:
      FluLineEditDemo(QWidget* parent = nullptr) : QWidget(parent)
      {
          auto lineEdit = new FluLineEdit(this);
          lineEdit->setFixedSize(120, 30);
          lineEdit->move(50, 50);

          setStyleSheet("background-color:rgb(249, 249, 249)");
          resize(800, 600);
      }
};
