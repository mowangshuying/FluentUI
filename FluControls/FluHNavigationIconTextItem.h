#pragma once

#include "FluHNavigationItem.h"

#include <QWidget>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>

#include "../FluUtils/FluUtils.h"
#include <QStyleOption>
#include <QPainter>

class FluHNavigationIconTextItem : public FluHNavigationItem
{
    Q_OBJECT
  public:
    FluHNavigationIconTextItem(QWidget* parent = nullptr) : FluHNavigationItem(parent)
    {
        m_itemType = FluHNavigationItemType::IconText;
        m_parentView = nullptr;

        m_wrapWidget1 = new QWidget;
        m_wrapWidget2 = new QWidget;

        m_wrapWidget1->setObjectName("wrapWidget1");
        m_wrapWidget2->setObjectName("wrapWidget2");

        m_vMainLayout = new QVBoxLayout;
        setLayout(m_vMainLayout);

        m_vMainLayout->setContentsMargins(0, 0, 0, 0);
        m_vMainLayout->setSpacing(5);
        m_vMainLayout->addWidget(m_wrapWidget1);
        m_vMainLayout->addWidget(m_wrapWidget2);
        m_wrapWidget2->hide();

        m_hLayout1 = new QHBoxLayout;
        setLayout(m_hLayout1);

        m_wrapWidget1->setLayout(m_hLayout1);
        m_hLayout1->setContentsMargins(4, 4, 4, 4);

        m_iconBtn = new QPushButton;
        m_label = new QLabel;
        m_arrow = new QPushButton;

        m_hLayout1->addWidget(m_iconBtn);
        m_hLayout1->addWidget(m_label, 1);
        m_hLayout1->addWidget(m_arrow);

        m_iconBtn->setObjectName("icon");
        m_label->setObjectName("label");
        m_arrow->setObjectName("arrow");

        m_iconBtn->setIconSize(QSize(24, 24));
        m_iconBtn->setIcon(FluIconUtils::getFluentIcon(FluAwesomeType::Home));

        m_arrow->setIconSize(QSize(18, 18));
        m_arrow->setIcon(FluIconUtils::getFluentIcon(FluAwesomeType::ChevronDown));
        m_arrow->setFixedWidth(25);

        setFixedHeight(40);
    }

    FluHNavigationIconTextItem(FluAwesomeType awesomeType, QString text, QWidget* parent = nullptr) : FluHNavigationIconTextItem(parent)
    {
        m_awesomeType = awesomeType;
        m_iconBtn->setIcon(FluIconUtils::getFluentIcon(m_awesomeType));
        m_label->setText(text);
        onThemeChanged();
    }

    ~FluHNavigationIconTextItem()
    {
    }

    QWidget* getWrapWidget1()
    {
        return m_wrapWidget1;
    }

    QWidget* getWrapWidget2()
    {
        return m_wrapWidget2;
    }

    QPushButton* getIconBtn()
    {
        return m_iconBtn;
    }

    QLabel* getLabel()
    {
        return m_label;
    }

    FluAwesomeType getAwesomeType()
    {
        return m_awesomeType;
    }

    QString getText()
    {
        return m_label->text();
    }


    void paintEvent(QPaintEvent* event)
    {
        QStyleOption opt;
        opt.initFrom(this);
        QPainter painter(this);
        style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
    }
signals:
    void itemClicked();
  public slots:
    void onItemClicked()
    {
    }
    void onThemeChanged()
    {
        if (FluThemeUtils::getUtils()->getTheme() == FluTheme::Light)
        {
            m_iconBtn->setIcon(FluIconUtils::getFluentIcon(m_awesomeType, QColor(8, 8, 8)));
            m_arrow->setIcon(FluIconUtils::getFluentIcon(FluAwesomeType::ChevronDown, QColor(8, 8, 8)));
            FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluHNavigationIconTextItem.qss", this);
        }
        else
        {
            m_iconBtn->setIcon(FluIconUtils::getFluentIcon(m_awesomeType, QColor(239, 239, 239)));
            m_arrow->setIcon(FluIconUtils::getFluentIcon(FluAwesomeType::ChevronDown, QColor(239, 239, 239)));
            FluStyleSheetUitls::setQssByFileName("../StyleSheet/dark/FluHNavigationIconTextItem.qss", this);
        }
    }

  protected:
    QWidget* m_wrapWidget1;
    QWidget* m_wrapWidget2;

    QWidget* m_indicator;
    QPushButton* m_iconBtn;
    QLabel* m_label;
    QPushButton* m_arrow;
    QHBoxLayout* m_hLayout1;

    std::vector<FluHNavigationIconTextItem*> m_items;

    QVBoxLayout* m_vMainLayout;

    FluAwesomeType m_awesomeType;
};
