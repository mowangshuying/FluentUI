#include "FluRoundMenuView.h"
#include "FluShortcutMenuItemDelegate.h"
#include "FluMenuAniMgr.h"

FluRoundMenuView::FluRoundMenuView(QWidget* parent /*= nullptr*/) : QListWidget(parent)
{
    m_itemHeight = 28;
    m_maxVisibleItem = -1;
    m_isBTSpacing = false;

    setViewportMargins(0, 6, 0, 6);
    setTextElideMode(Qt::ElideNone);
    setDragEnabled(false);
    setMouseTracking(true);
    setIconSize(QSize(20, 20));
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
        int h = qMin(wndSize.height(), m_maxVisibleItem * m_itemHeight + margins.top() + margins.bottom() + 3);
        wndSize.setHeight(h);
    }

    setFixedSize(wndSize);
    updateGeometries();
}

void FluRoundMenuView::setItemHeight(int height)
{
    if (height == m_itemHeight)
        return;

    for (int i = 0; i < count(); i++)
    {
        QListWidgetItem* pItem = item(i);
        QWidget* pWidget = itemWidget(pItem);
        if (pWidget == nullptr)
            pItem->setSizeHint(QSize(pItem->sizeHint().width(), height));
    }

    m_itemHeight = height;
    adjustSize();
}

void FluRoundMenuView::setMaxVisibleItems(int num)
{
    m_maxVisibleItem = num;
    adjustSize();
}

int FluRoundMenuView::getMaxVisibleItems()
{
    return m_maxVisibleItem;
}

int FluRoundMenuView::heightForAnimation(QPoint pos, FluMenuAniType aniType)
{
    int h = itemsHeight();
    return h;
}

int FluRoundMenuView::itemsHeight()
{
    int visibleItemCount = count();
    if (m_maxVisibleItem > 0 && m_maxVisibleItem < count())
        visibleItemCount = m_maxVisibleItem;

    int h = 0;
    for (int i = 0; i < count(); i++)
    {
        h += item(i)->sizeHint().height();
    }

    h += viewportMargins().top() + viewportMargins().bottom();
    return h;
}

bool FluRoundMenuView::getBTSpacing()
{
    return m_isBTSpacing;
}

void FluRoundMenuView::setBTSpacing(bool isBTSpacing)
{
    m_isBTSpacing = isBTSpacing;
}

void FluRoundMenuView::hockEvent(QEvent* event)
{
    FluRoundMenuView::event(event);
}

void FluRoundMenuView::onThemeChanged()
{
    FluStyleSheetUtils::setQssByFileName("FluRoundMenuView.qss", this, FluThemeUtils::getUtils()->getTheme());
}
