#pragma once

#include "FluTemplateDemo.h"
#include "../FluControls/FluCommandBar.h"
#include "../FluControls/FluCommandBarIconTextItem.h"
#include "../FluControls/FluCommandBarIconItem.h"

class FluCommandBarDemo : public FluTemplateDemo
{
    Q_OBJECT
  public:
    FluCommandBarDemo(QWidget* parent = nullptr) : FluTemplateDemo(parent)
    {
        // m_contentLayout->setAlignment(Qt::AlignCenter);

        auto commandBar = new FluCommandBar(this);
        commandBar->setHasMoreBtn(true);
        commandBar->move(200, 200);

        auto addBarItem = new FluCommandBarIconTextItem(FluAwesomeType::Add, tr("Add"), commandBar);
        commandBar->addBarItem(addBarItem);

        auto zoomInItem = new FluCommandBarIconTextItem(FluAwesomeType::ZoomIn, tr("ZoomIn"));
        commandBar->addBarItem(zoomInItem);

        auto zoomOutItem = new FluCommandBarIconTextItem(FluAwesomeType::ZoomOut, tr("ZoomOut"));
        commandBar->addBarItem(zoomOutItem);

        auto editBarItem = new FluCommandBarIconTextItem(FluAwesomeType::Edit, tr("Edit"), commandBar);
        commandBar->addBarItem(editBarItem);

        auto shareBarItem = new FluCommandBarIconTextItem(FluAwesomeType::Share, tr("Share"), commandBar);
        commandBar->addBarItem(shareBarItem);

        auto roundMenu = commandBar->getMoreBtn()->getRoundMenu();
        auto settingsAction = new FluAction(FluAwesomeType::Settings, tr("Settings"));
        settingsAction->setShortcut(QKeySequence("Ctrl+l"));
        roundMenu->addAction(settingsAction);

        auto button1Action = new FluAction(FluAwesomeType::Add, tr("Button1"));
        button1Action->setShortcut(QKeySequence("Ctrl+N)"));
        roundMenu->addAction(button1Action);

        auto button2Action = new FluAction(FluAwesomeType::Delete, tr("Button2"));
        button2Action->setShortcut(QKeySequence("Delete"));
        roundMenu->addAction(button2Action);

        auto button3Action = new FluAction(FluAwesomeType::Font, tr("Button3"));
        button3Action->setShortcut(QKeySequence("Ctrl+-"));
        roundMenu->addAction(button3Action);

        auto button4Action = new FluAction(FluAwesomeType::Font, tr("Button4"));
        button4Action->setShortcut(QKeySequence("Ctrl++"));
        roundMenu->addAction(button4Action);

        // auto moreBarItem = new FluCommandBarIconItem(FluAwesomeType::More);
    }
};
