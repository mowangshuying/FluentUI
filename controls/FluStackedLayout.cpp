#include "FluStackedLayout.h"
#include <QGraphicsOpacityEffect>

FluStackedLayout::FluStackedLayout() : QStackedLayout()
{
    m_opacityAnimation = new QPropertyAnimation(this, "value");
    m_opacityAnimation->setDuration(300);
    m_opacityAnimation->setEasingCurve(QEasingCurve::OutCubic);

    m_valueObject = new FluValueObject;
    m_opacityAnimation->setTargetObject(m_valueObject);
    // Resting opacity == 1.0: disable the effect so QWidgetPrivate::drawWidget short-circuits
    // before ever calling QGraphicsOpacityEffect::draw. This avoids the buffered fast-path that
    // re-enters QPainter::begin on an already-active paint device. The effect stays mounted and
    // is reused on the next fade-in; it is never detached or deleted.
    connect(m_opacityAnimation, &QPropertyAnimation::finished, this, [this]() {
        if (m_currentFadeEffect)
        {
            m_currentFadeEffect->setEnabled(false); // resting at 1.0: disabling bypasses effect draw, effect stays on the page for reuse
            m_currentFadeEffect = nullptr;
        }
        m_currentFadePage = nullptr;
    });
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

    // Stop any in-flight fade first: if a previous fade has not reached 1.0 yet, stop() fires the
    // finished callback which disables that prior effect. The effect object remains mounted on its
    // page (never detached or deleted) and is reused the next time that page becomes current.
    m_opacityAnimation->stop();

    auto effect = qobject_cast<QGraphicsOpacityEffect *>(itf.value()->graphicsEffect());
    if (!effect)
    {
        effect = new QGraphicsOpacityEffect(itf.value());
        itf.value()->setGraphicsEffect(effect);
    }

    m_currentFadePage = itf.value();
    m_currentFadeEffect = effect;

    // Enable for animation but clamp opacity strictly below 1.0 first: the first property write
    // only happens on the next timer tick, so a leftover 1.0 + enabled state could emit a dirty
    // frame that reproduces the QPainter warning. Guarantee opacity < 1.0 in the same function.
    effect->setOpacity(0.0);
    effect->setEnabled(true);

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
