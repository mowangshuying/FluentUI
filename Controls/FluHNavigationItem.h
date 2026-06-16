#pragma once

#include "FluWidget.h"
#include <QStyle>

class FluHNavigationView;
enum class FluHNavigationItemType
{
    Menu,
    IconText,
    Split,
    Search,
    Setting,
};

class FluHNavigationItem : public FluWidget
{
    Q_OBJECT
  public:
    FluHNavigationItem(QWidget* parent = nullptr);

    void setParentView(FluHNavigationView* view);
    FluHNavigationView* getParentView();

    FluHNavigationItemType getItemType();

    void setItemType(FluHNavigationItemType itemType);

    virtual void clearAllItemsSelectState() {};
    virtual void updateAllItemsStyleSheet() {};

    QString getKey()
    {
        return m_key;
    }

    void setKey(QString key)
    {
        m_key = key;
    }

  protected:
    FluHNavigationItemType m_itemType;
    FluHNavigationView* m_parentView;
    bool m_bLong;
    QString m_key;
};
