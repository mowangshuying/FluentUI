#pragma once

#include <QWidget>
#include <DockManager.h>
#include <DockAreaWidget.h>
#include <DockWidget.h>
#include <QPlainTextEdit>
#include <QMainWindow>
#include <QTableWidget>
#include "../Controls/FluWindowKitWindow.h"
#include "../Controls/FluTableView.h"
#include "../Controls/FluScintilla.h"
#include "../Controls/FluTextEdit.h"
#include "../Controls/FluDockManager.h"

class FluADSDemo : public FluWindowKitWindow
{
    Q_OBJECT
  public:
    FluADSDemo(QWidget* parent = nullptr);
    // public slots:
    //     void onThemeChanged();

  protected:
    // ads::CDockManager* m_dockManager;
    FluDockManager* m_dockMgr;
};
