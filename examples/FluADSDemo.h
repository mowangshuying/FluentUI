#pragma once

#include <QWidget>
#include <DockManager.h>
#include <DockAreaWidget.h>
#include <DockWidget.h>
#include <QPlainTextEdit>
#include <QMainWindow>
#include <QTableWidget>
#include "../controls/FluWindowKitWindow.h"
#include "../controls/FluTableView.h"
#include "../controls/FluScintilla.h"
#include "../controls/FluTextEdit.h"
#include "../controls/FluDockManager.h"

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
