#pragma once

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QStyleOption>
#include <QPainter>
#include <QVBoxLayout>

#include "../FluUtils/FluUtils.h"


class FluAppBarToggleButton : public QWidget
{
    Q_OBJECT
  public:
    FluAppBarToggleButton(FluAwesomeType awesomeType, QWidget* parent = nullptr) : QWidget(parent), m_awesomeType(awesomeType), m_bToggled(false)
    {
        m_vMainLayout = new QVBoxLayout;
        setLayout(m_vMainLayout);

        // m_vMainLayout->setContentsMargins(5, 5, 5, 5);
        m_vMainLayout->setAlignment(Qt::AlignHCenter);

        setFixedSize(70, 50);

        // icon and text;
        m_iconBtn = new QPushButton;
        // m_iconBtn->setFixedSize(25, 25);
        m_iconBtn->setIconSize(QSize(20, 20));
        m_iconBtn->setObjectName("iconBtn");
        m_vMainLayout->addWidget(m_iconBtn);

        m_textLabel = new QLabel;
        m_textLabel->setObjectName("textLabel");
        m_vMainLayout->addWidget(m_textLabel);

        m_iconBtn->setIcon(FluIconUtils::getFluentIconPixmap(awesomeType, FluThemeUtils::getUtils()->getTheme()));
        FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluAppBarToggleButton.qss", this);


        setToggled(m_bToggled);

        connect(m_iconBtn, &QPushButton::clicked, [=]() { emit clicked();
        });
        connect(this, &FluAppBarToggleButton::clicked, [=]() { 
            m_bToggled = !m_bToggled;
            setToggled(m_bToggled);

            updateIcon();
            

            update();
        });
        connect(FluThemeUtils::getUtils(), &FluThemeUtils::themeChanged, [=](FluTheme theme) { onThemeChanged(); });
    }

    void updateIcon()
    {
        if (FluThemeUtils::getUtils()->getTheme() == FluTheme::Light)
        {
            if (m_bToggled)
            {
                m_iconBtn->setIcon(FluIconUtils::getFluentIcon(m_awesomeType, FluTheme::Dark));
            }
            else
            {
                m_iconBtn->setIcon(FluIconUtils::getFluentIcon(m_awesomeType, FluTheme::Light));
            }
        }
        else
        {
            if (m_bToggled)
            {
                m_iconBtn->setIcon(FluIconUtils::getFluentIcon(m_awesomeType, FluTheme::Light));
            }
            else
            {
                m_iconBtn->setIcon(FluIconUtils::getFluentIcon(m_awesomeType, FluTheme::Dark));
            }
        }
    }

    void setAwesomeType(FluAwesomeType awesomeType)
    {
        m_awesomeType = awesomeType;
    }

    FluAwesomeType getAwesomeType()
    {
        return m_awesomeType;
    }

    void setText(QString text)
    {
        m_textLabel->setText(text);
    }

    QString getText()
    {
        return m_textLabel->text();
    }

    void setToggled(bool bToggled)
    {
        m_bToggled = bToggled;

        setProperty("toggled", m_bToggled);
        m_textLabel->setProperty("toggled", m_bToggled);
        m_iconBtn->setProperty("toggled", m_bToggled);
        style()->polish(this);
        m_textLabel->style()->polish(m_textLabel);
        m_iconBtn->style()->polish(m_iconBtn);
    }

    bool getToggled()
    {
        return m_bToggled;
    }

    void mouseReleaseEvent(QMouseEvent* event)
    {
        QWidget::mouseReleaseEvent(event);
        emit clicked();
    }

    void paintEvent(QPaintEvent* event)
    {
        QStyleOption opt;
        opt.initFrom(this);
        QPainter painter(this);
        style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
    }
  signals:
    void clicked();
  public slots:
    void onThemeChanged()
    {
        if (FluThemeUtils::getUtils()->getTheme() == FluTheme::Light)
        {
            FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluAppBarToggleButton.qss", this);
        }
        else
        {
            FluStyleSheetUitls::setQssByFileName("../StyleSheet/dark/FluAppBarToggleButton.qss", this);
        }

        updateIcon();
    }

  protected:
    bool m_bToggled;
    FluAwesomeType m_awesomeType;
    QVBoxLayout* m_vMainLayout;
    QPushButton* m_iconBtn;
    QLabel* m_textLabel;
};
