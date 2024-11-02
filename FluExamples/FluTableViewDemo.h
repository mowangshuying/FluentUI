#pragma once

#include "FluTemplateDemo.h"
#include <QTableWidget>
#include <QHeaderView>
#include "../FluControls/FluScrollDelegate.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include "../FluControls/FluPushButton.h"

class FluTableViewDemo : public FluTemplateDemo
{
    Q_OBJECT
  public:
    FluTableViewDemo(QWidget* parent = nullptr) : FluTemplateDemo(parent)
    {
        auto widget = new QTableWidget(this);
        auto delegate = new FluScrollDelegate(widget);

        auto vLayout = new QVBoxLayout;
        // vLayout->setSpacing(20);
        auto hLayout = new QHBoxLayout;
        hLayout->setContentsMargins(5, 5, 5, 5);

        auto deleteFirstRowBtn = new FluPushButton;
        deleteFirstRowBtn->setText("delete first row");
        hLayout->addWidget(deleteFirstRowBtn);

        connect(deleteFirstRowBtn, &FluPushButton::clicked, [=]() {
            int nRowCount = widget->rowCount();
            if (nRowCount > 0)
            {
                widget->removeRow(0);
            }
        });

        auto deleteLastRowBtn = new FluPushButton;
        deleteLastRowBtn->setText("delete last row");
        hLayout->addWidget(deleteLastRowBtn);

        connect(deleteLastRowBtn, &FluPushButton::clicked, [=]() {
            int nRowCount = widget->rowCount();
            if (nRowCount > 0)
            {
                widget->removeRow(nRowCount - 1);
            }
        });

        auto deleteCurrentRowBtn = new FluPushButton;
        deleteCurrentRowBtn->setText("delete current row");
        hLayout->addWidget(deleteCurrentRowBtn);

        connect(deleteCurrentRowBtn, &FluPushButton::clicked, [=]() {
            auto items = widget->selectedItems();
            int nCount = items.count();
            int nCurrentRow = 0;
            if (nCount > 0)
            {
                nCurrentRow = widget->row(items.at(0));
                widget->removeRow(nCurrentRow);
            }
            // LOG_DEBUG << "click:" << nCurrentRow;
        });

        m_contentLayout->addLayout(vLayout);
        vLayout->addWidget(widget);
        vLayout->addLayout(hLayout);

        resize(800, 800);
        // widget->move(50, 50);
        // widget->resize(700, 700);

        widget->setColumnCount(3);
        QStringList header;
        header << "index"
               << "time"
               << "content";

        widget->setHorizontalHeaderLabels(header);
        widget->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
        widget->setColumnWidth(0, 100);
        widget->setColumnWidth(1, 200);
        widget->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch);
        widget->setAlternatingRowColors(true);

        widget->verticalHeader()->setVisible(false);

        // set row select mode;
        widget->setSelectionBehavior(QAbstractItemView::SelectRows);
        widget->setSelectionMode(QAbstractItemView::SingleSelection);

        // insert items;
        for (int i = 0; i < 100; i++)
        {
            int nRowCount = widget->rowCount();
            widget->insertRow(nRowCount);

            auto item1 = new QTableWidgetItem(QString::asprintf("%d", i + 1));
            widget->setItem(i, 0, item1);

            auto item2 = new QTableWidgetItem(QString::asprintf("2024/10/14 06:28"));
            widget->setItem(i, 1, item2);

            auto item3 = new QTableWidgetItem(QString::asprintf("just a row test data"));
            widget->setItem(i, 2, item3);
        }
    }
};
