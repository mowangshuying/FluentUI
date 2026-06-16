#include "FluHNavigationMoreItem.h"
#include "FluHNavigationView.h"
#include "FluHNavigationFlyIconTextItem.h"

FluHNavigationMoreItem::FluHNavigationMoreItem(QWidget* parent /*= nullptr*/) : FluHNavigationItem(parent)
{
    m_vMainLayout = new QVBoxLayout;
    m_vMainLayout->setContentsMargins(0, 0, 0, 0);
    setLayout(m_vMainLayout);

    m_hIconBtnLayout = new QHBoxLayout;
    m_hIconBtnLayout->setContentsMargins(0, 0, 0, 0);
    m_hIconBtnLayout->setAlignment(Qt::AlignHCenter);

    m_iconBtn = new QPushButton;
    m_iconBtn->setFixedSize(36, 36);
    m_iconBtn->setIconSize(QSize(24, 24));
    m_iconBtn->setObjectName("iconBtn");

    m_hIconBtnLayout->addWidget(m_iconBtn);

    m_hIndicatorWrap = new QWidget;
    m_hIndicatorWrap->setObjectName("hIndicatorWrap");
    m_hIndicatorWrap->setFixedHeight(4);

    m_hIndicator = new QWidget;
    m_hIndicator->setFixedHeight(4);
    m_hIndicator->setFixedWidth(18);
    m_hIndicator->setObjectName("hIndicator");

    m_hIndicatorLayout = new QHBoxLayout;
    m_hIndicatorLayout->setContentsMargins(0, 0, 0, 0);
    m_hIndicatorLayout->setAlignment(Qt::AlignHCenter);
    m_hIndicatorWrap->setLayout(m_hIndicatorLayout);

    m_hIndicatorLayout->addWidget(m_hIndicator);

    m_vMainLayout->addLayout(m_hIconBtnLayout);
    m_vMainLayout->addWidget(m_hIndicatorWrap);

    // m_hIndicatorWrap->hide();

    connect(m_iconBtn, &QPushButton::clicked, this, [=]() { emit itemClicked(); });
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
    m_iconBtn->style()->polish(m_iconBtn);
    m_hIndicator->style()->polish(m_hIndicator);
}

void FluHNavigationMoreItem::updateSelected(bool b)
{
    m_bSelected = b;
    setProperty("selected", b);
    m_iconBtn->setProperty("selected", b);
    m_hIndicator->setProperty("selected", b);
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
        m_iconBtn->setIcon(FluIconUtils::getFluentIcon(FluAwesomeType::More, FluTheme::Light));
        // FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluHNavigationMoreItem.qss", this);
    }
    else
    {
        m_iconBtn->setIcon(FluIconUtils::getFluentIcon(FluAwesomeType::More, FluTheme::Dark));
        // FluStyleSheetUitls::setQssByFileName("../StyleSheet/dark/FluHNavigationMoreItem.qss", this);
    }
    FluStyleSheetUitls::setQssByFileName("FluHNavigationMoreItem.qss", this, FluThemeUtils::getUtils()->getTheme());
}
