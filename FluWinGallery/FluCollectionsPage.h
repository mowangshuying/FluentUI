#pragma once


#include <QWidget>
#include <QLabel>
#include "../FluControls/FluFWScrollView.h"
#include "FluATitlePage.h"
#include "FluATitlePage.h"
#include "../FluControls/FluHCard.h"

class FluCollectionsPage : public  FluATitlePage
{
	Q_OBJECT
  public:
	  FluCollectionsPage(QWidget* parent = nullptr) : FluATitlePage(parent)
	  {
              m_vMainLayout->setContentsMargins(35, 35, 0, 35);
              m_titleLabel->setText("Collections");

			  auto flipViewCard = new FluHCard(QPixmap("../res/ControlImages/FlipView.png"), "FlipView", "Pressents a collection of items that the user can flip through, one item at a time.");
              getFWScrollView()->getMainLayout()->addWidget(flipViewCard);

			   auto listViewCard = new FluHCard(QPixmap("../res/ControlImages/ListView.png"), "ListView", "A control that presents a collection of items in a vertical list.");
              getFWScrollView()->getMainLayout()->addWidget(listViewCard);

			   auto treeViewCard = new FluHCard(QPixmap("../res/ControlImages/TreeView.png"), "TreeView", "The TreeView control is a hierarchical list pattern with expanding and collapsing nodes that contain nested items.");
              getFWScrollView()->getMainLayout()->addWidget(treeViewCard);
	  }
};
