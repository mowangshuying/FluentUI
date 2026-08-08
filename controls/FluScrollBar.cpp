#include "FluScrollBar.h"
#include "FluScrollArea.h"
#include "FluScrollBarHandle.h"

FluScrollBar::FluScrollBar(Qt::Orientation orientation, QAbstractScrollArea* scrollArea /*= nullptr*/)
    : FluWidget(scrollArea),
      m_scrollArea(scrollArea),
      m_orientation(orientation),
      m_maxValue(0),
      m_minValue(0),
      m_value(0),
      m_padding(14),
      m_pageStep(50),
      m_isHideScrollBar(false),
      m_isExpanded(false),
      m_isEnter(false),
      m_isPressed(false),
      m_pendingAction(0),
      m_isFaded(false)
{
    m_scrollBarTrunk = new FluScrollBarTrunk(orientation, this);
    m_scrollBarHandle = new FluScrollBarHandle(orientation, this);
    m_timer = new QTimer(this);
    m_timer->setSingleShot(true);
    m_timer->setInterval(200);
    connect(m_timer, &QTimer::timeout, this, &FluScrollBar::onTimerTimeout);

    m_valueAnimation = new QPropertyAnimation(this, "value");

    // C. Auto-hide + fade setup
    m_opaEffect = new QGraphicsOpacityEffect(this);
    m_opaEffect->setOpacity(1.0);
    setGraphicsEffect(m_opaEffect);

    m_fadeAnimation = new QPropertyAnimation(m_opaEffect, "opacity", this);

    m_autoHideTimer = new QTimer(this);
    m_autoHideTimer->setSingleShot(true);
    m_autoHideTimer->setInterval(2000);
    connect(m_autoHideTimer, &QTimer::timeout, this, &FluScrollBar::onAutoHideTimeout);

    m_scrollBar = getOriginalScrollBar();
    hideOriginalScrollBar();
    adjustScrollBarPosAndSize(m_scrollArea->size());
    setRangeValue(0, 0);

    m_scrollArea->installEventFilter(this);
    connect(m_scrollBarTrunk->getPreButton(), &FluScrollBarArrowButton::clicked, this, &FluScrollBar::OnPageUp);
    connect(m_scrollBarTrunk->getLstButton(), &FluScrollBarArrowButton::clicked, this, &FluScrollBar::OnPageDown);
    connect(m_scrollBar, &QScrollBar::rangeChanged, this, [=](int minValue, int maxValue) { setRangeValue(minValue, maxValue); });
    connect(m_scrollBar, &QScrollBar::valueChanged, this, [=](int value) {
        if (m_value != value)
        {
            m_value = value;
            adjustHandlePos();
            emit valueChanged(value);
        }
    });
    connect(this, &FluScrollBar::valueChanged, m_scrollBar, [=](int value) {
        if (m_scrollBar->value() != value)
        {
            m_scrollBar->setValue(value);
        }
    });
    connect(m_scrollBarTrunk->getAnimation(), &QPropertyAnimation::valueChanged, this, &FluScrollBar::onOpacityAnimationChanged);

    // C. Connect valueChanged for auto-hide fade-in + D. arrow button boundary
    connect(this, &FluScrollBar::valueChanged, this, &FluScrollBar::onContentScrolled);

    onThemeChanged();
}

Qt::Orientation FluScrollBar::getOrientation()
{
    return m_orientation;
}

int FluScrollBar::getMaxValue()
{
    return m_maxValue;
}

void FluScrollBar::setMaxValue(int value)
{
    if (value == m_maxValue)
        return;

    m_maxValue = value;
    emit valueRangeChanged(m_minValue, m_maxValue);
}

int FluScrollBar::getMinValue()
{
    return m_minValue;
}

void FluScrollBar::setMinValue(int value)
{
    if (value == m_minValue)
        return;

    m_minValue = value;
    emit valueRangeChanged(m_minValue, m_maxValue);
}

void FluScrollBar::setRangeValue(int minValue, int maxValue)
{
    if (m_minValue == minValue && m_maxValue == maxValue)
    {
        if (maxValue == 0 || m_isHideScrollBar)
            setVisible(false);
        return;
    }

    m_minValue = minValue;
    m_maxValue = maxValue;

    adjustHandleSize();
    adjustHandlePos();
    setVisible(maxValue > 0 && !m_isHideScrollBar);
    emit valueRangeChanged(m_minValue, m_maxValue);
}

void FluScrollBar::animateToValue(int targetValue, int duration, QEasingCurve::Type curve)
{
    targetValue = qBound(m_minValue, targetValue, m_maxValue);
    if (m_valueAnimation->state() == QAbstractAnimation::Running)
        m_valueAnimation->stop();
    m_valueAnimation->setStartValue(m_value);
    m_valueAnimation->setEndValue(targetValue);
    m_valueAnimation->setEasingCurve(curve);
    m_valueAnimation->setDuration(duration);
    m_valueAnimation->start();
}

void FluScrollBar::scrollBy(int delta)
{
    int target = qBound(m_minValue, m_value + delta, m_maxValue);
    setValue(target);
}

void FluScrollBar::scrollCurrentValue(int value)
{
    scrollBy(value);
}

int FluScrollBar::getValue()
{
    return m_value;
}

void FluScrollBar::setValue(int value)
{
    if (m_value == value)
        return;
    m_value = value;
    adjustHandlePos();
    emit valueChanged(value);
}

int FluScrollBar::getPadding()
{
    return m_padding;
}

void FluScrollBar::setPadding(int padding)
{
    m_padding = padding;
}

int FluScrollBar::getPageStep()
{
    return m_pageStep;
}

void FluScrollBar::setPageStep(int pageStep)
{
    m_pageStep = pageStep;
}

int FluScrollBar::getTrunkLen()
{
    if (m_orientation == Qt::Vertical)
        return height() - 2 * m_padding;
    return width() - 2 * m_padding;
}

bool FluScrollBar::atTrunk(const QPoint& pos)
{
    if (m_orientation == Qt::Vertical)
        return pos.y() >= m_padding && pos.y() <= height() - m_padding;
    return pos.x() >= m_padding && pos.x() <= width() - m_padding;
}

int FluScrollBar::getSlideWayLen()
{
    if (m_orientation == Qt::Vertical)
        return getTrunkLen() - m_scrollBarHandle->height();
    return getTrunkLen() - m_scrollBarHandle->width();
}

void FluScrollBar::setHideScrollBar(bool isHideScrollBar)
{
    m_isHideScrollBar = isHideScrollBar;
}

bool FluScrollBar::isHideScrollBar()
{
    return m_isHideScrollBar;
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
    if (m_orientation == Qt::Vertical)
        m_scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    else if (m_orientation == Qt::Horizontal)
        m_scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

void FluScrollBar::adjustHandlePos()
{
    if (m_orientation == Qt::Vertical)
    {
        int total = m_maxValue - m_minValue;
        if (total < 1)
            total = 1;
        int delta = 1.0 * m_value / total * getSlideWayLen();

        int x = width() - m_scrollBarHandle->width() - 3;
        int y = m_padding + delta;
        m_scrollBarHandle->move(x, y);
    }
    else if (m_orientation == Qt::Horizontal)
    {
        int total = m_maxValue - m_minValue;
        if (total < 1)
            total = 1;
        int delta = 1.0 * m_value / total * getSlideWayLen();
        int x = m_padding + delta;
        int y = height() - m_scrollBarHandle->height() - 3;
        m_scrollBarHandle->move(x, y);
    }
}

void FluScrollBar::adjustHandleSize()
{
    if (m_orientation == Qt::Vertical)
    {
        int total = m_maxValue - m_minValue + m_scrollArea->height();
        if (total < 1)
            total = 1;

        int handleH = 1.0 * getTrunkLen() * m_scrollArea->height() / total;
        int maxH = qMax(30, getTrunkLen());
        handleH = qBound(30, handleH, maxH);

        m_scrollBarHandle->setFixedHeight(handleH);
    }
    else if (m_orientation == Qt::Horizontal)
    {
        int total = m_maxValue - m_minValue + m_scrollArea->width();
        if (total < 1)
            total = 1;

        int handleW = 1.0 * getTrunkLen() * m_scrollArea->width() / total;
        int maxW = qMax(30, getTrunkLen());
        handleW = qBound(30, handleW, maxW);

        m_scrollBarHandle->setFixedWidth(handleW);
    }
}

QColor FluScrollBar::getTrunkBackgroundColor()
{
    return m_scrollBarTrunk->getTrunkBackgroundColor();
}

void FluScrollBar::setTrunkBackgroundColor(QColor color)
{
    m_scrollBarTrunk->setTrunkBackgroundColor(color);
}

QColor FluScrollBar::getHandleBackgroundColor()
{
    return m_scrollBarHandle->getHandleBackgroundColor();
}

void FluScrollBar::setHandleBackgroundColor(QColor color)
{
    m_scrollBarHandle->setHandleBackgroundColor(color);
}

QColor FluScrollBar::getHandleHoverColor()
{
    return m_scrollBarHandle->getHandleHoverColor();
}

void FluScrollBar::setHandleHoverColor(QColor color)
{
    m_scrollBarHandle->setHandleHoverColor(color);
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
    m_isEnter = true;
    m_timer->stop();
    m_pendingAction = 1;
    m_timer->start();
    m_scrollBarHandle->setHovered(true);
    fadeIn();
}

void FluScrollBar::leaveEvent(QEvent* event)
{
    m_isEnter = false;
    m_timer->stop();
    m_pendingAction = 2;
    m_timer->start();
    m_scrollBarHandle->setHovered(false);
}

void FluScrollBar::resizeEvent(QResizeEvent* event)
{
    m_scrollBarTrunk->resize(size());
}

void FluScrollBar::mouseMoveEvent(QMouseEvent* event)
{
    QWidget::mouseMoveEvent(event);
    if (!m_isPressed)
        return;

    int dv = 0;
    if (m_orientation == Qt::Vertical)
    {
        dv = event->pos().y() - m_pressedPoint.y();
    }
    else
    {
        dv = event->pos().x() - m_pressedPoint.x();
    }

    dv = 1.0 * dv / getSlideWayLen() * (m_maxValue - m_minValue);
    int newValue = qBound(m_minValue, m_value + dv, m_maxValue);
    if (m_value != newValue)
    {
        m_value = newValue;
        adjustHandlePos();
        emit valueChanged(newValue);
    }
    m_pressedPoint = event->pos();
}

void FluScrollBar::mousePressEvent(QMouseEvent* event)
{
    QWidget::mousePressEvent(event);
    m_isPressed = true;
    m_pressedPoint = event->pos();

    if (childAt(event->pos()) == m_scrollBarHandle || !atTrunk(m_pressedPoint))
        return;

    int value = 0;
    if (m_orientation == Qt::Vertical)
    {
        if (event->pos().y() > m_scrollBarHandle->geometry().bottom())
        {
            value = event->pos().y() - m_scrollBarHandle->height() - m_padding;
        }
        else
        {
            value = event->pos().y() - m_padding;
        }
    }
    else
    {
        if (event->pos().x() > m_scrollBarHandle->geometry().right())
        {
            value = event->pos().x() - m_scrollBarHandle->width() - m_padding;
        }
        else
        {
            value = event->pos().x() - m_padding;
        }
    }

    animateToValue(1.0 * value / qMax(getSlideWayLen(), 1) * (m_maxValue - m_minValue));
}

void FluScrollBar::mouseReleaseEvent(QMouseEvent* event)
{
    QWidget::mouseReleaseEvent(event);
    m_isPressed = false;
}

void FluScrollBar::wheelEvent(QWheelEvent* event)
{
    if (m_scrollArea == nullptr)
        return;

    QApplication::sendEvent(m_scrollArea->viewport(), event);
}

void FluScrollBar::OnPageUp()
{
    animateToValue(m_value - getPageStep(), 180, QEasingCurve::OutQuad);
}

void FluScrollBar::OnPageDown()
{
    animateToValue(m_value + getPageStep(), 180, QEasingCurve::OutQuad);
}

// void FluScrollBar::onCurrentValueChanged(int value)
//{
//     setCurrentValue(value);
// }

void FluScrollBar::onTimerTimeout()
{
    if (m_pendingAction == 1)
        expand();
    else if (m_pendingAction == 2)
        collapse();
    m_pendingAction = 0;
}

void FluScrollBar::expand()
{
    if (m_isExpanded || !m_isEnter)
        return;

    m_isExpanded = true;
    m_scrollBarTrunk->expandTrunk();
}

void FluScrollBar::collapse()
{
    if (!m_isExpanded || m_isEnter)
        return;

    m_isExpanded = false;
    m_scrollBarTrunk->collapseTrunk();
}

void FluScrollBar::onOpacityAnimationChanged(const QVariant& value)
{
    qreal opacity = m_scrollBarTrunk->getEffect()->opacity();
    if (!m_scrollBarHandle->isHovered())
    {
        int baseThickness = 3 + opacity * 3;
        m_scrollBarHandle->setThickness(baseThickness);
    }

    // D. Arrow button visibility follows trunk opacity
    bool showArrows = opacity > 0.1;
    m_scrollBarTrunk->getPreButton()->setVisible(showArrows);
    m_scrollBarTrunk->getLstButton()->setVisible(showArrows);

    adjustHandlePos();
}

void FluScrollBar::onThemeChanged()
{
    FluStyleSheetUtils::setQssByFileName("FluScrollBar.qss", this, FluThemeUtils::getUtils()->getTheme());
    m_scrollBarHandle->update();
    m_scrollBarTrunk->update();
    update();
}

void FluScrollBar::onAutoHideTimeout()
{
    m_fadeAnimation->stop();
    m_fadeAnimation->setStartValue(m_opaEffect->opacity());
    m_fadeAnimation->setEndValue(0.3);
    m_fadeAnimation->setDuration(500);
    m_fadeAnimation->setEasingCurve(QEasingCurve::InQuad);
    m_fadeAnimation->start();
    m_isFaded = true;
}

void FluScrollBar::onContentScrolled()
{
    fadeIn();

    // D. Arrow button boundary detection
    if (m_scrollBarTrunk)
    {
        m_scrollBarTrunk->getPreButton()->setAtBoundary(m_value <= m_minValue);
        m_scrollBarTrunk->getLstButton()->setAtBoundary(m_value >= m_maxValue);
    }
}

void FluScrollBar::fadeIn()
{
    m_autoHideTimer->stop();
    if (m_isFaded || m_opaEffect->opacity() < 1.0)
    {
        m_fadeAnimation->stop();
        m_fadeAnimation->setStartValue(m_opaEffect->opacity());
        m_fadeAnimation->setEndValue(1.0);
        m_fadeAnimation->setDuration(200);
        m_fadeAnimation->setEasingCurve(QEasingCurve::OutQuad);
        m_fadeAnimation->start();
        m_isFaded = false;
    }
    m_autoHideTimer->start();
}
