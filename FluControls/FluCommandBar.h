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
    FluCommandBar(QWidget* parent = nullptr) : QFrame(parent)
    {
        m_nSpacing = 5;
        setFixedHeight(44);
        onThemeChanged();

        m_moreItem = new FluCommandBarIconItem(FluAwesomeType::More, this);
        m_moreItem->hide();
    }

    void setSpacing(int nSpacing)
    {
        m_nSpacing = nSpacing;
    }

    int getSpacing()
    {
        return m_nSpacing;
    }

    void setHasMoreBtn(bool bHasMoreBtn)
    {
        m_bHasMoreBtn = bHasMoreBtn;
        if (!bHasMoreBtn)
            m_moreItem->hide();
        else
            m_moreItem->show();
    }

    bool getHasMoreBtn()
    {
        return m_bHasMoreBtn;
    }

    FluCommandBarIconItem* getMoreBtn()
    {
        return m_moreItem;
    }

    void insertBarItem(int nIndex, FluCommandBarItem* barItem)
    {
        barItem->setParent(this);
        barItem->show();

        if (nIndex < 0 || nIndex >= m_widgets.size())
        {
            m_widgets.push_back(barItem);
        }
        else
        {
            m_widgets.insert(m_widgets.begin() + nIndex, barItem);
        }
        adjustBarItemPositon();
    }

    void addBarItem(FluCommandBarItem* barItem)
    {
        insertBarItem(-1, barItem);
    }

    void removeBarItem(FluCommandBarItem* barItem)
    {
        for (auto iter = m_widgets.begin(); iter != m_widgets.end(); iter++)
        {
            if ((*iter) == barItem)
            {
                m_widgets.erase(iter);
            }
        }
        adjustBarItemPositon();
    }

    void adjustBarItemPositon()
    {
        int nX = contentsMargins().left();
        for (auto iter = m_widgets.begin(); iter != m_widgets.end(); iter++)
        {
            (*iter)->move(nX, (height() - (*iter)->height()) / 2);
            nX += (*iter)->width() + getSpacing();
        }

        if (getHasMoreBtn())
        {
            m_moreItem->move(nX, (height() - m_moreItem->height()) / 2);
            nX += m_moreItem->width() + getSpacing();
        }

        nX += contentsMargins().right();

        setFixedWidth(nX);
    }

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
