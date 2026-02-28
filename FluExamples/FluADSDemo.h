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
#include "../FluControls/FluScintilla.h"
#include "../FluControls/FluTextEdit.h"

class FluADSDemo : public FluWindowKitWindow
{
	Q_OBJECT
public:
	FluADSDemo(QWidget* parent = nullptr);
public slots:
    void onThemeChanged();

protected:
    //ads::CDockManager* m_dockManager;
	ads::CDockManager* m_dockMgr;
};
