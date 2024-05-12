#pragma once

#include "../FluControls/FluWidget.h"

#include "../FluControls/FluVFlyout.h"
#include "../FluControls/FluPushButton.h"
#include "../FluControls/FluConfirmFlyout.h"

class FluFlyoutDemo : public FluWidget
{
    Q_OBJECT
  public:
    FluFlyoutDemo(QWidget* parent = nullptr)
    {
        auto btn = new FluPushButton(this);

        btn->setText("Empty cart");
        btn->move(200, 200);

        connect(btn, &FluPushButton::clicked, [=]() {
            auto flyout = new FluConfirmFlyout(btn, FluFlyoutPosition::Top);
            flyout->setTitle("Empty your cart?");
            flyout->setInfo("All item will be remove. Do your want to continue?");
            flyout->show();
        });

        resize(600, 400);
    }
};
