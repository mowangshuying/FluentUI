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

    void setIconTextItems(std::vector<FluVNavigationIconTextItem*> items);

    void adjustItemSize();

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

    FluVScrollView* m_widget;
    // QVBoxLayout* m_vCenterLayout;
    std::vector<FluVNavigationIconTextItem*> m_items;
};
