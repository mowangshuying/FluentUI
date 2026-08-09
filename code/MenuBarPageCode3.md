```cpp
auto btn = new FluPushButton;
btn->setText("Show menu");
btn->setFixedWidth(120);
displayBox->getBodyLayout()->addWidget(btn);

FluRoundMenu* roundMenu = new FluRoundMenu("", FluAwesomeType::None, this);
roundMenu->addAction(new FluAction(FluAwesomeType::Copy, "Copy"));
roundMenu->addAction(new FluAction(FluAwesomeType::Cut, "Cut"));

auto subRoundMenu = new FluRoundMenu("Add to", FluAwesomeType::Add);
QList<QAction*> actions;
actions.append(new FluAction("Music"));
actions.append(new FluAction("Video"));
subRoundMenu->addActions(actions);
roundMenu->addMenu(subRoundMenu);

roundMenu->addAction(new FluAction(FluAwesomeType::Paste, "Paste"));
roundMenu->addAction(new FluAction(FluAwesomeType::Undo, "Undo"));
roundMenu->addSeparator();
roundMenu->addAction(new FluAction("Select all"));
roundMenu->addAction(new FluAction(FluAwesomeType::Settings, "Setting"));
roundMenu->addAction(new FluAction(FluAwesomeType::Help, "Help"));
roundMenu->addAction(new FluAction(FluAwesomeType::Feedback, "Feedback"));

connect(btn, &FluPushButton::clicked, [=]() {
    auto gp = btn->mapToGlobal(QPoint(btn->width() + 5, -100));
    roundMenu->exec(gp, true, FluMenuAniType::dropDown);
});
```