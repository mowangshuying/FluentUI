#pragma once

#include "FluWidget.h"
#include <QStyle>

class FluVNavigationView;
enum class FluNavigationItemType
{
    Menu,
    IconText,
    Split,
    Search,
    Setting,
};

class FluNavigationItem : public FluWidget
{
    Q_OBJECT
  public:
    FluNavigationItem(QWidget* parent = nullptr);

    void setParentView(FluVNavigationView* view);
    FluVNavigationView* getParentView();

    FluNavigationItemType getItemType();

    void setItemType(FluNavigationItemType itemType);

    virtual void clearAllItemsSelectState(){};
    virtual void updateAllItemsStyleSheet(){};

    // when nav long set item long
    // when nav short set item short

    virtual int getItemHeight();  // to easy get item height

    virtual void setLong(bool bLong)
    {
        setProperty("isLong", bLong);
        m_bLong = bLong;
        style()->polish(this);
    }

    bool isLong()
    {
        return m_bLong;
    }

    QString getKey()
    {
        return m_key;
    }

    void setKey(QString key)
    {
        m_key = key;
    }

  protected:
    FluNavigationItemType m_itemType;
    FluVNavigationView* m_parentView;
    bool m_bLong;
    QString m_key;
};
