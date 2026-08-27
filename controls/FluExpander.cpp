#include "FluExpander.h"
#include <QEvent>
#include <QResizeEvent>

FluExpander::FluExpander(QWidget* parent /*= nullptr*/) : FluWidget(parent)
{
    m_wrap1 = new QWidget(this);
    m_wrap1->installEventFilter(this);
    m_wrap1->setObjectName("wrap1");
    m_wrap1->setMinimumHeight(48);  // the wrap1 set fixed height 48.
    setMinimumHeight(m_wrap1->minimumHeight());

    m_wrap1Layout = new QHBoxLayout;
    m_wrap1->setLayout(m_wrap1Layout);
    m_wrap1Layout->setContentsMargins(5, 5, 5, 5);

    m_downOrUpButton = new FluIconButton(FluAwesomeType::ChevronDown, m_wrap1);
    m_downOrUpButton->setNoBorder(true);

    m_wrap2 = new QWidget(this);
    m_wrap2->setObjectName("wrap2");
    m_wrap2->stackUnder(m_wrap1);

    m_wrap2Layout = new QVBoxLayout;
    m_wrap2Layout->setContentsMargins(5, 5, 5, 5);
    m_wrap2->setLayout(m_wrap2Layout);

    // m_isDown = true;
    setDown(true);
    setTopRadius0(false);

    m_expandAni = new QPropertyAnimation(this, "contentHeight");
    m_expandAni->setDuration(300);
    m_expandAni->setEasingCurve(QEasingCurve::OutCubic);

    connect(m_downOrUpButton, &QPushButton::clicked, [=](bool b) { onClicked(); });

    connect(m_expandAni, &QPropertyAnimation::finished, [=](void) { setDown(!m_isDown); });

    onThemeChanged();
}

bool FluExpander::getDown()
{
    return m_isDown;
}

void FluExpander::setDown(bool isDown)
{
    m_isDown = isDown;
    setProperty("down", isDown);
    m_wrap1->setProperty("down", isDown);
    m_wrap2->setProperty("down", isDown);

    style()->polish(this);
    m_wrap1->style()->polish(m_wrap1);
    m_wrap2->style()->polish(m_wrap2);
}

void FluExpander::setTopRadius0(bool isTopRadius0)
{
    m_wrap1->setProperty("topRadius0", isTopRadius0);
    setProperty("topRadius0", isTopRadius0);

    style()->polish(this);
    m_wrap1->style()->polish(m_wrap1);
}

QHBoxLayout* FluExpander::getWrap1Layout()
{
    return m_wrap1Layout;
}

QVBoxLayout* FluExpander::getWrap2Layout()
{
    return m_wrap2Layout;
}

void FluExpander::resizeEvent(QResizeEvent* event)
{
    m_wrap1->resize(event->size().width(), m_wrap1->height());
    m_wrap1->move(0, 0);
    m_wrap2->resize(event->size().width(), m_wrap2->sizeHint().height());
    m_wrap2->move(0, m_wrap1->height() + m_contentHeight - m_wrap2->sizeHint().height());

    int x = m_wrap1->width() - m_downOrUpButton->width() - 5;
    int y = (m_wrap1->height() - m_downOrUpButton->height()) / 2;
    m_downOrUpButton->move(x, y);
}

bool FluExpander::eventFilter(QObject* watched, QEvent* event)
{
    if (watched == m_wrap1 && event->type() == QEvent::MouseButtonRelease)
    {
        m_downOrUpButton->clicked();
    }
    return QWidget::eventFilter(watched, event);
}

void FluExpander::paintEvent(QPaintEvent* event)
{
    QStyleOption opt;
    opt.initFrom(this);
    QPainter painter(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
}

QSize FluExpander::sizeHint() const
{
    int w = qMax(m_wrap1->sizeHint().width(), m_wrap2->sizeHint().width());
    int h = qMax(m_wrap1->height(), m_wrap1->minimumHeight()) + m_contentHeight;
    return QSize(w, h);
}

void FluExpander::onThemeChanged()
{
    FluStyleSheetUtils::setQssByFileName("FluExpander.qss", this, FluThemeUtils::getUtils()->getTheme());
}

void FluExpander::onClicked()
{
    if (m_isDown)
    {
        m_expandAni->setStartValue(0);
        m_expandAni->setEndValue(m_wrap2->sizeHint().height());
        m_expandAni->start();

        m_downOrUpButton->setType1(FluAwesomeType::ChevronUp);
    }
    else
    {
        m_expandAni->setStartValue(m_wrap2->sizeHint().height());
        m_expandAni->setEndValue(0);
        m_expandAni->start();

        m_downOrUpButton->setType1(FluAwesomeType::ChevronDown);
    }
}

int FluExpander::getContentHeight() const
{
    return m_contentHeight;
}

void FluExpander::setContentHeight(int newContentHeight)
{
    if (m_contentHeight == newContentHeight)
        return;
    m_contentHeight = newContentHeight;
    setMinimumHeight(qMax(m_wrap1->height(), m_wrap1->minimumHeight()) + m_contentHeight);
    // let the layout system propagate the new height:
    // updateGeometry() invalidates this widget's size hints, and the invalidation
    // bubbles up through every ancestor layout (including scroll area viewports),
    // which is exactly what the old manual parent-resize loop tried to emulate.
    updateGeometry();
    emit contentHeightChanged();
}
