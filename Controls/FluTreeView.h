#pragma once

#include <QTreeWidget>
#include "FluTreeViewItemDelegate.h"
#include "FluScrollDelegate.h"

class FluTreeView : public QTreeWidget
{
    Q_OBJECT
    Q_PROPERTY(QColor indicatorColorEx READ getIndicatorColorEx WRITE setIndicatorColorEx)
    Q_PROPERTY(QColor backgroundColorEx READ getBackgroundColorEx WRITE setBackgroundColorEx)
    Q_PROPERTY(QColor textColorEx READ getTextColorEx WRITE setTextColorEx)
    Q_PROPERTY(QColor unCheckedPenColorEx READ getUnCheckedPenColorEx WRITE setUnCheckedPenColorEx)
    Q_PROPERTY(QColor unCheckedBrushColorEx READ getUnCheckedBrushColorEx WRITE setUnCheckedBrushColorEx)
    Q_PROPERTY(QColor checkedPenColorEx READ getCheckedPenColorEx WRITE setCheckedPenColorEx)
    Q_PROPERTY(QColor checkedBrushColorEx READ getCheckedBrushColorEx WRITE setCheckedBrushColorEx)
  public:
    FluTreeView(QWidget *parent = nullptr);
    QColor getIndicatorColorEx()
    {
        return m_ItemDelegate->getIndicatorColorEx();
    }

    void setIndicatorColorEx(QColor color)
    {
        m_ItemDelegate->setIndicatorColorEx(color);
    }

    QColor getBackgroundColorEx()
    {
        return m_ItemDelegate->getBackgroundColorEx();
    }

    void setBackgroundColorEx(QColor color)
    {
        m_ItemDelegate->setBackgroundColorEx(color);
    }

    QColor getTextColorEx()
    {
        return m_ItemDelegate->getTextColorEx();
    }

    void setTextColorEx(QColor color)
    {
        m_ItemDelegate->setTextColorEx(color);
    }

    QColor getUnCheckedPenColorEx()
    {
        return m_ItemDelegate->getUnCheckedPenColorEx();
    }

    void setUnCheckedPenColorEx(QColor color)
    {
        return m_ItemDelegate->setUnCheckedPenColorEx(color);
    }

    QColor getUnCheckedBrushColorEx()
    {
        return m_ItemDelegate->getUnCheckedBrushColorEx();
    }

    void setUnCheckedBrushColorEx(QColor color)
    {
        m_ItemDelegate->setUnCheckedBrushColorEx(color);
    }

    QColor getCheckedPenColorEx()
    {
        return m_ItemDelegate->getCheckedPenColorEx();
    }

    void setCheckedPenColorEx(QColor color)
    {
        m_ItemDelegate->setCheckedPenColorEx(color);
    }

    QColor getCheckedBrushColorEx()
    {
        return m_ItemDelegate->getCheckedBrushColorEx();
    }

    void setCheckedBrushColorEx(QColor color)
    {
        m_ItemDelegate->setCheckedBrushColorEx(color);
    }

    void drawBranches(QPainter *painter, const QRect &rect, const QModelIndex &index) const;
  public slots:
    void onThemeChanged();

  protected:
    FluTreeViewItemDelegate *m_ItemDelegate;
    FluScrollDelegate *m_scrollDelegate;
};
