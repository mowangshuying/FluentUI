#pragma once

#include "FluAEmptyPage.h"
#include "../FluUtils/FluUtils.h"
#include <QStyleOption>
#include <QPainter>

class FluIconsPage : public FluAEmptyPage
{
    Q_OBJECT
  public:
      FluIconsPage(QWidget* parent = nullptr) : FluAEmptyPage(parent)
      {
          m_mainLayout->setAlignment(Qt::AlignTop);
          m_titleLabel->setText("IconsPage");
          m_infoLabel->setText("Segoe FluentIcons instructions.");
          FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluIconsPage.qss", this);
      }

      void paintEvent(QPaintEvent* event)
      {
          QStyleOption opt;
          opt.initFrom(this);
          QPainter painter(this);
          style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
      }
};
