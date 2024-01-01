#include "FluTabDemo.h"

FluTabDemo::FluTabDemo(QWidget *parent /*= nullptr*/) : FluTabWidget(parent)
{
    resize(800, 600);
    // set attr
    setVisible(true);
    setTabsClosable(true);

    addColorExampleWidget();
    addChangeBackgrondWidget();
    addButtonExmapleWidget();
}

void FluTabDemo::addColorExampleWidget()
{
    FluColorDemo *widget = new FluColorDemo(this);
    widget->setAttribute(Qt::WA_DeleteOnClose);
    widget->setBgColor(QColor("#1994e1"));
    addTab(widget, "Colors example");
}

void FluTabDemo::addChangeBackgrondWidget()
{
    FluChangeBgDemo *widget = new FluChangeBgDemo(this);
    widget->setAttribute(Qt::WA_DeleteOnClose);
    addTab(widget, "Change background");
}

void FluTabDemo::addButtonExmapleWidget()
{
    FluButtonDemo *widget = new FluButtonDemo(this);
    widget->setAttribute(Qt::WA_DeleteOnClose);
    addTab(widget, "Button example");
}
