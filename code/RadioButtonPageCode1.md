```cpp
FluVRadioGroupBox* groupBox = new FluVRadioGroupBox("Options");
groupBox->move(50, 50);

auto btn1 = new FluRadioButton("Option 1", groupBox);
auto btn2 = new FluRadioButton("Option 2", groupBox);
auto btn3 = new FluRadioButton("Option 3", groupBox);

groupBox->addRadioButton(btn1);
groupBox->addRadioButton(btn2);
groupBox->addRadioButton(btn3);
```

