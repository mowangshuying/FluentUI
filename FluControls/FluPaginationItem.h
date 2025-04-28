#pragma once

#include <QPushButton>
#include "../FluUtils/FluUtils.h"
#include <QStyle>

enum class FluPaginationItemType
{
    Begin,
    Pre,
    Num,
    Next,
    End,
};

class FluPaginationItem : public QPushButton
{
    Q_OBJECT
    Q_PROPERTY(int pageNum READ getPageNum WRITE setPageNum)
    Q_PROPERTY(bool checked READ getChecked WRITE setChecked)
  public:
    FluPaginationItem(QWidget* parent = nullptr) : QPushButton(parent)
    {
        m_awesomeType = FluAwesomeType::None;
        setItemType(FluPaginationItemType::Num);
        setChecked(false);
        m_nPageNum = -1;
        m_nIndex = -1;
        setFixedHeight(30);
        setMinimumWidth(30);
        onThemeChanged();
        connect(FluThemeUtils::getUtils(), &FluThemeUtils::themeChanged, [=](FluTheme theme) { onThemeChanged(); });
    }

    FluPaginationItem(FluPaginationItemType type, QWidget* parent = nullptr) : FluPaginationItem(parent)
    {
        setItemType(type);
    }

    FluPaginationItemType getItemType()
    {
        return m_itemType;
    }

    void setItemType(FluPaginationItemType itemType)
    {
        m_itemType = itemType;
    }

    int getPageNum()
    {
        return m_nPageNum;
    }

    void setPageNum(int nPageNum)
    {
        m_nPageNum = nPageNum;
    }

    int getIndex()
    {
        return m_nIndex;
    }

    void setIndex(int nIndex)
    {
        m_nIndex = nIndex;
    }

    bool getChecked()
    {
        return m_bChecked;
    }

    void setChecked(bool bChecked)
    {
        m_bChecked = bChecked;
        style()->polish(this);
    }

  public slots:
    void onThemeChanged()
    {
        FluStyleSheetUitls::setQssByFileName("FluPaginationItem.qss", this, FluThemeUtils::getUtils()->getTheme());
    }

  protected:
    FluPaginationItemType m_itemType;
    FluAwesomeType m_awesomeType;
    bool m_bChecked;
    int m_nPageNum;
    int m_nIndex;
};
