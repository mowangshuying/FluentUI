#pragma once

#include <QScrollArea>
#include <QWidget>
#include <QHBoxLayout>
#include "../FluUtils/FluUtils.h"
#include <QWheelEvent>

class FluHScrollView : public QScrollArea
{
    Q_OBJECT
  public:
    FluHScrollView(QWidget* parent = nullptr) : QScrollArea(parent)
    {
        setWidgetResizable(true);
        setMinimumSize(0, 0);

        setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        m_contextWidget = new QWidget(this);
        setWidget(m_contextWidget);

        m_hMainLayout = new QHBoxLayout(m_contextWidget);
        m_contextWidget->setObjectName("contextWidget");

        FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluHScrollView.qss", this);
        connect(FluThemeUtils::getUtils(), &FluThemeUtils::themeChanged, this, [=](FluTheme theme) { onThemeChanged(); });
    }

    ~FluHScrollView()
    {
    }

    QHBoxLayout* getMainLayout()
    {
        return m_hMainLayout;
    }

    void wheelEvent(QWheelEvent* event)
    {
        QPointF pos(0, 0);
        QPointF gPos(0, 0);
        QPoint pixelDelta(0, 0);
        QPoint angleDelta(event->angleDelta().y(), 0);
        QWheelEvent wheelEvent(pos, gPos, pixelDelta, angleDelta, event->buttons(), event->modifiers(), event->phase(), event->inverted());
        QScrollArea::wheelEvent(&wheelEvent);
    }

  public slots:
    void onThemeChanged()
    {
        if (FluThemeUtils::isLightTheme())
        {
            FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluHScrollView.qss", this);
        }
        else
        {
            FluStyleSheetUitls::setQssByFileName("../StyleSheet/dark/FluHScrollView.qss", this);
        }
    }

  protected:
    QWidget* m_contextWidget;
    QHBoxLayout* m_hMainLayout;
};
