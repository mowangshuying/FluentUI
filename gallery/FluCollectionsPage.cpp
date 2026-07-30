#include "FluCollectionsPage.h"

FluCollectionsPage::FluCollectionsPage(QWidget* parent /*= nullptr*/) : FluATitlePage(parent)
{
    m_mainLayout->setContentsMargins(35, 35, 0, 35);
    m_titleLabel->setText(tr("Collections"));

    addHCard(FluIconUtils::getPixmap(("../res/ControlImages/FlipView.png")), tr("FlipView"), tr("Pressents a collection of items that the user can flip through, one item at a time."), "FlipViewPage");

    addHCard(FluIconUtils::getPixmap(("../res/ControlImages/ListView.png")), tr("ListView"), tr("A control that presents a collection of items in a vertical list."), "ListViewPage");

    addHCard(FluIconUtils::getPixmap(("../res/ControlImages/TreeView.png")), tr("TreeView"), tr("The TreeView control is a hierarchical list pattern with expanding and collapsing nodes that contain nested items."), "TreeViewPage");

    addHCard(FluIconUtils::getPixmap(("../res/ControlImages/GridView.png")), tr("TableView"), tr("A control taht presents a collection of items in rows and columns."), "TableViewPage");

    onThemeChanged();
}

void FluCollectionsPage::onThemeChanged()
{
    FluStyleSheetUtils::setQssByFileName("FluCollectionsPage.qss", this, FluThemeUtils::getUtils()->getTheme());
}
