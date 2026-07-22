#include "FluTimeLine.h"

FluTimeLine::FluTimeLine(QWidget* parent /*= nullptr*/) : FluVScrollView(parent)
{
    m_mainLayout->setSpacing(0);
    m_mainLayout->setAlignment(Qt::AlignTop);
}

void FluTimeLine::addTimeLineItem(QString text)
{
    addTimeLineItem(-1, text);
}

void FluTimeLine::addTimeLineItem(int index, QString text)
{
    if (index == -1)
    {
        if (m_itemsMap.empty())
        {
            index = 0;
        }
        else
        {
            auto iter = m_itemsMap.rbegin();
            index = iter->first + 1;
        }

        auto timeLineItem = new FluTimeLineItem;
        timeLineItem->addTextItem(text);
        m_itemsMap[index] = timeLineItem;
        m_mainLayout->addWidget(timeLineItem, 0, Qt::AlignTop);
        return;
    }
    else
    {
        auto itf = m_itemsMap.find(index);
        if (itf != m_itemsMap.end())
        {
            itf->second->addTextItem(text);
        }
    }
}
