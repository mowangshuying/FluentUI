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

class FluNavigationIconTextItem;

// class FluNavigationSearchItem : public QWidget
//{
// };

class FluNavigationView : public QWidget
{
    Q_OBJECT
  public:
    FluNavigationView(QWidget *parent = nullptr);

    void addItemToLayout1(FluNavigationIconTextItem *item);

    void addItemToLayout2(FluNavigationIconTextItem *item);

    void addItemToLayout3(FluNavigationIconTextItem *item);

    void clearAllItemsSelectState();

    void updateAllItemsStyleSheet();

    void paintEvent(QPaintEvent *event) override;

  public slots:
    void onMenuItemClicked();
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
