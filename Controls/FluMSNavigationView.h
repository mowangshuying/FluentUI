#pragma once

#include "FluWidget.h"
#include <QVBoxLayout>
#include "FluVScrollView.h"
#include <QStyleOption>
#include <QPainter>
#include "FluMSNavigationItem.h"

class FluMSNavigationView : public FluWidget
{
    Q_OBJECT
  public:
    FluMSNavigationView(QWidget* parent = nullptr) : FluWidget(parent)
    {
        m_vLayout = new QVBoxLayout;
        setLayout(m_vLayout);

        m_topWrapWidget = new QWidget(this);
        m_vScrollView = new FluVScrollView(this);
        m_bottomWrapWidget = new QWidget(this);

        m_vTopLayout = new QVBoxLayout;
        m_topWrapWidget->setLayout(m_vTopLayout);

        m_vBottomLayout = new QVBoxLayout;
        m_bottomWrapWidget->setLayout(m_vBottomLayout);

        m_vLayout->addWidget(m_topWrapWidget);
        m_vLayout->addWidget(m_vScrollView);
        m_vLayout->addWidget(m_bottomWrapWidget);

        m_topWrapWidget->setObjectName("topWrapWidget");
        m_vScrollView->setObjectName("vScrollView");
        m_bottomWrapWidget->setObjectName("bottomWrapWidget");

        m_vLayout->setContentsMargins(0, 4, 0, 4);
        m_vTopLayout->setContentsMargins(4, 0, 4, 0);
        m_vScrollView->getMainLayout()->setContentsMargins(4, 0, 4, 0);
        m_vBottomLayout->setContentsMargins(4, 0, 4, 0);

        m_vLayout->setAlignment(Qt::AlignTop);
        m_vTopLayout->setAlignment(Qt::AlignTop);
        m_vScrollView->getMainLayout()->setAlignment(Qt::AlignTop);
        m_vBottomLayout->setAlignment(Qt::AlignBottom);

        setFixedWidth(75);
        onThemeChanged();
    }

    void addItem(FluMSNavigationItem* item, FluMSNavigationItemPosition position = FluMSNavigationItemPosition::Mid)
    {
        item->setParentView(this);
        switch (position)
        {
            case FluMSNavigationItemPosition::Top:
                addItemToTopLayout(item);
                break;
            case FluMSNavigationItemPosition::Mid:
                addItemToMidLayout(item);
                break;
            case FluMSNavigationItemPosition::Bottom:
                addItemToBottomLayout(item);
                break;
            default:
                break;
        }
    }

    void addItemToTopLayout(QWidget* item)
    {
        m_vTopLayout->addWidget(item, 0, Qt::AlignTop);
    }

    void addItemToMidLayout(QWidget* item)
    {
        m_vScrollView->getMainLayout()->addWidget(item, 0, Qt::AlignTop);
    }

    void addItemToBottomLayout(QWidget* item)
    {
        m_vBottomLayout->addWidget(item, 0, Qt::AlignTop);
    }

    void setSelectedItem(FluMSNavigationItem* item)
    {
        for (int i = 0; i < m_vTopLayout->count(); i++)
        {
            auto curItem = (FluMSNavigationItem*)(m_vTopLayout->itemAt(i)->widget());
            curItem->setSelected(false);
        }

        for (int i = 0; i < m_vScrollView->getMainLayout()->count(); i++)
        {
            auto curItem = (FluMSNavigationItem*)(m_vScrollView->getMainLayout()->itemAt(i)->widget());
            curItem->setSelected(false);
        }

        for (int i = 0; i < m_vBottomLayout->count(); i++)
        {
            auto curItem = (FluMSNavigationItem*)(m_vBottomLayout->itemAt(i)->widget());
            curItem->setSelected(false);
        }

        if (item != nullptr)
            item->setSelected(true);
    }

    void paintEvent(QPaintEvent* event)
    {
        QStyleOption opt;
        opt.initFrom(this);
        QPainter painter(this);
        style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
    }

  public slots:
    void onThemeChanged()
    {
        FluStyleSheetUitls::setQssByFileName("FluMSNavigationView.qss", this, FluThemeUtils::getUtils()->getTheme());
    }

  protected:
    QVBoxLayout* m_vLayout;

    QVBoxLayout* m_vTopLayout;
    QWidget* m_topWrapWidget;
    FluVScrollView* m_vScrollView;
    QVBoxLayout* m_vBottomLayout;
    QWidget* m_bottomWrapWidget;
};
