```cpp
auto showDlgBtn = new FluPushButton;
showDlgBtn->setText("Show dialog");
showDlgBtn->setFixedSize(100, 30);

connect(showDlgBtn, &FluPushButton::clicked, [=]() {
    FluMessageBox messageBox("Save your work?", "***********  La La La! Ha! Ha! Ha! **********", window());
    messageBox.exec();
});
```

