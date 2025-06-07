#include "FluMSWindow.h"
#include "FluMSNavigationItem.h"

FluMSWindow::FluMSWindow(QWidget* parent /*= nullptr*/) : FluFrameLessWidget(parent)
{
    setWindowTitle("CppQt MS Window Dev");
#ifndef _DEBUG
    setWindowTitle("CppQt MS Window");
#endif
    resize(800, 600);

    m_titleBar->chromePalette()->setTitleBarActiveBackgroundColor(Qt::transparent);
    m_titleBar->chromePalette()->setTitleBarInactiveBackgroundColor(Qt::transparent);
    m_titleBar->chromePalette()->setTitleBarActiveForegroundColor(Qt::black);
    m_titleBar->chromePalette()->setTitleBarInactiveForegroundColor(Qt::black);
    m_titleBar->setFixedHeight(36);

    m_navView = new FluMSNavigationView(this);
    m_sLayout = new FluStackedLayout;

    m_contentLayout->addWidget(m_navView);
    m_contentLayout->addLayout(m_sLayout, 1);

    onThemeChanged();
    connect(FluThemeUtils::getUtils(), &FluThemeUtils::themeChanged, this, [=]() { onThemeChanged(); });
}

void FluMSWindow::addWidget(FluAwesomeType awesomeType, QString text, QString key, QWidget* page, FluMSNavigationItemPosition position)
{
    if (page == nullptr)
        return;

    if (key.isEmpty())
        return;

    auto navItem = new FluMSNavigationItem(awesomeType, text, key, m_navView);
    m_navView->addItem(navItem, position);
    m_sLayout->addWidget(key, page);
    connect(navItem, &FluMSNavigationItem::clicked, this, [=]() { m_sLayout->setCurrentWidget(key); });
}

void FluMSWindow::onThemeChanged()
{
    if (FluThemeUtils::isLightTheme())
    {
        m_titleBar->chromePalette()->setTitleBarActiveBackgroundColor(Qt::transparent);
        m_titleBar->chromePalette()->setTitleBarInactiveBackgroundColor(Qt::transparent);
        m_titleBar->chromePalette()->setTitleBarActiveForegroundColor(Qt::black);
        m_titleBar->chromePalette()->setTitleBarInactiveForegroundColor(Qt::black);
#ifndef Q_OS_MACOS
        m_titleBar->minimizeButton()->setActiveForegroundColor(Qt::black);
        m_titleBar->closeButton()->setActiveForegroundColor(Qt::black);
        m_titleBar->maximizeButton()->setActiveForegroundColor(Qt::black);
#endif
        m_titleBar->show();
        // FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluMSWindow.qss", this);
    }
    else
    {
        m_titleBar->chromePalette()->setTitleBarActiveBackgroundColor(Qt::transparent);
        m_titleBar->chromePalette()->setTitleBarInactiveBackgroundColor(Qt::transparent);
        m_titleBar->chromePalette()->setTitleBarActiveForegroundColor(Qt::white);
        m_titleBar->chromePalette()->setTitleBarInactiveForegroundColor(Qt::white);
#ifndef Q_OS_MACOS
        m_titleBar->minimizeButton()->setActiveForegroundColor(Qt::white);
        m_titleBar->closeButton()->setActiveForegroundColor(Qt::white);
        m_titleBar->maximizeButton()->setActiveForegroundColor(Qt::white);
#endif
        m_titleBar->show();
        // FluStyleSheetUitls::setQssByFileName("../StyleSheet/dark/FluMSWindow.qss", this);
    }

    FluStyleSheetUitls::setQssByFileName("FluMSWindow.qss", this, FluThemeUtils::getUtils()->getTheme());
}
