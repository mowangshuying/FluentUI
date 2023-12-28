#pragma once
#include "../FluControls/FluDef.h"
#include "../FluUtils/FluIconUtils.h"
#include <QApplication>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>
//
class FluIconToolWidget : public QWidget {
  Q_OBJECT
public:
  FluIconToolWidget(QWidget *parent = nullptr) : QWidget(parent) {
    auto vBoxLayout = new QVBoxLayout(this);
    auto hLayout1 = new QHBoxLayout(this);
    auto label1 = new QLabel("#值");
    auto lineEdit1 = new QLineEdit();
    auto hLayout2 = new QHBoxLayout(this);
    auto btn1 = new QPushButton("执行");

    vBoxLayout->addLayout(hLayout1);
    vBoxLayout->addLayout(hLayout2);

    hLayout1->addWidget(label1);
    hLayout1->addWidget(lineEdit1);
    hLayout2->addWidget(btn1);

    // FluIconUtils::saveFluentPng((FluAwesomeType)lineEdit1->text().toInt(),
    // "tmp");

    connect(btn1, &QPushButton::clicked, [=](bool bClicked) {
      FluIconUtils::saveFluentPng(
          QStringToEnum<FluAwesomeType>(lineEdit1->text()), "tmp.png");
    });
    resize(280, 80);
  }
};