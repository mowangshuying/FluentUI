#include "FluFrameLessDemo.h"

#include <QtCore/qdatetime.h>
#if (QT_VERSION >= QT_VERSION_CHECK(6, 0, 0))
#include <QtGui/qshortcut.h>
#else
#include <QtWidgets/qshortcut.h>
#endif
#include <FramelessHelper/Core/framelessmanager.h>
#include <FramelessHelper/Widgets/framelesswidgetshelper.h>
#include <FramelessHelper/Widgets/standardsystembutton.h>
#include <FramelessHelper/Widgets/standardtitlebar.h>
#include <QtWidgets/qboxlayout.h>
#include <QtWidgets/qfileiconprovider.h>
#include <QtWidgets/qlabel.h>

#include "../FluControls/FluPushButton.h"

FluFrameLessDemo::FluFrameLessDemo(QWidget *parent /*= nullptr*/) : FluFrameLessWidget(parent)
{
    setWindowTitle("Cpp WinUI3 Demo Dev");
#ifndef _DEBUG
    setWindowTitle("Cpp WinUI3 Demo");
#endif
    setWindowIcon(QIcon(":/res/Tiles/GalleryIcon.ico"));
    resize(800, 600);

    m_titleBar->chromePalette()->setTitleBarActiveBackgroundColor(Qt::transparent);
    // m_titleBar->chromePalette()->setTitleBarActiveBackgroundColor(Qt::yellow);

    m_titleBar->chromePalette()->setTitleBarInactiveBackgroundColor(Qt::transparent);
    m_titleBar->chromePalette()->setTitleBarActiveForegroundColor(Qt::black);
    m_titleBar->chromePalette()->setTitleBarInactiveForegroundColor(Qt::black);
    m_titleBar->setFixedHeight(48);

    // m_hThemeSwitchLayout = new QHBoxLayout;
    // m_hThemeSwitchLayout->setAlignment(Qt::AlignTop);
    // m_themeSwitch = new FluToggleSwitch;
    // m_themeSwitch->setEnabled(true);
    // m_themeSwitch->setText("");
    // m_themeSwitch->setEmptyText(true);
    //
    // m_themeSwitch->setMouseTracking(true);
    // m_hThemeSwitchLayout->setContentsMargins(0, 5, 0, 0);
    // m_hThemeSwitchLayout->addWidget(m_themeSwitch);

    // auto tmpPushBtn = new FluPushButton;
    // tmpPushBtn->setFixedSize(100, 30);
    // tmpPushBtn->setText("This Is A PushButton.");
    // m_hThemeSwitchLayout->addWidget(tmpPushBtn);

    // auto hTitleBarLayout = (QHBoxLayout *)m_titleBar->layout();
    // hTitleBarLayout->insertLayout(1, m_hThemeSwitchLayout, 0);
}
