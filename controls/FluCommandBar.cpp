#include "FluCommandBar.h"

FluCommandBar::FluCommandBar(QWidget* parent) : QFrame(parent)
{
    m_spacing = 5;
    setFixedHeight(30);
    onThemeChanged();

    m_moreItem = new FluCommandBarIconItem(FluAwesomeType::More, this);
    m_moreItem->hide();
    onThemeChanged();
    connect(FluThemeUtils::getUtils(), &FluThemeUtils::themeChanged, this, [=](FluTheme theme) { onThemeChanged(); });
}

void FluCommandBar::setSpacing(int spacing)
{
    m_spacing = spacing;
}

int FluCommandBar::getSpacing()
{
    return m_spacing;
}

void FluCommandBar::setHasMoreButton(bool hasMoreButton)
{
    m_hasMoreButton = hasMoreButton;
    if (!hasMoreButton)
        m_moreItem->hide();
    else
        m_moreItem->show();
}

bool FluCommandBar::getHasMoreButton()
{
    return m_hasMoreButton;
}

FluCommandBarIconItem* FluCommandBar::getMoreButton()
{
    return m_moreItem;
}

void FluCommandBar::insertBarItem(int index, FluCommandBarItem* barItem)
{
    barItem->setParent(this);
    barItem->show();

    if (index < 0 || index >= m_widgets.size())
    {
        m_widgets.push_back(barItem);
    }
    else
    {
        m_widgets.insert(m_widgets.begin() + index, barItem);
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
    int x = contentsMargins().left();
    for (auto iter = m_widgets.begin(); iter != m_widgets.end(); iter++)
    {
        (*iter)->move(x, (height() - (*iter)->height()) / 2);
        x += (*iter)->width() + getSpacing();
    }

    if (getHasMoreButton())
    {
        m_moreItem->move(x, (height() - m_moreItem->height()) / 2);
        x += m_moreItem->width() + getSpacing();
    }

    x += contentsMargins().right();

    setFixedWidth(x);
}
