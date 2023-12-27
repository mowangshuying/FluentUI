#pragma once

#include <QWidget>
#include <QTabWidget>

#include "FluColorDemo.h"
#include "FluChangeBgDemo.h"
#include "FluButtonDemo.h"
#include "../FluControls/FluTabWidget.h"

class FluTabDemo : public FluTabWidget
{
	Q_OBJECT
public:
	FluTabDemo(QWidget* parent = nullptr);

	void addColorExampleWidget();

	void addChangeBackgrondWidget();

	void addButtonExmapleWidget();
private:
};

