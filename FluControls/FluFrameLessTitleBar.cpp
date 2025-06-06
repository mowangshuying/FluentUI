#include "FluFrameLessTitleBar.h"
#include <QTimer>
#include <FramelessHelper/Core/Utils>
#include <FramelessHelper/Widgets/framelesswidgetshelper.h>


using namespace wangwenx190::FramelessHelper::Global;
using namespace wangwenx190::FramelessHelper;

 FluFrameLessTitleBar::FluFrameLessTitleBar(QWidget* parent /*= nullptr*/) : QWidget(parent)
{
    m_titleBarLayout = new QHBoxLayout(this);
    m_vSystemButtonsOuterLayout = new QVBoxLayout(this);
    m_hSystemButtonsInnerLayout = new QHBoxLayout(this);
#ifndef Q_OS_MACOS
    m_minimizeButton = new QPushButton;
    m_maximizeButton = new QPushButton;
    m_closeButton = new QPushButton;
#endif
}

QRect FluFrameLessTitleBar::windowIconRect() const
{
    if (!windowIconVisible_real())
    {
        return {};
    }
    const QSize size = windowIconSize();
#ifdef Q_OS_MACOS
    const auto x = [this, q, &size]() -> int {
        if (labelAlignment & Qt::AlignLeft)
        {
            return (kMacOSChromeButtonAreaWidth + kDefaultTitleBarContentsMargin);
        }
        const int titleBarWidth = q->width();
        const int labelWidth = titleLabelSize().width;
        if (labelAlignment & Qt::AlignRight)
        {
            // We need two spacer here, one is on the right edge of the title bar,
            // the other one is between the window icon and the window label.
            return (titleBarWidth - kDefaultTitleBarContentsMargin - labelWidth - kDefaultTitleBarContentsMargin - size.width());
        }
        if (labelAlignment & Qt::AlignHCenter)
        {
            const int centeredX = std::round(qreal(titleBarWidth - labelWidth) / qreal(2));
            return (centeredX - kDefaultTitleBarContentsMargin - size.width());
        }
        WARNING << "The alignment for the title label is not set!";
        return 0;
    }();
#else   // !Q_OS_MACOS
    const int x = kDefaultTitleBarContentsMargin;
#endif  // Q_OS_MACOS
    const int y = std::round(qreal(height() - size.height()) / qreal(2));
    return {QPoint(x, y), size};
}

bool FluFrameLessTitleBar::windowIconVisible_real() const
{
    return m_bWindowIconVisible && !windowIcon().isNull();
}

bool FluFrameLessTitleBar::isInTitleBarIconArea(const QPoint& pos) const
{
    if (!windowIconVisible_real())
    {
        return false;
    }
    return windowIconRect().contains(pos);
}

QFont FluFrameLessTitleBar::defaultFont() const
{
    QFont tFont = font();
    tFont.setPointSize(kDefaultTitleBarFontPointSize);
    return tFont;
}

FluFrameLessTitleBar::FontMetrics FluFrameLessTitleBar::titleLabelSize() const
{
    const QString text = windowTitle();
    if (text.isEmpty())
    {
        return {};
    }
    const QFont font = m_titleFont.value_or(defaultFont());
    const QFontMetrics fontMetrics(font);
    const int textWidth = Utils::horizontalAdvance(fontMetrics, text);
    return {/* .width */ std::min(textWidth, titleLabelMaxWidth()),
            /* .height */ fontMetrics.height(),
            /* .ascent */ fontMetrics.ascent()};
}

int FluFrameLessTitleBar::titleLabelMaxWidth() const
{
#ifndef Q_OS_MACOS
    const int chromeButtonAreaWidth = (m_closeButton->x() + m_closeButton->width() - m_minimizeButton->x());
#else
    static constexpr const int chromeButtonAreaWidth = 70;
#endif
    //Q_Q(const StandardTitleBar);
    int textMaxWidth = width();
    if ((m_labelAlignment & Qt::AlignLeft) || (m_labelAlignment & Qt::AlignRight))
    {
        textMaxWidth -= (windowIconRect().width() + chromeButtonAreaWidth + (kDefaultTitleBarContentsMargin * 2));
    }
    else if (m_labelAlignment & Qt::AlignHCenter)
    {
        textMaxWidth -= ((chromeButtonAreaWidth + kDefaultTitleBarContentsMargin) * 2);
    }
    else
    {
        textMaxWidth = std::round(qreal(textMaxWidth) * qreal(0.8));
    }
    return std::max(textMaxWidth, 0);
}

void FluFrameLessTitleBar::updateMaximizeButton()
{
#if !defined(Q_OS_MACOS)
    //const bool max = window->isMaximized();
    //m_maximizeButton->setButtonType(max ? SystemButtonType::Restore : SystemButtonType::Maximize);
    //m_maximizeButton->setToolTip(max ? tr("Restore") : tr("Maximize"));
#endif
}

void FluFrameLessTitleBar::updateTitleBarColor()
{
    update();
}

void FluFrameLessTitleBar::updateChromeButtonColor()
{
//#if (!defined(Q_OS_MACOS) && FRAMELESSHELPER_CONFIG(system_button))
//    const bool active = window->isActiveWindow();
//    const QColor activeForeground = chromePalette->titleBarActiveForegroundColor();
//    const QColor inactiveForeground = chromePalette->titleBarInactiveForegroundColor();
//    const QColor normal = chromePalette->chromeButtonNormalColor();
//    const QColor hover = chromePalette->chromeButtonHoverColor();
//    const QColor press = chromePalette->chromeButtonPressColor();
//    minimizeButton->setActiveForegroundColor(activeForeground);
//    minimizeButton->setInactiveForegroundColor(inactiveForeground);
//    minimizeButton->setNormalColor(normal);
//    minimizeButton->setHoverColor(hover);
//    minimizeButton->setPressColor(press);
//    minimizeButton->setActive(active);
//    maximizeButton->setActiveForegroundColor(activeForeground);
//    maximizeButton->setInactiveForegroundColor(inactiveForeground);
//    maximizeButton->setNormalColor(normal);
//    maximizeButton->setHoverColor(hover);
//    maximizeButton->setPressColor(press);
//    maximizeButton->setActive(active);
//    closeButton->setActiveForegroundColor(activeForeground);
//    closeButton->setInactiveForegroundColor(inactiveForeground);
//    closeButton->setNormalColor(chromePalette->closeButtonNormalColor());
//    closeButton->setHoverColor(chromePalette->closeButtonHoverColor());
//    closeButton->setPressColor(chromePalette->closeButtonPressColor());
//    closeButton->setActive(active);
//#endif
}

void FluFrameLessTitleBar::retranslateUi()
{
//#if defined(Q_OS_LINUX))
//    minimizeButton->setToolTip(tr("Minimize"));
//    maximizeButton->setToolTip(window->isMaximized() ? tr("Restore") : tr("Maximize"));
//    closeButton->setToolTip(tr("Close"));
//#endif
}

bool FluFrameLessTitleBar::mouseEventHandler(QMouseEvent* event)
{
#ifdef Q_OS_MACOS
    Q_UNUSED(event);
    return false;
#else  // !Q_OS_MACOS
    Q_ASSERT(event);
    if (!event)
    {
        return false;
    }
    //Q_Q(const StandardTitleBar);
    const Qt::MouseButton button = event->button();
#if (QT_VERSION >= QT_VERSION_CHECK(6, 0, 0))
    const QPoint scenePos = event->scenePosition().toPoint();
#else   // (QT_VERSION < QT_VERSION_CHECK(6, 0, 0))
    const QPoint scenePos = event->windowPos().toPoint();
#endif  // (QT_VERSION >= QT_VERSION_CHECK(6, 0, 0))
    const bool interestArea = isInTitleBarIconArea(scenePos);
    switch (event->type())
    {
        case QEvent::MouseButtonRelease:
            // We need a valid top level widget here.
            if (interestArea)
            {
                // Sadly the mouse release events are always triggered before the
                // mouse double click events, and if we intercept the mouse release
                // events here, we'll never get the double click events afterwards,
                // so we have to wait for a little bit to make sure the double
                // click events are handled first, before we actually handle the
                // mouse release events here.
                // We need to wait long enough because the time interval between these
                // events is really really short, if the delay time is not long enough,
                // we still can't trigger the double click event due to we have handled
                // the mouse release events here already. But we also can't wait too
                // long, otherwise the system menu will show up too late, which is not
                // a good user experience. In my experiments, I found that 150ms is
                // the minimum value we can use here.
                // We need a copy of the "scenePos" variable here, otherwise it will
                // soon fall out of scope when the lambda function actually runs.
                QTimer::singleShot(150, this, [this, button, scenePos]() {
                    // The close event is already triggered, don't try to show the
                    // system menu anymore, otherwise it will prevent our window
                    // from closing.
                    if (m_closeTriggered)
                    {
                        return;
                    }
                    // Please refer to the comments in StandardTitleBarPrivate::setWindowIconVisible().
                    FramelessWidgetsHelper::get(this)->showSystemMenu([button, this, &scenePos]() -> QPoint {
                        QPoint pos = scenePos;
                        if (button == Qt::LeftButton)
                        {
                            pos = {0, height()};
                        }
                        return mapToGlobal(pos);
                    }());
                });
                // Don't eat this event, we have not handled it yet.
            }
            break;
        case QEvent::MouseButtonDblClick:
            // We need a valid top level widget here.
            if ((button == Qt::LeftButton) && interestArea)
            {
                m_closeTriggered = true;
                close();
                
                // Eat this event, we have handled it here.
                event->accept();
                return true;
            }
            break;
        default:
            break;
    }
    return false;
#endif  // Q_OS_MACOS
}

bool FluFrameLessTitleBar::eventFilter(QObject* object, QEvent* event)
{
    Q_ASSERT(object);
    Q_ASSERT(event);

    if (!object || !event)
    {
        return false;
    }

    if (!object->isWidgetType())
    {
        return QWidget::eventFilter(object, event);
    }


    switch (event->type())
    {
        case QEvent::WindowStateChange:
            updateMaximizeButton();
            break;
        case QEvent::ActivationChange:
        {
            updateTitleBarColor();
            updateChromeButtonColor();
        }
        break;
        case QEvent::LanguageChange:
            retranslateUi();
            break;
        default:
            break;
    }
    return QObject::eventFilter(object, event);
}

Qt::Alignment FluFrameLessTitleBar::titleLabelAlignment() const
{
    return m_labelAlignment;
}

void FluFrameLessTitleBar::setTitleLabelAlignment(const Qt::Alignment value)
{
    m_labelAlignment = value;
    Q_EMIT titleLabelVisibleChanged();
}

QPushButton* FluFrameLessTitleBar::minimizeButton() const
{
    return m_minimizeButton;
}

QPushButton* FluFrameLessTitleBar::maximizeButton() const
{
    return m_maximizeButton;
}

QPushButton* FluFrameLessTitleBar::closeButton() const
{
    return m_closeButton;
}

bool FluFrameLessTitleBar::isExtended() const
{
    return m_bExtended;
}

void FluFrameLessTitleBar::setExtended(const bool value)
{
    m_bExtended = value;
    setFixedHeight(m_bExtended ? kDefaultExtendedTitleBarHeight : kDefaultTitleBarHeight);
    Q_EMIT extendedChanged();
}

bool FluFrameLessTitleBar::isHideWhenClose() const
{
    return m_bHideWhenClose;
}

void FluFrameLessTitleBar::setHideWhenClose(const bool value)
{
    if (m_bHideWhenClose == value)
        return;

    m_bHideWhenClose = value;
    Q_EMIT extendedChanged();
}

//ChromePalette* FluFrameLessTitleBar::chromePalette() const
//{
//}

bool FluFrameLessTitleBar::titleLabelVisible() const
{
    return m_bTitleLabelVisible;
}

void FluFrameLessTitleBar::setTitleLabelVisible(const bool value)
{
    if (m_bTitleLabelVisible == value)
    {
        return;
    }

    m_bTitleLabelVisible = value;
    update();
    Q_EMIT titleLabelVisibleChanged();
}

Q_NODISCARD QSize FluFrameLessTitleBar::windowIconSize() const
{
    return m_windowIconSize.value_or(kDefaultWindowIconSize);
}

void FluFrameLessTitleBar::setWindowIconSize(const QSize& value)
{
    if (value.isEmpty())
    {
        return;
    }
    if (windowIconSize() == value)
    {
        return;
    }

    m_windowIconSize = value;
    update();
    Q_EMIT windowIconSizeChanged();
}

Q_NODISCARD bool FluFrameLessTitleBar::windowIconVisible() const
{
    return m_bWindowIconVisible;
}

void FluFrameLessTitleBar::setWindowIconVisible(const bool value)
{
    if (m_bWindowIconVisible == value)
    {
        return;
    }
    m_bWindowIconVisible = value;
    update();
    Q_EMIT windowIconVisibleChanged();
#ifndef Q_OS_MACOS
    // Ideally we should use FramelessWidgetsHelper::get(this) everywhere, but sadly when
    // we call it here, it may be too early that FramelessWidgetsHelper has not attached
    // to the top level widget yet, and thus it will trigger an assert error (the assert
    // should not be suppressed, because it usually indicates there's something really
    // wrong). So here we have to use the top level widget directly, as a special case.
    // NOTE: In your own code, you should always use FramelessWidgetsHelper::get(this)
    // if possible.
    FramelessWidgetsHelper::get(this)->setHitTestVisible(windowIconRect(), windowIconVisible_real());
#endif  // Q_OS_MACOS
}

Q_NODISCARD QFont FluFrameLessTitleBar::titleFont() const
{
    return m_titleFont.value_or(QFont());
}

void FluFrameLessTitleBar::setTitleFont(const QFont& value)
{
    if (titleFont() == value)
    {
        return;
    }

    m_titleFont = value;
    update();
    Q_EMIT titleFontChanged();
}

void FluFrameLessTitleBar::paintEvent(QPaintEvent* event)
{
//    Q_ASSERT(event);
//    if (!event)
//    {
//        return;
//    }
//    Q_D(StandardTitleBar);
//    if (!d->window)
//    {
//        return;
//    }
//    const bool active = d->window->isActiveWindow();
//    const QColor backgroundColor = (active ? d->chromePalette->titleBarActiveBackgroundColor() : d->chromePalette->titleBarInactiveBackgroundColor());
//    const QColor foregroundColor = (active ? d->chromePalette->titleBarActiveForegroundColor() : d->chromePalette->titleBarInactiveForegroundColor());
//    QPainter painter(this);
//    painter.save();
//    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing | QPainter::SmoothPixmapTransform);
//    painter.fillRect(QRect(QPoint(0, 0), size()), backgroundColor);
//    if (d->titleLabelVisible)
//    {
//        const QString text = d->window->windowTitle();
//        if (!text.isEmpty())
//        {
//            painter.setPen(foregroundColor);
//            painter.setFont(d->titleFont.value_or(d->defaultFont()));
//            const auto pos = [this, d]() -> QPoint {
//                const StandardTitleBarPrivate::FontMetrics labelSize = d->titleLabelSize();
//                const int titleBarWidth = width();
//                int x = 0;
//                if (d->labelAlignment & Qt::AlignLeft)
//                {
//                    x = (d->windowIconRect().right() + kDefaultTitleBarContentsMargin);
//                }
//                else if (d->labelAlignment & Qt::AlignRight)
//                {
//                    x = (titleBarWidth - kDefaultTitleBarContentsMargin - labelSize.width);
//#if (!defined(Q_OS_MACOS) && FRAMELESSHELPER_CONFIG(system_button))
//                    x -= (titleBarWidth - d->minimizeButton->x());
//#endif
//                }
//                else if (d->labelAlignment & Qt::AlignHCenter)
//                {
//                    x = std::round(qreal(titleBarWidth - labelSize.width) / qreal(2));
//                }
//                else
//                {
//                    WARNING << "The alignment for the title label is not set!";
//                }
//                const int y = std::round((qreal(height() - labelSize.height) / qreal(2)) + qreal(labelSize.ascent));
//                return {x, y};
//            }();
//            const int textMaxWidth = d->titleLabelMaxWidth();
//            const QString elidedText = painter.fontMetrics().elidedText(text, Qt::ElideRight, textMaxWidth, Qt::TextShowMnemonic);
//            // No need to draw the text if there's only the elide mark left (or even less).
//            if (elidedText.size() > 3)
//            {
//                painter.drawText(pos, elidedText);
//            }
//        }
//    }
//    if (d->windowIconVisible)
//    {
//        const QIcon icon = d->window->windowIcon();
//        if (!icon.isNull())
//        {
//            icon.paint(&painter, d->windowIconRect());
//        }
//    }
//    painter.restore();
//    event->accept();
}

void FluFrameLessTitleBar::mouseReleaseEvent(QMouseEvent* event)
{
    mouseEventHandler(event);
}

void FluFrameLessTitleBar::mouseDoubleClickEvent(QMouseEvent* event)
{
    mouseEventHandler(event);
}
