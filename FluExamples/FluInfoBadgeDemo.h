#pragma once

#include "../FluControls/FluInfoBadge.h"
#include <QWidget>
#include <QHBoxLayout>

class FluInfoBadgeDemo : public QWidget
{
    // Q_OBJECT
  public:
    FluInfoBadgeDemo(QWidget* parent = nullptr) : QWidget(parent)
    {
        QHBoxLayout* hBoxLayout = new QHBoxLayout;
        setLayout(hBoxLayout);

        auto targetWidget1 = new QWidget(this);
        targetWidget1->setFixedSize(40, 40);
        targetWidget1->setStyleSheet("background-color:gray;border-radius:4px;");
        targetWidget1->move(250, 50);
        FluInfoBadge::setInfoBadge(this, targetWidget1, 0);
        hBoxLayout->addWidget(targetWidget1);

        auto targetWidget2 = new QWidget(this);
        targetWidget2->setFixedSize(40, 40);
        targetWidget2->setStyleSheet("background-color:gray;border-radius:4px;");
        targetWidget2->move(250, 50);
        FluInfoBadge::setInfoBadge(this, targetWidget2, 5);
        hBoxLayout->addWidget(targetWidget2);

        auto targetWidget3 = new QWidget(this);
        targetWidget3->setFixedSize(40, 40);
        targetWidget3->setStyleSheet("background-color:gray;border-radius:4px;");
        targetWidget3->move(250, 50);
        FluInfoBadge::setInfoBadge(this, targetWidget3, 50);
        hBoxLayout->addWidget(targetWidget3);

        auto targetWidget4 = new QWidget(this);
        targetWidget4->setFixedSize(40, 40);
        targetWidget4->setStyleSheet("background-color:gray;border-radius:4px;");
        targetWidget4->move(250, 100);
        FluInfoBadge::setInfoBadge(this, targetWidget4, 1000);
        hBoxLayout->addWidget(targetWidget4);

        resize(600, 400);
    }
};
