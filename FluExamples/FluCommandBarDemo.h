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
              //m_contentLayout->setAlignment(Qt::AlignCenter);

              auto commandBar = new FluCommandBar(this);
              commandBar->setHasMoreBtn(true);
              commandBar->move(200, 200);
			  //m_contentLayout->addWidget(commandBar);

			  //auto emojiBarItem = new FluCommandBarIconTextItem(FluAwesomeType::Emoji, tr("Emoji"), commandBar);
             // commandBar->addBarItem(emojiBarItem);

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

			  //auto moreBarItem = new FluCommandBarIconItem(FluAwesomeType::More);
	  }
};
