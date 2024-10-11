#include "FluListViewItemDelegate.h"

FluListViewItemDelegate::FluListViewItemDelegate(QWidget* parent /*= nullptr*/) : QStyledItemDelegate(parent)
{
}

void FluListViewItemDelegate::initStyleOption(QStyleOptionViewItem* option, const QModelIndex& index) const
{
    QStyledItemDelegate::initStyleOption(option, index);
    QFont textFont = QFont();
    textFont.setPixelSize(12);
    option->font = textFont;
}

void FluListViewItemDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    QStyledItemDelegate::paint(painter, option, index);
    QString text = index.data(Qt::DisplayRole).toString();
    painter->save();

    painter->setPen(Qt::NoPen);
    painter->setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);

    QRect backgroundRect = option.rect;
    painter->setBrush(QColor(243, 243, 243));
    if (FluThemeUtils::isDarkTheme())
    {
        painter->setBrush(QColor(32, 32, 32));
    }

    painter->drawRect(backgroundRect);

    QRect hoverSelectedRect(backgroundRect.x() + 2, backgroundRect.y() + 2, backgroundRect.width() - 4, backgroundRect.height() - 4);
    if (option.state.testFlag(QStyle::State_MouseOver) || option.state.testFlag(QStyle::State_Selected))
    {
        painter->setBrush(QColor(234, 234, 234));
        if (FluThemeUtils::isDarkTheme())
        {
            painter->setBrush(QColor(45, 45, 45));
        }

        painter->drawRoundedRect(hoverSelectedRect, 4, 4);
    }

    if (option.state.testFlag(QStyle::State_Selected))
    {
        QRect indicatorRect(hoverSelectedRect.x(), hoverSelectedRect.y() + 9, 3, 18);
        painter->setBrush(QColor(0, 90, 158));
        if (FluThemeUtils::isDarkTheme())
        {
            painter->setBrush(QColor(118, 185, 237));
        }

        painter->drawRoundedRect(indicatorRect, 2, 2);
    }

    QRect textRect(backgroundRect.x() + 12, backgroundRect.y() + 2, backgroundRect.width() - 12, backgroundRect.height() - 4);
    painter->setPen(Qt::black);
    if (FluThemeUtils::isDarkTheme())
    {
        painter->setPen(Qt::white);
    }
    painter->drawText(textRect, Qt::AlignLeft | Qt::AlignVCenter, text);

    painter->restore();
}

QSize FluListViewItemDelegate::sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    QSize tmpSize = QStyledItemDelegate::sizeHint(option, index);
    tmpSize.setHeight(40);
    return tmpSize;
}
