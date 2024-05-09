#pragma once

#include "../FluControls/FluNavigationView.h"
#include "../FluControls/FluNavigationIconTextItem.h"
#include <QFrame>
#include <QWidget>

class FluNavigationDemo : public QWidget
{
    Q_OBJECT
  public:
    FluNavigationDemo(QWidget *parent = nullptr) : QWidget(parent)
    {
        addDesignGuidaceText();

        resize(800, 600);
        setStyleSheet("background-color:rgb(255,255,255);");
        
    }

    void addDesignGuidaceIconText()
    {
        FluNavigationIconTextItem *item = new FluNavigationIconTextItem(FluAwesomeType::Design, "Design guidance", this);
        item->move(50, 50);

        FluNavigationIconTextItem *item1 = new FluNavigationIconTextItem(FluAwesomeType::FontSize, "Typography", item);
        FluNavigationIconTextItem *item2 = new FluNavigationIconTextItem(FluAwesomeType::EmojiTabSymbols, "Icons", item);
        FluNavigationIconTextItem *item3 = new FluNavigationIconTextItem(FluAwesomeType::Color, "Colors", item);
        FluNavigationIconTextItem *item4 = new FluNavigationIconTextItem(FluAwesomeType::SetHistoryStatus2, "Accessibility", item);

        FluNavigationIconTextItem *item5 = new FluNavigationIconTextItem("Screen reader support", item4);
        FluNavigationIconTextItem *item6 = new FluNavigationIconTextItem("Keyboard support", item4);
        FluNavigationIconTextItem *item7 = new FluNavigationIconTextItem("Color contrast", item4);

        item->addItem(item1);
        item->addItem(item2);
        item->addItem(item3);
        item->addItem(item4);
        item4->addItem(item5);
        item4->addItem(item6);
        item4->addItem(item7);
    }

    void addDesignGuidaceText()
    {
        FluNavigationIconTextItem *item = new FluNavigationIconTextItem("Design guidance", this);
        item->move(50, 50);

        FluNavigationIconTextItem *item1 = new FluNavigationIconTextItem( "Typography", item);
        FluNavigationIconTextItem *item2 = new FluNavigationIconTextItem( "Icons", item);
        FluNavigationIconTextItem *item3 = new FluNavigationIconTextItem("Colors", item);
        FluNavigationIconTextItem *item4 = new FluNavigationIconTextItem("Accessibility", item);

        FluNavigationIconTextItem *item5 = new FluNavigationIconTextItem("Screen reader support", item4);
        FluNavigationIconTextItem *item6 = new FluNavigationIconTextItem("Keyboard support", item4);
        FluNavigationIconTextItem *item7 = new FluNavigationIconTextItem("Color contrast", item4);

        item->addItem(item1);
        item->addItem(item2);
        item->addItem(item3);
        item->addItem(item4);
        item4->addItem(item5);
        item4->addItem(item6);
        item4->addItem(item7);
    }
};
