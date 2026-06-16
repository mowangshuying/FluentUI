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

    void adjustItemHeight();
    void adjustItemWidth();

    // to enable qss
    void paintEvent(QPaintEvent* event);

  signals:
    void itemClicked(QString key);
  public slots:
    void onThemeChanged();

  protected:
    QVBoxLayout* m_vMainLayout;

    FluVScrollView* m_vScrollView;
    std::vector<FluVNavigationIconTextItem*> m_items;
};
