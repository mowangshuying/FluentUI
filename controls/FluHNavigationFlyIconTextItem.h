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
    Q_PROPERTY(int dropHeight READ dropHeight WRITE setDropHeight)
  public:
    FluHNavigationFlyIconTextItem(QWidget* parent = nullptr);

    void setIconTextItems(std::vector<FluHNavigationIconTextItem*> items, int parentWidth = 0);

    void adjustItemWidth(int minWidth = 0);

    QVBoxLayout* getMainLayout();

    FluVScrollView* getVScrollView();

    void showWithAnimation(QPoint pos);

    void setPositionRelativeTo(QWidget* parentItem, int navBarHeight);

    int dropHeight() const { return m_dropHeight; }
    void setDropHeight(int h);

    void clearAllItemsSelectState();
    void updateAllItemsStyleSheet();

    void setNavView(FluHNavigationView* view);
    FluHNavigationView* getNavView();
    void getCloseByClickedItem(bool b);
    bool setCloseByClickedItem();

    void paintEvent(QPaintEvent* event)
    {
        QStyleOption opt;
        opt.initFrom(this);
        QPainter painter(this);
        style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
    }

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

    QGraphicsOpacityEffect* m_opacityEffect;
    QPropertyAnimation* m_fadeAnimation;
    QPropertyAnimation* m_dropAnimation;
    QParallelAnimationGroup* m_showGroup;
    int m_dropHeight;
    int m_fullHeight;
};
