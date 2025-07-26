#include "FluRoundMenuView.h"
#include "FluShortcutMenuItemDelegate.h"
#include "FluMenuAniMgr.h"

FluRoundMenuView::FluRoundMenuView(QWidget* parent /*= nullptr*/) : QListWidget(parent)
{
    m_itemHeight = 28;
    m_maxVisibleItem = -1;
    m_bBTSpacing = false;

    setViewportMargins(0, 6, 0, 6);
    setTextElideMode(Qt::ElideNone);
    setDragEnabled(false);
    setMouseTracking(true);
    setIconSize(QSize(14, 14));
    setItemDelegate(new FluShortcutMenuItemDelegate(this));
    m_scrollDelegate = new FluScrollDelegate(this);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    onThemeChanged();
    connect(FluThemeUtils::getUtils(), &FluThemeUtils::themeChanged, this, [=](FluTheme theme) { onThemeChanged(); });
}

void FluRoundMenuView::insertItem(int row, QListWidgetItem* item)
{
    QListWidget::insertItem(row, item);
    adjustSize();
}

void FluRoundMenuView::addItem(QListWidgetItem* item)
{
    QListWidget::addItem(item);
    adjustSize();
}

QListWidgetItem* FluRoundMenuView::takeItem(int row)
{
    QListWidgetItem* item = QListWidget::takeItem(row);
    adjustSize();
    return item;
}

void FluRoundMenuView::adjustSize(QPoint pos /*= QPoint()*/, FluMenuAniType aniType /*= FluMenuAniType::none*/)
{
    QSize wndSize = QSize(0, 0);
    for (int i = 0; i < count(); i++)
    {
        QSize tmpSizeHint = item(i)->sizeHint();
        wndSize.setWidth(qMax(tmpSizeHint.width(), wndSize.width()));
        wndSize.setHeight(tmpSizeHint.height() + wndSize.height());
    }

    viewport()->adjustSize();

    QMargins margins = viewportMargins();
    wndSize += QSize(margins.left() + margins.right() + 2, margins.top() + margins.bottom() + 3);
    if (m_maxVisibleItem > 0)
    {
        int nH = qMin(wndSize.height(), m_maxVisibleItem * m_itemHeight + margins.top() + margins.bottom() + 3);
        wndSize.setHeight(nH);
    }

    setFixedSize(wndSize);
    updateGeometries();
}

void FluRoundMenuView::setItemHeight(int nHeight)
{
    if (nHeight == m_itemHeight)
        return;

    for (int i = 0; i < count(); i++)
    {
        QListWidgetItem* pItem = item(i);
        QWidget* pWidget = itemWidget(pItem);
        if (pWidget == nullptr)
            pItem->setSizeHint(QSize(pItem->sizeHint().width(), nHeight));
    }

    m_itemHeight = nHeight;
    adjustSize();
}

void FluRoundMenuView::setMaxVisibleItems(int nNum)
{
    m_maxVisibleItem = nNum;
    adjustSize();
}

int FluRoundMenuView::getMaxVisibleItems()
{
    return m_maxVisibleItem;
}

int FluRoundMenuView::heightForAnimation(QPoint pos, FluMenuAniType aniType)
{
    int nH = itemsHeight();
    return nH;
}

int FluRoundMenuView::itemsHeight()
{
    int nVisibleItemCount = count();
    if (m_maxVisibleItem > 0 && m_maxVisibleItem < count())
        nVisibleItemCount = m_maxVisibleItem;

    int nH = 0;
    for (int i = 0; i < count(); i++)
    {
        nH += item(i)->sizeHint().height();
    }

    nH += viewportMargins().top() + viewportMargins().bottom();
    return nH;
}

bool FluRoundMenuView::getBTSpacing()
{
    return m_bBTSpacing;
}

void FluRoundMenuView::setBTSpacing(bool bBTSpacing)
{
    m_bBTSpacing = bBTSpacing;
}

void FluRoundMenuView::hockEvent(QEvent* event)
{
    FluRoundMenuView::event(event);
}

void FluRoundMenuView::onThemeChanged()
{
    FluStyleSheetUitls::setQssByFileName("FluRoundMenuView.qss", this, FluThemeUtils::getUtils()->getTheme());
}
