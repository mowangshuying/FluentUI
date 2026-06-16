#include "FluMenuItemDelegate.h"

FluMenuItemDelegate::FluMenuItemDelegate(QObject *parent /*= nullptr*/) : QStyledItemDelegate(parent)
{
}

bool FluMenuItemDelegate::isSeparator(QModelIndex index) const
{
    return index.model()->data(index, Qt::DecorationRole) == "separator";
}

void FluMenuItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if (!isSeparator(index))
        return QStyledItemDelegate::paint(painter, option, index);

    painter->save();
    int c = 0;
    if (FluThemeUtils::isDarkTheme())
        c = 255;
    else
        c = 0;

    QPen pen = QPen(QColor(c, c, c, 25), 1);
    pen.setCosmetic(true);
    painter->setPen(pen);

    QRect rect = option.rect;
    painter->drawLine(0, rect.y() + 4, rect.width() + 12, rect.y() + 4);
    painter->restore();
}
