```cpp
auto btn = new FluPushButton(tr("Top"), displayBox->getBodyWidget());
btn->move(50, 20);
// 4th argument: placement (default is Bottom)
FluToolTip::setToolTip(displayBox->getBodyWidget(), btn, "Placement: Top", FluToolTip::Placement::Top);
// or change it later at runtime
// toolTip->setPlacement(FluToolTip::Placement::Left);
```
