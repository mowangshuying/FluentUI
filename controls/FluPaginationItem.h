#pragma once

#include <QPushButton>
#include "../Utils/FluUtils.h"
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
        m_pageNum = -1;
        m_index = -1;
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
        return m_pageNum;
    }

    void setPageNum(int pageNum)
    {
        m_pageNum = pageNum;
    }

    int getIndex()
    {
        return m_index;
    }

    void setIndex(int index)
    {
        m_index = index;
    }

    bool getChecked()
    {
        return m_isChecked;
    }

    void setChecked(bool isChecked)
    {
        m_isChecked = isChecked;
        style()->polish(this);
    }

  public slots:
    void onThemeChanged()
    {
        FluStyleSheetUtils::setQssByFileName("FluPaginationItem.qss", this, FluThemeUtils::getUtils()->getTheme());
    }

  protected:
    FluPaginationItemType m_itemType;
    FluAwesomeType m_awesomeType;
    bool m_isChecked;
    int m_pageNum;
    int m_index;
};
