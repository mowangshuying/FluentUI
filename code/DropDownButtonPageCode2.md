```cpp
auto dropDownButton2 = new FluDropDownButton(this);
dropDownButton2->setFixedWidth(78);
dropDownButton2->setIcon(QIcon(FluIconUtils::getFluentIcon(FluAwesomeType::Mail)));
dropDownButton2->addIconTextItem(QIcon(FluIconUtils::getFluentIcon(FluAwesomeType::Send)), "Send");
dropDownButton2->addIconTextItem(QIcon(FluIconUtils::getFluentIcon(FluAwesomeType::MailReply)), "Reply");
dropDownButton2->addIconTextItem(QIcon(FluIconUtils::getFluentIcon(FluAwesomeType::MailReplyAll)), "Reply All");
```