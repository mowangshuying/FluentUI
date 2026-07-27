#pragma once

#include "FluWidget.h"
#include "FluToggleButton.h"
#include <QHBoxLayout>
#include <QString>
#include <QStyleOption>
#include <QPainter>
#include <QStyle>
#include <vector>

class FluPaginationItem;
class FluPagination : public QWidget
{
    Q_OBJECT
  public:
    FluPagination(int pageCurrent, int pageButtonCount, int itemCount, QWidget* parent = nullptr);

    void updateByPageCurrent();

    void paintEvent(QPaintEvent* event) override;
  signals:
    void currentPageChange(int currentPage);
    void requestPage(int page, int count);
  public slots:

    void onThemeChanged()
    {
        FluStyleSheetUtils::setQssByFileName("FluPagination.qss", this, FluThemeUtils::getUtils()->getTheme());
    }

  protected:
    QHBoxLayout* m_mainLayout;
    int m_pageCurrent;
    int m_itemCount;
    int m_pageButtonCount;
    int m_pageCount;
    int m_itemPerPage;
    int m_pageButtonHalf;

    std::vector<FluPaginationItem*> m_numVcts;
};
