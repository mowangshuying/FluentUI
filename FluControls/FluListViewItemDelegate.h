#pragma once

#include <QStyledItemDelegate>
#include <QPalette>
#include <QPainter>

#include "../FluUtils/FluUtils.h"

class FluListViewItemDelegate : public QStyledItemDelegate
{
    Q_OBJECT
  public:
    FluListViewItemDelegate(QWidget* parent = nullptr);

    void initStyleOption(QStyleOptionViewItem* option, const QModelIndex& index) const;

    void paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const;

    QSize sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const;
};
