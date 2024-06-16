#pragma once

#include <QStyledItemDelegate>
#include <QTreeView>


class FluTreeView;
class FluTreeViewItemDelegate : public QStyledItemDelegate
{
    Q_OBJECT
  public:
      FluTreeViewItemDelegate(FluTreeView* parent = nullptr);

      void initStyleOption(QStyleOptionViewItem* option, const QModelIndex& index) const;

      void paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const;

  protected:
      QColor m_foregroundColor;
      QColor m_backgroundColor;
      QColor m_hoverBackgroundColor;
      QColor m_selectBackgroundColor;
      QColor m_indicatorColor;

      FluTreeView* m_treeView;
};
