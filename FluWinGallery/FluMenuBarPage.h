#pragma once

#include "FluAEmptyPage.h"
#include "../FluUtils/FluUtils.h"
#include "../FluControls/FluDisplayBox.h"
#include "../FluControls/FluMenu.h"
#include "../FluControls/FluMenuBar.h"
#include "../FluControls/FluVScrollView.h"

class FluMenuBarPage : public FluAEmptyPage
{
    Q_OBJECT
  public:
    FluMenuBarPage(QWidget* parent = nullptr) : FluAEmptyPage(parent)
    {
        m_mainLayout->setAlignment(Qt::AlignTop);
        m_titleLabel->setText("MenuBar");
        m_infoLabel->setText("The Menubar simplifies the creation of basic applications by providing a set of menus at the top of the app or window.");

        addSimpleMenuBar();

        addMenuBarWithAccelerators();

        FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluMenuBarPage.qss", this);
    }

    void addSimpleMenuBar()
    {
        auto displayBox1 = new FluDisplayBox;
        displayBox1->setTitle("A Simple MenuBar");
        displayBox1->getCodeExpander()->setCodeByPath("../code/MenuBarPageCode1.md");
        displayBox1->setBodyWidgetFixedHeight(96);

        auto menuBar = new FluMenuBar;
        // menuBar->move(50, 50);

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
        menuBar->addMenu(fileMenu);

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
        menuBar->addMenu(editMenu);

        // Help
        auto aboutAction = new FluAction("About");
        auto helpMenu = new FluMenu(menuBar);
        helpMenu->setTitle("Help");
        helpMenu->addAction(aboutAction);
        menuBar->addMenu(helpMenu);

        displayBox1->getBodyLayout()->addWidget(menuBar);
        m_vScrollView->getMainLayout()->addWidget(displayBox1, 0, Qt::AlignTop);
    }

    void addMenuBarWithAccelerators()
    {
        auto displayBox1 = new FluDisplayBox;
        displayBox1->setTitle("MenuBar with keyboard accelerators");
        displayBox1->getCodeExpander()->setCodeByPath("../code/MenuBarPageCode2.md");
        displayBox1->setBodyWidgetFixedHeight(96);

        auto menuBar = new FluMenuBar;
        // menuBar->move(50, 50);

        auto newFileAction = new FluAction("New");
        auto openFileAction = new FluAction("Open");
        auto saveFileAction = new FluAction("Save");
        auto exitFileAction = new FluAction("Exit");

        newFileAction->setShortcut(QKeySequence::New);
        openFileAction->setShortcut(QKeySequence::Open);
        saveFileAction->setShortcut(QKeySequence::Save);
        exitFileAction->setShortcut(QKeySequence("Ctrl+E"));

        auto fileMenu = new FluMenu(menuBar);
        fileMenu->setTitle("File");
        fileMenu->addAction(newFileAction);
        fileMenu->addAction(openFileAction);
        fileMenu->addAction(saveFileAction);
        fileMenu->addAction(exitFileAction);
        menuBar->addMenu(fileMenu);

        // undo cut copy paste
        auto undoEditAction = new FluAction("Undo");
        auto cutEditAction = new FluAction("Cut");
        auto copyEditAction = new FluAction("Copy");
        auto pasteEditAction = new FluAction("Paste");

        undoEditAction->setShortcut(QKeySequence::Undo);
        cutEditAction->setShortcut(QKeySequence::Cut);
        copyEditAction->setShortcut(QKeySequence::Copy);
        pasteEditAction->setShortcut(QKeySequence::Paste);

        auto editMenu = new FluMenu(menuBar);
        editMenu->setTitle("Edit");
        editMenu->addAction(undoEditAction);
        editMenu->addAction(cutEditAction);
        editMenu->addAction(copyEditAction);
        editMenu->addAction(pasteEditAction);
        menuBar->addMenu(editMenu);

        // Help
        auto aboutAction = new FluAction("About");
        aboutAction->setShortcut(QKeySequence("Ctrl+L"));

        auto helpMenu = new FluMenu(menuBar);
        helpMenu->setTitle("Help");
        helpMenu->addAction(aboutAction);
        menuBar->addMenu(helpMenu);

        displayBox1->getBodyLayout()->addWidget(menuBar);
        m_vScrollView->getMainLayout()->addWidget(displayBox1, 0, Qt::AlignTop);
    }

  public slots:
    void onThemeChanged()
    {
        if (FluThemeUtils::getUtils()->getTheme() == FluTheme::Light)
        {
            FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluMenuBarPage.qss", this);
        }
        else
        {
            FluStyleSheetUitls::setQssByFileName("../StyleSheet/dark/FluMenuBarPage.qss", this);
        }
    }

  protected:
};
