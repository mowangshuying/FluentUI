#pragma once

#include "../FluUtils/FluUtils.h"
#include "FluMenuITemDelegate.h"
#include <QFontMetrics>
#include <QStyleOptionViewItem>

class FluShortcutMenuItemDelegate : public FluMenuItemDelegate
{
    Q_OBJECT
  public:
    FluShortcutMenuItemDelegate(QObject *parent = nullptr);

  public:
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
};
