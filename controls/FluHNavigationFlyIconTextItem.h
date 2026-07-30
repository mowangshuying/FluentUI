#pragma once

#include "FluWidget.h"

#include <QPainter>
#include <QStyleOption>
#include <QPaintEvent>

#include <QVBoxLayout>
#include <vector>
#include "FluVScrollView.h"
#include <QPropertyAnimation>
#include <QGraphicsOpacityEffect>
#include <QParallelAnimationGroup>

class FluHNavigationIconTextItem;
class FluHNavigationView;
class FluHNavigationFlyIconTextItem : public FluWidget
{
    Q_OBJECT
  public:
    FluHNavigationFlyIconTextItem(QWidget* parent = nullptr);

    void setIconTextItems(std::vector<FluHNavigationIconTextItem*> items, int parentWidth = 0);

    void adjustItemWidth(int minWidth = 0);

    QVBoxLayout* getMainLayout();

    FluVScrollView* getVScrollView();

    void clearAllItemsSelectState();
    void updateAllItemsStyleSheet();

    void setNavView(FluHNavigationView* view);
    FluHNavigationView* getNavView();
    void getCloseByClickedItem(bool b);
    bool setCloseByClickedItem();

    void closeEvent(QCloseEvent* event)
    {
        emit itemClose();
    }

  signals:
    void itemClose();
    void itemSelected(QString key);
  public slots:
    void onThemeChanged();

  protected:
    bool m_isCloseByClickedItem;
    QVBoxLayout* m_mainLayout;
    FluVScrollView* m_scrollView;
    FluHNavigationView* m_NavView;
    std::vector<FluHNavigationIconTextItem*> m_items;
};
