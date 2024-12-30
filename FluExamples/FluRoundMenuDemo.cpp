#include "FluRoundMenuDemo.h"

FluRoundMenuDemo::FluRoundMenuDemo(QWidget* parent /*= nullptr*/) : FluTemplateDemo(parent)
{
    //FluThemeUtils::getUtils()->setTheme(FluTheme::Dark);
    m_label = new QLabel("Right click your mouse!", this);
    m_label->setAlignment(Qt::AlignCenter);
    m_contentLayout->addWidget(m_label);
    resize(400, 400);
}

void FluRoundMenuDemo::contextMenuEvent(QContextMenuEvent* event)
{
    FluRoundMenu* roundMenu = new FluRoundMenu("", FluAwesomeType::None,  this);
    roundMenu->setMaxVisibleItems(5);
    auto copyAction = new FluAction(FluAwesomeType::Copy, "Copy");
    roundMenu->addAction(copyAction);

    auto cutAction = new FluAction(FluAwesomeType::Cut, "Cut");
    roundMenu->addAction(cutAction);

    auto subRoundMenu = new FluRoundMenu("Add to", FluAwesomeType::Add );
    //subRoundMenu->setIcon(FluIconUtils::getFluentIconPixmap(FluAwesomeType::Add, FluTheme::Dark));
    auto musicAction = new FluAction("Music");
    auto videoAction = new FluAction("Video");
    
    QList<QAction*> actions;
    actions.append(musicAction);
    actions.append(videoAction);
    subRoundMenu->addActions(actions);
    roundMenu->addMenu(subRoundMenu);

    auto pasteAction = new FluAction(FluAwesomeType::Paste, "Paste");
    roundMenu->addAction(pasteAction);

    auto undoAction = new FluAction(FluAwesomeType::Undo, "Undo");
    roundMenu->addAction(undoAction);

    roundMenu->addSeparator();

    auto selectAllAction = new FluAction("Select all");
    selectAllAction->setShortcut(QKeySequence("Ctrl+A"));
    roundMenu->addAction(selectAllAction);

    auto settingAction = new FluAction(FluAwesomeType::Settings, "Setting");
    auto helpAction = new FluAction(FluAwesomeType::Help, "Help");
    auto feedbackAction = new FluAction(FluAwesomeType::Feedback, "Feedback");

    settingAction->setShortcut(QKeySequence("Ctrl+S"));
    helpAction->setShortcut(QKeySequence("Ctrl+H"));
    feedbackAction->setShortcut(QKeySequence("Ctrl+F"));

    roundMenu->addAction(settingAction);
    roundMenu->addAction(helpAction);
    roundMenu->addAction(feedbackAction);

    roundMenu->exec(event->globalPos(), true, FluMenuAniType::dropDown);
}
