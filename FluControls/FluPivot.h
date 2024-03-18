#pragma once

#include <QWidget>
#include "FluStackedLayout.h"
#include <QVBoxLayout>
#include "FluPivotTitleBar.h"
#include "FluPivotTitleBarItem.h"
#include "FluStackedLayout.h"

class FluPivot : public QWidget
{
	Q_OBJECT
  public:
      FluPivot(QWidget* parent = nullptr) : QWidget(parent)
      {
          m_vMainLayout = new QVBoxLayout;
          setLayout(m_vMainLayout);

          m_vMainLayout->setSpacing(5);
          m_vMainLayout->setContentsMargins(0, 0, 0, 0);

          m_titleBar = new FluPivotTitleBar;
          m_vMainLayout->addWidget(m_titleBar);

          m_sLayout = new FluStackedLayout;
          m_vMainLayout->addLayout(m_sLayout);
      }

      void addPivotItem(QString key, QWidget* widget)
      {
          auto titleBarItem = new FluPivotTitleBarItem;
          titleBarItem->setKey(key);
          addPivotItem(titleBarItem, widget);
      }

      void addPivotItem(FluPivotTitleBarItem* item, QWidget* widget)
      {
          connect(item, &FluPivotTitleBarItem::clicked, [=]() { 
              pivotItemChanged(item);
              });

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

  protected:
    QVBoxLayout* m_vMainLayout;
    FluPivotTitleBar* m_titleBar;
    FluStackedLayout* m_sLayout;
};
