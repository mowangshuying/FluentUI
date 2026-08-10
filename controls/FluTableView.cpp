#include "FluTableView.h"
#include <QPainter>

FluTableView::FluTableView(QWidget* parent /*= nullptr*/) : QTableWidget(parent)
{
    m_tableItemDelegate = new FluTableItemDelegate(this);
    m_scrollDelegate = new FluScrollDelegate(this);

    setShowGrid(false);
    setMouseTracking(true);
    setAlternatingRowColors(true);
    setItemDelegate(m_tableItemDelegate);
    setSelectionBehavior(QTableWidget::SelectRows);
    horizontalHeader()->setHighlightSections(false);
    verticalHeader()->setHighlightSections(false);
    verticalHeader()->setDefaultSectionSize(38);
    horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    // Column sorting by header click (keeps the self-painted delegate intact).
    setSortingEnabled(true);

    onThemeChanged();
    connect(FluThemeUtils::getUtils(), &FluThemeUtils::themeChanged, this, [=](FluTheme theme) { onThemeChanged(); });
}

void FluTableView::setCurrentCell(int row, int column)
{
    QTableWidget::setCurrentCell(row, column);
}

void FluTableView::setCurrentCell(int row, int column, QItemSelectionModel::SelectionFlags command)
{
    QTableWidget::setCurrentCell(row, column, command);
}

void FluTableView::setHoverRow(int row)
{
    m_tableItemDelegate->setHoverRow(row);
    viewport()->update();
}

void FluTableView::setPressedRow(int row)
{
    m_tableItemDelegate->setPressedRow(row);
    viewport()->update();
}

void FluTableView::setSelectedRows(std::list<QModelIndex> indexList)
{
    m_tableItemDelegate->setSelectedRows(indexList);
    viewport()->update();
}

std::set<int> FluTableView::getReadOnlySet()
{
    return m_readOnlySet;
}

bool FluTableView::judgeReadOnlyCol(int col)
{
    return m_readOnlySet.find(col) != m_readOnlySet.end();
}

void FluTableView::setReadOnlySet(std::set<int> readOnlySet)
{
    m_readOnlySet = readOnlySet;
}

void FluTableView::setItemDelegate(FluTableItemDelegate* delegate)
{
    if (!delegate)
        return;

    m_tableItemDelegate = delegate;
    QTableView::setItemDelegate(delegate);
}

void FluTableView::selectRow(int row)
{
    QTableView::selectRow(row);
    updateSelectedRows();
}

void FluTableView::clearSelection()
{
    QTableView::clearSelection();
    updateSelectedRows();
}

void FluTableView::setCurrentIndex(QModelIndex index)
{
    QTableView::setCurrentIndex(index);
    updateSelectedRows();
}

void FluTableView::updateSelectedRows()
{
    QModelIndexList modelIndexList = selectedIndexes();
    std::list<QModelIndex> list;
    list.insert(list.begin(), modelIndexList.begin(), modelIndexList.end());

    setSelectedRows(list);
}

void FluTableView::setSortingEnabled(bool enable)
{
    QTableWidget::setSortingEnabled(enable);
    // Sorting may reorder rows; refresh the delegate's cached selection indices.
    updateSelectedRows();
}

void FluTableView::leaveEvent(QEvent* event)
{
    QTableView::leaveEvent(event);
    setHoverRow(-1);
}

void FluTableView::resizeEvent(QResizeEvent* event)
{
    QTableView::resizeEvent(event);
    viewport()->update();
}

void FluTableView::keyPressEvent(QKeyEvent* event)
{
    QTableView::keyPressEvent(event);
}

void FluTableView::mousePressEvent(QMouseEvent* event)
{
    QTableWidget::mousePressEvent(event);

    QModelIndex modelIndex = indexAt(event->pos());
    if (modelIndex.isValid())
        setPressedRow(modelIndex.row());
}

void FluTableView::mouseReleaseEvent(QMouseEvent* event)
{
    QTableWidget::mouseReleaseEvent(event);
    setPressedRow(-1);
}

void FluTableView::paintEvent(QPaintEvent* event)
{
    QTableView::paintEvent(event);

    if (model() && model()->rowCount() == 0)
    {
        QPainter painter(viewport());
        QColor emptyColor;
        if (FluThemeUtils::isLightTheme())
            emptyColor = QColor(96, 96, 96);
        else
            emptyColor = QColor(140, 140, 140);

        painter.setPen(emptyColor);
        painter.drawText(viewport()->rect(), Qt::AlignCenter, tr("No data"));
    }
}

void FluTableView::onThemeChanged()
{
    FluStyleSheetUtils::setQssByFileName("FluTableView.qss", this, FluThemeUtils::getUtils()->getTheme());
}