#pragma once

#include <QWidget>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include "../FluUtils/FluStyleSheetUitls.h"
#include <QStyleOption>
#include <QPainter>
#include "FluDef.h"
#include "../FluUtils/FluIconUtils.h"
#include <QTransform>
#include "../FluUtils/FluLogUtils.h"
#include <QMouseEvent>


class FluNavigationItem : public QWidget
{
	Q_OBJECT
public:
	FluNavigationItem(QWidget* parent = nullptr) : QWidget(parent)
	{
		setFixedSize(320, 40);
		m_wrapTopW = new QWidget(this);
		m_wrapBottomW = new QWidget(this);

		m_wrapTopW->setObjectName("wrapWidget1");
		m_wrapBottomW->setObjectName("wrapWidget2");

		m_bSelected = false;
		m_wrapTopW->setProperty("selected", false);
		setProperty("selected", false);

		m_emptyWidget = new QWidget(this);
		m_emptyWidget->setFixedSize(0, 0);
		//m_emptyWidget->hide();

		m_vMainLayout = new QVBoxLayout(this);
		m_vMainLayout->setContentsMargins(0, 0, 0, 0);
		m_vMainLayout->setSpacing(0);
		m_vMainLayout->addWidget(m_wrapTopW);
		m_vMainLayout->addWidget(m_wrapBottomW);
		m_wrapBottomW->hide();


		m_hTopLayout = new QHBoxLayout(m_wrapTopW);
		m_wrapTopW->setFixedSize(320, 40);
		m_vMainLayout->addLayout(m_vMainLayout);

		m_vBottomLayout = new QVBoxLayout(m_wrapBottomW);
		m_hTopLayout->setContentsMargins(0, 4, 0, 4);
		m_indicator = new QWidget(this);
		m_icon = new QPushButton(this);
		m_label = new QLabel("Home");
		m_arrow = new QPushButton(this);

		m_hTopLayout->addSpacing(4);
		m_hTopLayout->addWidget(m_emptyWidget);
		m_hTopLayout->addWidget(m_indicator);
		m_hTopLayout->addWidget(m_icon);
		m_hTopLayout->addSpacing(12);
		m_hTopLayout->addWidget(m_label, 1);
		m_hTopLayout->addWidget(m_arrow);

		m_hTopLayout->setSpacing(0);

		m_indicator->setFixedHeight(18);
		m_indicator->setFixedWidth(4);
		m_icon->setFixedSize(30, 30);
		m_label->setWordWrap(true);

		m_vBottomLayout->setContentsMargins(0, 0, 0, 0);
		m_vBottomLayout->setSpacing(0);
		m_indicator->setObjectName("indicator");
		m_icon->setObjectName("icon");
		m_label->setObjectName("label");
		m_arrow->setObjectName("arrow");

		m_icon->setIconSize(QSize(30, 30));
		m_icon->setIcon(FluIconUtils::getFluentIcon(FluAwesomeType::Home));

		m_arrow->setIconSize(QSize(30, 30));
		m_arrow->setIcon(FluIconUtils::getFluentIcon(FluAwesomeType::ChevronDown));
		m_bDown = true;
		m_bLong = true;
		m_arrow->hide();

		QString qss = FluStyleSheetUitls::getQssByFileName("../StyleSheet/FluNavigationItem.qss");
		setStyleSheet(qss);


		//m_currentWidth  = 320;
		m_parentItem = nullptr;
		connect(m_arrow, &QPushButton::clicked, [=](bool b) {
			if (m_bDown)
			{
				LOG_DEBUG << "click down.";


				//LOG_DEBUG << "before height:" << height();
				m_arrow->setIcon(FluIconUtils::getFluentIcon(FluAwesomeType::ChevronUp));
				// 展示子项目
				if (m_items.size() > 0)
				{
					int nH = 0;
					for (int i = 0; i < m_vBottomLayout->count(); i++)
					{
						auto item = (FluNavigationItem*)m_vBottomLayout->itemAt(i)->widget();
						nH += item->height();
					}

					m_wrapBottomW->setFixedHeight(nH);
					m_wrapBottomW->show();
					// 遍历所有子项目设置其长度
					setFixedHeight(m_wrapTopW->height() + m_wrapBottomW->height());
				}

				adjustItemHeight(m_parentItem);
				m_wrapBottomW->show();
				//show();
				//adjustItemHeight();
				m_bDown = false;
				//LOG_DEBUG << "end height:" << height();
			}
			else
			{
				m_arrow->setIcon(FluIconUtils::getFluentIcon(FluAwesomeType::ChevronDown));
				setFixedHeight(40);
				m_wrapBottomW->hide();

				adjustItemHeight(m_parentItem);

				m_bDown = true;
			}
			});

		connect(m_icon, &QPushButton::clicked, [=](bool b) {
		//	if (m_bLong)
		//	{
		//		m_bLong = false;
		//		m_label->hide();
		//		m_arrow->hide();
		//		setFixedWidth(48);
		//	}
		//	else
		//	{
		//		m_bLong = true;
		//		m_label->show();
		//		m_arrow->show();
		//		setFixedWidth(320);
		//	}
			});
	}

	FluNavigationItem(QIcon icon, QString text, QWidget* parent = nullptr) : FluNavigationItem(parent)
	{
		m_icon->setIcon(icon);
		m_label->setText(text);
	}

	FluNavigationItem(QString text, QWidget* parent = nullptr) : FluNavigationItem(parent)
	{
		m_icon->hide();
		//m_icon->setIcon(QIcon());
		m_label->setText(text);
	}

	void addChildItem(FluNavigationItem* item)
	{
		//item->m_currentWidth = m_currentWidth - 36;
		item->m_parentItem = this;
		m_items.append(item);

		int nDepth = item->getDepth();
		item->m_emptyWidget->setFixedWidth(36 * nDepth);
		item->show();

		m_vBottomLayout->addWidget(item);
		m_arrow->show();
	}

	int calcItemW2Height(FluNavigationItem* item)
	{
		int nH = 0;
		for (int i = 0; i < item->m_vBottomLayout->count(); i++)
		{
			auto tmpItem = (FluNavigationItem*)item->m_vBottomLayout->itemAt(i)->widget();
			nH += tmpItem->height();
		}
		return nH;
	}

	void adjustItemHeight(FluNavigationItem* item)
	{
		if (item == nullptr)
			return;

		int nH = calcItemW2Height(item);
		item->m_wrapBottomW->setFixedHeight(nH);
		item->setFixedHeight(item->m_wrapTopW->height() + item->m_wrapBottomW->height());
		adjustItemHeight(item->m_parentItem);
	}

	int getDepth()
	{
		int nDepth = 0;
		FluNavigationItem* item = m_parentItem;
		while (item != nullptr)
		{
			nDepth++;
			item = item->m_parentItem;
		}
		return nDepth;
	}

	// 获取到根节点
	FluNavigationItem* getRootItem()
	{
		int nDepth = 0;
		FluNavigationItem* item = this;
		while (item->m_parentItem != nullptr)
		{
			//nDepth++;
			item = item->m_parentItem;
		}
		return item;
	}

	// 更新整个树的选择状态
	void clearAllItemsSelectState()
	{
		FluNavigationItem* rootItem = getRootItem();
		clearItemsSelectState(rootItem);
	}

	void clearItemsSelectState(FluNavigationItem* item)
	{
		if (item == nullptr)
			return;

		item->m_bSelected = false;
		item->setProperty("selected", false);
		item->m_wrapTopW->setProperty("selected", false);
		item->m_indicator->setProperty("selected", false);
		for (int i = 0; i < item->m_vBottomLayout->count(); i++)
		{
			auto tmpItem = (FluNavigationItem*)item->m_vBottomLayout->itemAt(i)->widget();
			clearItemsSelectState(tmpItem);
		}
	}

	void updateAllItemsStyleSheet()
	{
		FluNavigationItem* rootItem = getRootItem();
		updateItemsStyleSheet(rootItem);
	}

	void updateItemsStyleSheet(FluNavigationItem* item)
	{
		if (item == nullptr)
			return;

		item->style()->polish(item);
		item->m_wrapTopW->style()->polish(item->m_wrapTopW);
		item->m_wrapBottomW->style()->polish(item->m_wrapBottomW);
		item->m_indicator->style()->polish(item->m_indicator);
		item->m_icon->style()->polish(item->m_icon);
		item->m_label->style()->polish(item->m_label);
		item->m_arrow->style()->polish(item->m_arrow);

		for (int i = 0; i < item->m_vBottomLayout->count(); i++)
		{
			auto tmpItem = (FluNavigationItem*)item->m_vBottomLayout->itemAt(i)->widget();
			updateItemsStyleSheet(tmpItem);
		}
	}

	void mouseReleaseEvent(QMouseEvent* event)
	{
		QPoint pos = event->pos();
		if (m_wrapTopW->rect().contains(pos))
		{
			clearAllItemsSelectState();


			m_bSelected = true;
			setProperty("selected", true);
			m_wrapTopW->setProperty("selected", true);
			m_indicator->setProperty("selected", true);

			updateAllItemsStyleSheet();
		}
	}

	void paintEvent(QPaintEvent* event)
	{
		QStyleOption opt;
		opt.initFrom(this);
		QPainter painter(this);
		style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
	}
protected:
	QWidget* m_wrapTopW;
	QWidget* m_wrapBottomW;

	QWidget* m_emptyWidget;

	QWidget* m_indicator;
	QPushButton* m_icon;
	QLabel*	m_label;
	QPushButton* m_arrow;
	QHBoxLayout* m_hTopLayout;
	QList<FluNavigationItem*> m_items;
	
	QVBoxLayout* m_vMainLayout;
	QVBoxLayout* m_vBottomLayout;

	//int m_currentWidth;
	
	FluNavigationItem* m_parentItem;
	bool m_bDown;
	bool m_bLong;
	bool m_bSelected;
};

class FluNavigationMenuItem : public QWidget
{
	Q_OBJECT
public:
	FluNavigationMenuItem(QWidget* parent = nullptr) : QWidget(parent)
	{
		m_hLayout = new QHBoxLayout(this);

		m_menuButton = new QPushButton(this);
		m_menuButton->setIcon(FluIconUtils::getFluentIcon(FluAwesomeType::GlobalNavButton));
		m_menuButton->setIconSize(QSize(30,30));
		m_menuButton->setFixedSize(30, 30);
		m_hLayout->setContentsMargins(10, 0, 0, 0);

		setFixedHeight(40);

		m_hLayout->addWidget(m_menuButton);
		m_hLayout->addStretch(1);
		m_menuButton->setObjectName("menuButton");
		QString qss = FluStyleSheetUitls::getQssByFileName("../StyleSheet/FluNavigationMenuItem.qss");
		setStyleSheet(qss);

		connect(m_menuButton, &QPushButton::clicked, [=](bool b) {emit menuClicked(); });
	}
signals:
	void menuClicked();
protected:
	QPushButton* m_menuButton;
	QHBoxLayout* m_hLayout;
};

class FluNavigationSearchItem : public QWidget 
{

};

class FluNavigationView : public QWidget
{
	Q_OBJECT
public:
	FluNavigationView(QWidget* parent = nullptr) : QWidget(parent)
	{
		m_vLayout = new QVBoxLayout(this);
		m_vLayout->setContentsMargins(0, 0, 0, 0);
		m_widget1 = new QWidget(this);
		m_widget2 = new QWidget(this);
		m_widget3 = new QWidget(this);

		m_vLayout1 = new QVBoxLayout(m_widget1);
		m_vLayout2 = new QVBoxLayout(m_widget2);
		m_vLayout3 = new QVBoxLayout(m_widget3);

		m_vLayout1->setContentsMargins(0, 0, 0, 0);
		m_vLayout2->setContentsMargins(0, 0, 0, 0);
		m_vLayout3->setContentsMargins(0, 0, 0, 0);

		m_vLayout1->setSpacing(0);
		m_vLayout2->setSpacing(0);
		m_vLayout3->setSpacing(0);

		m_vLayout1->setAlignment(Qt::AlignTop);
		m_vLayout2->setAlignment(Qt::AlignTop);
		m_vLayout3->setAlignment(Qt::AlignTop);


		m_vLayout->addWidget(m_widget1);
		m_vLayout->addWidget(m_widget2, 1);
		m_vLayout->addWidget(m_widget3);


		auto menuButtonItem = new FluNavigationMenuItem(this);
		m_vLayout1->addWidget(menuButtonItem);

		QString qss = FluStyleSheetUitls::getQssByFileName("../StyleSheet/FluNavigationView.qss");
		setStyleSheet(qss);

		m_bLong = true;
		setFixedWidth(320);
		connect(menuButtonItem, &FluNavigationMenuItem::menuClicked, [=]() {
			if (m_bLong)
			{
				setFixedWidth(48);
				m_bLong = false;
			}
			else
			{
				setFixedWidth(320);
				m_bLong = true;
			}
			});
	}

	void addNavigationItemTop(FluNavigationItem* item)
	{
		m_vLayout1->addWidget(item, Qt::AlignTop);
	}


	void addNavigationItemMid(FluNavigationItem* item)
	{
		m_vLayout2->addWidget(item, Qt::AlignTop);
	}

	void addNavigationItemButtom(FluNavigationItem* item)
	{
		m_vLayout3->addWidget(item);
	}

	void paintEvent(QPaintEvent* event)
	{
		QStyleOption opt;
		opt.initFrom(this);
		QPainter painter(this);
		style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
	}
public:
	QVBoxLayout* m_vLayout;

	QWidget* m_widget1;
	QWidget* m_widget2;
	QWidget* m_widget3;

	QVBoxLayout* m_vLayout1;
	QVBoxLayout* m_vLayout2;
	QVBoxLayout* m_vLayout3;

	bool m_bLong;
};

