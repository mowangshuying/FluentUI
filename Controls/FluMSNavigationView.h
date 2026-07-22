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
        m_layout = new QVBoxLayout;
        setLayout(m_layout);

        m_topWrapWidget = new QWidget(this);
        m_scrollView = new FluVScrollView(this);
        m_bottomWrapWidget = new QWidget(this);

        m_topLayout = new QVBoxLayout;
        m_topWrapWidget->setLayout(m_topLayout);

        m_bottomLayout = new QVBoxLayout;
        m_bottomWrapWidget->setLayout(m_bottomLayout);

        m_layout->addWidget(m_topWrapWidget);
        m_layout->addWidget(m_scrollView);
        m_layout->addWidget(m_bottomWrapWidget);

        m_topWrapWidget->setObjectName("topWrapWidget");
        m_scrollView->setObjectName("vScrollView");
        m_bottomWrapWidget->setObjectName("bottomWrapWidget");

        m_layout->setContentsMargins(0, 4, 0, 4);
        m_topLayout->setContentsMargins(4, 0, 4, 0);
        m_scrollView->getMainLayout()->setContentsMargins(4, 0, 4, 0);
        m_bottomLayout->setContentsMargins(4, 0, 4, 0);

        m_layout->setAlignment(Qt::AlignTop);
        m_topLayout->setAlignment(Qt::AlignTop);
        m_scrollView->getMainLayout()->setAlignment(Qt::AlignTop);
        m_bottomLayout->setAlignment(Qt::AlignBottom);

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
        m_topLayout->addWidget(item, 0, Qt::AlignTop);
    }

    void addItemToMidLayout(QWidget* item)
    {
        m_scrollView->getMainLayout()->addWidget(item, 0, Qt::AlignTop);
    }

    void addItemToBottomLayout(QWidget* item)
    {
        m_bottomLayout->addWidget(item, 0, Qt::AlignTop);
    }

    void setSelectedItem(FluMSNavigationItem* item)
    {
        for (int i = 0; i < m_topLayout->count(); i++)
        {
            auto curItem = (FluMSNavigationItem*)(m_topLayout->itemAt(i)->widget());
            curItem->setSelected(false);
        }

        for (int i = 0; i < m_scrollView->getMainLayout()->count(); i++)
        {
            auto curItem = (FluMSNavigationItem*)(m_scrollView->getMainLayout()->itemAt(i)->widget());
            curItem->setSelected(false);
        }

        for (int i = 0; i < m_bottomLayout->count(); i++)
        {
            auto curItem = (FluMSNavigationItem*)(m_bottomLayout->itemAt(i)->widget());
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
        FluStyleSheetUtils::setQssByFileName("FluMSNavigationView.qss", this, FluThemeUtils::getUtils()->getTheme());
    }

  protected:
    QVBoxLayout* m_layout;

    QVBoxLayout* m_topLayout;
    QWidget* m_topWrapWidget;
    FluVScrollView* m_scrollView;
    QVBoxLayout* m_bottomLayout;
    QWidget* m_bottomWrapWidget;
};
