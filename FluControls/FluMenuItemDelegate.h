#pragma once

#include <QStyledItemDelegate>
#include <QPainter>
#include <QStyleOptionViewItem>
#include <QModelIndex>
#include "../FluUtils/FluUtils.h"

class FluMenuItemDelegate : public QStyledItemDelegate
{
    Q_OBJECT
  public:
    FluMenuItemDelegate(QObject *parent = nullptr);

  public:
    bool isSeparator(QModelIndex index) const;
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
};
