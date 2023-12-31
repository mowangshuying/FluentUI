#pragma once

#include <QWidget>

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

    FluNavigationItemType getItemType();

    void setItemType(FluNavigationItemType itemType);

    virtual int getItemHeight(); // to easy get item height

protected:
    FluNavigationItemType m_itemType;
};
