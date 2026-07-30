#include "FluIndicatorMenuItemDeleage.h"
#include "../utils/FluUtils.h"

FluIndicatorMenuItemDeleage::FluIndicatorMenuItemDeleage(QObject *parent /*= nullptr*/) : FluMenuItemDelegate(parent)
{
}

void FluIndicatorMenuItemDeleage::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    FluMenuItemDelegate::paint(painter, option, index);
    if (isSeparator(index))
        return;

    //LOG_DEBUG << option.text;
    if (!(option.state & QStyle::State_Selected))
        return;

    LOG_DEBUG << option.text;
    painter->save();
    painter->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform | QPainter::TextAntialiasing);
    painter->setPen(Qt::NoPen);
    // painter->setBrush(themeColor());
    if (FluThemeUtils::isLightTheme())
        painter->setBrush(QColor(0, 98, 0));
    else if (FluThemeUtils::isDarkTheme())
        painter->setBrush(QColor(118, 185, 237));
    else if (FluThemeUtils::isAtomOneDarkTheme())
        painter->setBrush(QColor(82, 139, 255));

    //qreal height 

    painter->drawRoundedRect(6, option.rect.y() + option.rect.height() * 0.2, 3, option.rect.height() * 0.6, 1.5, 1.5);
    painter->restore();
}
