#pragma once

#include <QListWidget>
#include "FluMenuAniType.h"
#include <QEvent>
#include "../Utils/FluUtils.h"
#include "FluScrollDelegate.h"

class FluRoundMenuView : public QListWidget
{
    Q_OBJECT
    Q_PROPERTY(bool btSpacing READ getBTSpacing WRITE setBTSpacing)
  public:
    FluRoundMenuView(QWidget* parent = nullptr);

  public:
    void insertItem(int row, QListWidgetItem* item);

    void addItem(QListWidgetItem* item);

    QListWidgetItem* takeItem(int row);

    void adjustSize(QPoint pos = QPoint(), FluMenuAniType aniType = FluMenuAniType::none);

    void setItemHeight(int height);

    void setMaxVisibleItems(int num);

    int getMaxVisibleItems();

    int heightForAnimation(QPoint pos, FluMenuAniType aniType);

    int itemsHeight();

    bool getBTSpacing();

    void setBTSpacing(bool isBTSpacing);

    void hockEvent(QEvent* event);
  public slots:
    void onThemeChanged();

  protected:
    int m_itemHeight;
    int m_maxVisibleItem;

    bool m_isBTSpacing;
    FluScrollDelegate* m_scrollDelegate;
};
