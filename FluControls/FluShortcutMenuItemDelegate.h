#pragma once

#include "../FluUtils/FluUtils.h"
#include "FluMenuItemDelegate.h"
#include <QFontMetrics>
#include <QStyleOptionViewItem>
#include <QAction>

class FluShortcutMenuItemDelegate : public FluMenuItemDelegate
{
    Q_OBJECT
  public:
    FluShortcutMenuItemDelegate(QObject *parent = nullptr);

  public:
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
};
