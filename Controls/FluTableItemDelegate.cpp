#include "FluTableItemDelegate.h"
#include "FluTableView.h"

FluTableItemDelegate::FluTableItemDelegate(FluTableView *parent) : QStyledItemDelegate(parent)
{
    m_tableView = parent;
}

void FluTableItemDelegate::setHoverRow(int hoverRow)
{
    m_hoverRow = hoverRow;
}

void FluTableItemDelegate::setPressedRow(int pressedRow)
{
    m_pressedRow = pressedRow;
}

void FluTableItemDelegate::setSelectedRows(std::list<QModelIndex> indexList)
{
    m_selectedRows.clear();
    for (auto index : indexList)
    {
        m_selectedRows.insert(index.row());
        if (index.row() == m_pressedRow)
            setPressedRow(-1);
    }
}

QSize FluTableItemDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QSize tmpSize = QStyledItemDelegate::sizeHint(option, index);
    tmpSize = tmpSize.grownBy(QMargins(0, m_margin, 0, m_margin));
    return tmpSize;
}

QWidget *FluTableItemDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if (m_tableView->judgeReadOnlyCol(index.column()))
        return nullptr;

    auto lineEdit = new FluLineEdit(parent);
    return lineEdit;
}

void FluTableItemDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QRect tmpRect = option.rect;
    int x = std::max(4, tmpRect.x());
    int y = tmpRect.y() + (tmpRect.height() - editor->height()) / 2;
    int w = tmpRect.width();
    if (index.column() == 0)
        w -= 8;

    int h = tmpRect.height();
    editor->setGeometry(x, y, w, h - 4);
}

void FluTableItemDelegate::initStyleOption(QStyleOptionViewItem *option, const QModelIndex &index) const
{
    QStyledItemDelegate::initStyleOption(option, index);

    auto textColor = Qt::black;
    if (FluThemeUtils::isDarkTheme())
        textColor = Qt::white;

    option->palette.setColor(QPalette::Text, textColor);
    option->palette.setColor(QPalette::HighlightedText, textColor);
}

void FluTableItemDelegate::drawSelfIndicator(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    int marginH = 0.257 * option.rect.height();

    int x = 4;
    int y = option.rect.y() + marginH;
    int w = 3;
    int h = option.rect.height() - 2 * marginH;

    if (FluThemeUtils::isLightTheme())
        painter->setBrush(QColor(0, 90, 158));
    else if (FluThemeUtils::isDarkTheme())
        painter->setBrush(QColor(118, 185, 237));
    painter->drawRoundedRect(x, y, w, h, 1.5, 1.5);
}

void FluTableItemDelegate::drawSelfBackground(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    int r = 5;
    if (index.column() == 0)
    {
        QRect tmpRect = option.rect.adjusted(4, 0, r + 1, 0);
        painter->drawRoundedRect(tmpRect, r, r);
    }
    else if (index.column() == index.model()->columnCount(index.parent()) - 1)
    {
        QRect tmpRect = option.rect.adjusted(-r - 1, 0, -4, 0);
        painter->drawRoundedRect(tmpRect, r, r);
    }
    else
    {
        QRect tmpRect = option.rect.adjusted(-1, 0, 1, 0);
        painter->drawRect(tmpRect);
    }
}

void FluTableItemDelegate::drawSelfCheckBox(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    painter->save();

    painter->setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing | QPainter::SmoothPixmapTransform);
    bool isNull = index.data(Qt::CheckStateRole).isNull();
    if (isNull)
    {
        painter->restore();
        return;
    }

    int x = option.rect.x() + 20 + 2;
    int y = option.rect.center().y() - 8;
    int radius = 4;

    QRect checkBoxRect(x, y, 20, 20);
    int checked = index.data(Qt::CheckStateRole).toInt();
    if (checked == 2)
    {
        QPen pen;
        pen.setWidth(1);
        // pen.setColor(m_indicatorPenColor);
        if (FluThemeUtils::isLightTheme())
            pen.setColor(QColor(133, 133, 133));
        else if (FluThemeUtils::isDarkTheme())
            pen.setColor(QColor(153, 153, 153));

        painter->setPen(pen);
        // painter->setBrush(m_indicatorBrushColor);

        if (FluThemeUtils::isLightTheme())
            painter->setBrush(QColor(23, 104, 165));
        else if (FluThemeUtils::isDarkTheme())
            painter->setBrush(QColor(118, 185, 237));

        painter->drawRoundedRect(checkBoxRect, radius, radius);

        QPixmap pixmap = FluIconUtils::getFluentIconPixmap(FluAwesomeType::CheckMark, Qt::white);
        painter->drawPixmap(checkBoxRect, pixmap);
    }
    else if (checked == 1)
    {
        QPen pen;
        pen.setWidth(1);
        // pen.setColor(m_indicatorPenColor);
        if (FluThemeUtils::isLightTheme())
            pen.setColor(QColor(133, 133, 133));
        else if (FluThemeUtils::isDarkTheme())
            pen.setColor(QColor(153, 153, 153));
        painter->setPen(pen);

        // painter->setBrush(m_indicatorBrushColor);
        if (FluThemeUtils::isLightTheme())
            painter->setBrush(QColor(23, 104, 165));
        else if (FluThemeUtils::isDarkTheme())
            painter->setBrush(QColor(118, 185, 237));

        painter->drawRoundedRect(checkBoxRect, radius, radius);

        QPixmap pixmap = FluIconUtils::getFluentIconPixmap(FluAwesomeType::SubtractBold, Qt::white);
        painter->drawPixmap(checkBoxRect, pixmap);
    }
    else
    {
        QPen pen;
        pen.setWidth(1);

        if (FluThemeUtils::isLightTheme())
            pen.setColor(QColor(0, 0, 0, 122));
        else if (FluThemeUtils::isDarkTheme())
            pen.setColor(QColor(255, 255, 142));
        painter->setPen(pen);

        if (FluThemeUtils::isLightTheme())
            painter->setBrush(QColor(0, 0, 0, 6));
        else if (FluThemeUtils::isDarkTheme())
            painter->setBrush(QColor(0, 0, 0, 26));

        painter->drawRoundedRect(checkBoxRect, radius, radius);
    }

    painter->restore();
}

void FluTableItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QStyledItemDelegate::paint(painter, option, index);
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);

    painter->setClipping(true);
    painter->setClipRect(option.rect);

    option.rect.adjusted(0, m_margin, 0, -m_margin);

    bool isHover = m_hoverRow == index.row();
    bool isPressed = m_pressedRow == index.row();
    bool isAlternate = index.row() % 2 == 0 && m_tableView->alternatingRowColors();
    bool isSelected = std::find(m_selectedRows.begin(), m_selectedRows.end(), index.row()) != m_selectedRows.end();

    if (FluThemeUtils::isLightTheme())
    {
        if (!isSelected)
        {
            if (isPressed)
            {
                painter->setBrush(QColor(0, 0, 0, 6));
            }
            else if (isHover)
            {
                painter->setBrush(QColor(0, 0, 0, 12));
            }
            else if (isAlternate)
            {
                painter->setBrush(QColor(0, 0, 0, 5));
            }
        }
        else
        {
            if (isPressed)
            {
                painter->setBrush(QColor(0, 0, 0, 9));
            }
            else if (isHover)
            {
                painter->setBrush(QColor(0, 0, 0, 25));
            }
            else
            {
                painter->setBrush(QColor(0, 0, 0, 17));
            }
        }
    }
    else if (FluThemeUtils::isDarkTheme())
    {
        if (!isSelected)
        {
            if (isPressed)
            {
                painter->setBrush(QColor(255, 255, 255, 9));
            }
            else if (isHover)
            {
                painter->setBrush(QColor(255, 255, 255, 12));
            }
            else if (isAlternate)
            {
                painter->setBrush(QColor(255, 255, 255, 5));
            }
        }
        else
        {
            if (isPressed)
            {
                painter->setBrush(QColor(255, 255, 255, 15));
            }
            else if (isHover)
            {
                painter->setBrush(QColor(255, 255, 255, 25));
            }
            else
            {
                painter->setBrush(QColor(255, 255, 255, 17));
            }
        }
    }

    drawSelfBackground(painter, option, index);
    if (isSelected && index.column() == 0 && m_tableView->horizontalScrollBar()->value() == 0)
    {
        drawSelfIndicator(painter, option, index);
    }

    if (index.data(Qt::CheckStateRole).isValid())
        drawSelfIndicator(painter, option, index);

    painter->restore();
}
