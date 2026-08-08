#include "FluTabBarContent.h"
#include <QPainter>
#include <QPainterPath>
#include <QPaintEvent>
#include <QTimer>

// ---------------------------------------------------------------------------
// Private helper: unified paint layer for FluTabBar visual rendering.
// Sits below all FluTabBarItem widgets (z-order) as a child of m_mainWidget.
// Renders: unselected hover/pressed backgrounds, separator lines,
// and selected tab body (top 8px rounded corners, bottom 4px concave arcs).
// No Q_OBJECT – purely an internal implementation aid.
// ---------------------------------------------------------------------------
class FluTabBarPaintLayer : public QWidget
{
  public:
    explicit FluTabBarPaintLayer(FluTabBarContent* content, QWidget* parent) : QWidget(parent), m_content(content)
    {
        setAttribute(Qt::WA_TransparentForMouseEvents);
        setAttribute(Qt::WA_OpaquePaintEvent, false);
        if (parent)
            setFixedSize(parent->size());
    }

    void setTabHoverColor(const QColor& c)
    {
        m_hoverColor = c;
        update();
    }
    void setTabPressedColor(const QColor& c)
    {
        m_pressedColor = c;
        update();
    }
    void setTabSelectedColor(const QColor& c)
    {
        m_selectedColor = c;
        update();
    }
    void setTabSeparatorColor(const QColor& c)
    {
        m_separatorColor = c;
        update();
    }
    void setTabSelectedStrokeColor(const QColor& c)
    {
        m_selectedStrokeColor = c;
        update();
    }

  protected:
    void paintEvent(QPaintEvent* event) override
    {
        if (!m_content)
            return;

        QPainter p(this);
        p.setRenderHint(QPainter::Antialiasing);
        p.setPen(Qt::NoPen);

        auto items = m_content->getTabBarItems();
        int n = (int)items.size();

        // ---------- 1. Unselected item backgrounds (hover / pressed) ----------
        for (int i = 0; i < n; i++)
        {
            FluTabBarItem* item = items[i];
            if (item->getSelected())
                continue;

            QRect r = item->geometry();
            QColor bg;
            if (item->getPressed() && m_pressedColor.isValid())
                bg = m_pressedColor;
            else if (item->getHovered() && m_hoverColor.isValid())
                bg = m_hoverColor;

            if (bg.isValid() && bg.alpha() > 0)
                drawTabShape(p, r, bg);
        }

        // ---------- 2. Separator lines ----------
        if (m_separatorColor.isValid() && m_separatorColor.alpha() > 0)
        {
            p.setBrush(m_separatorColor);
            for (int i = 0; i < n - 1; i++)
            {
                FluTabBarItem* cur = items[i];
                FluTabBarItem* next = items[i + 1];
                bool showSep = !cur->getSelected() && !cur->getHovered() && !cur->getPressed() && !next->getSelected() && !next->getHovered() && !next->getPressed();
                if (showSep)
                {
                    QRect r = cur->geometry();
                    // 1px wide line at the item's right edge, y offset 8, height = item height - 16
                    p.fillRect(QRect(r.right() + 1, r.top() + 8, 1, r.height() - 16), m_separatorColor);
                }
            }
        }

        // ---------- 3. Selected tab (top rounded + bottom concave arcs) ----------
        for (int i = 0; i < n; i++)
        {
            FluTabBarItem* item = items[i];
            if (!item->getSelected())
                continue;

            QRect r = item->geometry();
            if (m_selectedColor.isValid())
                drawSelectedTab(p, r, m_selectedColor);
            break;  // only one selected
        }
    }

  private:
    // Draw a tab-shaped region: top-left 8px radius, top-right 8px radius, bottom flat.
    static void drawTabShape(QPainter& p, const QRect& r, const QColor& color)
    {
        if (r.isEmpty())
            return;

        const qreal rad = 8.0;
        const qreal x1 = r.left();
        const qreal y1 = r.top();
        const qreal x2 = r.right() + 1.0;   // exclusive right
        const qreal y2 = r.bottom() + 1.0;  // exclusive bottom

        QPainterPath path;
        path.moveTo(x1 + rad, y1);
        path.lineTo(x2 - rad, y1);
        // top-right corner: 90° → 0° (clockwise)
        path.arcTo(QRectF(x2 - 2.0 * rad, y1, 2.0 * rad, 2.0 * rad), 90.0, -90.0);
        path.lineTo(x2, y2);
        path.lineTo(x1, y2);
        path.lineTo(x1, y1 + rad);
        // top-left corner: 180° → 90° (clockwise)
        path.arcTo(QRectF(x1, y1, 2.0 * rad, 2.0 * rad), 180.0, -90.0);
        path.closeSubpath();

        p.save();
        p.setPen(Qt::NoPen);
        p.setBrush(color);
        p.drawPath(path);
        p.restore();
    }

    // Draw the selected tab body: top 8px rounded corners, flat bottom.
    // Bottom concave arcs are intentionally omitted here – when used inside
    // FluTabView the junction overlay draws them at the correct location
    // (tab-bar / content-panel boundary). For standalone FluTabBar this
    // produces a clean flat-bottom card.
    void drawSelectedTab(QPainter& p, const QRect& r, const QColor& color)
    {
        if (r.isEmpty())
            return;

        const qreal topR = 8.0;
        const qreal x1 = r.left();
        const qreal y1 = r.top();
        const qreal x2 = r.right() + 1.0;
        const qreal y2 = r.bottom() + 1.0;

        QPainterPath path;
        path.moveTo(x1 + topR, y1);
        path.lineTo(x2 - topR, y1);
        path.arcTo(QRectF(x2 - 2 * topR, y1, 2 * topR, 2 * topR), 90.0, -90.0);
        path.lineTo(x2, y2);
        path.lineTo(x1, y2);
        path.lineTo(x1, y1 + topR);
        path.arcTo(QRectF(x1, y1, 2 * topR, 2 * topR), 180.0, -90.0);
        path.closeSubpath();

        p.save();
        p.setPen(Qt::NoPen);
        p.setBrush(color);
        p.drawPath(path);
        p.restore();

        // 1px stroke on top + left + right edges only (skip bottom to preserve
        // seamless connection with content panel via junction overlay).
        if (m_selectedStrokeColor.isValid() && m_selectedStrokeColor.alpha() > 0)
        {
            QPainterPath strokePath;
            strokePath.moveTo(x1, y2);
            strokePath.lineTo(x1, y1 + topR);
            strokePath.arcTo(QRectF(x1, y1, 2 * topR, 2 * topR), 180.0, -90.0);
            strokePath.lineTo(x2 - topR, y1);
            strokePath.arcTo(QRectF(x2 - 2 * topR, y1, 2 * topR, 2 * topR), 90.0, -90.0);
            strokePath.lineTo(x2, y2);

            p.save();
            p.setPen(QPen(m_selectedStrokeColor, 1.0));
            p.setBrush(Qt::NoBrush);
            p.drawPath(strokePath);
            p.restore();
        }
    }

    FluTabBarContent* m_content;
    QColor m_hoverColor;
    QColor m_pressedColor;
    QColor m_selectedColor;
    QColor m_separatorColor;
    QColor m_selectedStrokeColor;
};

// ---------------------------------------------------------------------------

FluTabBarContent::FluTabBarContent(QWidget* parent /*= nullptr*/) : QScrollArea(parent)
{
    setWidgetResizable(true);
    verticalScrollBar()->setEnabled(false);
    horizontalScrollBar()->setEnabled(true);

    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    m_mainWidget = new QWidget(this);
    setWidget(m_mainWidget);

    m_mainWidget->setObjectName("mainWidget");

    m_mainLayout = new QHBoxLayout;
    m_mainWidget->setLayout(m_mainLayout);
    m_mainLayout->setContentsMargins(0, 4, 0, 0);

    m_midLayout = new QHBoxLayout;
    m_midLayout->setSpacing(0);

    m_midLayout->setAlignment(Qt::AlignLeft);
    m_mainLayout->addLayout(m_midLayout);
    m_mainLayout->addStretch();

    m_mainWidget->setFixedHeight(40);
    setFixedHeight(40);

    // Paint layer: child of m_mainWidget, behind all FluTabBarItem widgets.
    m_paintLayer = new FluTabBarPaintLayer(this, m_mainWidget);
    m_paintLayer->lower();

    connect(FluThemeUtils::getUtils(), &FluThemeUtils::themeChanged, this, [this](FluTheme) { onThemeChanged(); });
    FluStyleSheetUtils::setQssByFileName("FluTabBarContent.qss", this, FluThemeUtils::getUtils()->getTheme());
}

void FluTabBarContent::addBarItem(FluTabBarItem* item)
{
    insertTabBarItem(-1, item);
}

void FluTabBarContent::insertTabBarItem(int pos, FluTabBarItem* item)
{
    if ((pos < -1) && (pos > (int)(m_tabBarItems.size())))
    {
        return;
    }

    if (pos == -1)
    {
        pos = m_tabBarItems.size();
    }

    // insert to widget
    m_midLayout->insertWidget(pos, item);
    m_tabBarItems.insert(m_tabBarItems.begin() + pos, item);

    item->setSelected(false);
    if (m_tabBarItems.size() == 1)
    {
        item->setSelected(true);
    }

    item->adjustWidgetSize();

    connect(item, &FluTabBarItem::clicked, [=]() {
        for (auto itemIter = m_tabBarItems.begin(); itemIter != m_tabBarItems.end(); itemIter++)
        {
            (*itemIter)->setSelected(false);
            (*itemIter)->style()->polish((*itemIter));
        }

        item->setSelected(true);
        item->style()->polish(item);
        updatePaintLayer();
    });

    connect(item, &FluTabBarItem::visualStateChanged, this, [this]() { updatePaintLayer(); });
    connect(item, &FluTabBarItem::sizeChanged, this, [this]() { updatePaintLayer(); });

    // Defer: layout geometry isn't final until the pending layout activation runs.
    QTimer::singleShot(0, this, &FluTabBarContent::updatePaintLayer);
}

void FluTabBarContent::removeTabBarItem(FluTabBarItem* item)
{
    m_midLayout->removeWidget(item);
    auto itf = std::find(m_tabBarItems.begin(), m_tabBarItems.end(), item);
    if (itf != m_tabBarItems.end())
    {
        m_tabBarItems.erase(itf);
    }
    item->deleteLater();

    bool isHasSelected = false;
    for (auto itemIter = m_tabBarItems.begin(); itemIter != m_tabBarItems.end(); itemIter++)
    {
        if ((*itemIter)->getSelected())
        {
            isHasSelected = true;
            break;
        }
    }

    if (!isHasSelected && m_tabBarItems.size() > 0)
    {
        m_tabBarItems[0]->setSelected(true);
        m_tabBarItems[0]->style()->polish(m_tabBarItems[0]);
    }

    QTimer::singleShot(0, this, &FluTabBarContent::updatePaintLayer);
}

int FluTabBarContent::getSelectedTabBarItemIndex()
{
    int pos = -1;
    for (int i = 0; i < m_tabBarItems.size(); i++)
    {
        if (m_tabBarItems[i]->getSelected())
        {
            pos = i;
            break;
        }
    }
    return pos;
}

FluTabBarItem* FluTabBarContent::getSelectedTabBarItem()
{
    int itemIndex = getSelectedTabBarItemIndex();
    if (itemIndex < 0 || itemIndex >= m_tabBarItems.size())
        return nullptr;

    return m_tabBarItems[itemIndex];
}

std::vector<FluTabBarItem*> FluTabBarContent::getTabBarItems()
{
    return m_tabBarItems;
}

int FluTabBarContent::getTabBarItemMaxWidth()
{
    return m_tabBarItemMaxWidth;
}

void FluTabBarContent::setTabBarItemMaxWidth(int w)
{
    m_tabBarItemMaxWidth = w;
}

int FluTabBarContent::getTabBarItemMinWidth()
{
    return m_tabBarItemMinWidth;
}

void FluTabBarContent::setTabBarItemMinWidth(int w)
{
    m_tabBarItemMinWidth = w;
}

void FluTabBarContent::wheelEvent(QWheelEvent* event)
{
    QPointF pos(0, 0);
    QPointF gPos(0, 0);
    QPoint pixelDelta(0, 0);
    QPoint angleDelta(event->angleDelta().y(), 0);
    QWheelEvent wheelEvent(pos, gPos, pixelDelta, angleDelta, event->buttons(), event->modifiers(), event->phase(), event->inverted());
    QScrollArea::wheelEvent(&wheelEvent);
}

void FluTabBarContent::resizeEvent(QResizeEvent* event)
{
    QScrollArea::resizeEvent(event);
    if (m_paintLayer && m_mainWidget)
    {
        m_paintLayer->setFixedSize(m_mainWidget->size());
    }
    updatePaintLayer();
}

void FluTabBarContent::updatePaintLayer()
{
    if (!m_paintLayer)
        return;

    if (m_mainWidget && m_paintLayer->size() != m_mainWidget->size())
    {
        m_paintLayer->setFixedSize(m_mainWidget->size());
    }

    m_paintLayer->update();
}

void FluTabBarContent::onThemeChanged()
{
    FluStyleSheetUtils::setQssByFileName("FluTabBarContent.qss", this, FluThemeUtils::getUtils()->getTheme());
    // QSS reload triggers qproperty- setters which update the paint layer colors.
    // Force a repaint to pick up any color changes.
    updatePaintLayer();
}

// ---------------------------------------------------------------------------
// Q_PROPERTY accessors
// ---------------------------------------------------------------------------

QColor FluTabBarContent::getTabHoverColor() const
{
    return m_tabHoverColor;
}

void FluTabBarContent::setTabHoverColor(QColor c)
{
    m_tabHoverColor = c;
    if (m_paintLayer)
        m_paintLayer->setTabHoverColor(c);
}

QColor FluTabBarContent::getTabPressedColor() const
{
    return m_tabPressedColor;
}

void FluTabBarContent::setTabPressedColor(QColor c)
{
    m_tabPressedColor = c;
    if (m_paintLayer)
        m_paintLayer->setTabPressedColor(c);
}

QColor FluTabBarContent::getTabSelectedColor() const
{
    return m_tabSelectedColor;
}

void FluTabBarContent::setTabSelectedColor(QColor c)
{
    m_tabSelectedColor = c;
    if (m_paintLayer)
        m_paintLayer->setTabSelectedColor(c);
}

QColor FluTabBarContent::getTabSeparatorColor() const
{
    return m_tabSeparatorColor;
}

void FluTabBarContent::setTabSeparatorColor(QColor c)
{
    m_tabSeparatorColor = c;
    if (m_paintLayer)
        m_paintLayer->setTabSeparatorColor(c);
}

QColor FluTabBarContent::getTabSelectedStrokeColor() const
{
    return m_tabSelectedStrokeColor;
}

void FluTabBarContent::setTabSelectedStrokeColor(QColor c)
{
    m_tabSelectedStrokeColor = c;
    if (m_paintLayer)
        m_paintLayer->setTabSelectedStrokeColor(c);
}
