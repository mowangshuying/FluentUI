#pragma once

#include <QWidget>
#include "FluWidget.h"
#include <QMouseEvent>
#include <QPainter>
#include <QPaintEvent>
#include "../FluUtils/FluUtils.h"
#include <QStyle>

#define FluToggleSwitchWidth 42
#define FluToggleSwitchHeight 22
#define FluToggleSwitchIndicatorRadius 6

class FluToggleSwitchEx : public FluWidget
{
    Q_OBJECT
    Q_PROPERTY(QColor borderColor READ getBorderColor WRITE setBorderColor)
    Q_PROPERTY(QColor backgroundColor READ getBackgroundColor WRITE setBackgroundColor)
    Q_PROPERTY(QColor indicatorBorderColor READ getIndicatorBorderColor WRITE setIndicatorBorderColor)
    Q_PROPERTY(QColor indicatorBackgroundColor READ getIndicatorBackgroundColor WRITE setIndicatorBackgroundColor)
  public:
    FluToggleSwitchEx(QWidget* parent = nullptr) : FluWidget(parent)
    {
        setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        setAttribute(Qt::WA_Hover);

        m_bChecked = false;
        m_bMouseDown = false;

        setFixedSize(FluToggleSwitchWidth, FluToggleSwitchHeight);
        onThemeChanged();
    }

    void setChecked(bool bChecked)
    {
        m_bChecked = bChecked;
        emit toggled(m_bChecked);
        setProperty("checked", m_bChecked);
        style()->polish(this);
        update();
    }

    bool getChecked()
    {
        return m_bChecked;
    }

    void toggle()
    {
        setChecked(!m_bChecked);
    }

    void setBorderColor(QColor color)
    {
        m_borderColor = color;
        update();
    }

    QColor getBorderColor()
    {
        return m_borderColor;
    }

    void setBackgroundColor(QColor color)
    {
        m_backgroundColor = color;
        update();
    }

    QColor getBackgroundColor()
    {
        return m_backgroundColor;
    }

    void setIndicatorBorderColor(QColor color)
    {
        m_indicatorBorderColor = color;
        update();
    }

    QColor getIndicatorBorderColor()
    {
        return m_indicatorBorderColor;
    }

    void setIndicatorBackgroundColor(QColor color)
    {
        m_indicatorBackgroundColor = color;
        update();
    }

    QColor getIndicatorBackgroundColor()
    {
        return m_indicatorBackgroundColor;
    }

    QSize sizeHint() const
    {
        return QSize(FluToggleSwitchWidth, FluToggleSwitchHeight);
    }

    void paintEvent(QPaintEvent* event)
    {
        FluWidget::paintEvent(event);
        QPainter painter(this);
        painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);

        // set outer border color and backgroundcolor;
        // if (FluThemeUtils::isLightTheme())
        // {
        //     painter.setPen(QColor(130, 130, 130));
        //     painter.setBrush(QColor(237, 237, 237));
        //     if (m_bChecked)
        //     {
        //         painter.setPen(QColor(0, 90, 158));
        //         painter.setBrush(QColor(0, 90, 158));
        //     }
        // }
        // else if (FluThemeUtils::isDarkTheme())
        // {
        //     painter.setPen(QColor(153, 153, 153));
        //     painter.setBrush(QColor(29, 29, 29));
        //     if (m_bChecked)
        //     {
        //         painter.setPen(QColor(118, 185, 237));
        //         painter.setBrush(QColor(118, 185, 237));
        //     }
        // }

        // replace with color;
        painter.setPen(m_borderColor);
        painter.setBrush(m_backgroundColor);
        // draw outer;
        painter.drawRoundedRect(QRectF(rect()).adjusted(0.5, 0.5, -0.5, -0.5), 11, 11);

        // draw indicator;
        QRect indicatorRect;
        if (m_bChecked)
        {
            // 90,90,90
            indicatorRect = QRect(width() - 5 - 12, 5, 12, 12);
        }
        else
        {
            indicatorRect = QRect(5, 5, 12, 12);
        }

        // if (FluThemeUtils::isLightTheme())
        // {
        //     painter.setPen(QColor(90, 90, 90));
        //     painter.setBrush(QColor(90, 90, 90));
        //     if (m_bChecked)
        //     {
        //         painter.setPen(QColor(255, 255, 255));
        //         painter.setBrush(QColor(255, 255, 255));
        //     }
        // }
        // else if (FluThemeUtils::isDarkTheme())
        // {
        //     painter.setPen(QColor(207, 207, 207));
        //     painter.setBrush(QColor(207, 207, 207));
        //     if (m_bChecked)
        //     {
        //         painter.setPen(QColor(0, 0, 0));
        //         painter.setBrush(QColor(0, 0, 0));
        //     }
        // }

        // replace with color;
        painter.setPen(m_indicatorBorderColor);
        painter.setBrush(m_indicatorBackgroundColor);
        painter.drawEllipse(indicatorRect);
    }

    void mousePressEvent(QMouseEvent* event)
    {
        if (event->button() == Qt::LeftButton)
        {
            m_bMouseDown = true;
        }
    }

    void mouseReleaseEvent(QMouseEvent* event)
    {
        if (event->button() == Qt::LeftButton && m_bMouseDown)
        {
            m_bMouseDown = false;
            toggle();
            emit checked(m_bChecked);
        }
    }

    // void keyPressEvent(QKeyEvent* event)
    // {

    // }
  signals:
    void checked(bool bChecked);
    void toggled(bool bChecked);

  public slots:
    void onThemeChanged()
    {
        // if (FluThemeUtils::isLightTheme())
        //{
        //     FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluToggleSwitchEx.qss", this);
        // }
        // else if (FluThemeUtils::isDarkTheme())
        //{
        //     FluStyleSheetUitls::setQssByFileName("../StyleSheet/dark/FluToggleSwitchEx.qss", this);
        // }
        FluStyleSheetUitls::setQssByFileName("FluToggleSwitchEx.qss", this, FluThemeUtils::getUtils()->getTheme());
    }

  protected:
    bool m_bChecked;
    bool m_bMouseDown;

    // feature;
    QColor m_indicatorBorderColor;
    QColor m_indicatorBackgroundColor;
    QColor m_borderColor;
    QColor m_backgroundColor;
};
