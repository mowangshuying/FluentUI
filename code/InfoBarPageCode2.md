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
      FluShortInfoBar* sInfoBar = new FluShortInfoBar(FluShortInfoBarType::Info, window());
      sInfoBar->setFixedWidth(270);
      FluInfoBarMgr::getInstance()->addInfoBar(window(), sInfoBar);
  });

  connect(sucBtn, &FluPushButton::clicked, [=]() {
      FluShortInfoBar* sInfoBar = new FluShortInfoBar(FluShortInfoBarType::Suc, window());
      sInfoBar->setFixedWidth(270);
      FluInfoBarMgr::getInstance()->addInfoBar(window(), sInfoBar);
  });

  connect(warnBtn, &FluPushButton::clicked, [=]() {
      FluShortInfoBar* sInfoBar = new FluShortInfoBar(FluShortInfoBarType::Warn, window());
      sInfoBar->setFixedWidth(270);
      FluInfoBarMgr::getInstance()->addInfoBar(window(), sInfoBar);
  });

  connect(errorBtn, &FluPushButton::clicked, [=]() {
      FluShortInfoBar* sInfoBar = new FluShortInfoBar(FluShortInfoBarType::Error, window());
      sInfoBar->setFixedWidth(270);
      FluInfoBarMgr::getInstance()->addInfoBar(window(), sInfoBar);
  });

```

