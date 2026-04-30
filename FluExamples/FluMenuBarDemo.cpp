#include "FluMenuBarDemo.h"
#include "../FluControls/FluRoundMenu.h"

FluMenuBarDemo::FluMenuBarDemo(QWidget* parent /*= nullptr*/) : FluTemplateDemo(parent)
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

    auto fileMenu = new FluRoundMenu(menuBar);
    fileMenu->setTitle("File(&F)");
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
    editMenu->setTitle("Edit(&E)");
    editMenu->addAction(undoEditAction);
    editMenu->addAction(cutEditAction);
    editMenu->addAction(copyEditAction);
    editMenu->addAction(pasteEditAction);
    // menuBar->addMenu(editMenu);
    menuBar->addAction(editMenu->menuAction());

    // Help
    auto aboutAction = new FluAction("About");
    auto helpMenu = new FluMenu(menuBar);
    helpMenu->setTitle("Help(&H)");
    helpMenu->addAction(aboutAction);
    // menuBar->addMenu(helpMenu);
    menuBar->addAction(helpMenu->menuAction());

    //  FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluMenuBar.qss", menuBar);

    // menuBar->show();

    //auto vLayout = new QVBoxLayout;
    //setLayout(vLayout);

    //vLayout->addWidget(menuBar);
    m_contentLayout->addWidget(menuBar);
    resize(600, 400);
}
