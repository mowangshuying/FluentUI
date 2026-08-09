```cpp
auto btn2 = new FluToggleButton;
btn2->setText(tr("Checked"));
btn2->setToggled(true);

auto btn3 = new FluToggleButton;
btn3->setText(tr("Disabled"));
btn3->setEnabled(false);

// Listen for state changes
auto stateLabel = new QLabel;
connect(btn2, &FluToggleButton::toggledChanged, this, [=](bool isToggled) {
    stateLabel->setText(isToggled ? tr("State: Checked") : tr("State: Unchecked"));
});
```