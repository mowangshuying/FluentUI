#pragma once

#include <QTreeWidget>
#include "FluTreeViewItemDelegate.h"

class FluTreeView : public QTreeWidget
{
    Q_OBJECT
  public:
    FluTreeView(QWidget *parent = nullptr);

    void drawBranches(QPainter *painter, const QRect &rect, const QModelIndex &index) const;
  public slots:
    void onThemeChanged();

  protected:
    FluTreeViewItemDelegate *m_delegate;
};
