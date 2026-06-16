#include "FluColorViewHHandle.h"

FluColorViewHHandle::FluColorViewHHandle(QWidget* parent /*= nullptr*/) : FluWidget(parent)
{
    m_circleP = QPoint(10, 8);
    m_bPressed = false;

    m_color = QColor(110, 98, 251);

    m_nMinV = 0;
    m_nMaxV = 100;
    m_fV = 0;
}

void FluColorViewHHandle::setMaxV(int nV)
{
    m_nMaxV = nV;
}

int FluColorViewHHandle::getMaxV()
{
    return m_nMaxV;
}

void FluColorViewHHandle::setMinV(int nV)
{
    m_nMinV = nV;
}

int FluColorViewHHandle::getMinV()
{
    return m_nMinV;
}

float FluColorViewHHandle::getV()
{
    return m_fV;
}

void FluColorViewHHandle::setV(float v)
{
    m_fV = v;
    // update circleP;
    m_circleP.setX((width() - 20) * m_fV + 10);
    updateVByMouseOper(m_circleP.x(), false);
    // emit valueChanged(v);
}

void FluColorViewHHandle::updateVByMouseOper(int nX, bool bEmitSignal /*= true*/)
{
    m_fV = ((nX - 10) * 1.0) / (width() - 20);
    if (bEmitSignal)
        emit valueChanged(m_fV);
    update();
}

void FluColorViewHHandle::setFixedSize(int w, int h)
{
    FluWidget::setFixedSize(w, h);
    update();
}

void FluColorViewHHandle::setColor(QColor color, bool bEmitSignal /*= true*/)
{
    m_color = color;
    if (bEmitSignal)
    {
        emit colorChanged(m_color);
        emit valueChanged(m_fV);
    }
    update();
}

QColor FluColorViewHHandle::getColor()
{
    return m_color;
}

void FluColorViewHHandle::mouseMoveEvent(QMouseEvent* event)
{
    if (m_bPressed)
    {
        m_circleP = QPoint(event->pos().x(), 8);
        if (event->pos().x() > rect().width() - 10)
        {
            m_circleP = QPoint(rect().width() - 10, 8);
        }
        else if (event->pos().x() < 10)
        {
            m_circleP = QPoint(10, 8);
        }

        updateVByMouseOper(m_circleP.x());
        // LOG_DEBUG << "Value Changed:" << m_nV;
        // update();
    }
}

void FluColorViewHHandle::mousePressEvent(QMouseEvent* event)
{
    m_circleP = QPoint(event->pos().x(), 8);
    if (event->pos().x() > rect().width() - 10)
    {
        m_circleP = QPoint(rect().width() - 10, 8);
    }
    else if (event->pos().x() < 10)
    {
        m_circleP = QPoint(10, 8);
    }

    m_bPressed = true;
    emit pressed();
    updateVByMouseOper(m_circleP.x());

    // float percentage = (m_circleP.x() - 10) / (rect().width() - 20);
    // emit valueChanged(percentage);
    // LOG_DEBUG << "Value Changed:" << m_nV;
    // update();
}

void FluColorViewHHandle::mouseReleaseEvent(QMouseEvent* event)
{
    m_bPressed = false;
    // emit pressed();
}

void FluColorViewHHandle::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);

    // draw handle;
    painter.setPen(Qt::NoPen);
    // painter.setBrush(m_color);

    // QLinearGradient gradient();

    // rect;
    QRect handleR = rect();
    handleR = handleR.adjusted(2, 2, -2, -2);

    QLinearGradient gradient(handleR.x(), 0, handleR.x() + handleR.width(), 0);
    gradient.setColorAt(0, QColor(0, 0, 0));
    gradient.setColorAt(1, m_color);
    painter.setBrush(gradient);

    painter.drawRoundedRect(handleR, 6, 6);

    // draw out circle;
    painter.setBrush(QColor(255, 255, 255));
    painter.drawEllipse(m_circleP, 8, 8);

    // draw inner circle;
    painter.setBrush(QColor(27, 27, 27));
    painter.drawEllipse(m_circleP, 5, 5);
}
