```cpp
auto comboBox = new FluComboBox;
comboBox->setFixedWidth(200);
comboBox->move(50, 50);
comboBox->addItem("Blue");
comboBox->addItem("Green");
comboBox->addItem("Red");
comboBox->addItem("Yellow");

auto colorLabel = new FluColorLabel(displayBox);
colorLabel->setObjectName("colorLabel");
colorLabel->setProperty("color", "Blue");
colorLabel->setFixedSize(100, 30);

connect(comboBox, &FluComboBox::currentTextChanged, [=](const QString& text) {
    colorLabel->setProperty("color", text);
    colorLabel->style()->polish(colorLabel);
});
```

