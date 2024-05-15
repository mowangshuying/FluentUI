#pragma once

#include "FluWidget.h"
#include <QStyle>

class FluVNavigationView;
enum class FluVNavigationItemType
{
    Menu,
    IconText,
    Split,
    Search,
    Setting,
};

class FluVNavigationItem : public FluWidget
{
    Q_OBJECT
  public:
    FluVNavigationItem(QWidget* parent = nullptr);

    void setParentView(FluVNavigationView* view);
    FluVNavigationView* getParentView();

    FluVNavigationItemType getItemType();

    void setItemType(FluVNavigationItemType itemType);

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
    FluVNavigationItemType m_itemType;
    FluVNavigationView* m_parentView;
    bool m_bLong;
    QString m_key;
};
