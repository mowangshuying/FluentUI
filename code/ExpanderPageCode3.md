```cpp
auto expander = new FluExpander(this);
expander->setFixedWidth(350);
auto toggleBtn = new FluToggleButton;
toggleBtn->setFixedWidth(250);
toggleBtn->setText("This  ToggleButton is Centered.");
expander->getWrap1Layout()->addWidget(toggleBtn);

auto pushBtn = new FluPushButton;
pushBtn->setFixedWidth(230);
pushBtn->setText("This is a Left aligned.");
expander->getWrap2Layout()->setAlignment(Qt::AlignLeft);
expander->getWrap2Layout()->addWidget(pushBtn);
```

