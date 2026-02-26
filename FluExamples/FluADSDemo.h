#pragma once

#include <QWidget>
#include <DockManager.h>
#include <DockAreaWidget.h>
#include <DockWidget.h>
#include <QPlainTextEdit>
#include <QMainWindow>
#include <QTableWidget>

class FluADSDemo : public QMainWindow
{
	Q_OBJECT
public:
	FluADSDemo(QWidget* parent = nullptr);
protected:
    //ads::CDockManager* m_dockManager;
};
