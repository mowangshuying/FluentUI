#include "FluTabView.h"
#include <QPainterPath>
#include <QTimer>
#include <QResizeEvent>

// ---------------------------------------------------------------------------
// Private inner class: transparent widget that paints the Fluent TabView
// transition arcs at the junction between FluTabBar and #sWidget content.
// No Q_OBJECT — implementation detail only.
// ---------------------------------------------------------------------------
class FluTabViewJunctionOverlay : public QWidget
{
  public:
    explicit FluTabViewJunctionOverlay(FluTabView* parent) : QWidget(parent), m_tabView(parent)
    {
        setAttribute(Qt::WA_TransparentForMouseEvents);
        setAttribute(Qt::WA_TranslucentBackground);
    }

    void setNotchColor(const QColor& c) { m_notchColor = c; update(); }

  protected:
    void paintEvent(QPaintEvent*) override
    {
        if (!m_tabView)
            return;

        FluTabBar* bar = m_tabView->getTabBar();
        QWidget* content = m_tabView->getContentWidget();
        if (!bar || !content)
            return;

        // Locate the selected item
        FluTabBarItem* selItem = nullptr;
        auto items = bar->getTabBarItems();
        for (auto* item : items)
        {
            if (item->getSelected())
            {
                selItem = item;
                break;
            }
        }
        if (!selItem)
            return;

        // Map item & content geometry into overlay-local coordinates.
        QPoint selTopLeft = selItem->mapTo(this, QPoint(0, 0));
        QRect selRect(selTopLeft, selItem->size());

        QPoint contentTopLeft = content->mapTo(this, QPoint(0, 0));
        const qreal junctionY = contentTopLeft.y();

        QPainter p(this);
        p.setRenderHint(QPainter::Antialiasing);
        p.setPen(Qt::NoPen);

        const qreal R     = 4.0;
        QColor selColor   = bar->getSelectedTabColor();
        QColor bgColor    = m_notchColor;

        // --- 1. Bridge: fill any vertical gap under the selected tab ---------
        if (selColor.isValid() && selColor.alpha() > 0)
        {
            qreal bridgeTop    = selRect.bottom() + 1.0;
            qreal bridgeBottom = junctionY + R + 1.0;
            if (bridgeBottom > bridgeTop)
            {
                p.setBrush(selColor);
                p.drawRect(QRectF(selRect.left(), bridgeTop,
                                  selRect.width(), bridgeBottom - bridgeTop));
            }
        }

        // --- 2. Left notch: concave arc at bottom-left of selected tab -------
        if (bgColor.isValid() && bgColor.alpha() > 0)
        {
            p.setBrush(bgColor);

            QPainterPath leftNotch;
            leftNotch.moveTo(selRect.left() + 0.5, junctionY - R);
            leftNotch.lineTo(selRect.left() + 0.5, junctionY + R);
            leftNotch.lineTo(selRect.left() + R + 0.5, junctionY + R);
            leftNotch.arcTo(QRectF(selRect.left() + 0.5, junctionY - R, 2.0 * R, 2.0 * R),
                            270.0, -90.0);
            leftNotch.lineTo(selRect.left() + 0.5, junctionY - R);
            leftNotch.closeSubpath();
            p.drawPath(leftNotch);

            // --- 3. Right notch: concave arc at bottom-right -----------------
            QPainterPath rightNotch;
            rightNotch.moveTo(selRect.right() + 0.5, junctionY - R);
            rightNotch.lineTo(selRect.right() + 0.5, junctionY + R);
            rightNotch.lineTo(selRect.right() - R + 0.5, junctionY + R);
            rightNotch.arcTo(QRectF(selRect.right() - 2.0 * R + 0.5, junctionY - R, 2.0 * R, 2.0 * R),
                             270.0, 90.0);
            rightNotch.lineTo(selRect.right() + 0.5, junctionY - R);
            rightNotch.closeSubpath();
            p.drawPath(rightNotch);
        }
    }

  private:
    FluTabView* m_tabView;
    QColor      m_notchColor;
};

// ---------------------------------------------------------------------------

FluTabView::FluTabView(QWidget* parent /*= nullptr*/) : FluWidget(parent)
{
    m_mainLayout = new QVBoxLayout;
    m_mainLayout->setContentsMargins(1, 1, 1, 1);
    setLayout(m_mainLayout);

    m_mainLayout->setSpacing(0);
    m_mainLayout->setAlignment(Qt::AlignTop);

    m_tabBar = new FluTabBar;
    m_mainLayout->addWidget(m_tabBar);

    m_widgt = new QWidget;
    m_widgt->setObjectName("sWidget");
    m_mainLayout->addWidget(m_widgt, 1);

    m_layout = new FluStackedLayout;
    m_layout->setContentsMargins(10, 0, 10, 10);
    m_widgt->setLayout(m_layout);

    // Junction overlay: child of FluTabView, NOT in any layout.
    m_junctionOverlay = new FluTabViewJunctionOverlay(this);

    connect(m_tabBar, &FluTabBar::addTabButtonClicked, this, [=]() {
        emit addTabButtonClicked();
    });

    // Refresh overlay colors when the theme changes (QSS reloads asynchronously).
    connect(FluThemeUtils::getUtils(), &FluThemeUtils::themeChanged, this,
            [this](FluTheme) { QTimer::singleShot(0, this, &FluTabView::updateJunctionOverlay); });

    onThemeChanged();
}

void FluTabView::addTab(QString tabString, QWidget* tabWidget)
{
    auto tabBarItem = new FluTabBarItem;
    tabBarItem->setText(tabString);
    m_tabBar->addBarItem(tabBarItem);

    m_layout->addWidget(tabString, tabWidget);

    connect(tabBarItem, &FluTabBarItem::clicked, this, [=]() {
        m_layout->setCurrentWidget(tabString);
        updateJunctionOverlay();
    });
    connect(tabBarItem, &FluTabBarItem::clickedCloseButton, this, [=](FluTabBarItem* item) {
        m_tabBar->removeTabBarItem(item);
        m_layout->removeWidget(tabString, tabWidget);
        updateJunctionOverlay();
    });
    connect(tabBarItem, &FluTabBarItem::sizeChanged, this, &FluTabView::updateJunctionOverlay);
    connect(tabBarItem, &FluTabBarItem::visualStateChanged, this, &FluTabView::updateJunctionOverlay);

    // Defer overlay positioning until the new tab's geometry settles.
    QTimer::singleShot(0, this, &FluTabView::updateJunctionOverlay);
}

bool FluTabView::eventFilter(QObject* watched, QEvent* event)
{
    return QWidget::eventFilter(watched, event);
}

void FluTabView::paintEvent(QPaintEvent* event)
{
    QStyleOption opt;
    opt.initFrom(this);
    QPainter painter(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
}

void FluTabView::resizeEvent(QResizeEvent* event)
{
    QWidget::resizeEvent(event);
    updateJunctionOverlay();
}

void FluTabView::updateJunctionOverlay()
{
    if (!m_junctionOverlay || !m_widgt || !m_tabBar)
        return;

    // Resolve the tab-bar area background (notch fills this colour).
    // Mirrors the FluTabView background declared in FluTabView.qss.
    QColor notchColor;
    if (FluThemeUtils::isLightTheme())
        notchColor = QColor(249, 249, 249);
    else if (FluThemeUtils::isDarkTheme())
        notchColor = QColor(32, 32, 32);
    else // AtomOneDark
        notchColor = QColor(33, 37, 43);
    m_junctionOverlay->setNotchColor(notchColor);

    // Position the overlay as a strip centred on the tab-bar / content junction.
    const int junctionY  = m_widgt->geometry().top();
    const int stripHalf  = 6;                               // extend 6 px each side
    m_junctionOverlay->setGeometry(0, junctionY - stripHalf,
                                   width(), stripHalf * 2);
    m_junctionOverlay->raise();
    m_junctionOverlay->update();
}
