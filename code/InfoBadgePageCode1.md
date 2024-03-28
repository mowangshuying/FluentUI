```cpp
auto targetWidget1 = new QWidget(displayBox->getBodyWidget());
targetWidget1->setFixedSize(40, 40);
targetWidget1->setStyleSheet("background-color:gray;border-radius:4px;");
targetWidget1->move(50, 30);
FluInfoBadge::setInfoBadge(displayBox->getBodyWidget(), targetWidget1, 1);

auto targetWidget2 = new QWidget(displayBox->getBodyWidget());
targetWidget2->setFixedSize(40, 40);
targetWidget2->setStyleSheet("background-color:gray;border-radius:4px;");
targetWidget2->move(150, 30);
FluInfoBadge::setInfoBadge(displayBox->getBodyWidget(), targetWidget2, 22);

auto targetWidget3 = new QWidget(displayBox->getBodyWidget());
targetWidget3->setFixedSize(40, 40);
targetWidget3->setStyleSheet("background-color:gray;border-radius:4px;");
targetWidget3->move(250, 30);
FluInfoBadge::setInfoBadge(displayBox->getBodyWidget(), targetWidget3, 333);
```

