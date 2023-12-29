#pragma once

#include "../FluUtils/FluIconUtils.h"
#include "../FluUtils/FluLogUtils.h"
#include "../FluUtils/FluStyleSheetUitls.h"
#include "FluDef.h"
#include <QHBoxLayout>
#include <QLabel>
#include <QMouseEvent>
#include <QPainter>
#include <QPushButton>
#include <QScrollArea>
#include <QStyleOption>
#include <QTransform>
#include <QVBoxLayout>
#include <QWidget>

class FluNavigationView;
class FluNavigationItem : public QWidget
{
    Q_OBJECT
  public:
    FluNavigationItem(QWidget *parent = nullptr);

    FluNavigationItem(QIcon icon, QString text, QWidget *parent = nullptr);

    FluNavigationItem(QString text, QWidget *parent = nullptr);

    QList<FluNavigationItem *> getChildItems();

    void setParentView(FluNavigationView *view);

    FluNavigationView *getParentView();

    void addChildItem(FluNavigationItem *item);

    int calcItemW2Height(FluNavigationItem *item);

    void adjustItemHeight(FluNavigationItem *item);

    int getDepth();

    FluNavigationItem *getRootItem();

    void clearAllItemsSelectState()
    {
        FluNavigationItem *rootItem = getRootItem();
        clearItemsSelectState(rootItem);
    }

    void clearItemsSelectState(FluNavigationItem *item);

    void updateAllItemsStyleSheet()
    {
        FluNavigationItem *rootItem = getRootItem();
        updateItemsStyleSheet(rootItem);
    }

    void updateItemsStyleSheet(FluNavigationItem *item);

    void updateSelected(bool b);

    void mouseReleaseEvent(QMouseEvent *event) override;

    void paintEvent(QPaintEvent *event)
    {
        QStyleOption opt;
        opt.initFrom(this);
        QPainter painter(this);
        style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
    }
  signals:
    void itemClicked();

  protected:
    QWidget *m_wrapTopW;
    QWidget *m_wrapBottomW;

    QWidget *m_emptyWidget;

    QWidget *m_indicator;
    QPushButton *m_icon;
    QLabel *m_label;
    QPushButton *m_arrow;
    QHBoxLayout *m_hTopLayout;
    QList<FluNavigationItem *> m_items;

    QVBoxLayout *m_vMainLayout;
    QVBoxLayout *m_vBottomLayout;

    // int m_currentWidth;

    FluNavigationItem *m_parentItem;
    FluNavigationView *m_parentView;
    bool m_bDown;
    bool m_bLong;
    bool m_bSelected;
};

class FluNavigationMenuItem : public QWidget
{
    Q_OBJECT
  public:
    FluNavigationMenuItem(QWidget *parent = nullptr) : QWidget(parent)
    {
        m_hLayout = new QHBoxLayout(this);

        m_menuButton = new QPushButton(this);
        m_menuButton->setIcon(FluIconUtils::getFluentIcon(FluAwesomeType::GlobalNavButton));
        m_menuButton->setIconSize(QSize(30, 30));
        m_menuButton->setFixedSize(30, 30);
        m_hLayout->setContentsMargins(10, 0, 0, 0);

        setFixedHeight(40);
        setFixedWidth(320);

        m_hLayout->addWidget(m_menuButton);
        m_hLayout->addStretch(1);
        m_menuButton->setObjectName("menuButton");
        QString qss = FluStyleSheetUitls::getQssByFileName("../StyleSheet/light/FluNavigationMenuItem.qss");
        setStyleSheet(qss);

        connect(m_menuButton, &QPushButton::clicked, [=](bool b) { emit menuClicked(); });
    }
  signals:
    void menuClicked();

  protected:
    QPushButton *m_menuButton;
    QHBoxLayout *m_hLayout;
};

class FluNavigationSearchItem : public QWidget
{
};

class FluNavigationView : public QWidget
{
    Q_OBJECT
  public:
    FluNavigationView(QWidget *parent = nullptr) : QWidget(parent)
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

        auto srollArea = new QScrollArea(this);
        srollArea->setWidgetResizable(true);
        srollArea->setWidget(m_widget2);

        srollArea->setObjectName("srollArea");
        srollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

        m_vLayout->addWidget(m_widget1);
        m_vLayout->addWidget(srollArea, 1);
        m_vLayout->addWidget(m_widget3);

        m_widget1->setObjectName("widget1");
        m_widget2->setObjectName("widget2");
        m_widget3->setObjectName("widget3");


        auto menuButtonItem = new FluNavigationMenuItem(this);
        m_vLayout1->addWidget(menuButtonItem);

        QString qss = FluStyleSheetUitls::getQssByFileName("../StyleSheet/light/FluNavigationView.qss");
        setStyleSheet(qss);

        m_bLong = true;
        setFixedWidth(320 + 10);
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

    void addNavigationItemTop(FluNavigationItem *item)
    {
        m_vLayout1->addWidget(item, Qt::AlignTop);
    }

    void addNavigationItemMid(FluNavigationItem *item)
    {
        m_vLayout2->addWidget(item, Qt::AlignTop);
        item->setParentView(this);
    }

    void clearAllItemsSelectState()
    {
        for (int i = 0; i < m_vLayout2->count(); i++)
        {
            auto curItem = (FluNavigationItem *)m_vLayout2->itemAt(i)->widget();
            curItem->clearAllItemsSelectState();
        }
    }

    void updateAllItemsStyleSheet()
    {
        for (int i = 0; i < m_vLayout2->count(); i++)
        {
            auto curItem = (FluNavigationItem *)m_vLayout2->itemAt(i)->widget();
            curItem->updateAllItemsStyleSheet();
        }
    }

    void addNavigationItemButtom(FluNavigationItem *item)
    {
        m_vLayout3->addWidget(item);
    }

    void paintEvent(QPaintEvent *event)
    {
        QStyleOption opt;
        opt.initFrom(this);
        QPainter painter(this);
        style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
    }

  public:
    QVBoxLayout *m_vLayout;

    QWidget *m_widget1;
    QWidget *m_widget2;
    QWidget *m_widget3;

    QVBoxLayout *m_vLayout1;
    QVBoxLayout *m_vLayout2;
    QVBoxLayout *m_vLayout3;

    bool m_bLong;
};
