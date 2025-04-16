#pragma once

#include <QStyledItemDelegate>
#include <QPalette>
#include <QPainter>
#include <QColor>

#include "../FluUtils/FluUtils.h"

class FluListViewItemDelegate : public QStyledItemDelegate
{
    Q_OBJECT
  public:
    FluListViewItemDelegate(QWidget* parent = nullptr);

    // QColor;
    QColor getBackgroundColorEx() const;

    void setBackgroundColorEx(QColor color);

    QColor getHoverColorEx() const;

    void setHoverColorEx(QColor color);

    QColor getIndicatorColorEx() const;

    void setIndicatorColorEx(QColor color);

    QColor getTextColorEx() const;

    void setTextColorEx(QColor color);

    void initStyleOption(QStyleOptionViewItem* option, const QModelIndex& index) const;

    void paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const;

    QSize sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const;

  protected:
    QColor m_backgroundColorEx;
    QColor m_hoverColorEx;
    QColor m_indicatorColorEx;
    QColor m_textColorEx;
};
