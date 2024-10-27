#pragma once

#include "FluAEmptyPage.h"
#include "../FluControls/FluTableView.h"
#include "../FluControls/FluDisplayBox.h"
#include "../FluControls/FluVScrollView.h"

class FluTableViewPage : public FluAEmptyPage
{
    Q_OBJECT
  public:
      FluTableViewPage(QWidget* parent = nullptr) : FluAEmptyPage(parent)
      {
          m_mainLayout->setAlignment(Qt::AlignTop);
          m_titleLabel->setText("TableView");
          m_infoLabel->setText("The TableView control provides a flexible way to display a collection of data in row and columns.");

          auto displayBox = new FluDisplayBox;
          displayBox->setTitle("Base TableView Demo.");
          displayBox->getCodeExpander()->setCodeByPath("../code/TableViewPageCode1.md");
          displayBox->setBodyWidgetFixedHeight(600);

          // table view
          auto tableView = new FluTableView(this);
          tableView->setWordWrap(false);
          tableView->setColumnCount(3);
          tableView->setReadOnlySet({0});
          QStringList header;
          header << "index"
                 << "time"
                 << "content";
          tableView->setHorizontalHeaderLabels(header);
          tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
          tableView->setColumnWidth(0, 60);
          tableView->setColumnWidth(1, 200);
          tableView->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch);

          tableView->setAlternatingRowColors(true);
          tableView->verticalHeader()->setVisible(false);

          // insert items;
          for (int i = 0; i < 100; i++)
          {
              int nRowCount = tableView->rowCount();
              tableView->insertRow(nRowCount);

              auto item1 = new QTableWidgetItem(QString::asprintf("%d", i + 1));
              tableView->setItem(i, 0, item1);

              auto item2 = new QTableWidgetItem(QString::asprintf("2024/10/14 06:28"));
              tableView->setItem(i, 1, item2);

              auto item3 = new QTableWidgetItem(QString::asprintf("just a row test data"));
              tableView->setItem(i, 2, item3);
          }

          // 
          displayBox->getBodyLayout()->addWidget(tableView);
          m_vScrollView->getMainLayout()->addWidget(displayBox, 0, Qt::AlignTop);
          FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluTableViewPage.qss", this);

      }
    public slots:
      void onThemeChanged()
      {
          if (FluThemeUtils::isLightTheme())
          {
              FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluTableViewPage.qss", this);
          }
          else
          {
              FluStyleSheetUitls::setQssByFileName("../StyleSheet/dark/FluTableViewPage.qss", this);
          }
      }
};
