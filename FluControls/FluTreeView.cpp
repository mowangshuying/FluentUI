#include "FluTreeView.h"
#include <QHeaderView>
#include "../FluUtils/FluStyleSheetUitls.h"

FluTreeView::FluTreeView(QWidget *parent /*= nullptr*/) : QTreeWidget(parent)
{
    m_ItemDelegate = new FluTreeViewItemDelegate(this);
    m_scrollDelegate = new FluScrollDelegate(this);

    setIconSize(QSize(16, 16));
    setItemDelegate(m_ItemDelegate);

    header()->setHighlightSections(false);
    header()->setDefaultAlignment(Qt::AlignCenter);

    onThemeChanged();
    connect(FluThemeUtils::getUtils(), &FluThemeUtils::themeChanged, [=]() { onThemeChanged(); });
}

void FluTreeView::drawBranches(QPainter *painter, const QRect &rect, const QModelIndex &index) const
{
    QRect barcnchesRect(rect.x() + 16, rect.y(), rect.width(), rect.height());
    QTreeWidget::drawBranches(painter, barcnchesRect, index);
}

void FluTreeView::onThemeChanged()
{
    if (FluThemeUtils::isLightTheme())
    {
        // m_delegate->updateColor();
        FluStyleSheetUitls::setQssByFileName(FLURC("StyleSheet/light/FluTreeView.qss"), this);
    }
    else
    {
        // m_delegate->updateColor();
        FluStyleSheetUitls::setQssByFileName(FLURC("StyleSheet/dark/FluTreeView.qss"), this);
    }
}
