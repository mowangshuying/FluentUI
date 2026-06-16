#include <QtWidgets>

#include "FluFlowLayout.h"
//! [1]
FluFlowLayout::FluFlowLayout(QWidget *parent, int margin, int hSpacing, int vSpacing) : QLayout(parent), m_hSpace(hSpacing), m_vSpace(vSpacing)
{
    //	m_hSpace = 10;
    //	m_vSpace = 10;
    setContentsMargins(margin, margin, margin, margin);
}

FluFlowLayout::FluFlowLayout(int margin, int hSpacing, int vSpacing) : m_hSpace(hSpacing), m_vSpace(vSpacing)
{
    setContentsMargins(margin, margin, margin, margin);
}
//! [1]

//! [2]
FluFlowLayout::~FluFlowLayout()
{
    QLayoutItem *item;
    while ((item = takeAt(0)))
        delete item;
}
//! [2]

//! [3]
void FluFlowLayout::addItem(QLayoutItem *item)
{
    itemList.append(item);
}

void FluFlowLayout::setSpacing(int hSpace, int vSpace)
{
    m_hSpace = hSpace;
    m_vSpace = vSpace;
}

//! [3]

//! [4]
int FluFlowLayout::horizontalSpacing() const
{
    if (m_hSpace >= 0)
    {
        return m_hSpace;
    }
    else
    {
        return smartSpacing(QStyle::PM_LayoutHorizontalSpacing);
    }
}

int FluFlowLayout::verticalSpacing() const
{
    if (m_vSpace >= 0)
    {
        return m_vSpace;
    }
    else
    {
        return smartSpacing(QStyle::PM_LayoutVerticalSpacing);
    }
}
//! [4]

//! [5]
int FluFlowLayout::count() const
{
    return itemList.size();
}

QLayoutItem *FluFlowLayout::itemAt(int index) const
{
    return itemList.value(index);
}

QLayoutItem *FluFlowLayout::takeAt(int index)
{
    if (index >= 0 && index < itemList.size())
        return itemList.takeAt(index);
    else
        return 0;
}

void FluFlowLayout::removeAllWidgets()
{
    while (!itemList.isEmpty())
    {
        takeAt(0);
    }
}

//! [5]

//! [6]
Qt::Orientations FluFlowLayout::expandingDirections() const
{
    return (Qt::Orientation)0;
}
//! [6]

//! [7]
bool FluFlowLayout::hasHeightForWidth() const
{
    return true;
}

int FluFlowLayout::heightForWidth(int width) const
{
    int height = doLayout(QRect(0, 0, width, 0), true);
    return height;
}
//! [7]

//! [8]
void FluFlowLayout::setGeometry(const QRect &rect)
{
    QLayout::setGeometry(rect);
    doLayout(rect, false);
}

QSize FluFlowLayout::sizeHint() const
{
    return minimumSize();
}

QSize FluFlowLayout::minimumSize() const
{
    QSize size;
    QLayoutItem *item;
    foreach (item, itemList)
        size = size.expandedTo(item->minimumSize());

    QMargins margins = contentsMargins();
    size += QSize(margins.left() + margins.right(), margins.top() + margins.bottom());
    return size;
}
//! [8]

//! [9]
int FluFlowLayout::doLayout(const QRect &rect, bool testOnly) const
{
    int left, top, right, bottom;
    getContentsMargins(&left, &top, &right, &bottom);
    QRect effectiveRect = rect.adjusted(+left, +top, -right, -bottom);
    int x = effectiveRect.x();
    int y = effectiveRect.y();
    int lineHeight = 0;
    //! [9]

    //! [10]
    QLayoutItem *item;
    foreach (item, itemList)
    {
        QWidget *wid = item->widget();

        if (wid->isHidden())
            continue;

        int spaceX = horizontalSpacing();
        if (spaceX == -1)
            spaceX = wid->style()->layoutSpacing(QSizePolicy::PushButton, QSizePolicy::PushButton, Qt::Horizontal);
        int spaceY = verticalSpacing();
        if (spaceY == -1)
            spaceY = wid->style()->layoutSpacing(QSizePolicy::PushButton, QSizePolicy::PushButton, Qt::Vertical);
        //! [10]
        //! [11]
        int nextX = x + item->sizeHint().width() + spaceX;
        if (nextX - spaceX > effectiveRect.right() && lineHeight > 0)
        {
            x = effectiveRect.x();
            y = y + lineHeight + spaceY;
            nextX = x + item->sizeHint().width() + spaceX;
            lineHeight = 0;
        }

        if (!testOnly)
            item->setGeometry(QRect(QPoint(x, y), item->sizeHint()));

        x = nextX;
        lineHeight = qMax(lineHeight, item->sizeHint().height());
    }
    return y + lineHeight - rect.y() + bottom;
}
//! [11]
//! [12]
int FluFlowLayout::smartSpacing(QStyle::PixelMetric pm) const
{
    QObject *parent = this->parent();
    if (!parent)
    {
        return -1;
    }
    else if (parent->isWidgetType())
    {
        QWidget *pw = static_cast<QWidget *>(parent);
        return pw->style()->pixelMetric(pm, 0, pw);
    }
    else
    {
        return static_cast<QLayout *>(parent)->spacing();
    }
}
//! [12]
