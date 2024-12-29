#pragma once

#include <QWidget>
#include <QListWidgetItem>
#include <QPainter>
#include "FluRoundMenu.h"
#include "../FluUtils/FluUtils.h"

class FluSubMenuItemWidget : public QWidget
{
    Q_OBJECT
  public:
    FluSubMenuItemWidget(FluRoundMenu* menu, QListWidgetItem* item, QWidget* parent = nullptr);
  signals:
    void showMenuSig(QListWidgetItem* item);

  protected:
    void enterEvent(QEnterEvent* event);

    void paintEvent(QPaintEvent* event);

  public:
    QListWidgetItem* getItem();

    FluRoundMenu* getMenu();

  protected:
    FluRoundMenu* m_menu;
    QListWidgetItem* m_item;
};
