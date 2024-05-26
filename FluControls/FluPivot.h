#pragma once

#include "FluWidget.h"
#include "FluStackedLayout.h"
#include <QVBoxLayout>
#include "FluPivotTitleBar.h"
#include "FluPivotTitleBarItem.h"
#include "FluStackedLayout.h"

class FluPivot : public FluWidget
{
    Q_OBJECT
  public:
    FluPivot(QWidget* parent = nullptr) : FluWidget(parent)
    {
        m_vMainLayout = new QVBoxLayout;
        setLayout(m_vMainLayout);

        m_vMainLayout->setSpacing(5);
        m_vMainLayout->setContentsMargins(0, 0, 0, 0);

        m_titleBar = new FluPivotTitleBar;
        m_vMainLayout->addWidget(m_titleBar);

        m_sLayout = new FluStackedLayout;
        m_vMainLayout->addLayout(m_sLayout);

        FluStyleSheetUitls::setQssByFileName(":/StyleSheet/light/FluPivot.qss", this);
    }

    void addPivotItem(QString key, QWidget* widget)
    {
        auto titleBarItem = new FluPivotTitleBarItem;
        titleBarItem->setKey(key);
        addPivotItem(titleBarItem, widget);
    }

    void addPivotItem(FluPivotTitleBarItem* item, QWidget* widget)
    {
        connect(item, &FluPivotTitleBarItem::clicked, [=]() { pivotItemChanged(item); });

        m_titleBar->addTitleBarItem(item);
        m_sLayout->addWidget(item->getKey(), widget);
    }

  public slots:
    void pivotItemChanged(FluPivotTitleBarItem* item)
    {
        // change bar
        m_titleBar->setCurTitleBarItem(item);
        // change sLayout;
        m_sLayout->setCurrentWidget(item->getKey());
    }

    void onThemeChanged()
    {
        if (FluThemeUtils::getUtils()->getTheme() == FluTheme::Light)
        {
            FluStyleSheetUitls::setQssByFileName(":/StyleSheet/light/FluPivot.qss", this);
        }
        else
        {
            FluStyleSheetUitls::setQssByFileName(":/StyleSheet/dark/FluPivot.qss", this);
        }
    }

  protected:
    QVBoxLayout* m_vMainLayout;
    FluPivotTitleBar* m_titleBar;
    FluStackedLayout* m_sLayout;
};
