#include "FluRoundMenuDemo.h"

FluRoundMenuDemo::FluRoundMenuDemo(QWidget* parent /*= nullptr*/) : FluTemplateDemo(parent)
{
    m_label = new QLabel("Right click your mouse!", this);
    m_label->setAlignment(Qt::AlignCenter);
    m_contentLayout->addWidget(m_label);
    resize(400, 400);
}

void FluRoundMenuDemo::contextMenuEvent(QContextMenuEvent* event)
{
    FluRoundMenu* roundMenu = new FluRoundMenu("", this);
    auto copyAction = new QAction(FluIconUtils::getFluentIcon(FluAwesomeType::Copy), "Copy");
    roundMenu->addAction(copyAction);

    auto cutAction = new QAction(FluIconUtils::getFluentIcon(FluAwesomeType::Cut), "Cut");
    roundMenu->addAction(cutAction);

    auto subRoundMenu = new FluRoundMenu("Add to", this);
    subRoundMenu->setIcon(FluIconUtils::getFluentIconPixmap(FluAwesomeType::Add));
    auto musicAction = new QAction(FluIconUtils::getFluentIcon(FluAwesomeType::MusicAlbum), "Music");
    auto videoAction = new QAction(FluIconUtils::getFluentIcon(FluAwesomeType::Video), "Video");
    
    QList<QAction*> actions;
    actions.append(musicAction);
    actions.append(videoAction);
    subRoundMenu->addActions(actions);
    roundMenu->addMenu(subRoundMenu);

    auto pasteAction = new QAction(FluIconUtils::getFluentIcon(FluAwesomeType::Paste), "Paste");
    roundMenu->addAction(pasteAction);

    auto undoAction = new QAction(FluIconUtils::getFluentIcon(FluAwesomeType::Undo), "Undo");
    roundMenu->addAction(undoAction);

    roundMenu->addSeparator();

    auto selectAllAction = new QAction("Select all");
    selectAllAction->setShortcut(QKeySequence("Ctrl+A"));
    roundMenu->addAction(selectAllAction);

    auto settingAction = new QAction(FluIconUtils::getFluentIcon(FluAwesomeType::Settings), "Setting");
    auto helpAction = new QAction(FluIconUtils::getFluentIcon(FluAwesomeType::Help), "Help");
    auto feedbackAction = new QAction(FluIconUtils::getFluentIcon(FluAwesomeType::Feedback), "Feedback");

    settingAction->setShortcut(QKeySequence("Ctrl+S"));
    helpAction->setShortcut(QKeySequence("Ctrl+H"));
    feedbackAction->setShortcut(QKeySequence("Ctrl+F"));

    roundMenu->addAction(settingAction);
    roundMenu->addAction(helpAction);
    roundMenu->addAction(feedbackAction);

    roundMenu->exec(event->globalPos(), true, FluMenuAniType::dropDown);
}
