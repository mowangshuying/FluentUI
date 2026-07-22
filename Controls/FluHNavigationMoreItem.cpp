#include "FluHNavigationMoreItem.h"
#include "FluHNavigationView.h"
#include "FluHNavigationFlyIconTextItem.h"

FluHNavigationMoreItem::FluHNavigationMoreItem(QWidget* parent /*= nullptr*/) : FluHNavigationItem(parent)
{
    m_mainLayout = new QVBoxLayout;
    m_mainLayout->setContentsMargins(0, 0, 0, 0);
    setLayout(m_mainLayout);

    m_iconButtonLayout = new QHBoxLayout;
    m_iconButtonLayout->setContentsMargins(0, 0, 0, 0);
    m_iconButtonLayout->setAlignment(Qt::AlignHCenter);

    m_iconButton = new QPushButton;
    m_iconButton->setFixedSize(36, 36);
    m_iconButton->setIconSize(QSize(24, 24));
    m_iconButton->setObjectName("iconBtn");

    m_iconButtonLayout->addWidget(m_iconButton);

    m_horizontalIndicatorWrap = new QWidget;
    m_horizontalIndicatorWrap->setObjectName("hIndicatorWrap");
    m_horizontalIndicatorWrap->setFixedHeight(4);

    m_horizontalIndicator = new QWidget;
    m_horizontalIndicator->setFixedHeight(4);
    m_horizontalIndicator->setFixedWidth(18);
    m_horizontalIndicator->setObjectName("hIndicator");

    m_horizontalIndicatorLayout = new QHBoxLayout;
    m_horizontalIndicatorLayout->setContentsMargins(0, 0, 0, 0);
    m_horizontalIndicatorLayout->setAlignment(Qt::AlignHCenter);
    m_horizontalIndicatorWrap->setLayout(m_horizontalIndicatorLayout);

    m_horizontalIndicatorLayout->addWidget(m_horizontalIndicator);

    m_mainLayout->addLayout(m_iconButtonLayout);
    m_mainLayout->addWidget(m_horizontalIndicatorWrap);

    // m_horizontalIndicatorWrap->hide();

    connect(m_iconButton, &QPushButton::clicked, this, [=]() { emit itemClicked(); });
    connect(this, &FluHNavigationMoreItem::itemClicked, this, [=]() { onItemClicked(); });

    onThemeChanged();
}

void FluHNavigationMoreItem::clearAllItemsSelectState()
{
    updateSelected(false);
}

void FluHNavigationMoreItem::updateAllItemsStyleSheet()
{
    style()->polish(this);
    m_iconButton->style()->polish(m_iconButton);
    m_horizontalIndicator->style()->polish(m_horizontalIndicator);
}

void FluHNavigationMoreItem::updateSelected(bool b)
{
    m_isSelected = b;
    setProperty("selected", b);
    m_iconButton->setProperty("selected", b);
    m_horizontalIndicator->setProperty("selected", b);
}

void FluHNavigationMoreItem::mouseReleaseEvent(QMouseEvent* event)
{
    emit itemClicked();
}

void FluHNavigationMoreItem::paintEvent(QPaintEvent* event)
{
    QStyleOption opt;
    opt.initFrom(this);
    QPainter painter(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
}

void FluHNavigationMoreItem::onItemClicked()
{
    // if (m_parentView == nullptr)
    //     return;

    auto navView = getParentView();
    if (navView == nullptr)
    {
        return;
    }

    // show flyout item;
    auto flyIconTextItem = new FluHNavigationFlyIconTextItem;
    flyIconTextItem->setNavView(navView);
    flyIconTextItem->setIconTextItems(navView->getHideItems());
    flyIconTextItem->show();

    QPoint gPoint = mapToGlobal(QPoint(width() - flyIconTextItem->width(), height()));
    flyIconTextItem->move(gPoint.x(), gPoint.y());

    // update indicator;
    navView->clearAllItemsSelectState();
    updateSelected(true);
    navView->updateAllItemsStyleSheet();
}

void FluHNavigationMoreItem::onThemeChanged()
{
    if (FluThemeUtils::isLightTheme())
    {
        m_iconButton->setIcon(FluIconUtils::getFluentIcon(FluAwesomeType::More, FluTheme::Light));
        // FluStyleSheetUtils::setQssByFileName("../StyleSheet/light/FluHNavigationMoreItem.qss", this);
    }
    else
    {
        m_iconButton->setIcon(FluIconUtils::getFluentIcon(FluAwesomeType::More, FluTheme::Dark));
        // FluStyleSheetUtils::setQssByFileName("../StyleSheet/dark/FluHNavigationMoreItem.qss", this);
    }
    FluStyleSheetUtils::setQssByFileName("FluHNavigationMoreItem.qss", this, FluThemeUtils::getUtils()->getTheme());
}
