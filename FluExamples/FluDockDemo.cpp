#include "FluDockDemo.h"

FluDockDemo::FluDockDemo(QWidget* parent /*= nullptr*/) : QMainWindow(parent)
{
    m_textEdit = new QTextEdit;
    setCentralWidget(m_textEdit);

    // init menubar;
    QMenu* menu = menuBar()->addMenu("&File");
    menu->addAction("&Open...", this, SLOT(open()));
    menu->addAction("&Save", this, SLOT(save()));

    menu = menuBar()->addMenu("&Edit");
    menu->addAction("&Copy", this, SLOT(copy()));
    menu->addAction("&Paste", this, SLOT(paste()));
    menu->addAction("&Cut", this, SLOT(cut()));
    menu->addAction("&Delete", this, SLOT(del()));

    menu = menuBar()->addMenu("&Help");
    menu->addAction("&About", this, SLOT(about()));

    // dock windows;
    // Customers;
    QDockWidget* dock = new QDockWidget("Customers", this);
    dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);

    QListWidget* customerList = new QListWidget(dock);
    customerList->addItems(QStringList() << "John Doe, Harmony Enterprises, 12 Lakeside, Ambleton"
                                         << "Jane Doe, Memorabilia, 23 Watersedge, Beaton"
                                         << "Tammy Shea, Tiblanka, 38 Sea Views, Carlton"
                                         << "Tim Sheen, Caraba Gifts, 48 Ocean Way, Deal"
                                         << "Sol Harvey, Chicos Coffee, 53 New Springs, Eccleston"
                                         << "Sally Hobart, Tiroli Tea, 67 Long River, Fedula");
    dock->setWidget(customerList);
    addDockWidget(Qt::RightDockWidgetArea, dock);

    // Paragraphs.
    dock = new QDockWidget("Paragraphs", this);
    QListWidget* paragraphsList = new QListWidget(dock);
    paragraphsList->addItems(QStringList() << "Thank you for your payment which we have received today."
                                           << "Your order has been dispatched and should be with you "
                                              "within 28 days."
                                           << "We have dispatched those items that were in stock. The "
                                              "rest of your order will be dispatched once all the "
                                              "remaining items have arrived at our warehouse. No "
                                              "additional shipping charges will be made."
                                           << "You made a small overpayment (less than $5) which we "
                                              "will keep on account for you, or return at your request."
                                           << "You made a small underpayment (less than $1), but we have "
                                              "sent your order anyway. We'll add this underpayment to "
                                              "your next bill."
                                           << "Unfortunately you did not send enough money. Please remit "
                                              "an additional $. Your order will be dispatched as soon as "
                                              "the complete amount has been received."
                                           << "You made an overpayment (more than $5). Do you wish to "
                                              "buy more items, or should we return the excess to you?");

    dock->setWidget(paragraphsList);
    addDockWidget(Qt::RightDockWidgetArea, dock);

    dock = new QDockWidget("dock dmeo", this);
    dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea | Qt::BottomDockWidgetArea | Qt::TopDockWidgetArea);
    addDockWidget(Qt::BottomDockWidgetArea, dock);

    setCorner(Qt::BottomLeftCorner, Qt::LeftDockWidgetArea);
    setCorner(Qt::TopLeftCorner, Qt::LeftDockWidgetArea);
    setCorner(Qt::BottomRightCorner, Qt::RightDockWidgetArea);
    setCorner(Qt::TopRightCorner, Qt::RightDockWidgetArea);

    // status bar
    statusBar()->showMessage("Ready");
}
