#include "FluMenuBarPage.h"

FluMenuBarPage::FluMenuBarPage(QWidget* parent /*= nullptr*/) : FluAEmptyPage(parent)
{
    m_mainLayout->setAlignment(Qt::AlignTop);
    m_titleLabel->setText(tr("MenuBar"));
    m_infoLabel->setText(tr("The Menubar simplifies the creation of basic applications by providing a set of menus at the top of the app or window."));

    addSimpleMenuBar();

    addMenuBarWithAccelerators();

    onThemeChanged();
}

void FluMenuBarPage::addSimpleMenuBar()
{
    auto displayBox1 = new FluDisplayBox;
    displayBox1->setTitle("A Simple MenuBar");
    displayBox1->getCodeExpander()->setCodeByPath("../code/MenuBarPageCode1.md");
    displayBox1->setBodyWidgetFixedHeight(96);

    auto menuBar = new FluMenuBar;
    // menuBar->move(50, 50);

    auto newFileAction = new FluAction(tr("new"));
    auto openFileAction = new FluAction(tr("Open"));
    auto saveFileAction = new FluAction(tr("Save"));
    auto exitFileAction = new FluAction(tr("Exit"));

    auto fileMenu = new FluMenu(menuBar);
    fileMenu->setTitle(tr("File"));
    fileMenu->addAction(newFileAction);
    fileMenu->addAction(openFileAction);
    fileMenu->addAction(saveFileAction);
    fileMenu->addAction(exitFileAction);
    menuBar->addMenu(fileMenu);

    // undo cut copy paste
    auto undoEditAction = new FluAction(tr("Undo"));
    auto cutEditAction = new FluAction(tr("Cut"));
    auto copyEditAction = new FluAction(tr("Copy"));
    auto pasteEditAction = new FluAction(tr("Paste"));

    auto editMenu = new FluMenu(menuBar);
    editMenu->setTitle(tr("Edit"));
    editMenu->addAction(undoEditAction);
    editMenu->addAction(cutEditAction);
    editMenu->addAction(copyEditAction);
    editMenu->addAction(pasteEditAction);
    menuBar->addMenu(editMenu);

    // Help
    auto aboutAction = new FluAction(tr("About"));
    auto helpMenu = new FluMenu(menuBar);
    helpMenu->setTitle(tr("Help"));
    helpMenu->addAction(aboutAction);
    menuBar->addMenu(helpMenu);

    displayBox1->getBodyLayout()->addWidget(menuBar);
    m_vScrollView->getMainLayout()->addWidget(displayBox1, 0, Qt::AlignTop);
}

void FluMenuBarPage::addMenuBarWithAccelerators()
{
    auto displayBox1 = new FluDisplayBox;
    displayBox1->setTitle(tr("MenuBar with keyboard accelerators"));
    displayBox1->getCodeExpander()->setCodeByPath("../code/MenuBarPageCode2.md");
    displayBox1->setBodyWidgetFixedHeight(96);

    auto menuBar = new FluMenuBar;
    // menuBar->move(50, 50);

    auto newFileAction = new FluAction(tr("New"));
    auto openFileAction = new FluAction(tr("Open"));
    auto saveFileAction = new FluAction(tr("Save"));
    auto exitFileAction = new FluAction(tr("Exit"));

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
    auto undoEditAction = new FluAction(tr("Undo"));
    auto cutEditAction = new FluAction(tr("Cut"));
    auto copyEditAction = new FluAction(tr("Copy"));
    auto pasteEditAction = new FluAction(tr("Paste"));

    undoEditAction->setShortcut(QKeySequence::Undo);
    cutEditAction->setShortcut(QKeySequence::Cut);
    copyEditAction->setShortcut(QKeySequence::Copy);
    pasteEditAction->setShortcut(QKeySequence::Paste);

    auto editMenu = new FluMenu(menuBar);
    editMenu->setTitle(tr("Edit"));
    editMenu->addAction(undoEditAction);
    editMenu->addAction(cutEditAction);
    editMenu->addAction(copyEditAction);
    editMenu->addAction(pasteEditAction);
    menuBar->addMenu(editMenu);

    // Help
    auto aboutAction = new FluAction(tr("About"));
    aboutAction->setShortcut(QKeySequence("Ctrl+L"));

    auto helpMenu = new FluMenu(menuBar);
    helpMenu->setTitle(tr("Help"));
    helpMenu->addAction(aboutAction);
    menuBar->addMenu(helpMenu);

    displayBox1->getBodyLayout()->addWidget(menuBar);
    m_vScrollView->getMainLayout()->addWidget(displayBox1, 0, Qt::AlignTop);
}

void FluMenuBarPage::onThemeChanged()
{
    if (FluThemeUtils::isLightTheme())
    {
        FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluMenuBarPage.qss", this);
    }
    else
    {
        FluStyleSheetUitls::setQssByFileName("../StyleSheet/dark/FluMenuBarPage.qss", this);
    }
}
