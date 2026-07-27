#pragma once

#include <QStyledItemDelegate>
// #include <QTableView>
#include <set>
#include "FluLineEdit.h"
#include "../Utils/FluUtils.h"
#include <QScrollBar>

class FluTableView;
class FluTableItemDelegate : public QStyledItemDelegate
{
    Q_OBJECT
  public:
    FluTableItemDelegate(FluTableView* parent);

    void setHoverRow(int hoverRow);

    void setPressedRow(int pressedRow);

    void setSelectedRows(std::list<QModelIndex> indexList);

    QSize sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const override;

    // editing
    QWidget* createEditor(QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const override;

    void updateEditorGeometry(QWidget* editor, const QStyleOptionViewItem& option, const QModelIndex& index) const override;

    void initStyleOption(QStyleOptionViewItem* option, const QModelIndex& index) const override;

    void drawSelfIndicator(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const;

    void drawSelfBackground(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const;

    void drawSelfCheckBox(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const;

    void paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const override;

  protected:
    int m_margin;
    int m_hoverRow;
    int m_pressedRow;
    std::set<int> m_selectedRows;
    FluTableView* m_tableView;
};
