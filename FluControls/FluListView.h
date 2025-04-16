#pragma once

#include "FluVScrollView.h"
#include "../FluUtils/FluUtils.h"
#include <QVBoxLayout>
#include <QListWidget>
#include "FluListViewItemDelegate.h"

class FluListView : public QListWidget
{
    Q_OBJECT
    Q_PROPERTY(QColor backgroundColorEx READ getBackgroundColorEx WRITE setBackgroundColorEx)
    Q_PROPERTY(QColor hoverColorEx READ getHoverColorEx WRITE setHoverColorEx)
    Q_PROPERTY(QColor indicatorColorEx READ getIndicatorColorEx WRITE setIndicatorColorEx)
    Q_PROPERTY(QColor textColorEx READ getTextColorEx WRITE setTextColorEx)
  public:
    FluListView(QWidget* parent = nullptr);

    // QColor;
    QColor getBackgroundColorEx() const
    {
        return m_listViewItemDelegate->getBackgroundColorEx();
    }

    void setBackgroundColorEx(QColor color)
    {
        m_listViewItemDelegate->setBackgroundColorEx(color);
    }

    QColor getHoverColorEx() const
    {
        return m_listViewItemDelegate->getHoverColorEx();
    }

    void setHoverColorEx(QColor color)
    {
        m_listViewItemDelegate->setHoverColorEx(color);
    }

    QColor getIndicatorColorEx()
    {
        return m_listViewItemDelegate->getIndicatorColorEx();
    }

    void setIndicatorColorEx(QColor color)
    {
        m_listViewItemDelegate->setIndicatorColorEx(color);
    }

    QColor getTextColorEx()
    {
        return m_listViewItemDelegate->getTextColorEx();
    }

    void setTextColorEx(QColor color)
    {
        m_listViewItemDelegate->setTextColorEx(color);
    }
  public slots:
    void onThemeChanged();

  protected:
    FluScrollDelegate* m_delegate;
    FluListViewItemDelegate* m_listViewItemDelegate;
};
