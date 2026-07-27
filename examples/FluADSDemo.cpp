#include "FluADSDemo.h"
#include "../Controls/FluMenuBar.h"
#include "../Controls/FluAction.h"
#include "../Controls/FluMenu.h"

// #fill:#000000;
FluADSDemo::FluADSDemo(QWidget* parent /*= nullptr*/) : FluWindowKitWindow(parent)
{
    setWindowTitle("ADS demo");
    FluDockManager::setConfigFlag(FluDockManager::OpaqueSplitterResize, true);
    FluDockManager::setConfigFlag(FluDockManager::XmlCompressionEnabled, false);
    FluDockManager::setConfigFlag(FluDockManager::FocusHighlighting, true);

    // auto menuBar = new FluMenuBar;
    // m_agent->setHitTestVisible(menuBar);
    // m_titleBar->setMenuBar(menuBar);
    //   menuBar->move(50, 50);

    auto newFileAction = new FluAction("new");
    auto openFileAction = new FluAction("Open");
    auto saveFileAction = new FluAction("Save");
    auto exitFileAction = new FluAction("Exit");

    auto fileMenu = new FluMenu();
    fileMenu->setTitle("File(&F)");
    fileMenu->addAction(newFileAction);
    fileMenu->addAction(openFileAction);
    fileMenu->addAction(saveFileAction);
    fileMenu->addAction(exitFileAction);

    m_menuBar->addAction(fileMenu->menuAction());

    // undo cut copy paste
    auto undoEditAction = new FluAction("Undo");
    auto cutEditAction = new FluAction("Cut");
    auto copyEditAction = new FluAction("Copy");
    auto pasteEditAction = new FluAction("Paste");

    auto editMenu = new FluMenu(m_menuBar);
    editMenu->setTitle("Edit(&E)");
    editMenu->addAction(undoEditAction);
    editMenu->addAction(cutEditAction);
    editMenu->addAction(copyEditAction);
    editMenu->addAction(pasteEditAction);
    m_menuBar->addAction(editMenu->menuAction());

    // Help
    auto aboutAction = new FluAction("About");
    auto helpMenu = new FluMenu(m_menuBar);
    helpMenu->setTitle("Help(&H)");
    helpMenu->addAction(aboutAction);
    m_menuBar->addAction(helpMenu->menuAction());

    m_dockMgr = new FluDockManager(this);

    auto edit = new FluScintilla;
    //
    auto centralDockWidget = m_dockMgr->createDockWidget("CentralWidget", this);
    // centralDockWidget->setStyleSheet("background-color: pink;");
    centralDockWidget->setWidget(edit);
    auto centralDockArea = m_dockMgr->setCentralWidget(centralDockWidget);
    centralDockArea->setAllowedAreas(ads::DockWidgetArea::OuterDockAreas);

    auto table1 = new FluTableView;
    table1->setWordWrap(false);
    table1->setColumnCount(3);
    // table1->setRowCount(10);
    table1->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    table1->setColumnWidth(0, 30);
    // table1->setRowHeight()
    for (int i = 0; i < 3; i++)
    {
        table1->horizontalHeader()->setSectionResizeMode(i, QHeaderView::Stretch);
    }

    for (int i = 0; i < 10; i++)
    {
        int rowCount = table1->rowCount();
        table1->insertRow(rowCount);

        table1->setRowHeight(0, 30);
        auto item = new QTableWidgetItem(QString::asprintf("%d", i + 1));
        table1->setItem(i, 0, item);
    }

    table1->verticalHeader()->setVisible(false);
    table1->horizontalHeader()->setVisible(false);

    auto tableDockWidget1 = m_dockMgr->createDockWidget("Table 1");
    tableDockWidget1->setWidget(table1);
    tableDockWidget1->setMinimumSizeHintMode(ads::CDockWidget::MinimumSizeHintFromDockWidget);
    tableDockWidget1->resize(250, 150);
    tableDockWidget1->setMinimumSize(200, 150);
    auto tableArea1 = m_dockMgr->addDockWidget(ads::DockWidgetArea::LeftDockWidgetArea, tableDockWidget1);

    auto table2 = new FluTableView;
    table2->setColumnCount(5);
    table2->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    table2->setColumnWidth(0, 30);
    for (int i = 1; i < 5; i++)
    {
        table2->horizontalHeader()->setSectionResizeMode(i, QHeaderView::Stretch);
    }

    for (int i = 0; i < 1024; i++)
    {
        int rowCount = table2->rowCount();
        table2->insertRow(rowCount);

        table2->setRowHeight(0, 30);
        auto item = new QTableWidgetItem(QString::asprintf("%d", i + 1));
        table2->setItem(i, 0, item);
    }

    table2->verticalHeader()->setVisible(false);
    table2->horizontalHeader()->setVisible(false);

    auto tableDockWidget2 = m_dockMgr->createDockWidget("Table 2");

    tableDockWidget2->setMinimumSizeHintMode(ads::CDockWidget::MinimumSizeHintFromDockWidget);
    tableDockWidget2->resize(250, 150);
    tableDockWidget2->setMinimumSize(200, 150);
    m_dockMgr->addDockWidget(ads::DockWidgetArea::BottomDockWidgetArea, tableDockWidget2, tableArea1);

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
        int rowCount = propertiesTable->rowCount();
        propertiesTable->insertRow(rowCount);

        propertiesTable->setRowHeight(i, 30);
        auto item = new QTableWidgetItem(QString::asprintf("%d", i + 1));
        propertiesTable->setItem(i, 0, item);
    }

    propertiesTable->verticalHeader()->setVisible(false);
    propertiesTable->horizontalHeader()->setVisible(false);

    ads::CDockWidget* propertiesDockWidget = m_dockMgr->createDockWidget("Properties");
    propertiesDockWidget->setWidget(propertiesTable);
    propertiesDockWidget->setMinimumSizeHintMode(ads::CDockWidget::MinimumSizeHintFromDockWidget);
    propertiesDockWidget->setMinimumSize(200, 150);
    m_dockMgr->addDockWidget(ads::DockWidgetArea::RightDockWidgetArea, propertiesDockWidget, centralDockArea);
}

// void FluADSDemo::onThemeChanged()
//{
//     FluStyleSheetUtils::setQssByFileName("FluADSDemo.qss", m_dockMgr, FluThemeUtils::getUtils()->getTheme());
// }
