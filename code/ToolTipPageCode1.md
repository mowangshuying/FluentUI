```cpp
auto btn = new FluPushButton(tr("Hover me"), displayBox->getBodyWidget());
btn->move(50, 30);
FluToolTip::setToolTip(displayBox->getBodyWidget(), btn, "This is a tooltip.");
```
