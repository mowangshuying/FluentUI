#pragma once

#include <QWidget>

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

    virtual int getItemHeight();  // to easy get item height

  protected:
    FluNavigationItemType m_itemType;
    FluNavigationView* m_parentView;
};
