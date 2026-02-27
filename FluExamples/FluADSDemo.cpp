#include "FluADSDemo.h"

FluADSDemo::FluADSDemo(QWidget* parent /*= nullptr*/) : FluWindowKitWindow(parent)
{
    setWindowTitle("ADS demo");
    //delete statusBar();
    //setStatusBar(nullptr);
    //setMenuBar(nullptr);

    ads::CDockManager::setConfigFlag(ads::CDockManager::OpaqueSplitterResize, true);
    ads::CDockManager::setConfigFlag(ads::CDockManager::XmlCompressionEnabled, false);
    ads::CDockManager::setConfigFlag(ads::CDockManager::FocusHighlighting, true);

    //auto edit = new FluScintilla;
    //setCentralWidget(edit);

    auto dockMgr = new ads::CDockManager(this);
    //dockMgr->setContentsMargins(0, 0, 0, 0);
    //dockMgr->setStyleSheet("background-color: rgb(32, 32, 32);");

    /*auto onThemeChanged = [=](FluTheme theme) {
        if (theme == FluTheme::Light)
        {
            dockMgr->setStyleSheet("CDockManager{background-color: rgb(243, 243, 243);}");
        }
        else if (theme == FluTheme::Dark)
        {
            dockMgr->setStyleSheet("CDockManager{background-color: rgb(32, 32, 32);}");
        }
        else
        {
            dockMgr->setStyleSheet("CDockManager{background-color: rgb(40, 44, 52);}");
        }
    };*/

    onThemeChanged();
    connect(FluThemeUtils::getUtils(), &FluThemeUtils::themeChanged, this, [=](FluTheme theme) { 
        onThemeChanged();
    });


    auto edit = new FluScintilla;
    //
    auto centralDockWidget = dockMgr->createDockWidget("CentralWidget", this);
    //centralDockWidget->setStyleSheet("background-color: pink;");
    centralDockWidget->setWidget(edit);
    auto centralDockArea = dockMgr->setCentralWidget(centralDockWidget);
    centralDockArea->setAllowedAreas(ads::DockWidgetArea::OuterDockAreas);

    auto table1 = new FluTableView;
    table1->setWordWrap(false);
    table1->setColumnCount(3);
    //table1->setRowCount(10);
    table1->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    table1->setColumnWidth(0, 30);
    //table1->setRowHeight()
    for (int i = 1; i < 3; i++)
    {
        table1->horizontalHeader()->setSectionResizeMode(i, QHeaderView::Stretch);
    }

    for (int i = 0; i < 10; i++)
    {
        int nRowCount = table1->rowCount();
        table1->insertRow(nRowCount);

        table1->setRowHeight(i, 30);
        auto item = new QTableWidgetItem(QString::asprintf("%d", i + 1));
        table1->setItem(i, 0, item);
    }

    table1->verticalHeader()->setVisible(false);
    table1->horizontalHeader()->setVisible(false);

    auto tableDockWidget1 = dockMgr->createDockWidget("Table 1");
    tableDockWidget1->setWidget(table1);
    tableDockWidget1->setMinimumSizeHintMode(ads::CDockWidget::MinimumSizeHintFromDockWidget);
    tableDockWidget1->resize(250, 150);
    tableDockWidget1->setMinimumSize(200, 150);
    auto tableArea1 = dockMgr->addDockWidget(ads::DockWidgetArea::LeftDockWidgetArea, tableDockWidget1);

    auto table2 = new FluTableView;
    table2->setColumnCount(5);
    //table2->setRowCount(1024);
    table2->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    table2->setColumnWidth(0, 30);
    for (int i = 1; i < 5; i++)
    {
        table2->horizontalHeader()->setSectionResizeMode(i, QHeaderView::Stretch);
    }

    for (int i = 0; i < 1024; i++)
    {
        int nRowCount = table2->rowCount();
        table2->insertRow(nRowCount);

        table2->setRowHeight(i, 30);
        auto item = new QTableWidgetItem(QString::asprintf("%d", i + 1));
        table2->setItem(i, 0, item);
    }

    table2->verticalHeader()->setVisible(false);
    table2->horizontalHeader()->setVisible(false);

    
    auto tableDockWidget2 = dockMgr->createDockWidget("Table 2");
    tableDockWidget2->setStyleSheet("border: 1px solid pink;");
    // background transparency
    //tableDockWidget2->setBackgroundTransparent(true);
    //tableDockWidget2->setStyleSheet("");

    //tableDockWidget2->setWidget(table2);
    tableDockWidget2->setMinimumSizeHintMode(ads::CDockWidget::MinimumSizeHintFromDockWidget);
    tableDockWidget2->resize(250, 150);
    tableDockWidget2->setMinimumSize(200, 150);
    dockMgr->addDockWidget(ads::DockWidgetArea::BottomDockWidgetArea, tableDockWidget2, tableArea1);

    auto propertiesTable = new FluTableView();
    propertiesTable->setColumnCount(3);

     propertiesTable->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    propertiesTable->setColumnWidth(0, 30);
    for (int i = 1; i < 3; i++)
    {
        propertiesTable->horizontalHeader()->setSectionResizeMode(i, QHeaderView::Stretch);
    }

     for (int i = 0; i < 10; i++)
    {
         int nRowCount = propertiesTable->rowCount();
        propertiesTable->insertRow(nRowCount);

         propertiesTable->setRowHeight(i, 30);
         auto item = new QTableWidgetItem(QString::asprintf("%d", i + 1));
         propertiesTable->setItem(i, 0, item);
    }

    propertiesTable->verticalHeader()->setVisible(false);
    propertiesTable->horizontalHeader()->setVisible(false);


    ads::CDockWidget* propertiesDockWidget = dockMgr->createDockWidget("Properties");
    propertiesDockWidget->setWidget(propertiesTable);
    propertiesDockWidget->setMinimumSizeHintMode(ads::CDockWidget::MinimumSizeHintFromDockWidget);
    //propertiesDockWidget->resize(250, 150);
    propertiesDockWidget->setMinimumSize(200, 150);
    dockMgr->addDockWidget(ads::DockWidgetArea::RightDockWidgetArea, propertiesDockWidget, centralDockArea);
}

void FluADSDemo::onThemeChanged()
{
    //if (theme == FluTheme::Light)
    //{
    //    dockMgr->setStyleSheet("CDockManager{background-color: rgb(243, 243, 243);}");
    //}
    //else if (theme == FluTheme::Dark)
    //{
    //    dockMgr->setStyleSheet("CDockManager{background-color: rgb(32, 32, 32);}");
    //}
    //else
    //{
    //    dockMgr->setStyleSheet("CDockManager{background-color: rgb(40, 44, 52);}");
    //}
    FluStyleSheetUitls::setQssByFileName("FluADSDemo.qss", this, FluThemeUtils::getUtils()->getTheme());
}
