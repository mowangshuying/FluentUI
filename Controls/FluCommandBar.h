#pragma once

#include <QFrame>
#include "../Utils/FluUtils.h"
#include <vector>
#include "FluCommandBarItem.h"
#include "FluCommandBarIconItem.h"

class FluCommandBar : public QFrame
{
    Q_OBJECT
  public:
    FluCommandBar(QWidget* parent = nullptr);

    void setSpacing(int spacing);

    int getSpacing();

    void setHasMoreButton(bool hasMoreButton);

    bool getHasMoreButton();

    FluCommandBarIconItem* getMoreButton();

    void insertBarItem(int index, FluCommandBarItem* barItem);

    void addBarItem(FluCommandBarItem* barItem);

    void removeBarItem(FluCommandBarItem* barItem);

    void adjustBarItemPositon();

  public slots:
    void onThemeChanged()
    {
        FluStyleSheetUtils::setQssByFileName("FluCommandBar.qss", this, FluThemeUtils::getUtils()->getTheme());
    }

  protected:
    std::vector<FluCommandBarItem*> m_widgets;
    FluCommandBarIconItem* m_moreItem;
    int m_spacing;
    bool m_hasMoreButton;
};
