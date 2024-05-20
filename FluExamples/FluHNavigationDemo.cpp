#include "FluHNavigationDemo.h"

#include <FramelessHelper/Core/framelessmanager.h>
#include <FramelessHelper/Widgets/framelesswidgetshelper.h>
#include <FramelessHelper/Widgets/standardsystembutton.h>
#include <FramelessHelper/Widgets/standardtitlebar.h>
#include "../FluUtils/FluUtils.h"
#include "../FluControls/FluHNavigationIconTextItem.h"
#include "../FluControls/FluHNavigationSearchItem.h"
#include "../FluControls/FluHNavigationSettingsItem.h"

#include <QLabel>
FluHNavigationDemo::FluHNavigationDemo(QWidget* parent /*= nullptr*/) : FluFrameLessWidget(parent)
{
    setWindowTitle("CppQt WinUI3 Demo Dev");
#ifndef _DEBUG
    setWindowTitle("CppQt WinUI3 Demo");
#endif
    setWindowIcon(QIcon("../res/Tiles/GalleryIcon.ico"));

    m_titleBar->chromePalette()->setTitleBarActiveBackgroundColor(Qt::transparent);
    m_titleBar->chromePalette()->setTitleBarInactiveBackgroundColor(Qt::transparent);
    m_titleBar->chromePalette()->setTitleBarActiveForegroundColor(Qt::black);
    m_titleBar->chromePalette()->setTitleBarInactiveForegroundColor(Qt::black);
    m_titleBar->setFixedHeight(48);

    // new
    m_vMainLayout->setAlignment(Qt::AlignTop);
    m_hNavView = new FluHNavigationView;
    m_vMainLayout->insertWidget(1, m_hNavView, 0, Qt::AlignTop);

    // auto label = new QLabel;
    // m_vMainLayout->addWidget(label, 1);
    auto item1 = new FluHNavigationIconTextItem(FluAwesomeType::Home, "Home");
    m_hNavView->addItemToMidLayout(item1);

    auto item2 = new FluHNavigationIconTextItem(FluAwesomeType::Design, "Design guidance");
    m_hNavView->addItemToMidLayout(item2);

    auto item3 = new FluHNavigationIconTextItem(FluAwesomeType::AllApps, "All samples");
    m_hNavView->addItemToMidLayout(item3);

    auto item4 = new FluHNavigationIconTextItem(FluAwesomeType::CheckboxComposite, "Basic input");
    m_hNavView->addItemToMidLayout(item4);

    auto item5 = new FluHNavigationIconTextItem(FluAwesomeType::TiltDown, "Connections");
    m_hNavView->addItemToMidLayout(item5);

    auto item6 = new FluHNavigationIconTextItem(FluAwesomeType::Calendar, "Date & Time");
    m_hNavView->addItemToMidLayout(item6);

    auto item7 = new FluHNavigationIconTextItem(FluAwesomeType::Comment, "Dialogs & flyouts");
    m_hNavView->addItemToMidLayout(item7);

    auto item8 = new FluHNavigationIconTextItem(FluAwesomeType::PreviewLink, "Layout");
    m_hNavView->addItemToMidLayout(item8);

    auto item9 = new FluHNavigationIconTextItem(FluAwesomeType::Calendar, "Mendia");
    m_hNavView->addItemToMidLayout(item9);

    auto item10 = new FluHNavigationIconTextItem(FluAwesomeType::Save, "Menu & toolbars");
    m_hNavView->addItemToMidLayout(item10);

    auto item11 = new FluHNavigationIconTextItem(FluAwesomeType::BookmarksMirrored, "Navigation");
    m_hNavView->addItemToMidLayout(item11);

    auto item12 = new FluHNavigationIconTextItem(FluAwesomeType::Sort, "Scrolling");
    m_hNavView->addItemToMidLayout(item12);

    auto item13 = new FluHNavigationIconTextItem(FluAwesomeType::Reminder, "Status & info");
    m_hNavView->addItemToMidLayout(item13);

    auto item14 = new FluHNavigationIconTextItem(FluAwesomeType::Font, "Text");
    m_hNavView->addItemToMidLayout(item14);

    auto searchItem = new FluHNavigationSearchItem;
    searchItem->setFixedWidth(220);
    m_hNavView->addItemToRightLayout(searchItem);

    auto settingsItem = new FluHNavigationSettingsItem(FluAwesomeType::Settings);
    m_hNavView->addItemToRightLayout(settingsItem);


    auto bodyWidget = new QWidget;
    bodyWidget->setObjectName("bodyWidget");
    m_contentLayout->addWidget(bodyWidget);

    FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluHNavigationDemo.qss", this);
    connect(FluThemeUtils::getUtils(), &FluThemeUtils::themeChanged, [=](FluTheme theme) { onThemeChanged(); });
    resize(800, 600);
}

void FluHNavigationDemo::onThemeChanged()
{
    if (FluThemeUtils::getUtils()->getTheme() == FluTheme::Light)
    {
        m_titleBar->chromePalette()->setTitleBarActiveBackgroundColor(Qt::transparent);
        m_titleBar->chromePalette()->setTitleBarInactiveBackgroundColor(Qt::transparent);
        m_titleBar->chromePalette()->setTitleBarActiveForegroundColor(Qt::black);
        m_titleBar->chromePalette()->setTitleBarInactiveForegroundColor(Qt::black);

        m_titleBar->minimizeButton()->setActiveForegroundColor(Qt::black);
        m_titleBar->closeButton()->setActiveForegroundColor(Qt::black);
        m_titleBar->maximizeButton()->setActiveForegroundColor(Qt::black);

        // m_titleBar->update();
        // m_titleBar->style()->polish(m_titleBar);
        m_titleBar->show();
        FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluHNavigationDemo.qss", this);
        // repaint();
        // QApplication::processEvents();
    }
    else
    {
        m_titleBar->chromePalette()->setTitleBarActiveBackgroundColor(Qt::transparent);
        m_titleBar->chromePalette()->setTitleBarInactiveBackgroundColor(Qt::transparent);
        m_titleBar->chromePalette()->setTitleBarActiveForegroundColor(Qt::white);
        m_titleBar->chromePalette()->setTitleBarInactiveForegroundColor(Qt::white);
        // m_titleBar->update();
        // m_titleBar->style()->polish(m_titleBar);

        m_titleBar->minimizeButton()->setActiveForegroundColor(Qt::white);
        m_titleBar->closeButton()->setActiveForegroundColor(Qt::white);
        m_titleBar->maximizeButton()->setActiveForegroundColor(Qt::white);

        m_titleBar->show();
        FluStyleSheetUitls::setQssByFileName("../StyleSheet/dark/FluHNavigationDemo.qss", this);
        // repaint();
        // QApplication::processEvents();
    }
}
