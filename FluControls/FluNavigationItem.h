#pragma once

#include <QWidget>
#include <QStyle>

class FluNavigationView;
enum class FluNavigationItemType
{
    Menu,
    IconText,
    Split,
    Search,
};

class FluNavigationItem : public QWidget
{
    Q_OBJECT
  public:
    FluNavigationItem(QWidget* parent = nullptr);

    void setParentView(FluNavigationView* view);
    FluNavigationView* getParentView();

    FluNavigationItemType getItemType();

    void setItemType(FluNavigationItemType itemType);

    virtual void clearAllItemsSelectState(){};
    virtual void updateAllItemsStyleSheet(){};

    // when nav long set item long
    // when nav short set item short

    virtual int getItemHeight();  // to easy get item height

    void setLong(bool bLong)
    {
        setProperty("long", bLong);
        m_bLong = bLong;
        style()->polish(this);
    }

    bool isLong()
    {
        return m_bLong;
    }
  protected:
    FluNavigationItemType m_itemType;
    FluNavigationView* m_parentView;
    bool m_bLong;
};
