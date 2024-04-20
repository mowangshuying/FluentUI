#pragma once

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QHBoxLayout>
#include "../FluUtils/FluUtils.h"
#include <QStyleOption>
#include <QPainter>

class FluTabBarItem : public QWidget
{
    Q_OBJECT
  public:
    FluTabBarItem(QWidget* parent = nullptr)
    {
        m_hMainLayout = new QHBoxLayout;
        setLayout(m_hMainLayout);
        m_hMainLayout->setContentsMargins(0, 0, 0, 0);
        m_hMainLayout->setSpacing(0);

        m_iconBtn = new QPushButton(this);
        m_textBtn = new QPushButton(this);
        m_closeBtn = new QPushButton(this);

        m_iconBtn->setFixedSize(30, 30);
        m_closeBtn->setFixedSize(30, 20);

        m_iconBtn->setIconSize(QSize(25, 25));
        m_closeBtn->setIconSize(QSize(15, 15));
        m_textBtn->setFixedHeight(30);
        m_textBtn->setText("Document");

        m_iconBtn->setIcon(FluIconUtils::getFluentIcon(FluAwesomeType::Document));
        m_closeBtn->setIcon(FluIconUtils::getFluentIconPixmap(FluAwesomeType::ChromeClose));

        m_iconBtn->setObjectName("iconBtn");
        m_textBtn->setObjectName("textBtn");
        m_closeBtn->setObjectName("closeBtn");

        m_hMainLayout->addWidget(m_iconBtn, 0);
        m_hMainLayout->addWidget(m_textBtn, 1);
        m_hMainLayout->addWidget(m_closeBtn, 0);
        m_hMainLayout->addSpacing(5);

        setFixedHeight(35);
        //   setFixedWidth(240);

        connect(m_iconBtn, &QPushButton::clicked, [=]() { emit clicked(); });

        connect(m_textBtn, &QPushButton::clicked, [=]() { emit clicked(); });

        connect(m_closeBtn, &QPushButton::clicked, [=]() { emit clickedCloseBtn(this); });
        FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluTabBarItem.qss", this);
    }

    void setSelected(bool bSel)
    {
        m_bSel = bSel;
        setProperty("selected", bSel);
        m_closeBtn->setProperty("selected", bSel);
        m_closeBtn->style()->polish(m_closeBtn);
    }

    bool getSelected()
    {
        return m_bSel;
    }

    void setText(QString text)
    {
        m_textBtn->setText(text);
    }

    QString getText()
    {
        return m_textBtn->text();
    }

    void resizeEvent(QResizeEvent* event)
    {
        emit sizeChanged();
    }

    void enterEvent(QEnterEvent* event)
    {
        // m_closeBtn->setProperty("tabBarItemHover", true);
    }

    void leaveEvent(QEvent* event)
    {
        // m_closeBtn->setProperty("tabBarItemHover", false);
    }

    void mouseReleaseEvent(QMouseEvent* event)
    {
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
    void sizeChanged();
    void clickedCloseBtn(FluTabBarItem* item);

  protected:
    QHBoxLayout* m_hMainLayout;
    QPushButton* m_iconBtn;
    QPushButton* m_textBtn;
    QPushButton* m_closeBtn;

    bool m_bSel;
};
