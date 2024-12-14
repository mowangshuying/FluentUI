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

    virtual void clearAllItemsSelectState() {};
    virtual void updateAllItemsStyleSheet() {};

    // when nav long set item long
    // when nav short set item short

    virtual int getItemHeight();  // to easy get item height

    virtual void setLong(bool bLong);

    bool isLong();

    QString getKey();

    void setKey(QString key);

  protected:
    FluVNavigationItemType m_itemType;
    FluVNavigationView* m_parentView;
    bool m_bLong;
    QString m_key;
};
