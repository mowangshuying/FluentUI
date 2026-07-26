#include "FluStackedLayoutWrap.h"
#include "FluStackedLayout.h"

FluStackedLayoutWrap::FluStackedLayoutWrap(QWidget* parent) : QObject(parent)
{
    m_layout = new FluStackedLayout(parent);
}

FluStackedLayoutWrap::~FluStackedLayoutWrap()
{
    delete m_layout;
    m_layout = nullptr;
}

void FluStackedLayoutWrap::addWidget(const QString& str, QWidget* w)
{
    m_layout->addWidget(str, w);
}

int FluStackedLayoutWrap::addWidget(QWidget* w)
{
    return m_layout->addWidget(w);
}

void FluStackedLayoutWrap::removeWidget(const QString& str, QWidget* w)
{
    m_layout->removeWidget(str, w);
}

void FluStackedLayoutWrap::setCurrentWidget(const QString& str)
{
    m_layout->setCurrentWidget(str);
}

QWidget* FluStackedLayoutWrap::getWidget(const QString& str)
{
    return m_layout->getWidget(str);
}

FluStackedLayout* FluStackedLayoutWrap::layout() const
{
    return m_layout;
}
