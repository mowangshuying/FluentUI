#pragma once

#include <QPushButton>
#include "FluDef.h"
#include "../FluUtils/FluUtils.h"
#include <QTimer>

// to display fluent icon use fluent font
class FluIconButton : public QPushButton
{
    Q_OBJECT
  public:
    FluIconButton(QWidget* parent = nullptr) : QPushButton(parent)
    {
        // set fixed size
        setFixedSize(30, 30);
        setIconSize(QSize(20, 20));

        FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluIconButton.qss", this);
    }

    FluIconButton(FluAwesomeType type1, QWidget* parent = nullptr) : QPushButton(parent)
    {
        setFixedSize(30, 30);
        setIconSize(QSize(20, 20));
        // please ensure type1 will in FluAwesomeType, if can't suitable may crash.

        QPixmap pixmap = FluIconUtils::getFluentIconPixmap(type1);
        pixmap = pixmap.scaled(20, 20, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        setIcon(QIcon(pixmap));

        FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluIconButton.qss", this);
    }

    FluIconButton(FluAwesomeType type1, FluAwesomeType type2, QWidget* parent = nullptr) : QPushButton(parent), m_type1(type1), m_type2(type2)
    {
        setFixedSize(30, 30);
        setIconSize(QSize(20, 20));
        // please ensure type1 will in FluAwesomeType, if can't suitable may crash.

        QPixmap pixmap = FluIconUtils::getFluentIconPixmap(type1);
        pixmap = pixmap.scaled(20, 20, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        setIcon(QIcon(pixmap));

        FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluIconButton.qss", this);

        // can change type1 to type2, type2 auto change to type1
        m_timer = new QTimer;
        m_timer->setInterval(500);
        connect(m_timer, &QTimer::timeout, [=]() {
            // change type2 to type1
            QPixmap pixmap = FluIconUtils::getFluentIconPixmap(m_type1);
            pixmap = pixmap.scaled(20, 20, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
            setIcon(QIcon(pixmap));
        });

        connect(this, &FluIconButton::clicked, [=](bool b) {
            // change to type2
            QPixmap pixmap = FluIconUtils::getFluentIconPixmap(m_type2);
            pixmap = pixmap.scaled(20, 20, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
            setIcon(QIcon(pixmap));

            m_timer->start();
        });
    }

    void setType1(FluAwesomeType type1)
    {
        QPixmap pixmap = FluIconUtils::getFluentIconPixmap(type1);
        pixmap = pixmap.scaled(20, 20, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        setIcon(QIcon(pixmap));
    }

  protected:
    FluAwesomeType m_type1;
    FluAwesomeType m_type2;

    QTimer* m_timer;
    bool m_bClicked;
};
