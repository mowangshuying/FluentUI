#pragma once

#include "FluHNavigationItem.h"
#include <QPushButton>
#include <QHBoxLayout>

#include <QStyleOption>
#include <QPainter>
#include "../FluUtils/FluUtils.h"

class FluHNavigationMoreItem : public FluHNavigationItem
{
    Q_OBJECT
  public:
      FluHNavigationMoreItem(QWidget* parent = nullptr) : FluHNavigationItem(parent)
      {
          m_hMainLayout = new QHBoxLayout;
          setLayout(m_hMainLayout);

          m_hMainLayout->setContentsMargins(0, 0, 0, 0);

          m_iconBtn = new QPushButton;
          m_iconBtn->setFixedSize(40, 40);
          m_iconBtn->setIconSize(QSize(24, 24));

          m_iconBtn->setObjectName("iconBtn");
          m_hMainLayout->addWidget(m_iconBtn);

          onThemeChanged();
      }

      void paintEvent(QPaintEvent* event)
      {
          QStyleOption opt;
          opt.initFrom(this);
          QPainter painter(this);
          style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
      }

  public slots:
      void onThemeChanged()
      {
          if (FluThemeUtils::getUtils()->getTheme() == FluTheme::Light)
          {
              m_iconBtn->setIcon(FluIconUtils::getFluentIcon(FluAwesomeType::More, FluTheme::Light));
              FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluHNavigationMoreItem.qss", this);
          }
          else
          {
              m_iconBtn->setIcon(FluIconUtils::getFluentIcon(FluAwesomeType::More, FluTheme::Dark));
              FluStyleSheetUitls::setQssByFileName("../StyleSheet/dark/FluHNavigationMoreItem.qss", this);
          }
      }
  protected:
      QPushButton* m_iconBtn;
      QHBoxLayout* m_hMainLayout;
};
