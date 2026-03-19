#pragma once

#include <QFrame>
#include "../FluUtils/FluUtils.h"
#include <vector>
#include "FluCommandBarItem.h"
#include "FluCommandBarIconItem.h"

class FluCommandBar : public QFrame
{
    Q_OBJECT
  public:
    FluCommandBar(QWidget* parent = nullptr);

    void setSpacing(int nSpacing);

    int getSpacing();

    void setHasMoreBtn(bool bHasMoreBtn);

    bool getHasMoreBtn();

    FluCommandBarIconItem* getMoreBtn();

    void insertBarItem(int nIndex, FluCommandBarItem* barItem);

    void addBarItem(FluCommandBarItem* barItem);

    void removeBarItem(FluCommandBarItem* barItem);

    void adjustBarItemPositon();

  public slots:
    void onThemeChanged()
    {
        FluStyleSheetUitls::setQssByFileName("FluCommandBar.qss", this, FluThemeUtils::getUtils()->getTheme());
    }

  protected:
    std::vector<FluCommandBarItem*> m_widgets;
    FluCommandBarIconItem* m_moreItem;
    int m_nSpacing;
    bool m_bHasMoreBtn;
};
