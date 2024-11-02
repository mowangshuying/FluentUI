#pragma once

#include "FluTemplateDemo.h"
#include "../FluControls/FluTableView.h"

class FluTableViewExDemo : public FluTemplateDemo
{
  public:
    FluTableViewExDemo(QWidget* parent = nullptr) : FluTemplateDemo(parent)
    {
        m_tableView = new FluTableView(this);
        m_tableView->setWordWrap(false);
        m_tableView->setColumnCount(3);
        m_tableView->setReadOnlySet({0});
        QStringList header;
        header << "index"
               << "time"
               << "content";
        m_tableView->setHorizontalHeaderLabels(header);
        m_tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
        m_tableView->setColumnWidth(0, 60);
        m_tableView->setColumnWidth(1, 200);
        m_tableView->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch);

        m_tableView->setAlternatingRowColors(true);
        m_tableView->verticalHeader()->setVisible(false);

        m_contentLayout->addWidget(m_tableView);

        // insert items;
        for (int i = 0; i < 100; i++)
        {
            int nRowCount = m_tableView->rowCount();
            m_tableView->insertRow(nRowCount);

            auto item1 = new QTableWidgetItem(QString::asprintf("%d", i + 1));
            m_tableView->setItem(i, 0, item1);

            auto item2 = new QTableWidgetItem(QString::asprintf("2024/10/14 06:28"));
            m_tableView->setItem(i, 1, item2);

            auto item3 = new QTableWidgetItem(QString::asprintf("just a row test data"));
            m_tableView->setItem(i, 2, item3);
        }

        resize(700, 700);
    }

  public:
    // QHBoxLayout* m_hLayout;
    FluTableView* m_tableView;
};
