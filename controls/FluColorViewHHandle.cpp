#include "FluColorViewHHandle.h"

FluColorViewHHandle::FluColorViewHHandle(QWidget* parent /*= nullptr*/) : FluWidget(parent)
{
    m_circleP = QPoint(10, 8);
    m_isPressed = false;

    m_color = QColor(110, 98, 251);

    m_minValue = 0;
    m_maxValue = 100;
    m_value = 0;
}

void FluColorViewHHandle::setMaxValue(int value)
{
    m_maxValue = value;
}

int FluColorViewHHandle::getMaxValue()
{
    return m_maxValue;
}

void FluColorViewHHandle::setMinValue(int value)
{
    m_minValue = value;
}

int FluColorViewHHandle::getMinValue()
{
    return m_minValue;
}

float FluColorViewHHandle::getValue()
{
    return m_value;
}

void FluColorViewHHandle::setValue(float value)
{
    m_value = value;
    // update circleP;
    m_circleP.setX((width() - 20) * m_value + 10);
    updateValueByMouseOperation(m_circleP.x(), false);
    // emit valueChanged(value);
}

void FluColorViewHHandle::updateValueByMouseOperation(int xPosition, bool shouldEmitSignal /*= true*/)
{
    m_value = ((xPosition - 10) * 1.0) / (width() - 20);
    if (shouldEmitSignal)
        emit valueChanged(m_value);
    update();
}

void FluColorViewHHandle::setFixedSize(int w, int h)
{
    FluWidget::setFixedSize(w, h);
    update();
}

void FluColorViewHHandle::setColor(QColor color, bool shouldEmitSignal /*= true*/)
{
    m_color = color;
    if (shouldEmitSignal)
    {
        emit colorChanged(m_color);
        emit valueChanged(m_value);
    }
    update();
}

QColor FluColorViewHHandle::getColor()
{
    return m_color;
}

void FluColorViewHHandle::mouseMoveEvent(QMouseEvent* event)
{
    if (m_isPressed)
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

        updateValueByMouseOperation(m_circleP.x());
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

    m_isPressed = true;
    emit pressed();
    updateValueByMouseOperation(m_circleP.x());

    // float percentage = (m_circleP.x() - 10) / (rect().width() - 20);
    // emit valueChanged(percentage);
}

void FluColorViewHHandle::mouseReleaseEvent(QMouseEvent* event)
{
    m_isPressed = false;
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
