#pragma once

#include "FluWidget.h"
#include "FluTabBarContent.h"
#include <QHBoxLayout>
#include <QStyleOption>
#include <QPainter>
#include <QPushButton>
#include <QThread>

class FluTabBar : public FluWidget
{
    Q_OBJECT
  public:
    FluTabBar(QWidget* parent = nullptr) : FluWidget(parent)
    {
        m_hMainLayout = new QHBoxLayout;
        setLayout(m_hMainLayout);
        m_hMainLayout->setAlignment(Qt::AlignLeft);

        m_hMainLayout->setSpacing(0);
        m_hMainLayout->setContentsMargins(10, 0, 40, 0);
        m_hMainLayout->setSizeConstraint(QHBoxLayout::SetMinAndMaxSize);

        m_tabBarContent = new FluTabBarContent;
        m_tabBarContent->resize(0, height());
        m_hMainLayout->addWidget(m_tabBarContent);

        m_hMainLayout->addSpacing(8);

        m_addTabBtn = new QPushButton(this);
        m_addTabBtn->setFixedSize(30, 30);
        m_addTabBtn->setIconSize(QSize(20, 20));
        m_addTabBtn->setIcon(FluIconUtils::getFluentIcon(FluAwesomeType::Add));
        m_addTabBtn->setObjectName("addTabBtn");

        connect(m_addTabBtn, &QPushButton::clicked, [=]() { emit addTabBtnClicked(); });

        FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluTabBar.qss", this);
    }

    std::vector<FluTabBarItem*> getTabBarItems()
    {
        return m_tabBarContent->getTabBarItems();
    }

    void addBarItem(FluTabBarItem* item)
    {
        m_tabBarContent->addBarItem(item);
        connect(item, &FluTabBarItem::sizeChanged, [=]() { adjustAddTabBtnPosition(); });
    }

    void removeTabBarItem(FluTabBarItem* item)
    {
        m_tabBarContent->removeTabBarItem(item);
    }

    void resizeEvent(QResizeEvent* event)
    {
        QWidget::resizeEvent(event);
        adjustAddTabBtnPosition();
    }

    void paintEvent(QPaintEvent* event)
    {
        QStyleOption opt;
        opt.initFrom(this);
        QPainter painter(this);
        style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);

        adjustAddTabBtnPosition();
    }

    void adjustAddTabBtnPosition()
    {
        std::vector<FluTabBarItem*> items = getTabBarItems();
        if (items.size() == 0)
        {
            int nX = 10;
            int nY = 5;
            m_addTabBtn->move(nX, nY);
            return;
        }
        else
        {
            auto tailItem = items[items.size() - 1];

            int nTmp = 0;
            for (int i = 0; i < items.size(); i++)
            {
                nTmp += items[i]->width();
            }

            int nX = nTmp + 20;
            int nY = 5;

            if (nX + 40 > width())
            {
                nX = width() - 40;
            }
            m_addTabBtn->move(nX, nY);
        }
    }

  signals:
    void addTabBtnClicked();

  protected:
    QHBoxLayout* m_hMainLayout;
    FluTabBarContent* m_tabBarContent;
    QPushButton* m_addTabBtn;
};
