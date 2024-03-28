```cpp
 auto expander = new FluExpander(this);
 expander->setFixedWidth(350);
 auto titleLabel = new FluLabel;
 titleLabel->setFixedWidth(250);
 titleLabel->setText("This is a label in Header.");
 expander->getWrap1Layout()->addWidget(titleLabel);

 auto contentLabel = new FluLabel;
 contentLabel->setFixedWidth(230);
 contentLabel->setText("This is a label in the content.");
 expander->getWrap2Layout()->setAlignment(Qt::AlignCenter);
 expander->getWrap2Layout()->addWidget(contentLabel);
```

