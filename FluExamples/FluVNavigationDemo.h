#pragma once

#include "../FluControls/FluVNavigationView.h"
#include "../FluControls/FluVNavigationIconTextItem.h"
#include <QFrame>
#include "../FluControls/FluWidget.h"

class FluVNavigationDemo : public FluWidget
{
    Q_OBJECT
  public:
    FluVNavigationDemo(QWidget *parent = nullptr) : FluWidget(parent)
    {
        addDesignGuidaceText();

        resize(800, 600);
        setStyleSheet("background-color:rgb(255,255,255);");
    }

    void addDesignGuidaceIconText()
    {
        FluVNavigationIconTextItem *item = new FluVNavigationIconTextItem(FluAwesomeType::Design, "Design guidance", this);
        item->move(50, 50);

        FluVNavigationIconTextItem *item1 = new FluVNavigationIconTextItem(FluAwesomeType::FontSize, "Typography", item);
        FluVNavigationIconTextItem *item2 = new FluVNavigationIconTextItem(FluAwesomeType::EmojiTabSymbols, "Icons", item);
        FluVNavigationIconTextItem *item3 = new FluVNavigationIconTextItem(FluAwesomeType::Color, "Colors", item);
        FluVNavigationIconTextItem *item4 = new FluVNavigationIconTextItem(FluAwesomeType::SetHistoryStatus2, "Accessibility", item);

        FluVNavigationIconTextItem *item5 = new FluVNavigationIconTextItem("Screen reader support", item4);
        FluVNavigationIconTextItem *item6 = new FluVNavigationIconTextItem("Keyboard support", item4);
        FluVNavigationIconTextItem *item7 = new FluVNavigationIconTextItem("Color contrast", item4);

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
        FluVNavigationIconTextItem *item = new FluVNavigationIconTextItem("Design guidance", this);
        item->move(50, 50);

        FluVNavigationIconTextItem *item1 = new FluVNavigationIconTextItem("Typography", item);
        FluVNavigationIconTextItem *item2 = new FluVNavigationIconTextItem("Icons", item);
        FluVNavigationIconTextItem *item3 = new FluVNavigationIconTextItem("Colors", item);
        FluVNavigationIconTextItem *item4 = new FluVNavigationIconTextItem("Accessibility", item);

        FluVNavigationIconTextItem *item5 = new FluVNavigationIconTextItem("Screen reader support", item4);
        FluVNavigationIconTextItem *item6 = new FluVNavigationIconTextItem("Keyboard support", item4);
        FluVNavigationIconTextItem *item7 = new FluVNavigationIconTextItem("Color contrast", item4);

        item->addItem(item1);
        item->addItem(item2);
        item->addItem(item3);
        item->addItem(item4);
        item4->addItem(item5);
        item4->addItem(item6);
        item4->addItem(item7);
    }
};
