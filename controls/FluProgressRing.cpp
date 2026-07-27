#include "FluProgressRing.h"

FluProgressRing::FluProgressRing(QWidget* parent /*= nullptr*/) : FluWidget(parent), m_isTransparentTrack(true)
{
    m_minValue = 0;
    m_maxValue = 100;
    m_curValue = 0;
    m_isWorking = false;
    m_isShowText = false;
    setFixedSize(60, 60);

    m_workingTimer = new QTimer(parent);
    m_workingTimer->setInterval(3);
    m_workStartValue = 90;
    m_workingTimer->start();

    connect(m_workingTimer, &QTimer::timeout, [=]() {
        // m_times++;
        // m_times = m_times %= 100;
        // progressRing->setCurValue(m_times);

        if (!m_isWorking)
            return;

        m_workStartValue -= 1;
        // m_workStartValue %= 360;
        if (m_workStartValue == 0)
            m_workStartValue = 360;
        update();
    });
}

void FluProgressRing::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    float minWH = qMin(width(), height());
    float trunkW = 6;

    QPen pen;
    pen.setWidth(6);
    pen.setCapStyle(Qt::RoundCap);
    pen.setJoinStyle(Qt::RoundJoin);
    pen.setColor(QColor(211, 211, 211));
    if (FluThemeUtils::isDarkTheme())
        pen.setColor(QColor(154, 154, 154));

    if (m_isTransparentTrack)
        pen.setColor(Qt::transparent);

    painter.setPen(pen);
    QRectF outerC(4, 4, minWH - trunkW - 2, minWH - trunkW - 2);
    painter.drawEllipse(outerC);

    pen.setColor(QColor(0, 90, 158));
    if (FluThemeUtils::isDarkTheme())
        pen.setColor(QColor(118, 185, 237));

    if (FluThemeUtils::isAtomOneDarkTheme())
        pen.setColor(QColor(82, 139, 255));

    painter.setPen(pen);
    if (!m_isWorking)
    {
        painter.drawArc(outerC, 90 * 16, -360 * 16 * (m_curValue * 1.0 / (m_maxValue - m_minValue)));
    }
    else
    {
        painter.drawArc(outerC, m_workStartValue * 16, -360 * 16 * 0.25);
    }

    if (!m_isWorking && m_isShowText)
    {
        // drawText
        pen.setWidth(1);
        pen.setColor(Qt::black);
        if (FluThemeUtils::isDarkTheme() || FluThemeUtils::isAtomOneDarkTheme())
            pen.setColor(Qt::white);

        painter.setPen(pen);

        QString curPersent = QString::asprintf("%d%%", m_curValue * 100 / (m_maxValue - m_minValue));
        painter.drawText(outerC, Qt::AlignCenter, curPersent);
    }
}

void FluProgressRing::setMinMaxValue(int minValue, int maxValue)
{
    m_minValue = minValue;
    m_maxValue = maxValue;
}

void FluProgressRing::setCurValue(int curValue)
{
    m_curValue = curValue;
    update();
}

int FluProgressRing::getCurValue()
{
    return m_curValue;
}

bool FluProgressRing::getWorking()
{
    return m_isWorking;
}

void FluProgressRing::setWorking(bool isWorking)
{
    m_isWorking = isWorking;
    update();
}

void FluProgressRing::setShowText(bool isShowText)
{
    m_isShowText = isShowText;
    update();
}

bool FluProgressRing::getShowText()
{
    return m_isShowText;
}

bool FluProgressRing::getTransparentTrack()
{
    return m_isTransparentTrack;
}

void FluProgressRing::setTransparentTrack(bool isTransparentTrack)
{
    m_isTransparentTrack = isTransparentTrack;
    update();
}
