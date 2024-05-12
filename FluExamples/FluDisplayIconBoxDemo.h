#pragma once

#include "../FluControls/FluWidget.h"
#include "../FluControls/FluDisplayIconBox.h"

class FluDisplayIconBoxDemo : public FluWidget
{
    Q_OBJECT
  public:
    FluDisplayIconBoxDemo(QWidget* parent = nullptr) : FluWidget(parent)
    {
        setStyleSheet("background-color:rgb(243,243,243);");
        resize(600, 400);

        auto iconBox = new FluDisplayIconBox(FluAwesomeType::Wifi, this);
        iconBox->move(50, 50);
    }
};
