```cpp
auto btn = new FluPushButton(tr("Hover for details"), displayBox->getBodyWidget());
btn->move(50, 30);
FluToolTip::setToolTip(displayBox->getBodyWidget(), btn,
                       "This tooltip spans multiple lines\n"
                       "to show how longer descriptions\n"
                       "are displayed gracefully.");
```
