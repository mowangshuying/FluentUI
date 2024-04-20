#pragma once

#include <QWidget>

#include "../FluControls/FluTabView.h"

class FluTabViewDemo : public QWidget
{
  public:
    FluTabViewDemo(QWidget* parent = nullptr) : QWidget(parent)
    {
        auto tabView = new FluTabView;
        ///*  for (int i = 0; i < 3; i++)
        //  {
        //      auto tabBarItem = new FluTabBarItem;
        //      tabBar->addBarItem(tabBarItem);
        //  }*/

        auto vMainLayout = new QVBoxLayout;
        setLayout(vMainLayout);

        vMainLayout->addWidget(tabView);
        //   m_vMainLayout->addStretch(1);

        ///* auto page0 = new QLabel;
        // page0->setText("Page0: This is page0");
        // page0->setAlignment(Qt::AlignCenter);
        // tabView->addTab("Page0", page0);

        // auto page1 = new QLabel;
        // page1->setText("Page1: This is page1");
        // page1->setAlignment(Qt::AlignCenter);
        // tabView->addTab("Page1", page1);

        // auto page2 = new QLabel;
        // page2->setText("Page2: This is page2");
        // page2->setAlignment(Qt::AlignCenter);
        // tabView->addTab("Page2", page2);*/

        static int PAGENUM = 3;
        connect(tabView, &FluTabView::addTabBtnClicked, [=]() {
            QString keyString = QString::asprintf("Page%d", PAGENUM);
            QString valueString = QString::asprintf("Page%d: This is page%d", PAGENUM, PAGENUM);

            auto page = new QLabel;
            page->setText(valueString);
            page->setAlignment(Qt::AlignCenter);
            tabView->addTab(keyString, page);

            PAGENUM++;
        });

        resize(600, 400);
    }
};
