#include "FluTreeView.h"
#include <QHeaderView>
#include "../FluUtils/FluStyleSheetUitls.h"

FluTreeView::FluTreeView(QWidget *parent /*= nullptr*/) : QTreeWidget(parent)
{
    m_delegate = new FluTreeViewItemDelegate(this);
    setItemDelegate(m_delegate);

    header()->setHighlightSections(false);
    header()->setDefaultAlignment(Qt::AlignCenter);

    FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluTreeView.qss", this);
}

void FluTreeView::drawBranches(QPainter *painter, const QRect &rect, const QModelIndex &index) const
{
    // rect.setX(rect.x() + 15);
    QRect barcnchesRect(rect.x() + 16, rect.y(), rect.width(), rect.height());
    QTreeWidget::drawBranches(painter, barcnchesRect, index);
}
