```cpp
 auto boder = new FluBorder;
 boder->setFixedSize(250, 40);
 boder->setText("Text inside a border");
 displayBox->getBodyContentLayout()->addWidget(boder);

 FluVRadioGroupBox* group = new FluVRadioGroupBox("Background", this);
 auto btn1 = new FluRadioButton("Green", group);
 auto btn2 = new FluRadioButton("Yellow", group);
 auto btn3 = new FluRadioButton("Blue", group);
 group->addRadioButton(btn1);
 group->addRadioButton(btn2);
 group->addRadioButton(btn3);
 connect(btn1, &FluRadioButton::toggled, [=]() { boder->setBackGroundColor("green"); });
 connect(btn2, &FluRadioButton::toggled, [=]() { boder->setBackGroundColor("yellow"); });
 connect(btn3, &FluRadioButton::toggled, [=]() { boder->setBackGroundColor("blue"); });
```

