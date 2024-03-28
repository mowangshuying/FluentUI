```cpp
auto border = new FluBorder;
border->setFixedSize(376, 54);
border->setBorderWidth(12);

auto* backgroundGroup = new FluHRadioGroupBox("Background", this);
auto btn1 = new FluRadioButton("Green", backgroundGroup);
auto btn2 = new FluRadioButton("Yellow", backgroundGroup);
auto btn3 = new FluRadioButton("White", backgroundGroup);
backgroundGroup->addRadioButton(btn1);
backgroundGroup->addRadioButton(btn2);
backgroundGroup->addRadioButton(btn3);
connect(btn1, &FluRadioButton::toggled, [=]() { border->setBackGroundColor("green"); });
connect(btn2, &FluRadioButton::toggled, [=]() { border->setBackGroundColor("yellow"); });
connect(btn3, &FluRadioButton::toggled, [=]() { border->setBackGroundColor("white"); });

auto* borderGroup = new FluHRadioGroupBox("Border", this);
auto btn4 = new FluRadioButton("Green", borderGroup);
auto btn5 = new FluRadioButton("Yellow", borderGroup);
auto btn6 = new FluRadioButton("White", borderGroup);
borderGroup->addRadioButton(btn4);
borderGroup->addRadioButton(btn5);
borderGroup->addRadioButton(btn6);
connect(btn4, &FluRadioButton::toggled, [=]() { border->setBorderColor("green"); });
connect(btn5, &FluRadioButton::toggled, [=]() { border->setBorderColor("yellow"); });
connect(btn6, &FluRadioButton::toggled, [=]() { border->setBorderColor("white"); });
```

