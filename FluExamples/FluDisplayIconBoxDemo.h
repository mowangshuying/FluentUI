#pragma once

#include <QWidget>
#include "../FluControls/FluDisplayIconBox.h"

class FluDisplayIconBoxDemo : public QWidget
{
    Q_OBJECT
  public:
    FluDisplayIconBoxDemo(QWidget* parent = nullptr) : QWidget(parent)
    {
        setStyleSheet("background-color:rgb(243,243,243);");
        resize(600, 400);

        auto iconBox = new FluDisplayIconBox(FluAwesomeType::Wifi, this);
        iconBox->move(50, 50);
    }
};
