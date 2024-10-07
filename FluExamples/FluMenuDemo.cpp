#include "FluMenuDemo.h"

FluMenuDemo::FluMenuDemo(QWidget* parent /*= nullptr*/) : FluWidget(parent)
{
    m_menu = new FluMenu;

    auto action1 = new FluAction(FluIconUtils::getFluentIcon(FluAwesomeType::Save), "Save");
    action1->setShortcut(QKeySequence::Save);
    m_menu->addAction(action1);

    auto action2 = new FluAction(FluIconUtils::getFluentIcon(FluAwesomeType::Copy), "Copy");
    action2->setShortcut(QKeySequence::Copy);
    m_menu->addAction(action2);

    auto action3 = new FluAction(FluIconUtils::getFluentIcon(FluAwesomeType::Delete), "Delete");
    action3->setShortcut(QKeySequence::Delete);
    m_menu->addAction(action3);

    m_menu->addSeparator();

    auto subMenu = new FluMenu;
    subMenu->setTitle("More");
    subMenu->setIcon(FluIconUtils::getFluentIcon(FluAwesomeType::More));
    m_menu->addMenu(subMenu);

    auto action5 = new FluAction(FluIconUtils::getFluentIcon(FluAwesomeType::Save), "Save");
    action5->setShortcut(QKeySequence::Save);
    subMenu->addAction(action5);

    auto action6 = new FluAction(FluIconUtils::getFluentIcon(FluAwesomeType::Copy), "Copy");
    action6->setShortcut(QKeySequence::Copy);
    subMenu->addAction(action6);

    auto action7 = new FluAction(FluIconUtils::getFluentIcon(FluAwesomeType::Delete), "Delete");
    action7->setShortcut(QKeySequence::Delete);
    subMenu->addAction(action7);

    setStyleSheet("background-color:white;");
}

void FluMenuDemo::contextMenuEvent(QContextMenuEvent* event)
{
    m_menu->exec(event->globalPos());
}
