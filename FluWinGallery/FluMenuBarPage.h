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
        connect(FluThemeUtils::getUtils(), &FluThemeUtils::themeChanged, [=](FluTheme theme) { onThemeChanged(); });
    }

    void addSimpleMenuBar()
    {
        auto displayBox1 = new FluDisplayBox;
        displayBox1->setTitle("A Simple MenuBar");
        displayBox1->getCodeExpander()->setCodeByPath("../code/MenuBarPageCode1");
        displayBox1->setBodyWidgetFixedHeight(96);

        auto menuBar = new FluMenuBar;
        // menuBar->move(50, 50);

        auto newFileAction = new QAction("new");
        auto openFileAction = new QAction("Open");
        auto saveFileAction = new QAction("Save");
        auto exitFileAction = new QAction("Exit");

        auto fileMenu = new FluMenu(menuBar);
        fileMenu->setTitle("File");
        fileMenu->addAction(newFileAction);
        fileMenu->addAction(openFileAction);
        fileMenu->addAction(saveFileAction);
        fileMenu->addAction(exitFileAction);
        menuBar->addMenu(fileMenu);

        // undo cut copy paste
        auto undoEditAction = new QAction("Undo");
        auto cutEditAction = new QAction("Cut");
        auto copyEditAction = new QAction("Copy");
        auto pasteEditAction = new QAction("Paste");

        auto editMenu = new FluMenu(menuBar);
        editMenu->setTitle("Edit");
        editMenu->addAction(undoEditAction);
        editMenu->addAction(cutEditAction);
        editMenu->addAction(copyEditAction);
        editMenu->addAction(pasteEditAction);
        menuBar->addMenu(editMenu);

        // Help
        auto aboutAction = new QAction("About");
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
        displayBox1->getCodeExpander()->setCodeByPath("../code/MenuBarPageCode2");
        displayBox1->setBodyWidgetFixedHeight(96);

        auto menuBar = new FluMenuBar;
        // menuBar->move(50, 50);

        auto newFileAction = new QAction("New");
        auto openFileAction = new QAction("Open");
        auto saveFileAction = new QAction("Save");
        auto exitFileAction = new QAction("Exit");

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
        auto undoEditAction = new QAction("Undo");
        auto cutEditAction = new QAction("Cut");
        auto copyEditAction = new QAction("Copy");
        auto pasteEditAction = new QAction("Paste");

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
        auto aboutAction = new QAction("About");
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
