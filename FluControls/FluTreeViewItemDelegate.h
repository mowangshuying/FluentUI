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

    void drawBackground(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const;

    void drawCheckBox(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const;

    void drawIndicator(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const;
  protected:
    FluTreeView* m_treeView;

};