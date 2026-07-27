#pragma once

#include <QStyledItemDelegate>
#include <QTreeView>

class FluTreeView;
class FluTreeViewItemDelegate : public QStyledItemDelegate
{
    Q_OBJECT
  public:
    FluTreeViewItemDelegate(FluTreeView* parent = nullptr);

    QColor getIndicatorColorEx()
    {
        return m_indicatorColorEx;
    }

    void setIndicatorColorEx(QColor color)
    {
        m_indicatorColorEx = color;
    }

    QColor getBackgroundColorEx()
    {
        return m_backgroundColorEx;
    }

    void setBackgroundColorEx(QColor color)
    {
        m_backgroundColorEx = color;
    }

    QColor getTextColorEx()
    {
        return m_textColorEx;
    }

    void setTextColorEx(QColor color)
    {
        m_textColorEx = color;
    }

    QColor getUnCheckedPenColorEx()
    {
        return m_unCheckedPenColorEx;
    }

    void setUnCheckedPenColorEx(QColor color)
    {
        m_unCheckedPenColorEx = color;
    }

    QColor getUnCheckedBrushColorEx()
    {
        return m_unCheckedBrushColorEx;
    }

    void setUnCheckedBrushColorEx(QColor color)
    {
        m_unCheckedBrushColorEx = color;
    }

    QColor getCheckedPenColorEx()
    {
        return m_checkedPenColorEx;
    }

    void setCheckedPenColorEx(QColor color)
    {
        m_checkedPenColorEx = color;
    }

    QColor getCheckedBrushColorEx()
    {
        return m_checkedBrushColorEx;
    }

    void setCheckedBrushColorEx(QColor color)
    {
        m_checkedBrushColorEx = color;
    }

    void initStyleOption(QStyleOptionViewItem* option, const QModelIndex& index) const;

    void paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const;

    void drawBackground(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const;

    void drawCheckBox(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const;

    void drawIndicator(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const;

  protected:
    FluTreeView* m_treeView;

    QColor m_indicatorColorEx;
    QColor m_backgroundColorEx;
    QColor m_textColorEx;

    QColor m_unCheckedPenColorEx;
    QColor m_unCheckedBrushColorEx;

    QColor m_checkedPenColorEx;
    QColor m_checkedBrushColorEx;
};