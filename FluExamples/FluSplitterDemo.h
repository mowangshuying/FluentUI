#pragma once

#include <QWidget>
#include <QSplitter>
#include <QVBoxLayout>
#include <QFrame>
#include "FluTemplateDemo.h"
#include "../FluUtils/FluUtils.h"

class FluSplitterDemo : public FluTemplateDemo
{
	Q_OBJECT
  public:
	  FluSplitterDemo(QWidget* parent = nullptr) : FluTemplateDemo(parent)
	  {
		  //auto vLayout = new QVBoxLayout;
		  auto widget1 = new QFrame;
		  auto widget2 = new QFrame;

		  widget1->setStyleSheet("QFrame{border: 1px solid rgb(61,61,61);background-color:rgb(31,31,31);}");
		  widget2->setStyleSheet("QFrame{border: 1px solid rgb(61,61,61);background-color:rgb(31,31,31);}");

		  auto splitter = new QSplitter(Qt::Vertical, 0);
          splitter->addWidget(widget1);
		  splitter->addWidget(widget2);
		  splitter->setStretchFactor(0,3);
		  splitter->setStretchFactor(1,7);
		  splitter->setStyleSheet("background-color:rgb(16,16,16)");

		  m_contentLayout->addWidget(splitter);
          //setLayout(vLayout);
          FluThemeUtils::getUtils()->setTheme(FluTheme::Dark);
		  resize(800, 600);
      }
};
