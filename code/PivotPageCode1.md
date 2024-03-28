```cpp
auto pivot = new FluPivot;
// pivot->setFixedWidth(800);

auto label1 = new QLabel;
label1->setObjectName("label");
label1->setText("This is a All Page");
label1->setAlignment(Qt::AlignCenter);
pivot->addPivotItem("All", label1);

auto label2 = new QLabel;
label2->setObjectName("label");
label2->setText("This is a Unread Page");
label2->setAlignment(Qt::AlignCenter);
pivot->addPivotItem("Unread", label2);

auto label3 = new QLabel;
label3->setObjectName("label");
label3->setText("This is Flagged Page");
label3->setAlignment(Qt::AlignCenter);
pivot->addPivotItem("Flagged", label3);

auto label4 = new QLabel;
label4->setObjectName("label");
label4->setText("This is Urgent Page");
label4->setAlignment(Qt::AlignCenter);
pivot->addPivotItem("Urgent", label4);
```

