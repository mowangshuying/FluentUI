#pragma once

#include "FluWidget.h"
#include <QStyle>

class FluVNavigationView;
class FluVNavigationFlyIconTextItem;
enum class FluVNavigationItemType
{
    Menu,
    IconText,
    Split,
    Search,
    Setting,
};

enum class FluVNavigationState
{
    None,
    Collapsing,
    Expanding,
    Collapsed,
    Expanded,
    // Long,
    // Short,
};

class FluVNavigationItem : public FluWidget
{
    Q_OBJECT
  public:
    FluVNavigationItem(QWidget* parent = nullptr);

    void setState(FluVNavigationState state);
    FluVNavigationState getState();

    void setParentView(FluVNavigationView* view);
    FluVNavigationView* getParentView();

    FluVNavigationFlyIconTextItem* getFlyItem();

    void setParentFlyItem(FluVNavigationFlyIconTextItem* flyItem);

    FluVNavigationItemType getItemType();

    void setItemType(FluVNavigationItemType itemType);

    virtual void clearAllItemsSelectState() {};
    virtual void updateAllItemsStyleSheet() {};

    // when nav long set item long
    // when nav short set item short

    virtual int getItemHeight();  // to easy get item height

    virtual void setLong(bool bLong);

    virtual void setItemWidth(int nWidth)
    {
        setFixedWidth(nWidth);
    }

    bool isLong();

    QString getKey();

    void setKey(QString key);

  protected:
    FluVNavigationItemType m_itemType;
    FluVNavigationView* m_parentView;
    FluVNavigationFlyIconTextItem* m_flyItem;  // for fly item
    FluVNavigationState m_state;
    bool m_bLong;
    QString m_key;
};
