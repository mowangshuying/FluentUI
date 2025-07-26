#include "FluMenuBarPage.h"
#include "../FluControls/FluPushButton.h"
#include "../FluControls/FluRoundMenu.h"

FluMenuBarPage::FluMenuBarPage(QWidget* parent /*= nullptr*/) : FluAEmptyPage(parent)
{
    m_mainLayout->setAlignment(Qt::AlignTop);
    m_titleLabel->setText(tr("MenuBar"));
    m_infoLabel->setText(tr("The Menubar simplifies the creation of basic applications by providing a set of menus at the top of the app or window."));

    addSimpleMenuBar();

    addMenuBarWithAccelerators();

    onThemeChanged();

    addRoundMenu();
}

void FluMenuBarPage::addSimpleMenuBar()
{
    auto displayBox1 = new FluDisplayBox;
    displayBox1->setTitle(tr("A Simple MenuBar"));
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

void FluMenuBarPage::addRoundMenu()
{
    auto displayBox = new FluDisplayBox;
    displayBox->setTitle(tr("A Round Menu"));
    displayBox->getCodeExpander()->setCodeByPath("../code/MenuBarPageCode3.md");

    auto btn = new FluPushButton;
    btn->setText(tr("show menu"));
    btn->setFixedWidth(120);

    FluRoundMenu* roundMenu = new FluRoundMenu("", FluAwesomeType::None, this);
    auto copyAction = new FluAction(FluAwesomeType::Copy, tr("Copy"));
    roundMenu->addAction(copyAction);

    auto cutAction = new FluAction(FluAwesomeType::Cut, tr("Cut"));
    roundMenu->addAction(cutAction);

    auto subRoundMenu = new FluRoundMenu(tr("Add to"), FluAwesomeType::Add);
    auto musicAction = new FluAction(tr("Music"));
    auto videoAction = new FluAction(tr("Video"));

    QList<QAction*> actions;
    actions.append(musicAction);
    actions.append(videoAction);
    subRoundMenu->addActions(actions);
    roundMenu->addMenu(subRoundMenu);

    auto pasteAction = new FluAction(FluAwesomeType::Paste, tr("Paste"));
    roundMenu->addAction(pasteAction);

    auto undoAction = new FluAction(FluAwesomeType::Undo, tr("Undo"));
    roundMenu->addAction(undoAction);

    roundMenu->addSeparator();

    auto selectAllAction = new FluAction(tr("Select all"));
    // selectAllAction->setShortcut(QKeySequence("Ctrl+A"));
    roundMenu->addAction(selectAllAction);

    auto settingAction = new FluAction(FluAwesomeType::Settings, tr("Setting"));
    auto helpAction = new FluAction(FluAwesomeType::Help, tr("Help"));
    auto feedbackAction = new FluAction(FluAwesomeType::Feedback, tr("Feedback"));

    // settingAction->setShortcut(QKeySequence("Ctrl+S"));
    // helpAction->setShortcut(QKeySequence("Ctrl+H"));
    // feedbackAction->setShortcut(QKeySequence("Ctrl+F"));

    roundMenu->addAction(settingAction);
    roundMenu->addAction(helpAction);
    roundMenu->addAction(feedbackAction);

    displayBox->getBodyLayout()->addWidget(btn);
    m_vScrollView->getMainLayout()->addWidget(displayBox, 0, Qt::AlignTop);

    connect(btn, &FluPushButton::clicked, this, [=]() {
        auto gp = btn->mapToGlobal(QPoint(btn->width() + 5, -100));
        roundMenu->exec(gp, true, FluMenuAniType::dropDown);
    });
}

void FluMenuBarPage::onThemeChanged()
{
    FluStyleSheetUitls::setQssByFileName("FluMenuBarPage.qss", this, FluThemeUtils::getUtils()->getTheme());
}
