#pragma once

#include <QPainter>
#include <QPainterPath>
#include "FluWidget.h"
#include <QMouseEvent>
#include "../FluUtils/FluUtils.h"
#include <QLinearGradient>

class FluColorViewHHandle : public FluWidget
{
    Q_OBJECT
  public:
    FluColorViewHHandle(QWidget* parent = nullptr) : FluWidget(parent)
    {
        m_circleP = QPoint(10, 8);
        m_bPressed = false;

        m_color = QColor(110, 98, 251);

        m_nMinV = 0;
        m_nMaxV = 100;
        m_fV = 0;
    }

    void setMaxV(int nV)
    {
        m_nMaxV = nV;
    }

    int getMaxV()
    {
        return m_nMaxV;
    }

    void setMinV(int nV)
    {
        m_nMinV = nV;
    }

    int getMinV()
    {
        return m_nMinV;
    }

    float getV()
    {
        return m_fV;
    }

    void setV(float v)
    {
        m_fV = v;
        // update circleP;
        m_circleP.setX((width() - 20) * m_fV + 10);
        updateVByMouseOper(m_circleP.x(), false);
        // emit valueChanged(v);
    }

    void updateVByMouseOper(int nX, bool bEmitSignal = true)
    {
        m_fV = ((nX - 10) * 1.0) / (width() - 20);
        if (bEmitSignal)
            emit valueChanged(m_fV);
        update();
    }

    void setFixedSize(int w, int h)
    {
        FluWidget::setFixedSize(w, h);
        update();
    }

    void setColor(QColor color, bool bEmitSignal = true)
    {
        m_color = color;
        if (bEmitSignal)
        {
            emit colorChanged(m_color);
            emit valueChanged(m_fV);
        }
        update();
    }

    QColor getColor()
    {
        return m_color;
    }

    void mouseMoveEvent(QMouseEvent* event)
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

    void mousePressEvent(QMouseEvent* event)
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

    void mouseReleaseEvent(QMouseEvent* event)
    {
        m_bPressed = false;
        // emit pressed();
    }

    void paintEvent(QPaintEvent* event)
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

  signals:
    void colorChanged(QColor color);
    void valueChanged(float percentage);
    void pressed();

  protected:
    QColor m_color;
    QPoint m_circleP;

    int m_nMaxV;
    int m_nMinV;
    float m_fV;

    bool m_bPressed;
};
