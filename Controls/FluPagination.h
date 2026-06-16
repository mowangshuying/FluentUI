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
    FluPagination(int nPageCurrent, int nPageButtonCount, int nItemCount, QWidget* parent = nullptr);

    void updateByPageCurrent();

    void paintEvent(QPaintEvent* event) override;
  signals:
    void currentPageChange(int nCurrentPage);
    void requestPage(int nPage, int nCount);
  public slots:

    void onThemeChanged()
    {
        FluStyleSheetUitls::setQssByFileName("FluPagination.qss", this, FluThemeUtils::getUtils()->getTheme());
    }

  protected:
    QHBoxLayout* m_hMainLayout;
    int m_nPageCurrent;
    int m_nItemCount;
    int m_nPageButtonCount;
    int m_nPageCount;
    int m_nItemPerPage;
    int m_nPageButtonHalf;

    std::vector<FluPaginationItem*> m_numVcts;
};
