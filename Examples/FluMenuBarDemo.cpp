#include "FluMenuBarDemo.h"
#include "../Controls/FluRoundMenu.h"
#include "../Controls/FluPMenuBar.h"
#include "../Controls/FluPMenu.h"
#include <FramelessHelper/Widgets/standardtitlebar.h>
#include <FramelessHelper/Widgets/framelesswidgetshelper.h>

FRAMELESSHELPER_USE_NAMESPACE
FluMenuBarDemo::FluMenuBarDemo(QWidget* parent /*= nullptr*/) : FluTemplateDemo(parent)
{
    setWindowTitle("");
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
    auto hLayout = (QHBoxLayout*)m_titleBar->layout();
    hLayout->insertSpacing(0, 30);
    hLayout->insertWidget(1, menuBar, 1, Qt::AlignLeft | Qt::AlignTop);
    FramelessWidgetsHelper::get(this)->setHitTestVisible(menuBar);

    auto newFileAction = new FluAction("New");
    newFileAction->setShortcut(QKeySequence::New);

    auto openFileMenu = new FluPMenu(menuBar);
    openFileMenu->setTitle("Open");
    auto openFileAction1 = new FluAction("OpenFile1");
    openFileMenu->addAction(openFileAction1);
    auto openFileAction2 = new FluAction("OpenFile2");
    openFileMenu->addAction(openFileAction2);
    auto openFIleAction3 = new FluAction("OpenFile3");
    openFileMenu->addAction(openFIleAction3);
    auto openFileAction4 = new FluAction("OpenFile4");
    openFileMenu->addAction(openFileAction4);
    auto openFileAction5 = new FluAction("OpenFile5");
    openFileAction5->setShortcut(QKeySequence::Open);
    openFileMenu->addAction(openFileAction5);

    auto saveFileAction = new FluAction("Save");
    saveFileAction->setShortcut(QKeySequence::Save);
    saveFileAction->setAwesomeType(FluAwesomeType::Save);
    auto exitFileAction = new FluAction("Exit");
    exitFileAction->setShortcut(QKeySequence::Quit);
    exitFileAction->setAwesomeType(FluAwesomeType::QuarentinedItems);

    auto fileMenu = new FluPMenu(menuBar);
    fileMenu->setTitle("File(&F)");
    fileMenu->addAction(newFileAction);
    fileMenu->addAction(openFileMenu->menuAction());
    fileMenu->addAction(saveFileAction);
    fileMenu->addAction(exitFileAction);

    menuBar->addAction(fileMenu->menuAction());

    // undo cut copy paste
    auto undoEditAction = new FluAction("Undo");
    undoEditAction->setShortcut(QKeySequence::Undo);
    auto cutEditAction = new FluAction("Cut");
    cutEditAction->setShortcut(QKeySequence::Cut);
    auto copyEditAction = new FluAction("Copy");
    copyEditAction->setShortcut(QKeySequence::Copy);
    auto pasteEditAction = new FluAction("Paste");
    pasteEditAction->setShortcut(QKeySequence::Paste);

    auto editMenu = new FluPMenu(menuBar);
    editMenu->setTitle("Edit(&E)");
    editMenu->addAction(undoEditAction);
    editMenu->addAction(cutEditAction);
    editMenu->addAction(copyEditAction);
    editMenu->addAction(pasteEditAction);
    menuBar->addAction(editMenu->menuAction());

    // Help
    auto aboutAction = new FluAction("About");
    auto helpMenu = new FluPMenu(menuBar);
    helpMenu->setTitle("Help(&H)");
    helpMenu->addAction(aboutAction);

    menuBar->addAction(helpMenu->menuAction());
    resize(600, 400);
}
