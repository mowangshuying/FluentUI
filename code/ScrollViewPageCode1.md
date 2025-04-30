```
QPixmap img("../res/SampleMedia/LandscapeImage9.jpg");
auto imgBox = new FluImageBox(img, this);
imgBox->setFixedSize(2000, 2000);
auto scrollArea = new FluScrollArea;
scrollArea->setWidget(imgBox);
scrollArea->setFixedSize(400, 300);
```

