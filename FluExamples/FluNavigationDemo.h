#pragma once

#include "../FluControls/FluNavigationView.h"
#include <QFrame>
#include <QWidget>

class FluNavigationDemo : public QWidget {
  Q_OBJECT
public:
  FluNavigationDemo(QWidget *parent = nullptr) : QWidget(parent) {
    FluNavigationItem *item = new FluNavigationItem(
        FluIconUtils::getFluentIcon(FluAwesomeType::Design), "Design guidance",
        this);
    item->move(50, 50);

    FluNavigationItem *item1 = new FluNavigationItem(
        FluIconUtils::getFluentIcon(FluAwesomeType::FontSize), "Typography",
        item);
    FluNavigationItem *item2 = new FluNavigationItem(
        FluIconUtils::getFluentIcon(FluAwesomeType::EmojiTabSymbols), "Icons",
        item);
    FluNavigationItem *item3 = new FluNavigationItem(
        FluIconUtils::getFluentIcon(FluAwesomeType::Color), "Colors", item);
    FluNavigationItem *item4 = new FluNavigationItem(
        FluIconUtils::getFluentIcon(FluAwesomeType::SetHistoryStatus2),
        "Accessibility", item);

    FluNavigationItem *item5 =
        new FluNavigationItem("Screen reader support", item4);
    FluNavigationItem *item6 = new FluNavigationItem("Keyboard support", item4);
    FluNavigationItem *item7 = new FluNavigationItem("Color contrast", item4);

    item->addChildItem(item1);
    item->addChildItem(item2);
    item->addChildItem(item3);
    item->addChildItem(item4);
    item4->addChildItem(item5);
    item4->addChildItem(item6);
    item4->addChildItem(item7);

    resize(800, 600);

    setStyleSheet("background-color:rgb(255,255,255);");
  }
};
