#pragma once

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QStyleOption>
#include <QPainter>

#include "../FluUtils/FluUtils.h"
#include "../FluControls/FluVScrollView.h"

class FluSettingPage : public QWidget
{
	Q_OBJECT
  public:
	  FluSettingPage(QWidget* parent = nullptr) : QWidget(parent)
	  {
              m_mainLayout = new QVBoxLayout;
              m_mainLayout->setAlignment(Qt::AlignTop);
              setLayout(m_mainLayout);

              m_mainLayout->setContentsMargins(35, 35, 35, 35);

              m_titleLabel = new QLabel;
              m_titleLabel->setObjectName("titleLabel");
              m_titleLabel->setText("Settings");
              m_mainLayout->addWidget(m_titleLabel);

              m_vScrollView = new FluVScrollView;
              m_vScrollView->setObjectName("vScrollView");
              m_mainLayout->addWidget(m_vScrollView, 1);

              m_vScrollView->getMainLayout()->setAlignment(Qt::AlignTop);

              m_appBehaviorLabel = new QLabel;
              m_appBehaviorLabel->setObjectName("appBehaviorLabel");
              m_appBehaviorLabel->setText("Appearance & behavior");
              m_vScrollView->getMainLayout()->addWidget(m_appBehaviorLabel);

              m_aboutLabel = new QLabel;
              m_aboutLabel->setObjectName("aboutLabel");
              m_aboutLabel->setText("About");
              m_vScrollView->getMainLayout()->addWidget(m_aboutLabel);

              FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluSettingPage.qss", this);
	  }

	  void paintEvent(QPaintEvent* event)
	  {
              QStyleOption opt;
              opt.initFrom(this);
              QPainter painter(this);
              style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
	  }

 protected:
          QVBoxLayout* m_mainLayout;

          QLabel* m_titleLabel;
          QLabel* m_appBehaviorLabel;
          QLabel* m_aboutLabel;
          FluVScrollView* m_vScrollView;
};
