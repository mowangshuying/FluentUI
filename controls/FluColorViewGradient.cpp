#include "FluColorViewGradient.h"

#include <limits>

FluColorViewGradient::FluColorViewGradient(QWidget* parent /*= nullptr*/) : FluWidget(parent)
{
    setFixedSize(192, 192);
    m_pixmap = FluIconUtils::getPixmap(("../res/ControlResImages/GradientColor.png"));
    m_pixmap = m_pixmap.scaled(192, 192);
    m_image = m_pixmap.toImage();

    m_isPressed = false;
    m_color = QColor(110, 98, 251);
    m_circleP = QPoint(96, 96);
}

void FluColorViewGradient::setFixedSize(int w, int h)
{
    FluWidget::setFixedSize(w, h);
    m_pixmap = m_pixmap.scaled(w, h);
    m_image = m_pixmap.toImage();
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
    if (m_image.isNull())
        return false;

    int targetR = color.red();
    int targetG = color.green();
    int targetB = color.blue();

    // Find the pixel whose color is closest to the target by squared RGB distance.
    // This replaces the previous O(n^2) brute-force search that re-derived the image
    // (m_pixmap.toImage()) on every pixel comparison.
    int bestDist = std::numeric_limits<int>::max();
    bool found = false;
    for (int y = 0; y < m_image.height(); y++)
    {
        for (int x = 0; x < m_image.width(); x++)
        {
            QRgb pixel = m_image.pixel(x, y);
            int dr = qRed(pixel) - targetR;
            int dg = qGreen(pixel) - targetG;
            int db = qBlue(pixel) - targetB;
            int dist = dr * dr + dg * dg + db * db;
            if (dist < bestDist)
            {
                bestDist = dist;
                point.setX(x);
                point.setY(y);
                found = true;
            }
        }
    }

    return found;
}

bool FluColorViewGradient::isCloseTo(int target, int current, int radius)
{
    return (target >= current - radius && target <= current + radius);
}

void FluColorViewGradient::circleMoveToPoint(QColor color)
{
    QPoint point;
    auto isFind = findColor(color, point);
    if (isFind)
    {
        m_circleP = point;
        m_color = m_image.pixelColor(m_circleP);
    }

    update();
}

void FluColorViewGradient::mouseMoveEvent(QMouseEvent* event)
{
    if (m_isPressed)
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

        m_isPressed = true;
        m_color = m_image.pixelColor(m_circleP);
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

    m_isPressed = true;
    m_color = m_image.pixelColor(m_circleP);
    colorChanged(m_color);
    update();
}

void FluColorViewGradient::mouseReleaseEvent(QMouseEvent* event)
{
    m_isPressed = false;
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
