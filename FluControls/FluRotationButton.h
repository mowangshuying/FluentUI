#pragma once

#include <QPushButton>
#include <QTimer>
#include <QPainter>
#include <qmatrix4x4.h>
#include <QPixmap>
#include "../FluUtils/FluIconUtils.h"
#include "../FluUtils/FluUtils.h"

class FluRotationButton : public QPushButton
{
    Q_OBJECT
  public:
    FluRotationButton(QWidget* parent = nullptr) : QPushButton(parent)
    {
        m_timer = new QTimer(this);
        m_timer->start();
        m_timer->setInterval(1000 / 60);
        m_bRotation = false;
        m_nAngle = 0;
        m_nReserveAngle = 0;

        connect(m_timer, SIGNAL(timeout()), this, SLOT(onTimeOut()));
        connect(FluThemeUtils::getUtils(), &FluThemeUtils::themeChanged, this, [=](FluTheme theme) { onThemeChanged(); });
    }

    FluRotationButton(FluAwesomeType awesomeType, QWidget* parent = nullptr) : FluRotationButton(parent)
    {
        m_awesomeType = awesomeType;
        onThemeChanged();
    }

    void setAwesomeType(FluAwesomeType awesomeType)
    {
        m_awesomeType = awesomeType;
    }

    void setRotation(bool b)
    {
        m_bRotation = b;
    }

    void setReserveAngle(int nReserveAngle)
    {
        m_nReserveAngle = nReserveAngle;
        m_timer->start();
    }

  public slots:
    void onTimeOut()
    {
        if (m_nReserveAngle <= 0)
        {
            m_timer->stop();
            m_nReserveAngle = 0;
            return;
        }

        QTransform transform;
        transform.rotate(m_nAngle);

        // QPixmap pixmap = FluIconUtils::getFluentIconPixmap(m_awesomeType, m_penColor);
        QPixmap pixmap = FluIconUtils::getFluentIconPixmap(m_awesomeType, FluThemeUtils::getUtils()->getTheme());
        pixmap = pixmap.transformed(transform);
        QIcon icon(pixmap);
        setIcon(icon);

        m_nReserveAngle--;
        m_nAngle += 90;
    }

    void onThemeChanged()
    {
        if (FluThemeUtils::getUtils()->getTheme() == FluTheme::Light)
        {
            setIcon(FluIconUtils::getFluentIcon(m_awesomeType, FluTheme::Light));
            FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluRotationButton.qss", this);
        }
        else
        {
            setIcon(FluIconUtils::getFluentIcon(m_awesomeType, FluTheme::Dark));
            FluStyleSheetUitls::setQssByFileName("../StyleSheet/dark/FluRotationButton.qss", this);
        }
    }

  protected:
    FluAwesomeType m_awesomeType;
    QTimer* m_timer;
    QColor m_penColor;
    int m_nAngle;
    int m_nReserveAngle;
    bool m_bRotation;
};
