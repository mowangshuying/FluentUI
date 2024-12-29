#pragma once

#include <QListWidget>
#include "FluMenuAniType.h"
#include <QEvent>
#include "../FluUtils/FluUtils.h"

class FluRoundMenuView : public QListWidget
{
    Q_OBJECT
  public:
    FluRoundMenuView(QWidget* parent = nullptr);

  public:
    void insertItem(int row, QListWidgetItem* item);

    void addItem(QListWidgetItem* item);

    QListWidgetItem* takeItem(int row);

    void adjustSize(QPoint pos = QPoint(), FluMenuAniType aniType = FluMenuAniType::none);

    void setItemHeight(int nHeight);

    void setMaxVisibleItems(int nNum);

    int getMaxVisibleItems();

    int heightForAnimation(QPoint pos, FluMenuAniType aniType);

    int itemsHeight();

    void hockEvent(QEvent* event);

  private:
    int m_itemHeight;
    int m_maxVisibleItem;
};
