#pragma once

#include "FluMenuItemDelegate.h"

class FluIndicatorMenuItemDeleage : public FluMenuItemDelegate
{
  public:
    FluIndicatorMenuItemDeleage(QObject *parent = nullptr);

  public:
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
};
