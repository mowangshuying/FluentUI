#include "FluHScrollView.h"

FluHScrollView::FluHScrollView(QWidget* parent /*= nullptr*/) : QScrollArea(parent)
{
    setWidgetResizable(true);
    setMinimumSize(0, 0);

    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_contextWidget = new QWidget(this);
    setWidget(m_contextWidget);

    m_hMainLayout = new QHBoxLayout(m_contextWidget);
    m_contextWidget->setObjectName("contextWidget");

    onThemeChanged();
    connect(FluThemeUtils::getUtils(), &FluThemeUtils::themeChanged, this, [=](FluTheme theme) { onThemeChanged(); });
}

FluHScrollView::~FluHScrollView()
{
}

QHBoxLayout* FluHScrollView::getMainLayout()
{
    return m_hMainLayout;
}

void FluHScrollView::wheelEvent(QWheelEvent* event)
{
    QPointF pos(0, 0);
    QPointF gPos(0, 0);
    QPoint pixelDelta(0, 0);
    QPoint angleDelta(event->angleDelta().y(), 0);
    QWheelEvent wheelEvent(pos, gPos, pixelDelta, angleDelta, event->buttons(), event->modifiers(), event->phase(), event->inverted());
    QScrollArea::wheelEvent(&wheelEvent);
}

void FluHScrollView::onThemeChanged()
{
    FluStyleSheetUitls::setQssByFileName("FluHScrollView.qss", this, FluThemeUtils::getUtils()->getTheme());
}
