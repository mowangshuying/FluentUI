#include "FluCommandBar.h"

FluCommandBar::FluCommandBar(QWidget* parent) : QFrame(parent)
{
    m_nSpacing = 5;
    setFixedHeight(30);
    onThemeChanged();

    m_moreItem = new FluCommandBarIconItem(FluAwesomeType::More, this);
    m_moreItem->hide();
    onThemeChanged();
    connect(FluThemeUtils::getUtils(), &FluThemeUtils::themeChanged, this, [=](FluTheme theme) {
        onThemeChanged();
        });
}

void FluCommandBar::setSpacing(int nSpacing)
{
    m_nSpacing = nSpacing;
}

int FluCommandBar::getSpacing()
{
    return m_nSpacing;
}

void FluCommandBar::setHasMoreBtn(bool bHasMoreBtn)
{
    m_bHasMoreBtn = bHasMoreBtn;
    if (!bHasMoreBtn)
        m_moreItem->hide();
    else
        m_moreItem->show();
}

bool FluCommandBar::getHasMoreBtn()
{
    return m_bHasMoreBtn;
}

FluCommandBarIconItem* FluCommandBar::getMoreBtn()
{
    return m_moreItem;
}

void FluCommandBar::insertBarItem(int nIndex, FluCommandBarItem* barItem)
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

void FluCommandBar::addBarItem(FluCommandBarItem* barItem)
{
    insertBarItem(-1, barItem);
}

void FluCommandBar::removeBarItem(FluCommandBarItem* barItem)
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

void FluCommandBar::adjustBarItemPositon()
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
