#include "FluTableViewPage.h"

FluTableViewPage::FluTableViewPage(QWidget* parent /*= nullptr*/) : FluAEmptyPage(parent)
{
    m_mainLayout->setAlignment(Qt::AlignTop);
    m_titleLabel->setText(tr("TableView"));
    m_infoLabel->setText(tr("The TableView control provides a flexible way to display a collection of data in row and columns."));

    auto displayBox = new FluDisplayBox;
    displayBox->setTitle(tr("Base TableView Demo."));
    displayBox->getCodeExpander()->setCodeByPath(FLURC("code/TableViewPageCode1.md"));
    displayBox->setBodyWidgetFixedHeight(600);

    // table view
    auto tableView = new FluTableView(this);
    tableView->setWordWrap(false);
    tableView->setColumnCount(3);
    tableView->setReadOnlySet({0});
    QStringList header;
    header << tr("index") << tr("time") << tr("content");
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
    FluStyleSheetUitls::setQssByFileName(FLURC("StyleSheet/light/FluTableViewPage.qss"), this);
}

void FluTableViewPage::onThemeChanged()
{
    if (FluThemeUtils::isLightTheme())
    {
        FluStyleSheetUitls::setQssByFileName(FLURC("StyleSheet/light/FluTableViewPage.qss"), this);
    }
    else
    {
        FluStyleSheetUitls::setQssByFileName(FLURC("StyleSheet/dark/FluTableViewPage.qss"), this);
    }
}
