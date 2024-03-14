#pragma once

#include <QWidget>
#include <QPainter>
#include <QTimer>
#include "../FluUtils/FluUtils.h"

class FluProgressRing : public QWidget
{
    Q_OBJECT
  public:
    FluProgressRing(QWidget* parent = nullptr) : QWidget(parent)
    {
        m_minValue = 0;
        m_maxValue = 100;
        m_curValue = 0;
        m_bWorking = false;
        m_bShowText = false;
        setFixedSize(60, 60);

        m_workingTimer = new QTimer(parent);
        m_workingTimer->setInterval(3);
        m_workStartValue = 90;
        m_workingTimer->start();

        connect(m_workingTimer, &QTimer::timeout, [=]() {
            // m_nTimes++;
            // m_nTimes = m_nTimes %= 100;
            // progressRing->setCurValue(m_nTimes);

            if (!m_bWorking)
                return;

            m_workStartValue += 1;
            m_workStartValue %= 360;
            update();
        });
    }

    void paintEvent(QPaintEvent* event)
    {
        QPainter painter(this);
        painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
        float minWH = qMin(width(), height());
        float trunkW = 6;

        QPen pen;
        pen.setWidth(6);
        pen.setColor(QColor(211, 211, 211));
        painter.setPen(pen);
        QRectF outerC(4, 4, minWH - trunkW - 2, minWH - trunkW - 2);
        painter.drawEllipse(outerC);

        pen.setColor(QColor(0, 90, 158));
        painter.setPen(pen);
        if (!m_bWorking)
        {
            painter.drawArc(outerC, 90 * 16, -360 * 16 * (m_curValue * 1.0 / (m_maxValue - m_minValue)));
        }
        else
        {
            painter.drawArc(outerC, m_workStartValue * 16, -360 * 16 * 0.25);
        }

        if (!m_bWorking && m_bShowText)
        {
            // drawText
            pen.setWidth(1);
            pen.setColor(Qt::black);
            if (FluThemeUtils::getUtils()->getTheme() == FluTheme::Dark)
                pen.setColor(Qt::white);

            painter.setPen(pen);

            QString curPersent = QString::asprintf("%d%", m_curValue * 100 / (m_maxValue - m_minValue));
            painter.drawText(outerC, Qt::AlignCenter, curPersent);
        }
    }

    void setMinMaxValue(int minValue, int maxValue)
    {
        m_minValue = minValue;
        m_maxValue = maxValue;
    }

    void setCurValue(int curValue)
    {
        m_curValue = curValue;
        update();
    }

    int getCurValue()
    {
        return m_curValue;
    }

    bool getWorking()
    {
        return m_bWorking;
    }

    void setWorking(bool bWorking)
    {
        m_bWorking = bWorking;
    }

    void setShowText(bool bShowText)
    {
        m_bShowText = bShowText;
    }

    bool getShowText()
    {
        return m_bShowText;
    }

  protected:
    int m_minValue;
    int m_maxValue;
    int m_curValue;

    int m_workStartValue;
    bool m_bWorking;
    bool m_bShowText;
    QTimer* m_workingTimer;
};
