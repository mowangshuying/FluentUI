#include "FluColorViewGradient.h"

FluColorViewGradient::FluColorViewGradient(QWidget* parent /*= nullptr*/) : FluWidget(parent)
{
    setFixedSize(192, 192);
    m_pixmap = FluIconUtils::getPixmap(("../res/ControlResImages/GradientColor.png"));
    m_pixmap = m_pixmap.scaled(192, 192);
}

void FluColorViewGradient::setFixedSize(int w, int h)
{
    FluWidget::setFixedSize(w, h);
    m_pixmap = m_pixmap.scaled(w, h);
    update();
}

void FluColorViewGradient::setColor(QColor color)
{
    m_color = color;
}

QColor FluColorViewGradient::getColor()
{
    return m_color;
}

bool FluColorViewGradient::findColor(QColor color, QPoint& point)
{
    // LOG_DEBUG << "find color:" << color.red() << "," << color.green() << ", " << color.blue();
    bool bFind = false;

    // std::vector<QColor> colors;
    for (int i = 0; i < 256; i++)
    {
        for (int j = 0; j < 256; j++)
        {
            QColor curColor = m_pixmap.toImage().pixelColor(i, j);
            // colors.push_back(curColor);
            // LOG_DEBUG << "cur color:" << curColor.red() << "," << curColor.green() << "," << curColor.blue();
            if (atRange(color.red(), curColor.red(), 2) && atRange(color.green(), curColor.green(), 2) && atRange(color.blue(), curColor.blue(), 2))
            {
                point.setX(i);
                point.setY(j);
                bFind = true;
                break;
            }
        }
    }

    // std::sort(colors.begin(), colors.end(), [=](const QColor &color1, const QColor &color2) {
    //     if (color1.red() != color2.red())
    //         return color1.red() < color2.red();

    //      if (color1.green() != color2.green())
    //         return color1.green() < color2.green();

    //      return color1.blue() < color2.blue();
    // });

    // for (int i = 0; i < colors.size(); i++)
    // {
    //     auto color = colors[i];
    //     LOG_DEBUG << "find color:" << color.red() << "," << color.green() << ", " << color.blue();
    // }

    return bFind;
}

bool FluColorViewGradient::atRange(int i, int j, int nRadius)
{
    if (i >= j - nRadius && i <= j + nRadius)
        return true;
    return false;
}

void FluColorViewGradient::circleMoveToPoint(QColor color)
{
    QPoint point;
    auto bFind = findColor(color, point);
    if (bFind)
    {
        m_circleP = point;
        m_color = m_pixmap.toImage().pixelColor(m_circleP);
    }

    update();
}

void FluColorViewGradient::mouseMoveEvent(QMouseEvent* event)
{
    if (m_bPressed)
    {
        m_circleP = QPoint(event->pos().x(), event->pos().y());
        if (event->pos().x() < 8)
        {
            m_circleP.setX(8);
        }
        else if (event->pos().x() > rect().width() - 8)
        {
            m_circleP.setX(rect().width() - 8);
        }

        if (event->pos().y() < 8)
        {
            m_circleP.setY(8);
        }
        else if (event->pos().y() > rect().height() - 8)
        {
            m_circleP.setY(rect().height() - 8);
        }

        m_bPressed = true;
        m_color = m_pixmap.toImage().pixelColor(m_circleP);
        colorChanged(m_color);
        update();
    }
}

void FluColorViewGradient::mousePressEvent(QMouseEvent* event)
{
    m_circleP = QPoint(event->pos().x(), event->pos().y());
    if (event->pos().x() < 8)
    {
        m_circleP.setX(8);
    }
    else if (event->pos().x() > rect().width() - 8)
    {
        m_circleP.setX(rect().width() - 8);
    }

    if (event->pos().y() < 8)
    {
        m_circleP.setY(8);
    }
    else if (event->pos().y() > rect().height() - 8)
    {
        m_circleP.setY(rect().height() - 8);
    }

    m_bPressed = true;
    m_color = m_pixmap.toImage().pixelColor(m_circleP);
#ifdef _DEBUG
    // LOG_DEBUG << "color r:" << m_color.red();
    // LOG_DEBUG << "color g:" << m_color.green();
    // LOG_DEBUG << "color b:" << m_color.blue();
#endif
    colorChanged(m_color);
    update();
}

void FluColorViewGradient::mouseReleaseEvent(QMouseEvent* event)
{
    m_bPressed = false;
}

void FluColorViewGradient::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);

    // clip;
    QPainterPath path;
    path.addRoundedRect(rect(), 4, 4);
    painter.setClipPath(path);

    // pixmap;
    painter.drawPixmap(rect(), m_pixmap);

    // draw circle;
    QPen pen;
    pen.setWidth(3);
    pen.setColor(Qt::black);
    painter.setPen(pen);
    painter.drawEllipse(m_circleP, 6, 6);
}
