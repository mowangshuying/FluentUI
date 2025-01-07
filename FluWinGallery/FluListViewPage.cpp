#include "FluListViewPage.h"

FluListViewPage::FluListViewPage(QWidget* parent /*= nullptr*/) : FluAEmptyPage(parent)
{
    m_mainLayout->setAlignment(Qt::AlignTop);
    m_titleLabel->setText(tr("ListView"));
    m_infoLabel->setText(tr("The ListView lets you show a collection of items in a list that scrolls vertically."));

    auto displayBox1 = new FluDisplayBox;
    displayBox1->setTitle(tr("Basic ListView with Simple DateTemplate"));
    displayBox1->getCodeExpander()->setCodeByPath("../code/ListViewPageCode1.md");
    displayBox1->setBodyWidgetFixedHeight(480);

    FluListView* listView = new FluListView(displayBox1);

    listView->setFixedSize(350, 400);
    listView->addItem(tr("Kendall Collins"));
    listView->addItem(tr("Henry Ross"));
    listView->addItem(tr("Vance DeLeon"));
    listView->addItem(tr("Victoria Burke"));

    listView->addItem(tr("Amber Rodriguez"));
    listView->addItem(tr("Amari Rivera"));
    listView->addItem(tr("Jessie lrwin"));
    listView->addItem(tr("Quinn Campbell"));

    listView->addItem(tr("Olivia Wilson"));
    listView->addItem(tr("Ana Bowman"));
    listView->addItem(tr("Shawn Hughes"));
    listView->addItem(tr("Oscar Ward"));

    listView->addItem(tr("Madison Butler"));
    listView->addItem(tr("Graham Barnes"));
    listView->addItem(tr("Anthony lvanov"));
    listView->addItem(tr("Michael peltier"));

    // listView->move(50, 80);

    displayBox1->getBodyLayout()->addWidget(listView);

    m_vScrollView->getMainLayout()->addWidget(displayBox1, 0, Qt::AlignTop);
    onThemeChanged();
}

void FluListViewPage::onThemeChanged()
{
    if (FluThemeUtils::isLightTheme())
    {
        FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluListViewPage.qss", this);
    }
    else
    {
        FluStyleSheetUitls::setQssByFileName("../StyleSheet/dark/FluListViewPage.qss", this);
    }
}
