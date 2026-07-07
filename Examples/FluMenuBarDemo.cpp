#include "FluMenuBarDemo.h"
#include "../Controls/FluRoundMenu.h"
#include "../Controls/FluPMenuBar.h"

FluMenuBarDemo::FluMenuBarDemo(QWidget* parent /*= nullptr*/) : FluTemplateDemo(parent)
{
    // ppMenuBar0();
    ppMenuBar1();
}

void FluMenuBarDemo::normalMenuBar()
{
    auto menuBar = new FluMenuBar;
    auto newFileAction = new FluAction("new");
    newFileAction->setAwesomeType(FluAwesomeType::FileExplorer);
    newFileAction->setShortcut(QKeySequence::New);
    auto openFileAction = new FluAction("Open");
    openFileAction->setShortcut(QKeySequence::Open);
    openFileAction->setAwesomeType(FluAwesomeType::OpenFile);
    auto saveFileAction = new FluAction("Save");
    saveFileAction->setShortcut(QKeySequence::Save);
    openFileAction->setAwesomeType(FluAwesomeType::Save);
    auto exitFileAction = new FluAction("Exit");
    exitFileAction->setShortcut(QKeySequence::Quit);

    auto fileMenu = new FluMenu(menuBar);
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
    menuBar->addAction(editMenu->menuAction());

    // Help
    auto aboutAction = new FluAction("About");
    auto helpMenu = new FluMenu(menuBar);
    helpMenu->setTitle("Help(&H)");
    helpMenu->addAction(aboutAction);

    menuBar->addAction(helpMenu->menuAction());
    m_contentLayout->addWidget(menuBar);
    resize(600, 400);
}

void FluMenuBarDemo::ppMenuBar0()
{
    auto menuBar = new FluPMenuBar;
    menuBar->setFixedHeight(30);

    auto fileAction = new FluAction("文件(&F)");
    fileAction->setAwesomeType(FluAwesomeType::FileExplorer);
    menuBar->addAction(fileAction);

    auto editAction = new FluAction("编辑(&E)");
    menuBar->addAction(editAction);

    // Help
    auto helpAction = new FluAction("帮助(&H)");
    menuBar->addAction(helpAction);

    m_vMainLayout->insertWidget(1, menuBar, Qt::AlignTop);
    resize(600, 400);
}

void FluMenuBarDemo::ppMenuBar1()
{
    auto menuBar = new FluPMenuBar;
    auto newFileAction = new FluAction("new");
    newFileAction->setAwesomeType(FluAwesomeType::FileExplorer);
    newFileAction->setShortcut(QKeySequence::New);
    auto openFileAction = new FluAction("Open");
    openFileAction->setShortcut(QKeySequence::Open);
    openFileAction->setAwesomeType(FluAwesomeType::OpenFile);
    auto saveFileAction = new FluAction("Save");
    saveFileAction->setShortcut(QKeySequence::Save);
    openFileAction->setAwesomeType(FluAwesomeType::Save);
    auto exitFileAction = new FluAction("Exit");
    exitFileAction->setShortcut(QKeySequence::Quit);

    auto fileMenu = new FluMenu(menuBar);
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
    menuBar->addAction(editMenu->menuAction());

    // Help
    auto aboutAction = new FluAction("About");
    auto helpMenu = new FluMenu(menuBar);
    helpMenu->setTitle("Help(&H)");
    helpMenu->addAction(aboutAction);

    menuBar->addAction(helpMenu->menuAction());
    // m_contentLayout->addWidget(menuBar);

     m_vMainLayout->insertWidget(1, menuBar, 0, Qt::AlignTop);

     QWidget* w = new QWidget;
     m_contentLayout->addWidget(w, 1);
    resize(600, 400);
}
