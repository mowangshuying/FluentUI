#pragma once

#include "FluHNavigationItem.h"
#include <QPushButton>
#include <QHBoxLayout>

#include <QStyleOption>
#include <QPainter>
#include "../Utils/FluUtils.h"

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
    QHBoxLayout* m_iconButtonLayout;
    QPushButton* m_iconButton;
    // QHBoxLayout* m_iconLayout;

    QWidget* m_horizontalIndicatorWrap;
    QHBoxLayout* m_horizontalIndicatorLayout;
    QWidget* m_horizontalIndicator;

    QVBoxLayout* m_mainLayout;

    bool m_isSelected;
};
