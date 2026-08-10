#include "FluTableItemDelegate.h"
#include "FluTableView.h"

#include <algorithm>

namespace
{
// Visual/metric constants aligned with WinUI 3 table styling.
constexpr int kRowRadius = 5;
constexpr int kCellHorizontalPadding = 4;
constexpr int kIndicatorXOffset = 4;
constexpr int kIndicatorWidth = 3;
constexpr qreal kIndicatorMarginRatio = 0.257;
constexpr int kCheckBoxSize = 20;
constexpr int kCheckBoxRadius = 4;
constexpr int kCheckBoxLeftPadding = 22; // 20 (editorial indent) + 2 (glyph offset)
constexpr int kEditorTopPadding = 4;
constexpr int kEditorLeftPadding = 8;
} // namespace

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
    int x = std::max(kEditorLeftPadding, tmpRect.x());
    int y = tmpRect.y() + (tmpRect.height() - editor->height()) / 2;
    int w = tmpRect.width();
    if (index.column() == 0)
        w -= kEditorLeftPadding;

    int h = tmpRect.height();
    editor->setGeometry(x, y, w, h - kEditorTopPadding);
}

void FluTableItemDelegate::initStyleOption(QStyleOptionViewItem *option, const QModelIndex &index) const
{
    QStyledItemDelegate::initStyleOption(option, index);

    const QColor color = textColor();
    option->palette.setColor(QPalette::Text, color);
    option->palette.setColor(QPalette::HighlightedText, color);
}

void FluTableItemDelegate::drawSelfIndicator(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    int marginH = static_cast<int>(kIndicatorMarginRatio * option.rect.height());

    int x = kIndicatorXOffset;
    int y = option.rect.y() + marginH;
    int w = kIndicatorWidth;
    int h = option.rect.height() - 2 * marginH;

    painter->setBrush(indicatorColor());
    painter->drawRoundedRect(x, y, w, h, 1.5, 1.5);
}

void FluTableItemDelegate::drawSelfBackground(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    int lastColumn = index.model()->columnCount(index.parent()) - 1;
    if (index.column() == 0)
    {
        QRect tmpRect = option.rect.adjusted(kCellHorizontalPadding, 0, kRowRadius + 1, 0);
        painter->drawRoundedRect(tmpRect, kRowRadius, kRowRadius);
    }
    else if (index.column() == lastColumn)
    {
        QRect tmpRect = option.rect.adjusted(-kRowRadius - 1, 0, -kCellHorizontalPadding, 0);
        painter->drawRoundedRect(tmpRect, kRowRadius, kRowRadius);
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

    int x = option.rect.x() + kCheckBoxLeftPadding;
    int y = option.rect.center().y() - kCheckBoxSize / 2;

    QRect checkBoxRect(x, y, kCheckBoxSize, kCheckBoxSize);
    int checked = index.data(Qt::CheckStateRole).toInt();

    QPen pen;
    pen.setWidth(1);

    if (checked == 2 || checked == 1)
    {
        pen.setColor(checkboxBorderColor());
        painter->setPen(pen);
        painter->setBrush(checkboxFillColor());

        painter->drawRoundedRect(checkBoxRect, kCheckBoxRadius, kCheckBoxRadius);

        QPixmap pixmap = FluIconUtils::getFluentIconPixmap(checked == 2 ? FluAwesomeType::CheckMark : FluAwesomeType::SubtractBold, Qt::white);
        painter->drawPixmap(checkBoxRect, pixmap);
    }
    else
    {
        if (FluThemeUtils::isLightTheme())
        {
            pen.setColor(QColor(0, 0, 0, 122));
            painter->setBrush(QColor(0, 0, 0, 6));
        }
        else
        {
            pen.setColor(QColor(255, 255, 255, 180));
            painter->setBrush(QColor(255, 255, 255, 26));
        }

        painter->setPen(pen);
        painter->drawRoundedRect(checkBoxRect, kCheckBoxRadius, kCheckBoxRadius);
    }

    painter->restore();
}

void FluTableItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    // Suppress the built-in checkbox so the themed checkbox is painted below.
    QStyleOptionViewItem opt = option;
    if (index.data(Qt::CheckStateRole).isValid())
        opt.features &= ~QStyleOptionViewItem::HasCheckIndicator;

    QStyledItemDelegate::paint(painter, opt, index);

    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);

    painter->setClipping(true);
    painter->setClipRect(option.rect);

    bool isHover = m_hoverRow == index.row();
    bool isPressed = m_pressedRow == index.row();
    bool isAlternate = index.row() % 2 == 0 && m_tableView->alternatingRowColors();
    bool isSelected = std::find(m_selectedRows.begin(), m_selectedRows.end(), index.row()) != m_selectedRows.end();

    const bool isLight = FluThemeUtils::isLightTheme();
    const int hoverAlpha = 12;
    const int alternateAlpha = 5;
    const int pressedAlpha = isLight ? 6 : 9;
    const int selectedAlpha = 17;
    const int selectedHoverAlpha = 25;
    const int selectedPressedAlpha = isLight ? 9 : 15;

    QColor bgColor;
    if (!isSelected)
        bgColor = overlayColor(isPressed ? pressedAlpha : (isHover ? hoverAlpha : (isAlternate ? alternateAlpha : 0)));
    else
        bgColor = overlayColor(isPressed ? selectedPressedAlpha : (isHover ? selectedHoverAlpha : selectedAlpha));

    if (bgColor.alpha() > 0)
        painter->setBrush(bgColor);

    drawSelfBackground(painter, option, index);

    if (isSelected && index.column() == 0 && m_tableView->horizontalScrollBar()->value() == 0)
    {
        drawSelfIndicator(painter, option, index);
    }

    if (index.data(Qt::CheckStateRole).isValid())
        drawSelfCheckBox(painter, option, index);

    painter->restore();
}

QColor FluTableItemDelegate::indicatorColor() const
{
    if (FluThemeUtils::isLightTheme())
        return QColor(0, 90, 158);
    if (FluThemeUtils::isDarkTheme())
        return QColor(118, 185, 237);
    return QColor(82, 139, 255); // AtomOneDark accent
}

QColor FluTableItemDelegate::textColor() const
{
    if (FluThemeUtils::isLightTheme())
        return Qt::black;
    return Qt::white;
}

QColor FluTableItemDelegate::checkboxBorderColor() const
{
    if (FluThemeUtils::isLightTheme())
        return QColor(133, 133, 133);
    return QColor(153, 153, 153);
}

QColor FluTableItemDelegate::checkboxFillColor() const
{
    if (FluThemeUtils::isLightTheme())
        return QColor(23, 104, 165);
    if (FluThemeUtils::isDarkTheme())
        return QColor(118, 185, 237);
    return QColor(82, 139, 255); // AtomOneDark accent
}

QColor FluTableItemDelegate::overlayColor(int alpha) const
{
    if (FluThemeUtils::isLightTheme())
        return QColor(0, 0, 0, alpha);
    return QColor(255, 255, 255, alpha);
}