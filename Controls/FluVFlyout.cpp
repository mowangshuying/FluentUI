#include "FluVFlyout.h"

FluVFlyout::FluVFlyout(QWidget* target, FluFlyoutPosition position /*= FluFlyoutPosition::Top*/) : FluWidget(nullptr), m_targetWidget(target), m_position(position)
{
    m_mainLayout = new QHBoxLayout;
    m_mainLayout->setSpacing(0);
    m_mainLayout->setContentsMargins(10, 10, 10, 10);
    setLayout(m_mainLayout);

    m_shadowWidget = new QWidget(this);
    m_shadowWidget->setObjectName("shadowWidget");

    m_mainLayout->addWidget(m_shadowWidget);

    m_shadowLayout = new QVBoxLayout;
    m_shadowWidget->setLayout(m_shadowLayout);
    m_shadowLayout->setContentsMargins(8, 8, 8, 8);

    setFixedWidth(360);
    setMinimumHeight(96);

    setShadowEffect();

    setAttribute(Qt::WA_TranslucentBackground);
    setWindowFlags(Qt::Popup | Qt::FramelessWindowHint | Qt::NoDropShadowWindowHint);

    onThemeChanged();
}

void FluVFlyout::setShadowEffect()
{
    // set shadow;
    m_shadowEffect = new QGraphicsDropShadowEffect;
    m_shadowEffect->setBlurRadius(8);
    m_shadowEffect->setOffset(0, 0);
    m_shadowEffect->setColor(QColor(0, 0, 0, 30));
    if (FluThemeUtils::isDarkTheme())
        m_shadowEffect->setColor(QColor(0, 0, 0, 80));
    m_shadowWidget->setGraphicsEffect(m_shadowEffect);
}

void FluVFlyout::showEvent(QShowEvent* event)
{
    int x = 0;
    int y = 0;

    QPoint targetPos = m_targetWidget->mapToGlobal(QPoint(0, 0));
    switch (m_position)
    {
        case FluFlyoutPosition::Top:
        {
            x = targetPos.x() + (m_targetWidget->width() - width()) / 2;
            y = targetPos.y() - height() + 5;
        }
        break;
        case FluFlyoutPosition::Bottom:
        {
            x = targetPos.x() + (m_targetWidget->width() - width()) / 2;
            y = targetPos.y() + m_targetWidget->height() - 5;
        }
        break;
        case FluFlyoutPosition::Left:
        {
            x = targetPos.x() - width() + 5;
            y = targetPos.y() - (height() - m_targetWidget->height()) / 2;
        }
        break;
        case FluFlyoutPosition::Right:
        {
            x = targetPos.x() + m_targetWidget->width() - 5;
            y = targetPos.y() - (height() - m_targetWidget->height()) / 2;
        }
        break;
        default:
            break;
    }

    move(x, y);
}

void FluVFlyout::closeEvent(QCloseEvent* event)
{
    //  LOG_DEBUG << "close it!";
    FluWidget::closeEvent(event);
    deleteLater();
}

void FluVFlyout::paintEvent(QPaintEvent* event)
{
    QStyleOption opt;
    opt.initFrom(this);
    QPainter painter(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
}

void FluVFlyout::onThemeChanged()
{
    FluStyleSheetUtils::setQssByFileName("FluVFlyout.qss", this, FluThemeUtils::getUtils()->getTheme());
}
