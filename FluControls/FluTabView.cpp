#include "FluTabView.h"

FluTabView::FluTabView(QWidget* parent /*= nullptr*/) : FluWidget(parent)
{
    m_vMainLayout = new QVBoxLayout;
    m_vMainLayout->setContentsMargins(1, 1, 1, 1);
    setLayout(m_vMainLayout);

    m_vMainLayout->setSpacing(0);

    m_vMainLayout->setAlignment(Qt::AlignTop);

    m_tabBar = new FluTabBar;
    m_vMainLayout->addWidget(m_tabBar);

    m_sWidgt = new QWidget;
    m_sWidgt->setObjectName("sWidget");
    m_vMainLayout->addWidget(m_sWidgt, 1);

    m_sLayout = new FluStackedLayout;
    m_sLayout->setContentsMargins(10, 0, 10, 10);
    m_sWidgt->setLayout(m_sLayout);

    connect(m_tabBar, &FluTabBar::addTabBtnClicked, [=]() { emit addTabBtnClicked(); });
    FluStyleSheetUitls::setQssByFileName("FluTabView.qss", this, FluThemeUtils::getUtils()->getTheme());
}

void FluTabView::addTab(QString tabString, QWidget* tabWidget)
{
    auto tabBarItem = new FluTabBarItem;
    tabBarItem->setText(tabString);
    m_tabBar->addBarItem(tabBarItem);

    m_sLayout->addWidget(tabString, tabWidget);
    connect(tabBarItem, &FluTabBarItem::clicked, [=]() { m_sLayout->setCurrentWidget(tabString); });
    connect(tabBarItem, &FluTabBarItem::clickedCloseBtn, [=](FluTabBarItem* item) {
        m_tabBar->removeTabBarItem(item);
        m_sLayout->removeWidget(tabString, tabWidget);
    });
}

bool FluTabView::eventFilter(QObject* watched, QEvent* event)
{
    return QWidget::eventFilter(watched, event);
}

void FluTabView::paintEvent(QPaintEvent* event)
{
    QStyleOption opt;
    opt.initFrom(this);
    QPainter painter(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
}
