#include "FluTreeViewItemDelegate.h"
#include "FluTreeView.h"
#include <QColor>
#include <QPalette>
#include <QPainter>
#include "../FluUtils/FluUtils.h"
#include <QFont>

FluTreeViewItemDelegate::FluTreeViewItemDelegate(FluTreeView* parent /*= nullptr*/) : QStyledItemDelegate(parent)
{
    m_treeView = parent;
}

void FluTreeViewItemDelegate::initStyleOption(QStyleOptionViewItem* option, const QModelIndex& index) const
{
    QStyledItemDelegate::initStyleOption(option, index);

    // set font size;
    QFont tmpFont;
    tmpFont.setPixelSize(14);
    tmpFont.setWeight(QFont::Normal);
    option->font = tmpFont;

    option->palette.setColor(QPalette::Text, m_textColorEx);
    option->palette.setColor(QPalette::HighlightedText, m_textColorEx);

}

void FluTreeViewItemDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    painter->setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
    QStyledItemDelegate::paint(painter, option, index);
    drawBackground(painter, option, index);
    drawCheckBox(painter, option, index);
    drawIndicator(painter, option, index);
}

void FluTreeViewItemDelegate::drawBackground(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    painter->save();
    painter->setPen(Qt::NoPen);

    bool bSelected = option.state & QStyle::State_Selected;
    bool bHover = option.state & QStyle::State_MouseOver;

    if (!bSelected && !bHover)
    {
        painter->restore();
        return;
    }

    int tmpH = option.rect.height() - 4;
    QColor tmpBrushC = m_backgroundColorEx;
    painter->setBrush(QBrush(tmpBrushC));
    painter->drawRoundedRect(4, option.rect.y() + 2, m_treeView->width() - 8, option.rect.height() - 4, 4, 4);
    painter->restore();
}

void FluTreeViewItemDelegate::drawCheckBox(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const
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

    if (nChecked == Qt::CheckState::Unchecked)
    {
        painter->setBrush(m_unCheckedBrushColorEx);
        painter->setPen(m_unCheckedPenColorEx);
        painter->drawRoundedRect(checkBoxRect, nRadius, nRadius);
    }
    else
    {
       // if (FluThemeUtils::isLightTheme())
       // {
            // painter->setBrush(QColor(0, 90, 158));
            // painter->setPen(QColor(0, 90, 158));
            painter->setBrush(m_checkedBrushColorEx);
            painter->setPen(m_checkedPenColorEx);
            painter->drawRoundedRect(checkBoxRect, nRadius, nRadius);
            if (nChecked == Qt::CheckState::Checked)
            {
                QPixmap pixmap = FluIconUtils::getFluentIconPixmap(FluAwesomeType::CheckMark, FluThemeUtils::getUtils()->getTheme());
                painter->drawPixmap(checkBoxRect, pixmap);
            }
            else if (nChecked == Qt::CheckState::PartiallyChecked)
            {
                QPixmap pixmap = FluIconUtils::getFluentIconPixmap(FluAwesomeType::SubtractBold, FluThemeUtils::getUtils()->getTheme());
                painter->drawPixmap(checkBoxRect, pixmap);
            }
       // }
        //else if (FluThemeUtils::isDarkTheme())
        //{
        //    // painter->setBrush(QColor(118, 185, 237));
        //    // painter->setPen(QColor(118, 185, 237));
        //    painter->setBrush(m_checkedBrushColorEx);
        //    painter->setPen(m_checkedPenColorEx);
        //    painter->drawRoundedRect(checkBoxRect, nRadius, nRadius);
        //    if (nChecked == Qt::CheckState::Checked)
        //    {
        //        QPixmap pixmap = FluIconUtils::getFluentIconPixmap(FluAwesomeType::CheckMark, FluThemeUtils::getUtils()->getTheme());
        //        painter->drawPixmap(checkBoxRect, pixmap);
        //    }
        //    else if (nChecked == Qt::CheckState::PartiallyChecked)
        //    {
        //        QPixmap pixmap = FluIconUtils::getFluentIconPixmap(FluAwesomeType::SubtractBold, FluThemeUtils::getUtils()->getTheme());
        //        painter->drawPixmap(checkBoxRect, pixmap);
        //    }
        //}
    }
    painter->restore();
}

void FluTreeViewItemDelegate::drawIndicator(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    painter->save();
    painter->setPen(Qt::NoPen);

    bool bSelected = option.state & QStyle::State_Selected;

    if (!bSelected)
    {
        painter->restore();
        return;
    }

    int tmpH = option.rect.height() - 4;
    QColor tmpBrushC;
    tmpBrushC = m_indicatorColorEx;
    painter->setBrush(QBrush(tmpBrushC));

    painter->drawRoundedRect(4, 9 + option.rect.y(), 3, option.rect.height() - 17, 1.5, 1.5);
    painter->restore();
}
