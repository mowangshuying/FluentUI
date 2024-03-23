#pragma once

#include <QWidget>
#include <QMenuBar>
#include "../FluControls/FluMenu.h"
#include "../FluControls/FluMenuBar.h"
#include "../FluUtils/FluStyleSheetUitls.h"
#include <QMenu>

class FluMenuBarDemo : public QWidget
{
    Q_OBJECT
  public:
    FluMenuBarDemo(QWidget* parent = nullptr) : QWidget(parent)
    {
        // auto menuBar = new QMenuBar(this);
        //  menuBar->move(50, 50);

        // menuBar->addMenu("&Flile");
        // menuBar->addMenu("&Eidt");
        // menuBar->addMenu("&Help");

        auto menuBar = new FluMenuBar;
        //  menuBar->move(50, 50);

        auto newFileAction = new FluAction("new");
        auto openFileAction = new FluAction("Open");
        auto saveFileAction = new FluAction("Save");
        auto exitFileAction = new FluAction("Exit");

        auto fileMenu = new FluMenu(menuBar);
        fileMenu->setTitle("File");
        fileMenu->addAction(newFileAction);
        fileMenu->addAction(openFileAction);
        fileMenu->addAction(saveFileAction);
        fileMenu->addAction(exitFileAction);

        menuBar->addAction(fileMenu->menuAction());

        // undo cut copy paste
        auto undoEditAction = new FluAction("Undo");
        auto cutEditAction = new FluAction("Cut");
        auto copyEditAction = new FluAction("Copy");
        auto pasteEditAction = new FluAction("Paste");

        auto editMenu = new FluMenu(menuBar);
        editMenu->setTitle("Edit");
        editMenu->addAction(undoEditAction);
        editMenu->addAction(cutEditAction);
        editMenu->addAction(copyEditAction);
        editMenu->addAction(pasteEditAction);
        // menuBar->addMenu(editMenu);
        menuBar->addAction(editMenu->menuAction());

        // Help
        auto aboutAction = new FluAction("About");
        auto helpMenu = new FluMenu(menuBar);
        helpMenu->setTitle("Help");
        helpMenu->addAction(aboutAction);
        // menuBar->addMenu(helpMenu);
        menuBar->addAction(helpMenu->menuAction());

        //  FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluMenuBar.qss", menuBar);

        // menuBar->show();

        auto vLayout = new QVBoxLayout;
        setLayout(vLayout);

        vLayout->addWidget(menuBar);
        resize(600, 400);
    }
};
