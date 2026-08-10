```cpp
auto infoBtn = new FluPushButton;
auto sucBtn = new FluPushButton;
auto warnBtn = new FluPushButton;
auto errorBtn = new FluPushButton;

infoBtn->setText("Informational");
sucBtn->setText("Success");
warnBtn->setText("Warning");
errorBtn->setText("Error");

infoBtn->setFixedWidth(120);
sucBtn->setFixedWidth(120);
warnBtn->setFixedWidth(120);
errorBtn->setFixedWidth(120);

connect(infoBtn, &FluPushButton::clicked, [=]() {
    FluInfoBarMgr::showInfoBar(window(), FluInfoBarSeverity::Informational, "This is an informational message.");
});

connect(sucBtn, &FluPushButton::clicked, [=]() {
    FluInfoBarMgr::showInfoBar(window(), FluInfoBarSeverity::Success, "This is an success message.");
});

connect(warnBtn, &FluPushButton::clicked, [=]() {
    FluInfoBarMgr::showInfoBar(window(), FluInfoBarSeverity::Warning, "This is an warn message.");
});

connect(errorBtn, &FluPushButton::clicked, [=]() {
    FluInfoBarMgr::showInfoBar(window(), FluInfoBarSeverity::Error, "This is an error message.");
});

```