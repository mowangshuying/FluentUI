#pragma once

#include "FluWidget.h"
#include <QVBoxLayout>
#include "FluVNavigationItem.h"
#include <vector>
#include "FluVScrollView.h"

#include <QPaintEvent>
#include <QStyleOption>
#include <QPainter>

class FluVNavigationIconTextItem;
class FluVNavigationFlyIconTextItem : public FluWidget
{
    Q_OBJECT
  public:
    FluVNavigationFlyIconTextItem(QWidget* parent = nullptr);

    ~FluVNavigationFlyIconTextItem();

    void setItemWidth(int width);

    void setItemHeight(int height);

    void setIconTextItems(std::vector<FluVNavigationIconTextItem*> items);

    void adjustItemHeight();
    void adjustItemWidth();

    // to enable qss
    void paintEvent(QPaintEvent* event);

  signals:
    void itemClicked(QString key);
  public slots:
    void onThemeChanged();

  protected:
    QVBoxLayout* m_mainLayout;

    FluVScrollView* m_scrollView;
    std::vector<FluVNavigationIconTextItem*> m_items;

    int m_itemHeight;
    int m_itemWidth;
};
