#include "FluChangeBgDemo.h"

FluChangeBgDemo::FluChangeBgDemo(QWidget *parent /*= nullptr*/) : FluWidget(parent)
{
    m_normalBgColor = QColor("#1994e1");
    m_hoverBgColor = QColor("#d1eaf9");
    m_isHover = false;
    setMouseTracking(true);
    qDebug() << __FUNCTION__;
}

FluChangeBgDemo::~FluChangeBgDemo()
{
    qDebug() << __FUNCTION__;
}

void FluChangeBgDemo::enterEvent(QEnterEvent *event)
{
    m_isHover = true;
    update();
}

void FluChangeBgDemo::leaveEvent(QEvent *event)
{
    m_isHover = false;
    update();
}

void FluChangeBgDemo::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);
    QPainter painter(this);
    if (m_isHover)
    {
        qDebug() << "hover it!";
        painter.fillRect(rect(), m_normalBgColor);
    }
    else
    {
        qDebug() << "not hover it!";
        painter.fillRect(rect(), m_hoverBgColor);
    }
}
