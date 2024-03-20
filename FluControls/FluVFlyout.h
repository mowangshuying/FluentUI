#pragma once

#include <QWidget>
#include <QVBoxLayout>
#include "../FluUtils/FluUtils.h"
#include <QStyleOption>
#include <QPainter>
#include "FluLabel.h"
#include "FluPushButton.h"

enum class FluFlyoutPosition
{
    Top,
    Bottom,
    Left,
    Right,
};

class FluVFlyout : public QWidget
{
    Q_OBJECT
  public:
    FluVFlyout(QWidget* target, FluFlyoutPosition position = FluFlyoutPosition::Top) 
        : QWidget(nullptr), m_targetWidget(target), m_position(position)
    {
        m_vMainLayout = new QVBoxLayout;
        setLayout(m_vMainLayout);
        setContentsMargins(8, 8, 8, 8);

        setFixedWidth(360);
        setMinimumHeight(96);
        
        setAttribute(Qt::WA_TranslucentBackground);
        setWindowFlags(Qt::Popup | Qt::FramelessWindowHint | Qt::NoDropShadowWindowHint);
        FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluFlyout.qss", this);
    }

    void showEvent(QShowEvent* event)
    {
        int nX = 0;
        int nY = 0;

        QPoint targetPos = m_targetWidget->mapToGlobal(QPoint(0, 0));
        switch (m_position)
        {
            case FluFlyoutPosition::Top:
            {
                nX = targetPos.x() + (m_targetWidget->width() - width()) / 2;
                nY = targetPos.y() - height() - 5;  // 5 is spacing.
            }
            break;
            case FluFlyoutPosition::Bottom:
            {
                nX = targetPos.x() + (m_targetWidget->width() - width()) / 2;
                nY = targetPos.y() + m_targetWidget->height() + 5;  // 5 is spacing.
            }
            break;
            case FluFlyoutPosition::Left:
            {
                nX = targetPos.x() - width() - 5;
                nY = targetPos.y() - (height() - m_targetWidget->height()) / 2;
            }
            break;
            case FluFlyoutPosition::Right:
            {
                nX = targetPos.x() + m_targetWidget->width() + 5;
                nY = targetPos.y() - (height() - m_targetWidget->height()) / 2;
            }
            break;
            default:
                break;
        }

        move(nX, nY);
    }

    void closeEvent(QCloseEvent* event)
    {
        LOG_DEBUG << "close it!";
        deleteLater();
    }

    void paintEvent(QPaintEvent* event)
    {
        QStyleOption opt;
        opt.initFrom(this);
        QPainter painter(this);
        style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
    }

  protected:
    QVBoxLayout* m_vMainLayout;
    QWidget* m_targetWidget;
    FluFlyoutPosition m_position;
};
