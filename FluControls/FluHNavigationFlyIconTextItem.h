#pragma once

#include "FluWidget.h"

#include <QPainter>
#include <QStyleOption>
#include <QPaintEvent>

#include <QVBoxLayout>
#include <vector>
#include "FluVScrollView.h"

class FluHNavigationIconTextItem;
class FluHNavigationView;
class FluHNavigationFlyIconTextItem : public FluWidget
{
    Q_OBJECT
  public:
    FluHNavigationFlyIconTextItem(QWidget* parent = nullptr);

    void setIconTextItems(std::vector<FluHNavigationIconTextItem*> items);

    void adjustItemWidth();

    QVBoxLayout* getMainLayout()
    {
        return m_vMainLayout;
    }

    FluVScrollView* getVScrollView()
    {
        return m_vScrollView;
    }

    // 
    void clearAllItemsSelectState();
    void updateAllItemsStyleSheet();

    void setNavView(FluHNavigationView* view);

    FluHNavigationView* getNavView();

    // to enable qss
    void paintEvent(QPaintEvent* event)
    {
        QStyleOption opt;
        opt.initFrom(this);
        QPainter painter(this);
        style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
    }
  public slots:
    void onThemeChanged();

  protected:
    QVBoxLayout* m_vMainLayout;
    FluVScrollView* m_vScrollView;
    FluHNavigationView* m_NavView;
    std::vector<FluHNavigationIconTextItem*> m_items;
};
