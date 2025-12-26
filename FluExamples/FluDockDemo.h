#pragma once

// take it from Qt examples (dockwidgets)
#include <QMainWindow>
#include <QTextEdit>
#include <QStatusBar>
#include <QMessageBox>
#include <QMenuBar>
#include <QMenu>
#include <QDockWidget>
#include <QListWidget>

class FluDockDemo : public QMainWindow
{
	Q_OBJECT
public:
	FluDockDemo(QWidget* parent = nullptr);

    void open()
    {

    }

    void copy()
    {

    }

    void save()
    {

    }

    void paste()
    {

    }

    void cut()
    {

    }

    void del()
    {

    }

    void about()
    {
        QMessageBox::about(this, "About Fluent UI",
            "The <b>Fluent UI</b> example demonstrates how to use the Fluent UI widgets.");
    }

 protected:
    QTextEdit* m_textEdit;
};
