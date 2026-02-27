#include "FluWindowKitWindow.h"

#include "FluWindowKitWidget.h"
#include <QWKWidgets/widgetwindowagent.h>

#include <QLabel>
#include "FluWindowkitButton.h"
#include "FluWindowKitTitleBar.h"
#include "../FluUtils/FluUtils.h"
#include "FluLabel.h"
#include <QWindow>

#include <QStyleOption>
#include "FluThemeButton.h"

FluWindowKitWindow::FluWindowKitWindow(QWidget* parent) : QMainWindow(parent)
{
    setWindowIcon(QIcon("../res/Tiles/GalleryIcon.ico"));
    setWindowTitle("windowkit window");
    resize(800, 600);

    auto agent = new QWK::WidgetWindowAgent(this);
    agent->setup(this);
    // agent->setWindowAttribute("dwm-blur", true);

    m_titleLabel = new FluLabel;
    m_titleLabel->setAlignment(Qt::AlignCenter);
    m_titleLabel->setObjectName("titleLabel");
    m_titleLabel->setText("WindowKit Widget.");

#ifndef Q_OS_MAC
    m_iconButton = new FluWindowkitButton;
    m_iconButton->setObjectName("iconButton");
    m_iconButton->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);

    m_pinButton = new FluWindowkitButton;
    m_pinButton->setCheckable(true);
    m_pinButton->setObjectName("pinButton");
    m_pinButton->setIconNormal(FluIconUtils::getFluentIcon(FluAwesomeType::Pin, FluThemeUtils::getUtils()->getTheme()));
    m_pinButton->setIconChecked(FluIconUtils::getFluentIcon(FluAwesomeType::PinFill, FluThemeUtils::getUtils()->getTheme()));
    m_pinButton->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);

    m_themeButton = new FluThemeButton;
    m_themeButton->setObjectName("themeButton");
    m_themeButton->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);

    m_minButton = new FluWindowkitButton;
    m_minButton->setObjectName("minButton");
    m_minButton->setProperty("systemButton", true);
    m_minButton->setIconNormal(FluIconUtils::getFluentIcon(FluAwesomeType::ChromeMinimize, FluThemeUtils::getUtils()->getTheme()));
    m_minButton->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);

    m_maxButton = new FluWindowkitButton;
    m_maxButton->setCheckable(true);
    m_maxButton->setObjectName("maxButton");
    m_maxButton->setProperty("systemButton", true);
    m_maxButton->setIconNormal(FluIconUtils::getFluentIcon(FluAwesomeType::ChromeMaximize, FluThemeUtils::getUtils()->getTheme()));
    m_maxButton->setIconChecked(FluIconUtils::getFluentIcon(FluAwesomeType::ChromeRestore, FluThemeUtils::getUtils()->getTheme()));
    m_maxButton->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);

    m_closeButton = new FluWindowkitButton;
    m_closeButton->setObjectName("closeButton");
    m_closeButton->setProperty("systemButton", true);
    m_closeButton->setIconNormal(FluIconUtils::getFluentIcon(FluAwesomeType::ChromeClose, FluThemeUtils::getUtils()->getTheme()));
    m_closeButton->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
#endif

    m_titleBar = new FluWindowKitTitleBar;
    m_titleBar->setFixedHeight(35);
#ifndef Q_OS_MAC
    m_titleBar->setIconButton(m_iconButton);
    m_titleBar->setThemeButton(m_themeButton);
    m_titleBar->setPinButton(m_pinButton);
    m_titleBar->setMinButton(m_minButton);
    m_titleBar->setMaxButton(m_maxButton);
    m_titleBar->setCloseButton(m_closeButton);
#endif
    m_titleBar->setTitleLabel(m_titleLabel);
    m_titleBar->setHostWidget(this);
    agent->setTitleBar(m_titleBar);

    //// contentLayout;
    //m_contentLayout = new QHBoxLayout;
    //m_contentLayout->setContentsMargins(0, 0, 0, 0);
    //m_contentLayout->setSpacing(0);

    //// mainLayout;
    //m_vMainLayout = new QVBoxLayout(this);
    //m_vMainLayout->setSpacing(0);
    //m_vMainLayout->setContentsMargins(0, 0, 0, 0);
    //m_vMainLayout->addWidget(m_titleBar, 0, Qt::AlignTop);
    //m_vMainLayout->addLayout(m_contentLayout, 1);
    //setLayout(m_vMainLayout);

#ifndef Q_OS_MAC
    agent->setHitTestVisible(m_themeButton, true);
    agent->setHitTestVisible(m_pinButton, true);
    agent->setSystemButton(QWK::WindowAgentBase::WindowIcon, m_iconButton);
    agent->setSystemButton(QWK::WindowAgentBase::Minimize, m_minButton);
    agent->setSystemButton(QWK::WindowAgentBase::Maximize, m_maxButton);
    agent->setSystemButton(QWK::WindowAgentBase::Close, m_closeButton);
#endif

    setMenuWidget(m_titleBar);

#ifndef Q_OS_MAC
    connect(m_titleBar, &FluWindowKitTitleBar::pinRequested, this, [=](bool pin) {
        // if (isHidden() || isMinimized() || isMaximized() || isFullScreen())
        // {
        //     return;
        // }

        // auto window = windowHandle();
        // window->setFlag(Qt::WindowStaysOnTopHint, pin);
        // setWindowFlag(Qt::WindowStaysOnTopHint, pin);
        // show();
        // m_pinButton->setChecked(pin);
    });

    connect(m_titleBar, &FluWindowKitTitleBar::minimizeRequested, this, &QWidget::showMinimized);
    connect(m_titleBar, &FluWindowKitTitleBar::maximizeRequested, this, [this](bool max) {
        if (max)
        {
            showMaximized();
        }
        else
        {
            showNormal();
        }

        emulateLeaveEvent(m_maxButton);
    });

    onThemeChanged();
    connect(m_titleBar, &FluWindowKitTitleBar::closeRequested, this, &QWidget::close);
    connect(FluThemeUtils::getUtils(), &FluThemeUtils::themeChanged, [=](FluTheme theme) { onThemeChanged(); });
#endif  // !Q_OS_MAC

#ifdef Q_OS_WIN
    // setAttribute(Qt::WA_TranslucentBackground);
    // agent->setWindowAttribute(QStringLiteral("acrylic-material"), true);
    // style()->polish(this);
#endif
    setAttribute(Qt::WA_ContentsMarginsRespectsSafeArea);
    // setWindowIcon(QIcon("../res/Tiles/GalleryIcon.ico"));
}

void FluWindowKitWindow::emulateLeaveEvent(QWidget* widget)
{
    Q_ASSERT(widget);
    if (!widget)
    {
        return;
    }
    QTimer::singleShot(0, widget, [widget]() {
#if (QT_VERSION >= QT_VERSION_CHECK(5, 14, 0))
        const QScreen* screen = widget->screen();
#else
	        const QScreen *screen = widget->windowHandle()->screen();
#endif
        const QPoint globalPos = QCursor::pos(screen);
        if (!QRect(widget->mapToGlobal(QPoint{0, 0}), widget->size()).contains(globalPos))
        {
            QCoreApplication::postEvent(widget, new QEvent(QEvent::Leave));
            if (widget->testAttribute(Qt::WA_Hover))
            {
                const QPoint localPos = widget->mapFromGlobal(globalPos);
                const QPoint scenePos = widget->window()->mapFromGlobal(globalPos);
                static constexpr const auto oldPos = QPoint{};
                const Qt::KeyboardModifiers modifiers = QGuiApplication::keyboardModifiers();
#if (QT_VERSION >= QT_VERSION_CHECK(6, 4, 0))
                const auto event = new QHoverEvent(QEvent::HoverLeave, scenePos, globalPos, oldPos, modifiers);
                Q_UNUSED(localPos);
#elif (QT_VERSION >= QT_VERSION_CHECK(6, 3, 0))
	                const auto event =  new QHoverEvent(QEvent::HoverLeave, localPos, globalPos, oldPos, modifiers);
	                Q_UNUSED(scenePos);
#else
	                const auto event =  new QHoverEvent(QEvent::HoverLeave, localPos, oldPos, modifiers);
	                Q_UNUSED(scenePos);
#endif
                QCoreApplication::postEvent(widget, event);
            }
        }
    });
}

void FluWindowKitWindow::onThemeChanged()
{
    m_pinButton->setIconNormal(FluIconUtils::getFluentIcon(FluAwesomeType::Pin, FluThemeUtils::getUtils()->getTheme()));
    m_pinButton->setIconChecked(FluIconUtils::getFluentIcon(FluAwesomeType::PinFill, FluThemeUtils::getUtils()->getTheme()));
    m_minButton->setIconNormal(FluIconUtils::getFluentIcon(FluAwesomeType::ChromeMinimize, FluThemeUtils::getUtils()->getTheme()));
    m_maxButton->setIconNormal(FluIconUtils::getFluentIcon(FluAwesomeType::ChromeMaximize, FluThemeUtils::getUtils()->getTheme()));
    m_maxButton->setIconChecked(FluIconUtils::getFluentIcon(FluAwesomeType::ChromeRestore, FluThemeUtils::getUtils()->getTheme()));
    m_closeButton->setIconNormal(FluIconUtils::getFluentIcon(FluAwesomeType::ChromeClose, FluThemeUtils::getUtils()->getTheme()));
    FluStyleSheetUitls::setQssByFileName("FluWindowKitWindow.qss", this, FluThemeUtils::getUtils()->getTheme());
}
