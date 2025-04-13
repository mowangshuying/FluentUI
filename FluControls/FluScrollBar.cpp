#include "FluScrollBar.h"
#include "FluScrollArea.h"
#include "FluScrollBarHandle.h"

FluScrollBar::FluScrollBar(Qt::Orientation orientation, QAbstractScrollArea* scrollArea /*= nullptr*/)
    : FluWidget(scrollArea), m_scrollArea(scrollArea), m_orientation(orientation), m_nMaxValue(0), m_nMinValue(0), m_nCurrentValue(0), m_nPadding(14), m_nPageStep(50), m_bHideScrollBar(false), m_bExpanded(false)
{
    m_scrollBarTrunk = new FluScrollBarTrunk(orientation, this);
    m_scrollBarHandle = new FluScrollBarHandle(orientation, this);
    m_timer = new QTimer(this);

    m_scrollBar = getOriginalScrollBar();
    hideOriginalScrollBar();
    adjustScrollBarPosAndSize(m_scrollArea->size());
    setRangeValue(0, 0);
    //  adjustHandleSize();
    //  adjustHandlePos();

    m_scrollArea->installEventFilter(this);
    connect(m_scrollBarTrunk->getPreBtn(), &FluScrollBarArrowButton::clicked, this, &FluScrollBar::OnPageUp);
    connect(m_scrollBarTrunk->getLstBtn(), &FluScrollBarArrowButton::clicked, this, &FluScrollBar::OnPageDown);
    connect(m_scrollBar, &QScrollBar::rangeChanged, this, [=](int nMinValue, int nMaxValue) { setRangeValue(nMinValue, nMaxValue); });
    connect(m_scrollBar, &QScrollBar::valueChanged, this, &FluScrollBar::onCurrentValueChanged);
    connect(this, &FluScrollBar::currentValueChanged, m_scrollBar, [=](int nValue) { m_scrollBar->setValue(nValue); });
    connect(m_scrollBarTrunk->getAnimation(), &QPropertyAnimation::valueChanged, this, &FluScrollBar::onOpacityAnimationChanged);
    onThemeChanged();
}

Qt::Orientation FluScrollBar::getOrientation()
{
    return m_orientation;
}

int FluScrollBar::getMaxValue()
{
    return m_nMaxValue;
}

void FluScrollBar::setMaxValue(int nValue)
{
    if (nValue == m_nMaxValue)
        return;

    m_nMaxValue = nValue;
    emit valueRangeChanged(m_nMinValue, m_nMaxValue);
}

int FluScrollBar::getMinValue()
{
    return m_nMinValue;
}

void FluScrollBar::setMinValue(int nValue)
{
    if (nValue == m_nMinValue)
        return;

    m_nMinValue = nValue;
    emit valueRangeChanged(m_nMinValue, m_nMaxValue);
}

void FluScrollBar::setRangeValue(int nMinValue, int nMaxValue)
{
    if (m_nMinValue == nMinValue && m_nMaxValue == nMaxValue)
    {
        if (nMaxValue == 0 || m_bHideScrollBar)
            setVisible(false);
        return;
    }

    m_nMinValue = nMinValue;
    m_nMaxValue = nMaxValue;

    adjustHandleSize();
    adjustHandlePos();
    setVisible(nMaxValue > 0 && !m_bHideScrollBar);
    emit valueRangeChanged(m_nMinValue, m_nMaxValue);
}

int FluScrollBar::getCurrentValue()
{
    return m_nCurrentValue;
}

void FluScrollBar::setCurrrentValue(int nValue)
{
    if (nValue < m_nMinValue)
        nValue = m_nMinValue;
    else if (nValue > m_nMaxValue)
        nValue = m_nMaxValue;
    m_nCurrentValue = nValue;

    adjustHandlePos();
    emit currentValueChanged(m_nCurrentValue);
}

void FluScrollBar::scrollCurrentValue(int nValue)
{
    m_nCurrentValue += nValue;
    setCurrrentValue(m_nCurrentValue);
}

int FluScrollBar::getPadding()
{
    return m_nPadding;
}

void FluScrollBar::setPadding(int nPadding)
{
    m_nPadding = nPadding;
}

int FluScrollBar::getPageStep()
{
    return m_nPageStep;
}

void FluScrollBar::setPageStep(int nPageStep)
{
    m_nPageStep = nPageStep;
}

int FluScrollBar::getTrunkLen()
{
    if (m_orientation == Qt::Vertical)
        return height() - 2 * m_nPadding;
    return width() - 2 * m_nPadding;
}

bool FluScrollBar::atTrunk(const QPoint& pos)
{
    if (m_orientation == Qt::Vertical)
        return pos.y() >= m_nPadding && pos.y() <= height() - m_nPadding;
    return pos.x() >= m_nPadding && pos.x() <= width() - m_nPadding;
}

int FluScrollBar::getSlideWayLen()
{
    if (m_orientation == Qt::Vertical)
        return getTrunkLen() - m_scrollBarHandle->height();
    return getTrunkLen() - m_scrollBarHandle->width();
}

void FluScrollBar::setHideScrollBar(bool bHideScrollBar)
{
    m_bHideScrollBar = bHideScrollBar;
}

bool FluScrollBar::isHideScrollBar()
{
    return m_bHideScrollBar;
}

void FluScrollBar::adjustScrollBarPosAndSize(QSize scrollAreaSize)
{
    if (m_orientation == Qt::Vertical)
    {
        resize(12, scrollAreaSize.height() - 2);
        move(scrollAreaSize.width() - 13, 1);

        adjustHandleSize();
        adjustHandlePos();
    }
    else if (m_orientation == Qt::Horizontal)
    {
        resize(scrollAreaSize.width() - 2, 12);
        move(1, scrollAreaSize.height() - 13);

        adjustHandleSize();
        adjustHandlePos();
    }
}

QScrollBar* FluScrollBar::getOriginalScrollBar()
{
    QScrollBar* scrollBar = nullptr;
    if (m_orientation == Qt::Vertical)
        scrollBar = m_scrollArea->verticalScrollBar();
    else if (m_orientation == Qt::Horizontal)
        scrollBar = m_scrollArea->horizontalScrollBar();
    return scrollBar;
}

void FluScrollBar::hideOriginalScrollBar()
{
    // if (m_orientation == Qt::Vertical)
    m_scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    // else if (m_orientation == Qt::Horizontal)
    m_scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

void FluScrollBar::adjustHandlePos()
{
    if (m_orientation == Qt::Vertical)
    {
        int nTotal = m_nMaxValue - m_nMinValue;
        if (nTotal < 1)
            nTotal = 1;
        int nDelta = 1.0 * getCurrentValue() / nTotal * getSlideWayLen();

        int nX = width() - m_scrollBarHandle->width() - 3;
        // LOG_DEBUG << width() << "," << m_scrollBarHandle->width();
        int nY = m_nPadding + nDelta;
        m_scrollBarHandle->move(nX, nY);
    }
    else if (m_orientation == Qt::Horizontal)
    {
        int nTotal = m_nMaxValue - m_nMinValue;
        if (nTotal < 1)
            nTotal = 1;
        int nDelta = 1.0 * getCurrentValue() / nTotal * getSlideWayLen();
        int nX = m_nPadding + nDelta;
        int nY = height() - m_scrollBarHandle->height() - 3;
        m_scrollBarHandle->move(nX, nY);
    }
}

void FluScrollBar::adjustHandleSize()
{
    if (m_orientation == Qt::Vertical)
    {
        int nTotal = m_nMaxValue - m_nMinValue + m_scrollArea->height();
        if (nTotal < 1)
            nTotal = 1;

        int nHandleH = 1.0 * getTrunkLen() * m_scrollArea->height() / nTotal;
        if (nHandleH < 30)
            nHandleH = 30;

        m_scrollBarHandle->setFixedHeight(nHandleH);
    }
    else if (m_orientation == Qt::Horizontal)
    {
        int nTotal = m_nMaxValue - m_nMinValue + m_scrollArea->width();
        if (nTotal < 1)
            nTotal = 1;

        int nHanldeW = 1.0 * getTrunkLen() * m_scrollArea->width() / nTotal;
        if (nHanldeW < 30)
            nHanldeW = 30;

        m_scrollBarHandle->setFixedWidth(nHanldeW);
    }
}

QColor FluScrollBar::getTrunkBackgoundColor()
{
    return m_scrollBarTrunk->getTrunkBackgoundColor();
}

void FluScrollBar::setTrunkBackgoundColor(QColor color)
{
    m_scrollBarTrunk->setTrunkBackgoundColor(color);
}

QColor FluScrollBar::getHandleBackgroundColor()
{
    return m_scrollBarHandle->getHandleBackgroundColor();
}

void FluScrollBar::setHandleBackgroundColor(QColor color)
{
    m_scrollBarHandle->setHandleBackgroundColor(color);
}

bool FluScrollBar::eventFilter(QObject* watched, QEvent* event)
{
    if (watched == m_scrollArea && event->type() == QEvent::Resize)
    {
        auto resizeEvent = (QResizeEvent*)event;
        adjustScrollBarPosAndSize(resizeEvent->size());
    }
    return QWidget::eventFilter(watched, event);
}

void FluScrollBar::enterEvent(QEnterEvent* event)
{
    m_bEnter = true;
    m_timer->stop();
    m_timer->singleShot(200, this, &FluScrollBar::expand);
}

void FluScrollBar::leaveEvent(QEvent* event)
{
    m_bEnter = false;
    m_timer->stop();
    m_timer->singleShot(200, this, &FluScrollBar::collapse);
}

void FluScrollBar::resizeEvent(QResizeEvent* event)
{
    m_scrollBarTrunk->resize(size());
}

void FluScrollBar::mouseMoveEvent(QMouseEvent* event)
{
    QWidget::mouseMoveEvent(event);
    if (!m_bPressed)
        return;

    int nDv = 0;
    if (m_orientation == Qt::Vertical)
    {
        nDv = event->pos().y() - m_pressedPoint.y();
    }
    else
    {
        nDv = event->pos().x() - m_pressedPoint.x();
    }

    nDv = 1.0 * nDv / getSlideWayLen() * (m_nMaxValue - m_nMinValue);
    FluScrollBar::setCurrrentValue(getCurrentValue() + nDv);
    m_pressedPoint = event->pos();
}

void FluScrollBar::mousePressEvent(QMouseEvent* event)
{
    QWidget::mousePressEvent(event);
    m_bPressed = true;
    m_pressedPoint = event->pos();

    if (childAt(event->pos()) == m_scrollBarHandle || !atTrunk(m_pressedPoint))
        return;

    int nValue = 0;
    if (m_orientation == Qt::Vertical)
    {
        if (event->pos().y() > m_scrollBarHandle->geometry().bottom())
        {
            nValue = event->pos().y() - m_scrollBarHandle->height() - m_nPadding;
        }
        else
        {
            nValue = event->pos().y() - m_nPadding;
        }
    }
    else
    {
        if (event->pos().x() > m_scrollBarHandle->geometry().right())
        {
            nValue = event->pos().x() - m_scrollBarHandle->width() - m_nPadding;
        }
        else
        {
            nValue = event->pos().x() - m_nPadding;
        }
    }

    setCurrrentValue(1.0 * nValue / qMax(getSlideWayLen(), 1) * (m_nMaxValue - m_nMinValue));
}

void FluScrollBar::mouseReleaseEvent(QMouseEvent* event)
{
    QWidget::mouseReleaseEvent(event);
    m_bPressed = false;
}

void FluScrollBar::wheelEvent(QWheelEvent* event)
{
    if (m_scrollArea == nullptr)
        return;

    QApplication::sendEvent(m_scrollArea->viewport(), event);
}

void FluScrollBar::OnPageUp()
{
    setCurrrentValue(getCurrentValue() - getPageStep());
}

void FluScrollBar::OnPageDown()
{
    setCurrrentValue(getCurrentValue() + getPageStep());
}

void FluScrollBar::onCurrentValueChanged(int nValue)
{
    setCurrrentValue(nValue);
}

void FluScrollBar::expand()
{
    if (m_bExpanded || !m_bEnter)
        return;

    m_bExpanded = true;
    m_scrollBarTrunk->expandTrunk();
}

void FluScrollBar::collapse()
{
    if (!m_bExpanded || m_bEnter)
        return;

    m_bExpanded = false;
    m_scrollBarTrunk->collapseTrunk();
}

void FluScrollBar::onOpacityAnimationChanged(const QVariant& value)
{
    qreal opacity = m_scrollBarTrunk->getEffect()->opacity();
    if (m_orientation == Qt::Vertical)
    {
        m_scrollBarHandle->setFixedWidth(3 + opacity * 3);
    }
    else
    {
        m_scrollBarHandle->setFixedHeight(3 + opacity * 3);
    }
    adjustHandlePos();
}

void FluScrollBar::onThemeChanged()
{
    FluStyleSheetUitls::setQssByFileName("FluScrollBar.qss", this, FluThemeUtils::getUtils()->getTheme());
    m_scrollBarHandle->update();
    m_scrollBarTrunk->update();
    update();
}
