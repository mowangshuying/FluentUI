#include "FluPagination.h"
#include "../Utils/FluUtils.h"
#include <qmath.h>
#include "FluPaginationItem.h"

FluPagination::FluPagination(int pageCurrent, int pageButtonCount, int itemCount, QWidget* parent /*= nullptr*/) : QWidget(parent)
{
    m_pageCurrent = pageCurrent;
    m_itemCount = itemCount;
    m_pageButtonCount = pageButtonCount;

    m_itemPerPage = 10;
    m_pageCount = 0;
    if (m_itemCount > 0)
    {
        m_pageCount = qCeil(m_itemCount / m_itemPerPage);
    }

    m_pageButtonHalf = qFloor(m_pageButtonCount / 2) + 1;

    //// update current;
    // updateByPageCurrent();

    // set H;
    setFixedHeight(40);

    // layout;
    m_mainLayout = new QHBoxLayout;
    setLayout(m_mainLayout);
    m_mainLayout->setContentsMargins(0, 0, 0, 0);
    m_mainLayout->setSpacing(10);

    m_mainLayout->addStretch(1);
    // pre pre;
    auto beginItem = new FluPaginationItem(FluPaginationItemType::Begin);
    beginItem->setText("<<");
    m_mainLayout->addWidget(beginItem);

    connect(beginItem, &FluPaginationItem::clicked, this, [=]() {
        m_pageCurrent = 1;
        updateByPageCurrent();
    });

    // pre
    auto preItem = new FluPaginationItem(FluPaginationItemType::Pre);
    preItem->setText("<");
    connect(preItem, &FluPaginationItem::clicked, this, [=]() {
        if (m_pageCurrent > 1)
            m_pageCurrent--;
        updateByPageCurrent();
    });

    m_mainLayout->addWidget(preItem);

    // button list count 5;
    for (int i = 1; i <= m_pageButtonCount; i++)
    {
        if (i > m_pageCount)
            continue;

        auto numItem = new FluPaginationItem(FluPaginationItemType::Num);
        numItem->setText(QString::number(i));
        numItem->setPageNum(i);
        numItem->setIndex(i);
        m_numVcts.push_back(numItem);
        m_mainLayout->addWidget(numItem);
        connect(numItem, &FluPaginationItem::clicked, this, [=]() {
            m_pageCurrent = numItem->getPageNum();
            updateByPageCurrent();
        });
    }

    // lst
    auto nextItem = new FluPaginationItem(FluPaginationItemType::Next);
    nextItem->setText(">");
    m_mainLayout->addWidget(nextItem);

    connect(nextItem, &FluPaginationItem::clicked, this, [=]() {
        if (m_pageCurrent <= m_pageCount - 1)
            m_pageCurrent++;
        updateByPageCurrent();
    });

    // lst lst
    auto endItem = new FluPaginationItem(FluPaginationItemType::End);
    endItem->setText(">>");
    connect(endItem, &FluPaginationItem::clicked, this, [=]() {
        m_pageCurrent = m_pageCount;
        updateByPageCurrent();
    });

    m_mainLayout->addWidget(endItem);

    // m_mainLayout = new QHBoxLayout;
    // m_mainLayout->setContentsMargins(0, 0, 0, 0);
    // setLayout(m_mainLayout);

    m_mainLayout->addStretch(1);
    setFixedWidth(500);

    // update current;
    updateByPageCurrent();

    onThemeChanged();
    connect(FluThemeUtils::getUtils(), &FluThemeUtils::themeChanged, [=]() { onThemeChanged(); });
}

void FluPagination::updateByPageCurrent()
{
    emit requestPage(m_pageCurrent, m_itemPerPage);
    emit currentPageChange(m_pageCurrent);
    if (m_pageCount <= m_pageButtonCount)
    {
        for (int i = 0; i < m_numVcts.size(); i++)
        {
            auto tmpItem = m_numVcts[i];
            tmpItem->setText(QString::number(tmpItem->getIndex()));
            tmpItem->setPageNum(tmpItem->getIndex());
            tmpItem->setChecked(tmpItem->getIndex() == m_pageCurrent);
        }
        return;
    }

    if (m_pageCurrent <= m_pageButtonHalf)
    {
        for (int i = 0; i < m_numVcts.size(); i++)
        {
            auto tmpItem = m_numVcts[i];
            tmpItem->setText(QString::number(tmpItem->getIndex()));
            tmpItem->setPageNum(tmpItem->getIndex());
            tmpItem->setChecked(tmpItem->getIndex() == m_pageCurrent);
        }
        return;
    }

    if (m_pageCurrent >= m_pageCount - m_pageButtonHalf + 1)
    {
        // m_pageCount - m_pageButtonHalf + 1
        for (int i = 0; i < m_numVcts.size(); i++)
        {
            auto tmpItem = m_numVcts[i];
            auto tmpNum = m_pageCount - m_pageButtonCount + tmpItem->getIndex();
            tmpItem->setText(QString::number(tmpNum));
            tmpItem->setPageNum(tmpNum);
            tmpItem->setChecked(tmpNum == m_pageCurrent);
        }
        return;
    }

    for (int i = 0; i < m_numVcts.size(); i++)
    {
        auto tmpItem = m_numVcts[i];
        auto tmpNum = tmpItem->getIndex() + m_pageCurrent - m_pageButtonHalf;
        tmpItem->setText(QString::number(tmpNum));
        tmpItem->setPageNum(tmpNum);
        tmpItem->setChecked(tmpNum == m_pageCurrent);
    }
}

void FluPagination::paintEvent(QPaintEvent* event)
{
    QStyleOption opt;
    opt.initFrom(this);
    QPainter painter(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
}
