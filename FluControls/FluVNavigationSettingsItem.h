#pragma once

#include "FluVNavigationItem.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QStyleOption>
#include <QPainter>
#include "FluRotationButton.h"
#include "../FluUtils/FluUtils.h"

class FluVNavigationSettingsItem : public FluVNavigationItem
{
    Q_OBJECT
  public:
    FluVNavigationSettingsItem(QIcon icon, QString text, QWidget* parent = nullptr);

    FluVNavigationSettingsItem(FluAwesomeType awesomeType, QString text, QWidget* parent);

    QLabel* getLabel();

    void hideLabel();

    void showLabel();

    void updateAllItemsStyleSheet();

    void updateItemsStyleSheet();

    void updateSelected(bool b);

    void clearAllItemsSelectState();

    void mouseReleaseEvent(QMouseEvent* event);

    // to enable qss
    void paintEvent(QPaintEvent* event);

  signals:
    void itemClicked();
  public slots:
    void onItemClicked();
    void onThemeChanged();

  protected:
    QHBoxLayout* m_hMainLayout;
    QWidget* m_indicator;
    FluRotationButton* m_icon;
    QLabel* m_label;

    bool m_bSelected;
};
