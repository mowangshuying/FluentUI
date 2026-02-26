#include "FluADSDemo.h"

FluADSDemo::FluADSDemo(QWidget* parent /*= nullptr*/) : QMainWindow(parent)
{
    ads::CDockManager::setConfigFlag(ads::CDockManager::OpaqueSplitterResize, true);
    ads::CDockManager::setConfigFlag(ads::CDockManager::XmlCompressionEnabled, false);
    ads::CDockManager::setConfigFlag(ads::CDockManager::FocusHighlighting, true);

    auto dockMgr = new ads::CDockManager(this);

    auto plainTextEdit = new QPlainTextEdit();
    plainTextEdit->setPlaceholderText("This is the central editor. Enter your text here.");
    
    auto centralDockWidget = dockMgr->createDockWidget("CentralWidget");
    centralDockWidget->setWidget(plainTextEdit);
    auto centralDockArea = dockMgr->setCentralWidget(centralDockWidget);
    centralDockArea->setAllowedAreas(ads::DockWidgetArea::OuterDockAreas);

    QTableWidget* table1 = new QTableWidget();
    table1->setColumnCount(3);
    table1->setRowCount(10);

    auto tableDockWidget1 = dockMgr->createDockWidget("Table 1");
    tableDockWidget1->setWidget(table1);
    tableDockWidget1->setMinimumSizeHintMode(ads::CDockWidget::MinimumSizeHintFromDockWidget);
    tableDockWidget1->resize(250, 150);
    tableDockWidget1->setMinimumSize(200, 150);
    auto tableArea1 = dockMgr->addDockWidget(ads::DockWidgetArea::LeftDockWidgetArea, tableDockWidget1);

    auto table2 = new QTableWidget();
    table2->setColumnCount(5);
    table2->setRowCount(1020);
    
    auto tableDockWidget2 = dockMgr->createDockWidget("Table 2");
    tableDockWidget2->setWidget(table2);
    tableDockWidget2->setMinimumSizeHintMode(ads::CDockWidget::MinimumSizeHintFromDockWidget);
    tableDockWidget2->resize(250, 150);
    tableDockWidget2->setMinimumSize(200, 150);
    dockMgr->addDockWidget(ads::DockWidgetArea::BottomDockWidgetArea, tableDockWidget2, tableArea1);

    QTableWidget* propertiesTable = new QTableWidget();
    propertiesTable->setColumnCount(3);
    propertiesTable->setRowCount(10);

    ads::CDockWidget* propertiesDockWidget = dockMgr->createDockWidget("Properties");
    propertiesDockWidget->setWidget(propertiesTable);
    propertiesDockWidget->setMinimumSizeHintMode(ads::CDockWidget::MinimumSizeHintFromDockWidget);
    propertiesDockWidget->resize(250, 150);
    propertiesDockWidget->setMinimumSize(200, 150);
    dockMgr->addDockWidget(ads::DockWidgetArea::RightDockWidgetArea, propertiesDockWidget, centralDockArea);
}
