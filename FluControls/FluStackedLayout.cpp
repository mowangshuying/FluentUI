#include "FluStackedLayout.h"

FluStackedLayout::FluStackedLayout() : QStackedLayout()
{
    // m_animation = new QPropertyAnimation;
    // m_animation->setPropertyName("pos");
    // m_animation->setDuration(500);
    // m_animation->setEasingCurve(QEasingCurve::OutBounce);
}

FluStackedLayout::FluStackedLayout(QWidget *parent) : QStackedLayout(parent)
{
}

FluStackedLayout::FluStackedLayout(QLayout *parentLayout) : QStackedLayout(parentLayout)
{
}

void FluStackedLayout::addWidget(QString str, QWidget *w)
{
    m_widgetMap[str] = w;
    QStackedLayout::addWidget(w);
}

int FluStackedLayout::addWidget(QWidget *w)
{
    return QStackedLayout::addWidget(w);
}

void FluStackedLayout::removeWidget(QString str, QWidget *w)
{
    auto itf = m_widgetMap.find(str);
    if (itf == m_widgetMap.end())
        return;

    m_widgetMap.remove(str);
    QStackedLayout::removeWidget(w);
}

void FluStackedLayout::setCurrentWidget(QString str)
{
    auto itf = m_widgetMap.find(str);
    if (itf == m_widgetMap.end())
        return;

    QStackedLayout::setCurrentWidget(itf.value());

    // m_animation->setTargetObject(itf.value());
    //  m_animation->setStartValue(itf.value()->pos());
    // m_animation->setKeyValueAt(0.5, itf.value()->pos() + QPoint(0, 50));
    // m_animation->setEndValue(itf.value()->pos());
    //  m_animation->start();
}

QWidget *FluStackedLayout::getWidget(QString str)
{
    auto itf = m_widgetMap.find(str);
    if (itf == m_widgetMap.end())
        return nullptr;

    return itf.value();
}
