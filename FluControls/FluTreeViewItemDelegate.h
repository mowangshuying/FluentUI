#pragma once

#include <QStyledItemDelegate>
#include <QTreeView>

class FluTreeView;
class FluTreeViewItemDelegate : public QStyledItemDelegate
{
    Q_OBJECT
  public:
    FluTreeViewItemDelegate(FluTreeView* parent = nullptr);

    void updateColor();

    void initStyleOption(QStyleOptionViewItem* option, const QModelIndex& index) const;

    void paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const;

    void paintRect(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const;

    void paintCheckBox(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const;

    void paintArrow(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const;

  protected:
    QColor m_fontColor;  // the font color;

    QColor m_normalBackgroundColor;
    QColor m_hoverBackgroundColor;
    QColor m_selectBackgroundColor;

    QColor m_indicatorPenColor;
    QColor m_indicatorBrushColor;
    QColor m_textColor;

    FluTreeView* m_treeView;
};
