#include "FluListViewDemo.h"

FluListViewDemo::FluListViewDemo(QWidget* parent /*= nullptr*/) : FluWidget(parent)
{
    FluListView* listView = new FluListView(this);

    listView->setFixedSize(350, 400);
    listView->addItem("Kendall Collins");
    listView->addItem("Henry Ross");
    listView->addItem("Vance DeLeon");
    listView->addItem("Victoria Burke");

    listView->addItem("Amber Rodriguez");
    listView->addItem("Amari Rivera");
    listView->addItem("Jessie lrwin");
    listView->addItem("Quinn Campbell");

    listView->addItem("Olivia Wilson");
    listView->addItem("Ana Bowman");
    listView->addItem("Shawn Hughes");
    listView->addItem("Oscar Ward");

    listView->addItem("Madison Butler");
    listView->addItem("Graham Barnes");
    listView->addItem("Anthony lvanov");
    listView->addItem("Michael peltier");

    listView->move(50, 50);
    resize(600, 600);
}
