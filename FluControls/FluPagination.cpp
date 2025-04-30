#include "FluPagination.h"
#include "../FluUtils/FluUtils.h"
#include <qmath.h>
#include "FluPaginationItem.h"

FluPagination::FluPagination(int nPageCurrent, int nPageButtonCount, int nItemCount, QWidget* parent /*= nullptr*/) : QWidget(parent)
{
    m_nPageCurrent = nPageCurrent;
    m_nItemCount = nItemCount;
    m_nPageButtonCount = nPageButtonCount;

    m_nItemPerPage = 10;
    m_nPageCount = 0;
    if (m_nItemCount > 0)
    {
        m_nPageCount = qCeil(m_nItemCount / m_nItemPerPage);
    }

    m_nPageButtonHalf = qFloor(m_nPageButtonCount / 2) + 1;

    //// update current;
    // updateByPageCurrent();

    // set H;
    setFixedHeight(40);

    // layout;
    m_hMainLayout = new QHBoxLayout;
    setLayout(m_hMainLayout);
    m_hMainLayout->setContentsMargins(0, 0, 0, 0);
    m_hMainLayout->setSpacing(10);

    m_hMainLayout->addStretch(1);
    // pre pre;
    auto beginItem = new FluPaginationItem(FluPaginationItemType::Begin);
    beginItem->setText("<<");
    m_hMainLayout->addWidget(beginItem);

    connect(beginItem, &FluPaginationItem::clicked, this, [=]() {
        m_nPageCurrent = 1;
        updateByPageCurrent();
    });

    // pre
    auto preItem = new FluPaginationItem(FluPaginationItemType::Pre);
    preItem->setText("<");
    connect(preItem, &FluPaginationItem::clicked, this, [=]() {
        if (m_nPageCurrent > 1)
            m_nPageCurrent--;
        updateByPageCurrent();
    });

    m_hMainLayout->addWidget(preItem);

    // button list count 5;
    for (int i = 1; i <= m_nPageButtonCount; i++)
    {
        if (i > m_nPageCount)
            continue;

        auto numItem = new FluPaginationItem(FluPaginationItemType::Num);
        numItem->setText(QString::number(i));
        numItem->setPageNum(i);
        numItem->setIndex(i);
        m_numVcts.push_back(numItem);
        m_hMainLayout->addWidget(numItem);
        connect(numItem, &FluPaginationItem::clicked, this, [=]() {
            m_nPageCurrent = numItem->getPageNum();
            updateByPageCurrent();
        });
    }

    // lst
    auto nextItem = new FluPaginationItem(FluPaginationItemType::Next);
    nextItem->setText(">");
    m_hMainLayout->addWidget(nextItem);

    connect(nextItem, &FluPaginationItem::clicked, this, [=]() {
        if (m_nPageCurrent <= m_nPageCount - 1)
            m_nPageCurrent++;
        updateByPageCurrent();
    });

    // lst lst
    auto endItem = new FluPaginationItem(FluPaginationItemType::End);
    endItem->setText(">>");
    connect(endItem, &FluPaginationItem::clicked, this, [=]() {
        m_nPageCurrent = m_nPageCount;
        updateByPageCurrent();
    });

    m_hMainLayout->addWidget(endItem);

    // m_hMainLayout = new QHBoxLayout;
    // m_hMainLayout->setContentsMargins(0, 0, 0, 0);
    // setLayout(m_hMainLayout);

    m_hMainLayout->addStretch(1);
    setFixedWidth(500);

    // update current;
    updateByPageCurrent();

    onThemeChanged();
    connect(FluThemeUtils::getUtils(), &FluThemeUtils::themeChanged, [=]() { onThemeChanged(); });
}

void FluPagination::updateByPageCurrent()
{
    emit requestPage(m_nPageCurrent, m_nItemPerPage);
    emit currentPageChange(m_nPageCurrent);
    if (m_nPageCount <= m_nPageButtonCount)
    {
        for (int i = 0; i < m_numVcts.size(); i++)
        {
            auto tmpItem = m_numVcts[i];
            tmpItem->setText(QString::number(tmpItem->getIndex()));
            tmpItem->setPageNum(tmpItem->getIndex());
            tmpItem->setChecked(tmpItem->getIndex() == m_nPageCurrent);
        }
        return;
    }

    if (m_nPageCurrent <= m_nPageButtonHalf)
    {
        for (int i = 0; i < m_numVcts.size(); i++)
        {
            auto tmpItem = m_numVcts[i];
            tmpItem->setText(QString::number(tmpItem->getIndex()));
            tmpItem->setPageNum(tmpItem->getIndex());
            tmpItem->setChecked(tmpItem->getIndex() == m_nPageCurrent);
        }
        return;
    }

    if (m_nPageCurrent >= m_nPageCount - m_nPageButtonHalf + 1)
    {
        // m_nPageCount - m_nPageButtonHalf + 1
        for (int i = 0; i < m_numVcts.size(); i++)
        {
            auto tmpItem = m_numVcts[i];
            auto tmpNum = m_nPageCount - m_nPageButtonCount + tmpItem->getIndex();
            tmpItem->setText(QString::number(tmpNum));
            tmpItem->setPageNum(tmpNum);
            tmpItem->setChecked(tmpNum == m_nPageCurrent);
        }
        return;
    }

    for (int i = 0; i < m_numVcts.size(); i++)
    {
        auto tmpItem = m_numVcts[i];
        auto tmpNum = tmpItem->getIndex() + m_nPageCurrent - m_nPageButtonHalf;
        tmpItem->setText(QString::number(tmpNum));
        tmpItem->setPageNum(tmpNum);
        tmpItem->setChecked(tmpNum == m_nPageCurrent);
    }
}

void FluPagination::paintEvent(QPaintEvent* event)
{
    QStyleOption opt;
    opt.initFrom(this);
    QPainter painter(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
}
