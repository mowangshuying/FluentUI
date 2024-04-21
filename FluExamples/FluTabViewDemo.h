#pragma once

#include <QWidget>

#include "../FluControls/FluTabView.h"

class FluTabViewDemo : public QWidget
{
  public:
    FluTabViewDemo(QWidget* parent = nullptr) : QWidget(parent)
    {
        auto tabView = new FluTabView;
        auto vMainLayout = new QVBoxLayout;
        setLayout(vMainLayout);

        vMainLayout->addWidget(tabView);

        static int PAGENUM = 1;
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
