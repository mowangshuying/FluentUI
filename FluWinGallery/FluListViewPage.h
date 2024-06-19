#pragma once

#include "FluAEmptyPage.h"
#include "../FluControls/FluDisplayBox.h"
#include "../FluControls/FluListView.h"

class FluListViewPage : public FluAEmptyPage
{
    Q_OBJECT
  public:
    FluListViewPage(QWidget* parent = nullptr) : FluAEmptyPage(parent)
    {
        m_mainLayout->setAlignment(Qt::AlignTop);
        m_titleLabel->setText("ListView");
        m_infoLabel->setText("The ListView lets you show a collection of items in a list that scrolls vertically.");

        auto displayBox1 = new FluDisplayBox;
        displayBox1->setTitle("Basic ListView with Simple DateTemplate");
        displayBox1->getCodeExpander()->setCodeByPath("../code/ListViewPageCode1.md");
        displayBox1->setBodyWidgetFixedHeight(480);

        FluListView* listView = new FluListView(displayBox1);

        listView->setFixedSize(350, 400);
        listView->addItem("Kendall Collins");
        listView->addItem("Henry Ross");
        listView->addItem("Vance DeLeon");
        listView->addItem("Victoria Burke");

        listView->addItem("Amber Rodriguez");
        listView->addItem("Amari Rivera");
        listView->addItem("Jessie lrwin");
        listView->addItem("Quinn Campbell");

        listView->addItem("Olivia Wilson");
        listView->addItem("Ana Bowman");
        listView->addItem("Shawn Hughes");
        listView->addItem("Oscar Ward");

        listView->addItem("Madison Butler");
        listView->addItem("Graham Barnes");
        listView->addItem("Anthony lvanov");
        listView->addItem("Michael peltier");

        // listView->move(50, 80);

        displayBox1->getBodyLayout()->addWidget(listView);

        m_vScrollView->getMainLayout()->addWidget(displayBox1, 0, Qt::AlignTop);
        FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluListViewPage.qss", this);
    }

  public slots:
    void onThemeChanged()
    {
        if (FluThemeUtils::getUtils()->getTheme() == FluTheme::Light)
        {
            FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluListViewPage.qss", this);
        }
        else
        {
            FluStyleSheetUitls::setQssByFileName("../StyleSheet/dark/FluListViewPage.qss", this);
        }
    }
};
