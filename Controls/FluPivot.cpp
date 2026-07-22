#include "FluPivot.h"

FluPivot::FluPivot(QWidget* parent /*= nullptr*/) : FluWidget(parent)
{
    m_mainLayout = new QVBoxLayout;
    setLayout(m_mainLayout);

    m_mainLayout->setSpacing(5);
    m_mainLayout->setContentsMargins(0, 0, 0, 0);

    m_titleBar = new FluPivotTitleBar;
    m_mainLayout->addWidget(m_titleBar);

    m_layout = new FluStackedLayout;
    m_mainLayout->addLayout(m_layout);

    onThemeChanged();
}

void FluPivot::addPivotItem(QString key, QWidget* widget)
{
    auto titleBarItem = new FluPivotTitleBarItem;
    titleBarItem->setKey(key);
    addPivotItem(titleBarItem, widget);
}

void FluPivot::addPivotItem(FluPivotTitleBarItem* item, QWidget* widget)
{
    connect(item, &FluPivotTitleBarItem::clicked, [=]() { pivotItemChanged(item); });

    m_titleBar->addTitleBarItem(item);
    m_layout->addWidget(item->getKey(), widget);
}

void FluPivot::pivotItemChanged(FluPivotTitleBarItem* item)
{
    // change bar
    m_titleBar->setCurTitleBarItem(item);
    // change sLayout;
    m_layout->setCurrentWidget(item->getKey());
}

void FluPivot::onThemeChanged()
{
    FluStyleSheetUtils::setQssByFileName("FluPivot.qss", this, FluThemeUtils::getUtils()->getTheme());
}
