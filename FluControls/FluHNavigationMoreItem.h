#pragma once

#include "FluHNavigationItem.h"
#include <QPushButton>
#include <QHBoxLayout>

#include <QStyleOption>
#include <QPainter>
#include "../FluUtils/FluUtils.h"

class FluHNavigationMoreItem : public FluHNavigationItem
{
    Q_OBJECT
  public:
    FluHNavigationMoreItem(QWidget* parent = nullptr);


    void clearAllItemsSelectState();

    void updateAllItemsStyleSheet();

    void updateSelected(bool b);

    void mouseReleaseEvent(QMouseEvent* event);

    void paintEvent(QPaintEvent* event);

signals:
    void itemClicked();
  public slots:
      void onItemClicked();
      void onThemeChanged();

  protected:
    QHBoxLayout* m_hIconBtnLayout;
    QPushButton* m_iconBtn;
    //QHBoxLayout* m_hIconLayout;

    QWidget* m_hIndicatorWrap;
    QHBoxLayout* m_hIndicatorLayout;
    QWidget* m_hIndicator;

    QVBoxLayout* m_vMainLayout;

    bool m_bSelected;
};
