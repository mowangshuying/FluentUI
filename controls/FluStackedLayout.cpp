#include "FluStackedLayout.h"
#include <QGraphicsOpacityEffect>

FluStackedLayout::FluStackedLayout() : QStackedLayout()
{
    m_opacityAnimation = new QPropertyAnimation(this, "value");
    m_opacityAnimation->setDuration(300);
    m_opacityAnimation->setEasingCurve(QEasingCurve::OutCubic);

    m_valueObject = new FluValueObject;
    m_opacityAnimation->setTargetObject(m_valueObject);
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

    auto effect = qobject_cast<QGraphicsOpacityEffect *>(itf.value()->graphicsEffect());
    if (!effect)
    {
        effect = new QGraphicsOpacityEffect(itf.value());
        itf.value()->setGraphicsEffect(effect);
    }

    m_opacityAnimation->setTargetObject(effect);
    m_opacityAnimation->setPropertyName("opacity");
    m_opacityAnimation->setStartValue(0.0);
    m_opacityAnimation->setEndValue(1.0);
    m_opacityAnimation->start();
}

QWidget *FluStackedLayout::getWidget(QString str)
{
    auto itf = m_widgetMap.find(str);
    if (itf == m_widgetMap.end())
        return nullptr;

    return itf.value();
}
