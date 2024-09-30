#include "FluTreeViewItemDelegate.h"
#include "FluTreeView.h"
#include <QColor>
#include <QPalette>
#include <QPainter>
#include "../FluUtils/FluUtils.h"

FluTreeViewItemDelegate::FluTreeViewItemDelegate(FluTreeView* parent /*= nullptr*/) : QStyledItemDelegate(parent)
{
    m_treeView = parent;
    updateColor();
}

void FluTreeViewItemDelegate::updateColor()
{
    if (FluThemeUtils::isLightTheme())
    {
        m_hoverBackgroundColor = QColor(0, 0, 0, 16);
        m_selectBackgroundColor = QColor(0, 0, 0, 16);
        m_normalBackgroundColor = QColor(243, 243, 243);
        m_indicatorPenColor = QColor(133, 133, 133);
        m_indicatorBrushColor = QColor(23, 104, 165);
        m_textColor = Qt::black;
    }
    else if (FluThemeUtils::isDarkTheme())
    {
        m_hoverBackgroundColor = QColor(45, 45, 45, 50);
        m_selectBackgroundColor = QColor(45, 45, 45, 50);

        m_normalBackgroundColor = QColor(32, 32, 32);
        m_indicatorBrushColor = QColor(118, 185, 237);
        m_indicatorPenColor = QColor(153, 153, 153);
        m_textColor = Qt::white;
    }
}

void FluTreeViewItemDelegate::initStyleOption(QStyleOptionViewItem* option, const QModelIndex& index) const
{
    QStyledItemDelegate::initStyleOption(option, index);
}

void FluTreeViewItemDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    QStyledItemDelegate::paint(painter, option, index);
    paintRect(painter, option, index);
    // paintCheckBox(painter, option, index);
    // paintArrow(painter, option, index);
}

void FluTreeViewItemDelegate::paintRect(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    painter->save();

    bool bSelected = option.state & QStyle::State_Selected;
    bool bHover = option.state & QStyle::State_MouseOver;

    // if (index.column() == 0)
    {
        painter->setPen(Qt::NoPen);
        painter->setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);

        QRect backgroundRect = QRect(0, option.rect.y(), m_treeView->width(), option.rect.height());

        painter->setBrush(m_normalBackgroundColor);
        painter->drawRect(backgroundRect);

        QRect hoverSelectedRect(backgroundRect.x(), backgroundRect.y() + 2, backgroundRect.width(), backgroundRect.height() - 4);
        QRect indicatorRect(hoverSelectedRect.x() + 2, hoverSelectedRect.y() + 7, 3, 18);
        if (bSelected)
        {
            // draw selected;
            painter->setBrush(m_selectBackgroundColor);
            painter->drawRoundedRect(hoverSelectedRect, 4, 4);

            // draw indicator;
            painter->setBrush(m_indicatorBrushColor);
            painter->drawRoundedRect(indicatorRect, 1.5, 1.5);
        }
        else if (bHover)
        {
            painter->setBrush(m_hoverBackgroundColor);
            painter->drawRoundedRect(hoverSelectedRect, 4, 4);
        }
    }

    // if (index.column() == 0)
    {
        QString text = index.data(Qt::DisplayRole).toString();
        LOG_DEBUG << "Rect:" << option.rect << ", text:" << text;
        QRect textRect(option.rect.x(), option.rect.y(), option.rect.width(), option.rect.height());
        painter->setPen(Qt::red);
        painter->drawText(textRect, Qt::AlignLeft | Qt::AlignVCenter, text);
        // painter->drawRect(textRect);
    }

    painter->restore();
}

void FluTreeViewItemDelegate::paintCheckBox(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    painter->save();
    painter->setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing | QPainter::SmoothPixmapTransform);
    bool isNull = index.data(Qt::CheckStateRole).isNull();
    if (isNull)
    {
        painter->restore();
        return;
    }

    int nX = option.rect.x() + 20 + 2;
    int nY = option.rect.center().y() - 8;
    int nRadius = 4;

    QRect checkBoxRect(nX, nY, 20, 20);
    int nChecked = index.data(Qt::CheckStateRole).toInt();
    if (nChecked == 2)
    {
        QPen pen;
        pen.setWidth(1);
        pen.setColor(m_indicatorPenColor);
        painter->setPen(pen);
        painter->setBrush(m_indicatorBrushColor);
        painter->drawRoundedRect(checkBoxRect, nRadius, nRadius);

        QPixmap pixmap = FluIconUtils::getFluentIconPixmap(FluAwesomeType::CheckMark, Qt::white);
        painter->drawPixmap(checkBoxRect, pixmap);
    }
    else if (nChecked == 1)
    {
        // painter->setPen(Qt::red);
        QPen pen;
        pen.setWidth(1);
        pen.setColor(m_indicatorPenColor);
        painter->setPen(pen);

        painter->setBrush(m_indicatorBrushColor);
        painter->drawRoundedRect(checkBoxRect, nRadius, nRadius);

        QPixmap pixmap = FluIconUtils::getFluentIconPixmap(FluAwesomeType::SubtractBold, Qt::white);
        painter->drawPixmap(checkBoxRect, pixmap);
    }
    else
    {
        // painter->setPen(Qt::red);
        QPen pen;
        pen.setWidth(1);
        pen.setColor(m_indicatorPenColor);
        painter->setPen(pen);
        painter->setBrush(m_normalBackgroundColor);
        painter->drawRoundedRect(checkBoxRect, nRadius, nRadius);
    }
}

void FluTreeViewItemDelegate::paintArrow(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    painter->save();
    painter->setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing | QPainter::SmoothPixmapTransform);

    bool bSelected = option.state & QStyle::State_Selected;
    bool bHover = option.state & QStyle::State_MouseOver;

    int nX = option.rect.x();
    int nY = option.rect.center().y() - 8;
    int nRadius = 4;

    QRect arrowRect(nX, nY, 20, 20);
#if (QT_VERSION >= QT_VERSION_CHECK(6, 0, 0))
    if (m_treeView->itemFromIndex(index)->childCount() > 0)
    {
        if (m_treeView->isExpanded(index))
        {
            QPixmap pixmap = FluIconUtils::getFluentIconPixmap(FluAwesomeType::ChevronUp, FluThemeUtils::getUtils()->getTheme());
            painter->drawPixmap(arrowRect, pixmap);
        }
        else
        {
            QPixmap pixmap = FluIconUtils::getFluentIconPixmap(FluAwesomeType::ChevronDown, FluThemeUtils::getUtils()->getTheme());
            painter->drawPixmap(arrowRect, pixmap);
        }
    }
#endif

    painter->restore();
}
