#pragma once

#include "FluNavigationItem.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QStyleOption>
#include <QPainter>
#include "FluRotationButton.h"
#include "../FluUtils/FluUtils.h"

class FluNavigationSettingsItem : public FluNavigationItem
{
    Q_OBJECT
  public:
    FluNavigationSettingsItem(QIcon icon, QString text, QWidget* parent = nullptr) : FluNavigationItem(parent)
    {
        setFixedSize(320, 40);
        m_hMainLayout = new QHBoxLayout;
        setLayout(m_hMainLayout);

        m_hMainLayout->setContentsMargins(0, 4, 0, 4);

        m_indicator = new QWidget(this);
        m_icon = new FluRotationButton(this);
        m_label = new QLabel;
        m_label->setText(text);

        m_indicator->setFixedHeight(18);
        m_indicator->setFixedWidth(4);
        m_icon->setFixedSize(30, 30);
        m_label->setWordWrap(true);

        m_icon->setIconSize(QSize(24, 24));
        m_icon->setIcon(icon);

        m_indicator->setObjectName("indicator");
        m_icon->setObjectName("icon");
        m_label->setObjectName("label");

        m_hMainLayout->addSpacing(4);
        m_hMainLayout->addWidget(m_indicator);
        m_hMainLayout->addWidget(m_icon);
        m_hMainLayout->addSpacing(12);
        m_hMainLayout->addWidget(m_label, 1);
        m_hMainLayout->setSpacing(0);

        FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluNavigationSettingsItem.qss", this);
        connect(m_icon, &FluRotationButton::clicked, [=](bool b) { emit itemClicked(); });
        connect(this, &FluNavigationSettingsItem::itemClicked, this, &FluNavigationSettingsItem::onItemClicked);
        connect(FluThemeUtils::getUtils(), &FluThemeUtils::themeChanged, [=](FluTheme theme) { onThemeChanged(); });

    }

    FluNavigationSettingsItem(FluAwesomeType awesomeType, QString text, QWidget* parent) : FluNavigationSettingsItem(QIcon(), text, parent)
    {
        m_icon->setIcon(FluIconUtils::getFluentIcon(awesomeType));
        m_icon->setAwesomeType(awesomeType);
    }

    void updateAllItemsStyleSheet()
    {
        updateItemsStyleSheet();
    }

    void updateItemsStyleSheet()
    {
        style()->polish(this);
        m_indicator->style()->polish(m_indicator);
        m_icon->style()->polish(m_icon);
        m_label->style()->polish(m_label);
    }

    void updateSelected(bool b)
    {
        m_bSelected = b;
        setProperty("selected", b);
        m_indicator->setProperty("selected", b);
        m_label->setProperty("selected", b);
    }

    void clearAllItemsSelectState()
    {
        updateSelected(false);
    }

    void mouseReleaseEvent(QMouseEvent* event)
    {
        FluNavigationItem::mouseReleaseEvent(event);
        emit itemClicked();
    }

    // to enable qss
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
    void onItemClicked();
    void onThemeChanged()
    {
        if (FluThemeUtils::getUtils()->getTheme() == FluTheme::Light)
        {
            //m_icon->setIcon(FluIconUtils::getFluentIcon(FluAwesomeType::Settings, QColor(8, 8, 8)));
            FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluNavigationSettingsItem.qss", this);
        }
        else
        {
            //m_icon->setIcon(FluIconUtils::getFluentIcon(FluAwesomeType::Settings, QColor(239, 239, 239)));
            FluStyleSheetUitls::setQssByFileName("../StyleSheet/dark/FluNavigationSettingsItem.qss", this);
        }
    }
  protected:
    QHBoxLayout* m_hMainLayout;
    QWidget* m_indicator;
    FluRotationButton* m_icon;
    QLabel* m_label;

    bool m_bSelected;
};
