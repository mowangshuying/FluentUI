#include "FluListViewItemDelegate.h"

FluListViewItemDelegate::FluListViewItemDelegate(QWidget* parent /*= nullptr*/) : QStyledItemDelegate(parent)
{
}

// QColor;
QColor FluListViewItemDelegate::getBackgroundColorEx() const
{
    return m_backgroundColorEx;
}

void FluListViewItemDelegate::setBackgroundColorEx(QColor color)
{
    m_backgroundColorEx = color;
}

QColor FluListViewItemDelegate::getHoverColorEx() const
{
    return m_hoverColorEx;
}

void FluListViewItemDelegate::setHoverColorEx(QColor color)
{
    m_hoverColorEx = color;
}

QColor FluListViewItemDelegate::getIndicatorColorEx() const
{
    return m_indicatorColorEx;
}

void FluListViewItemDelegate::setIndicatorColorEx(QColor color)
{
    m_indicatorColorEx = color;
}

QColor FluListViewItemDelegate::getTextColorEx() const
{
    return m_textColorEx;
}

void FluListViewItemDelegate::setTextColorEx(QColor color)
{
    m_textColorEx = color;
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
    painter->setBrush(getBackgroundColorEx());
    painter->drawRect(backgroundRect);

    QRect hoverSelectedRect(backgroundRect.x() + 2, backgroundRect.y() + 2, backgroundRect.width() - 4, backgroundRect.height() - 4);
    if (option.state.testFlag(QStyle::State_MouseOver) || option.state.testFlag(QStyle::State_Selected))
    {
        painter->setBrush(getHoverColorEx());
        painter->drawRoundedRect(hoverSelectedRect, 4, 4);
    }

    if (option.state.testFlag(QStyle::State_Selected))
    {
        QRect indicatorRect(hoverSelectedRect.x(), hoverSelectedRect.y() + 9, 3, 18);
        painter->setBrush(getIndicatorColorEx());
        painter->drawRoundedRect(indicatorRect, 2, 2);
    }

    QRect textRect(backgroundRect.x() + 12, backgroundRect.y() + 2, backgroundRect.width() - 12, backgroundRect.height() - 4);
    painter->setPen(getTextColorEx());
    painter->drawText(textRect, Qt::AlignLeft | Qt::AlignVCenter, text);

    painter->restore();
}

QSize FluListViewItemDelegate::sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    QSize tmpSize = QStyledItemDelegate::sizeHint(option, index);
    tmpSize.setHeight(40);
    return tmpSize;
}
