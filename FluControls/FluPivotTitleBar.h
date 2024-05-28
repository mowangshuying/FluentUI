#pragma once

#include "FluWidget.h"
#include <QHBoxLayout>
#include "FluPivotTitleBarItem.h"

class FluPivotTitleBar : public FluWidget
{
    Q_OBJECT
  public:
    FluPivotTitleBar(QWidget* parent = nullptr) : FluWidget(parent)
    {
        m_hMainLayout = new QHBoxLayout;
        setLayout(m_hMainLayout);

        m_hMainLayout->setContentsMargins(0, 0, 0, 0);
        m_hMainLayout->setAlignment(Qt::AlignLeft);

        FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluPivotTitleBar.qss", this);
    }

    void addTitleBarItem(FluPivotTitleBarItem* item)
    {
        m_hMainLayout->addWidget(item);
    }

    void setCurTitleBarItem(FluPivotTitleBarItem* titleBarItem)
    {
        for (int i = 0; i < m_hMainLayout->count(); i++)
        {
            QLayoutItem* item = m_hMainLayout->itemAt(i);
            if (item == nullptr)
                continue;

            FluPivotTitleBarItem* curTitleBarItem = (FluPivotTitleBarItem*)item->widget();
            if (curTitleBarItem == nullptr)
                continue;

            if (titleBarItem == curTitleBarItem)
            {
                curTitleBarItem->setSelected(true);
            }
            else
            {
                curTitleBarItem->setSelected(false);
            }
        }
    }
  public slots:
    void onThemeChanged()
    {
        if (FluThemeUtils::getUtils()->getTheme() == FluTheme::Light)
        {
            FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluPivotTitleBar.qss", this);
        }
        else
        {
            FluStyleSheetUitls::setQssByFileName("../StyleSheet/dark/FluPivotTitleBar.qss", this);
        }
    }

  protected:
    QHBoxLayout* m_hMainLayout;
};
