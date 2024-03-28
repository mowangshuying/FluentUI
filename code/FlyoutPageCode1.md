```cpp
auto emptyCartBtn = new FluPushButton;
emptyCartBtn->setText("Empty cart");

connect(emptyCartBtn, &FluPushButton::clicked, this, [=]() { 
    auto flyout = new FluConfirmFlyout(emptyCartBtn, FluFlyoutPosition::Top);
    flyout->setTitle("Empty your cart?");
    flyout->setInfo("All item will be remove. Do your want to continue?");
    flyout->show();
});
```

