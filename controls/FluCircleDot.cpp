#include "FluCircleDot.h"

FluCircleDot::FluCircleDot(QWidget* parent /*= nullptr*/) : FluWidget(parent)
{
    setFixedSize(11, 11);
    onThemeChanged();
    m_target = parent;

}

void FluCircleDot::setTopRightMargin(int marginTop, int marginRight)
{
    m_marginTop = marginTop;
    m_marginRight = marginRight;
}

void FluCircleDot::moveTopRight()
{
    int x = m_target->width() - m_marginRight - width() / 2;
    int y = m_marginTop - height() / 2;
    move(x, y);
}

void FluCircleDot::paintEvent(QPaintEvent* event)
{
    QStyleOption opt;
    opt.initFrom(this);
    QPainter painter(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
}

bool FluCircleDot::eventFilter(QObject* watched, QEvent* event)
{
    if (m_target == nullptr)
        return FluWidget::eventFilter(watched, event);

    if (watched == m_target)
    {
        if (event->type() == QEvent::Resize || event->type() == QEvent::Move)
        {
            moveTopRight();
        }
    }

    return FluWidget::eventFilter(watched, event);
}

void FluCircleDot::setCircleDot(QWidget* target, int marginTop, int marginRight)
{
    if (target == nullptr)
        return;

    FluCircleDot* circleDot = new FluCircleDot(target);
    circleDot->setTopRightMargin(marginTop, marginRight);
    target->installEventFilter(circleDot);

    circleDot->moveTopRight();
}
