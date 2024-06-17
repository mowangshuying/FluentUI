#include "FluTreeViewItemDelegate.h"
#include "FluTreeView.h"
#include <QColor>
#include <QPalette>
#include <QPainter>
#include "../FluUtils/FluUtils.h"

FluTreeViewItemDelegate::FluTreeViewItemDelegate(FluTreeView* parent /*= nullptr*/) : QStyledItemDelegate(parent)
{
    m_treeView = parent;
    if (FluThemeUtils::isLightTheme())
    {
        // m_foregroundColor = QColor(55, 55, 55);

        // m_backgroundColor = QColor(243, 243, 243);
        m_hoverBackgroundColor = QColor(0, 0, 0, 16);
        m_selectBackgroundColor = QColor(0, 0, 0, 16);
        m_indicatorColor = QColor(0, 90, 158);
    }
    else if (FluThemeUtils::isDarkTheme())
    {
        // m_foregroundColor = QColor(238, 238, 238);

        // m_backgroundColor = QColor(32, 32, 32);
        m_hoverBackgroundColor = QColor(45, 45, 45, 9);
        m_selectBackgroundColor = QColor(45, 45, 45, 9);

        m_indicatorColor = QColor(118, 185, 237);
    }
}

void FluTreeViewItemDelegate::initStyleOption(QStyleOptionViewItem* option, const QModelIndex& index) const
{
    QStyledItemDelegate::initStyleOption(option, index);
    //option->palette.setColor(QPalette::Text, m_foregroundColor);
    //option->palette.setColor(QPalette::HighlightedText, m_foregroundColor);
}

void FluTreeViewItemDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    QStyledItemDelegate::paint(painter, option, index);
    painter->save();

    bool bSelected = option.state & QStyle::State_Selected;
    bool bHover = option.state & QStyle::State_MouseOver;

    painter->setPen(Qt::NoPen);
    painter->setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);

    QRect backgroundRect = QRect(0, option.rect.y(), m_treeView->width(), option.rect.height());
    QRect hoverSelectedRect(backgroundRect.x(), backgroundRect.y() + 2, backgroundRect.width(), backgroundRect.height() - 4);
    QRect indicatorRect(hoverSelectedRect.x(), hoverSelectedRect.y() + 7, 3, 18);
    if (bSelected)
    {
        // draw selected;
        painter->setBrush(m_selectBackgroundColor);
        painter->drawRoundedRect(hoverSelectedRect, 4, 4);

        // draw indicator;
        painter->setBrush(m_indicatorColor);
        painter->drawRoundedRect(indicatorRect, 4, 4);
    }
    else if (bHover)
    {
        painter->setBrush(m_hoverBackgroundColor);
        painter->drawRoundedRect(hoverSelectedRect, 4, 4);
    }

    painter->restore();
}
