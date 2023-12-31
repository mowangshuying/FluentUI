#include "FluStackedLayout.h"

FluStackedLayout::FluStackedLayout() : QStackedLayout()
{
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
}
