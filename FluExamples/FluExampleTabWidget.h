#pragma once

#include <QWidget>
#include <QTabWidget>

#include "FluColorExampleWidget.h"
#include "FluChangeBackgroundWidget.h"

class FluExampleTabWidget : public QTabWidget
{
	Q_OBJECT
public:
	FluExampleTabWidget(QWidget* parent = nullptr) : QTabWidget(parent)
	{
		resize(800, 600);

		// 设置一些属性
		setVisible(true); // 
		setTabsClosable(true);//设置可关闭

		// 添加窗口
		addColorExampleWidget();
		addChangeBackgrondWidget();
	}


	void addColorExampleWidget()
	{
		FluColorExampleWidget* widget = new FluColorExampleWidget(this);
		widget->setAttribute(Qt::WA_DeleteOnClose);
		widget->setBgColor(QColor("#1994e1"));
		addTab(widget, "颜色窗口");
		//widget->setBackgroundRole();
		//QPalette::ColorRole
		//widget->setBackgroundRole(Qt::magenta);
	}

	void addChangeBackgrondWidget()
	{
		FluChangeBackgroundWidget* widget = new FluChangeBackgroundWidget(this);
		widget->setAttribute(Qt::WA_DeleteOnClose);
		addTab(widget, "悬浮改变背景颜色");
	}
private:

};

