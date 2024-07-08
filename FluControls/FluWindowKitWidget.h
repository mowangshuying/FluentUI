#pragma once

#include <QWidget>
#include <QCoreApplication>
#include <QGuiApplication>
#include <QHoverEvent>
#include <QTimer>
#include <QScreen>
#include <QVBoxLayout>
#include <QHBoxLayout>

class FluWindowKitWidget : public QWidget
{
  public:
    FluWindowKitWidget(QWidget *parent = nullptr);

    static inline void emulateLeaveEvent(QWidget *widget)
    {
        Q_ASSERT(widget);
        if (!widget)
        {
            return;
        }
        QTimer::singleShot(0, widget, [widget]() {
#if (QT_VERSION >= QT_VERSION_CHECK(5, 14, 0))
            const QScreen *screen = widget->screen();
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

  protected:
    QVBoxLayout *m_vMainLayout;
    QHBoxLayout *m_contentLayout;
};
