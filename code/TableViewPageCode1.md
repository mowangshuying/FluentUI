```cpp
// table view
auto tableView = new FluTableView(this);
tableView->setWordWrap(false);
tableView->setColumnCount(3);
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
```

