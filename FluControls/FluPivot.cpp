#include "FluPivot.h"

FluPivot::FluPivot(QWidget* parent /*= nullptr*/) : FluWidget(parent)
{
    m_vMainLayout = new QVBoxLayout;
    setLayout(m_vMainLayout);

    m_vMainLayout->setSpacing(5);
    m_vMainLayout->setContentsMargins(0, 0, 0, 0);

    m_titleBar = new FluPivotTitleBar;
    m_vMainLayout->addWidget(m_titleBar);

    m_sLayout = new FluStackedLayout;
    m_vMainLayout->addLayout(m_sLayout);

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
    m_sLayout->addWidget(item->getKey(), widget);
}

void FluPivot::pivotItemChanged(FluPivotTitleBarItem* item)
{
    // change bar
    m_titleBar->setCurTitleBarItem(item);
    // change sLayout;
    m_sLayout->setCurrentWidget(item->getKey());
}

void FluPivot::onThemeChanged()
{
    FluStyleSheetUitls::setQssByFileName("FluPivot.qss", this, FluThemeUtils::getUtils()->getTheme());
}
