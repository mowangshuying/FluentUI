#include "FluCircleDot.h"

FluCircleDot::FluCircleDot(QWidget* parent /*= nullptr*/) : FluWidget(parent)
{
    setFixedSize(11, 11);
    onThemeChanged();
    m_target = parent;

    connect(FluThemeUtils::getUtils(), &FluThemeUtils::themeChanged, [=](FluTheme theme) { onThemeChanged(); });
}

void FluCircleDot::setTopRightMargin(int nMarginTop, int nMarginRight)
{
    m_nMarginTop = nMarginTop;
    m_nMarginRight = nMarginRight;
}

void FluCircleDot::moveTopRight()
{
    int nX = m_target->width() - m_nMarginRight - width() / 2;
    int nY = m_nMarginTop - height() / 2;
    move(nX, nY);
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

void FluCircleDot::setCircleDot(QWidget* target, int nMarginTop, int nMarginRight)
{
    if (target == nullptr)
        return;

    FluCircleDot* circleDot = new FluCircleDot(target);
    circleDot->setTopRightMargin(nMarginTop, nMarginRight);
    target->installEventFilter(circleDot);

    circleDot->moveTopRight();
}

void FluCircleDot::onThemeChanged()
{
    FluStyleSheetUitls::setQssByFileName("FluCircleDot.qss", this, FluThemeUtils::getUtils()->getTheme());
}
