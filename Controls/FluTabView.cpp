#include "FluTabView.h"

FluTabView::FluTabView(QWidget* parent /*= nullptr*/) : FluWidget(parent)
{
    m_mainLayout = new QVBoxLayout;
    m_mainLayout->setContentsMargins(1, 1, 1, 1);
    setLayout(m_mainLayout);

    m_mainLayout->setSpacing(0);

    m_mainLayout->setAlignment(Qt::AlignTop);

    m_tabBar = new FluTabBar;
    m_mainLayout->addWidget(m_tabBar);

    m_widgt = new QWidget;
    m_widgt->setObjectName("sWidget");
    m_mainLayout->addWidget(m_widgt, 1);

    m_layout = new FluStackedLayout;
    m_layout->setContentsMargins(10, 0, 10, 10);
    m_widgt->setLayout(m_layout);

    connect(m_tabBar, &FluTabBar::addTabButtonClicked, [=]() { emit addTabButtonClicked(); });
    // FluStyleSheetUtils::setQssByFileName("FluTabView.qss", this, FluThemeUtils::getUtils()->getTheme());
    onThemeChanged();
}

void FluTabView::addTab(QString tabString, QWidget* tabWidget)
{
    auto tabBarItem = new FluTabBarItem;
    tabBarItem->setText(tabString);
    m_tabBar->addBarItem(tabBarItem);

    m_layout->addWidget(tabString, tabWidget);
    connect(tabBarItem, &FluTabBarItem::clicked, [=]() { m_layout->setCurrentWidget(tabString); });
    connect(tabBarItem, &FluTabBarItem::clickedCloseButton, [=](FluTabBarItem* item) {
        m_tabBar->removeTabBarItem(item);
        m_layout->removeWidget(tabString, tabWidget);
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
