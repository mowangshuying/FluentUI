#include "FluTabBar.h"
#include <QPropertyAnimation>
#include <QEasingCurve>

FluTabBar::FluTabBar(QWidget* parent /*= nullptr*/) : FluWidget(parent)
{
    m_mainLayout = new QHBoxLayout;
    setLayout(m_mainLayout);
    m_mainLayout->setAlignment(Qt::AlignLeft);

    m_mainLayout->setSpacing(0);
    m_mainLayout->setContentsMargins(10, 0, 40, 0);
    m_mainLayout->setSizeConstraint(QHBoxLayout::SetMinAndMaxSize);

    m_tabBarContent = new FluTabBarContent;
    m_tabBarContent->resize(0, height());
    m_mainLayout->addWidget(m_tabBarContent);

    m_mainLayout->addSpacing(0);

    m_addTabButton = new QPushButton(this);
    m_addTabButton->setFixedSize(32, 24);
    m_addTabButton->setIconSize(QSize(12, 12));
    m_addTabButton->setIcon(FluIconUtils::getFluentIcon(FluAwesomeType::Add, FluThemeUtils::getUtils()->getTheme()));
    m_addTabButton->setObjectName("addTabBtn");

    onThemeChanged();
    connect(m_addTabButton, &QPushButton::clicked, [=]() { emit addTabButtonClicked(); });
}

std::vector<FluTabBarItem*> FluTabBar::getTabBarItems()
{
    return m_tabBarContent->getTabBarItems();
}

QColor FluTabBar::getSelectedTabColor() const
{
    return m_tabBarContent->getTabSelectedColor();
}

void FluTabBar::addBarItem(FluTabBarItem* item)
{
    m_tabBarContent->addBarItem(item);
    adjustAddTabButtonPosition();
    connect(item, &FluTabBarItem::sizeChanged, [=]() { adjustAddTabButtonPosition(); });
    connect(item, &FluTabBarItem::clickedCloseButton, [this, item]() { removeTabBarItem(item); });
    animateItemIn(item);
}

void FluTabBar::removeTabBarItem(FluTabBarItem* item)
{
    if (m_animatingItem == item)
        return;
    m_animatingItem = item;
    auto anim = new QPropertyAnimation(item, "tabWidth", this);
    anim->setDuration(200);
    anim->setStartValue(item->width());
    anim->setEndValue(1);
    anim->setEasingCurve(QEasingCurve::OutCubic);
    connect(anim, &QPropertyAnimation::finished, this, [this, item, anim]() {
        m_animatingItem = nullptr;
        m_tabBarContent->removeTabBarItem(item);
        adjustAddTabButtonPosition();
        anim->deleteLater();
    });
    anim->start();
}

void FluTabBar::animateItemIn(FluTabBarItem* item)
{
    int target = item->getWidgetWidth();
    m_animatingItem = item;
    item->setFixedWidth(1);
    auto anim = new QPropertyAnimation(item, "tabWidth", this);
    anim->setDuration(200);
    anim->setStartValue(1);
    anim->setEndValue(target);
    anim->setEasingCurve(QEasingCurve::OutCubic);
    connect(anim, &QPropertyAnimation::finished, this, [this, item, anim]() {
        m_animatingItem = nullptr;
        item->adjustWidgetSize();
        adjustAddTabButtonPosition();
        anim->deleteLater();
    });
    anim->start();
}

void FluTabBar::resizeEvent(QResizeEvent* event)
{
    QWidget::resizeEvent(event);
    adjustAddTabButtonPosition();
}

void FluTabBar::paintEvent(QPaintEvent* event)
{
    QStyleOption opt;
    opt.initFrom(this);
    QPainter painter(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
    // adjustAddTabButtonPosition();
}

void FluTabBar::adjustAddTabButtonPosition()
{
    std::vector<FluTabBarItem*> items = getTabBarItems();
    if (items.size() == 0)
    {
        int x = 10;
        int y = 15;
        m_addTabButton->move(x, y);
        return;
    }
    else
    {
        auto tailItem = items[items.size() - 1];

        int tmp = 0;
        for (int i = 0; i < items.size(); i++)
        {
            // items[i]->show();
            tmp += items[i]->getWidgetWidth();
        }

        int x = tmp + 10;
        int y = 15;

        if (x + 40 > width())
        {
            x = width() - 40;
        }

        // total width
        int totalWidth = 0;
        std::vector<int> totalWidths;
        for (int i = 0; i < items.size(); i++)
        {
            totalWidths.push_back(items[i]->getWidgetWidth());
            totalWidth += items[i]->getWidgetWidth();
        }

        if (totalWidth > (width() - 50))
        {
            float fScale = (float)(width() - 50) / (float)totalWidth;
            for (int i = 0; i < items.size(); i++)
            {
                if (items[i] == m_animatingItem)
                    continue;
                items[i]->setFixedWidth((int)(fScale * items[i]->getWidgetWidth()));
                // x += totalWidths[i] * fScale;
            }
        }
        else
        {
            for (int i = 0; i < items.size(); i++)
            {
                if (items[i] == m_animatingItem)
                    continue;
                items[i]->setFixedWidth(items[i]->getWidgetWidth());
            }
        }

        m_addTabButton->move(x, y);
    }
}

void FluTabBar::onThemeChanged()
{
    FluStyleSheetUtils::setQssByFileName("FluTabBar.qss", this, FluThemeUtils::getUtils()->getTheme());
    m_addTabButton->setIcon(FluIconUtils::getFluentIcon(FluAwesomeType::Add, FluThemeUtils::getUtils()->getTheme()));
}
