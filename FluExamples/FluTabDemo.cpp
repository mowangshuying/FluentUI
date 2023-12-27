#include "FluTabDemo.h"

FluTabDemo::FluTabDemo(QWidget* parent /*= nullptr*/) : FluTabWidget(parent)
{
	resize(800, 600);
	// 设置一些属性
	setVisible(true); // 
	setTabsClosable(true);//设置可关闭
	// 添加窗口
	addColorExampleWidget();
	addChangeBackgrondWidget();
	addButtonExmapleWidget();
}

void FluTabDemo::addColorExampleWidget()
{
	FluColorDemo* widget = new FluColorDemo(this);
	widget->setAttribute(Qt::WA_DeleteOnClose);
	widget->setBgColor(QColor("#1994e1"));
	addTab(widget, "颜色示例");
}

void FluTabDemo::addChangeBackgrondWidget()
{
	FluChangeBgDemo* widget = new FluChangeBgDemo(this);
	widget->setAttribute(Qt::WA_DeleteOnClose);
	addTab(widget, "改变背景");
}

void FluTabDemo::addButtonExmapleWidget()
{
	FluButtonDemo* widget = new FluButtonDemo(this);
	widget->setAttribute(Qt::WA_DeleteOnClose);
	addTab(widget, "按钮示例");
}
