#pragma once

#include <QWidget>
#include <DockManager.h>
#include <DockAreaWidget.h>
#include <DockWidget.h>
#include <QPlainTextEdit>
#include <QMainWindow>
#include <QTableWidget>
#include "../FluControls/FluWindowKitWindow.h"
#include "../FluControls/FluTableView.h"

class FluADSDemo : public FluWindowKitWindow
{
	Q_OBJECT
public:
	FluADSDemo(QWidget* parent = nullptr);
protected:
    //ads::CDockManager* m_dockManager;
};
