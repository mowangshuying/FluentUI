#include "FluIndicatorMenuItemDeleage.h"
#include "../FluUtils/FluUtils.h"

FluIndicatorMenuItemDeleage::FluIndicatorMenuItemDeleage(QObject *parent /*= nullptr*/) : FluMenuItemDelegate(parent)
{
}

void FluIndicatorMenuItemDeleage::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    FluMenuItemDelegate::paint(painter, option, index);
    if (isSeparator(index))
        return;

    if (!(option.state & QStyle::State_Selected))
        return;

    painter->save();
    painter->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform | QPainter::TextAntialiasing);
    painter->setPen(Qt::NoPen);
    // painter->setBrush(themeColor());
    if (FluThemeUtils::isLightTheme())
        painter->setBrush(QColor(0, 98, 158));
    else if (FluThemeUtils::isDarkTheme())
        painter->setBrush(QColor(118, 185, 237));
    else if (FluThemeUtils::isAtomOneDarkTheme())
        painter->setBrush(QColor(82, 139, 255));


    painter->drawRoundedRect(6, 9 + option.rect.y(), 3, 15, 1.5, 1.5);
    painter->restore();
}
