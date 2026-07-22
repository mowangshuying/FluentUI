#include "FluPivotTitleBar.h"

FluPivotTitleBar::FluPivotTitleBar(QWidget* parent /*= nullptr*/) : FluWidget(parent)
{
    m_mainLayout = new QHBoxLayout;
    setLayout(m_mainLayout);

    m_mainLayout->setContentsMargins(0, 0, 0, 0);
    m_mainLayout->setAlignment(Qt::AlignLeft);

    onThemeChanged();
}

void FluPivotTitleBar::addTitleBarItem(FluPivotTitleBarItem* item)
{
    m_mainLayout->addWidget(item);
}

void FluPivotTitleBar::setCurTitleBarItem(FluPivotTitleBarItem* titleBarItem)
{
    for (int i = 0; i < m_mainLayout->count(); i++)
    {
        QLayoutItem* item = m_mainLayout->itemAt(i);
        if (item == nullptr)
            continue;

        FluPivotTitleBarItem* curTitleBarItem = (FluPivotTitleBarItem*)item->widget();
        if (curTitleBarItem == nullptr)
            continue;

        if (titleBarItem == curTitleBarItem)
        {
            curTitleBarItem->setSelected(true);
        }
        else
        {
            curTitleBarItem->setSelected(false);
        }
    }
}

void FluPivotTitleBar::onThemeChanged()
{
    FluStyleSheetUtils::setQssByFileName("FluPivotTitleBar.qss", this, FluThemeUtils::getUtils()->getTheme());
}
