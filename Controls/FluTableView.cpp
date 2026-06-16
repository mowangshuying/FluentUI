#include "FluTableView.h"

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

    // FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluTableView.qss", this);
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

void FluTableView::setHoverRow(int nRow)
{
    m_tableItemDelegate->setHoverRow(nRow);
    viewport()->update();
}

void FluTableView::setPressedRow(int nRow)
{
    m_tableItemDelegate->setPressedRow(nRow);
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

bool FluTableView::judgeReadOnlyCol(int nCol)
{
    return m_readOnlySet.find(nCol) != m_readOnlySet.end();
}

void FluTableView::setReadOnlySet(std::set<int> readOnlySet)
{
    m_readOnlySet = readOnlySet;
}

void FluTableView::setItemDelegate(FluTableItemDelegate* delegate)
{
    QTableView::setItemDelegate(m_tableItemDelegate);
    m_tableItemDelegate = delegate;
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
    if (event->button() == Qt::LeftButton)
        return;

    QModelIndex modelIndex = indexAt(event->pos());
    if (modelIndex.isValid())
    {
        setPressedRow(modelIndex.row());
    }
}

void FluTableView::mouseReleaseEvent(QMouseEvent* event)
{
    QTableWidget::mouseReleaseEvent(event);
}

void FluTableView::onThemeChanged()
{
    FluStyleSheetUitls::setQssByFileName("FluTableView.qss", this, FluThemeUtils::getUtils()->getTheme());
}
