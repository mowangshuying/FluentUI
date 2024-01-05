#pragma once

#include <QPushButton>
#include <QTimer>
#include <QPainter>
#include <qmatrix4x4.h>
#include <QPixmap>
#include "../FluUtils/FluIconUtils.h"

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
        connect(m_timer, SIGNAL(timeout()), this, SLOT(onTimeOut()));
        // connect(this, &FluRotationButton::clicked, [=](bool b) {
        //     m_nReserveAngle = 16;
        // });
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
        //    return;

        QTransform transform;
        transform.rotate(m_nAngle);

        QPixmap pixmap = FluIconUtils::getFluentIconPixmap(FluAwesomeType::Settings);
        pixmap = pixmap.transformed(transform);
        QIcon icon(pixmap);
        setIcon(icon);

        m_nReserveAngle--;
        m_nAngle += 90;
    }

  protected:
    QTimer* m_timer;
    int m_nAngle;
    int m_nReserveAngle;
    bool m_bRotation;
};
