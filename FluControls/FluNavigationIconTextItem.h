#pragma once

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
#include "FluNavigationItem.h"

class FluNavigationView;
class FluNavigationIconTextItem : public FluNavigationItem
{
    Q_OBJECT
  public:
    FluNavigationIconTextItem(QWidget *parent = nullptr);

    FluNavigationIconTextItem(QIcon icon, QString text, QWidget *parent = nullptr);

    FluNavigationIconTextItem(QString text, QWidget *parent = nullptr);

    QList<FluNavigationIconTextItem *> getChildItems();

    void setParentView(FluNavigationView *view);

    // get navigation view
    FluNavigationView *getParentView();

    void addItem(FluNavigationIconTextItem *item);

    int calcItemW2Height(FluNavigationIconTextItem *item);

    void adjustItemHeight(FluNavigationIconTextItem *item);

    int getDepth();

    FluNavigationIconTextItem *getRootItem();

    void clearAllItemsSelectState()
    {
        FluNavigationIconTextItem *rootItem = getRootItem();
        clearItemsSelectState(rootItem);
    }

    void clearItemsSelectState(FluNavigationIconTextItem *item);

    void updateAllItemsStyleSheet()
    {
        FluNavigationIconTextItem *rootItem = getRootItem();
        updateItemsStyleSheet(rootItem);
    }

    void updateItemsStyleSheet(FluNavigationIconTextItem *item);

    void updateSelected(bool b);

    void enableThisItem(bool b);

    bool isDown()
    {
        return m_bDown;
    }

    void mouseReleaseEvent(QMouseEvent *event) override;

    // to enable qss
    void paintEvent(QPaintEvent *event)
    {
        QStyleOption opt;
        opt.initFrom(this);
        QPainter painter(this);
        style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
    }

  signals:
    void itemClicked();
  public slots:
    void onItemClicked();

  protected:
    QWidget *m_wrapWidget1;
    QWidget *m_wrapWidget2;

    QWidget *m_emptyWidget;

    QWidget *m_indicator;
    QPushButton *m_icon;
    QLabel *m_label;
    QPushButton *m_arrow;
    QHBoxLayout *m_hLayout1;
    QList<FluNavigationIconTextItem *> m_items;

    QVBoxLayout *m_vMainLayout;
    QVBoxLayout *m_vLayout1;

    FluNavigationIconTextItem *m_parentItem;
    FluNavigationView *m_parentView;

    //     int m_vSpacing;

    bool m_bDown;
    bool m_bLong;
    bool m_bSelected;
    bool m_bEnableThisItem;
};
