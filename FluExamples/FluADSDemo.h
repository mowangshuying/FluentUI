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
#include "../FluControls/FluDockManager.h"

class FluADSDemo : public FluWindowKitWindow
{
	Q_OBJECT
public:
	FluADSDemo(QWidget* parent = nullptr);
//public slots:
//    void onThemeChanged();

protected:
    //ads::CDockManager* m_dockManager;
  FluDockManager* m_dockMgr;
};
