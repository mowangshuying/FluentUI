```cpp
auto targetBtn = new FluPushButton(tr("Click to Increment"), interactiveBox->getBodyWidget());
auto badge = FluInfoBadge::setInfoBadge(interactiveBox->getBodyWidget(), targetBtn, FluInfoBadgeLevel::Suc, 1);
connect(targetBtn, &FluPushButton::clicked, this, [=]() {
    badge->setValue(badge->getValue() + 1);
});
```