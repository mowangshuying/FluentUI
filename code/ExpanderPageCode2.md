```cpp
auto expander = new FluExpander(this);
expander->setFixedWidth(350);
auto toggleBtn = new FluToggleButton;
toggleBtn->setFixedWidth(250);
toggleBtn->setText("This is a ToggleButton in Header.");
expander->getWrap1Layout()->addWidget(toggleBtn);

auto pushBtn = new FluPushButton;
pushBtn->setFixedWidth(230);
pushBtn->setText("This is a Button in the content.");
expander->getWrap2Layout()->setAlignment(Qt::AlignCenter);
expander->getWrap2Layout()->addWidget(pushBtn);
```

