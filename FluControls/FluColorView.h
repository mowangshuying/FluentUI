#pragma once

#include "FluColorViewGradient.h"
#include "FluColorViewHHandle.h"
#include "FluColorViewVHandle.h"

#include <QVBoxLayout>
#include <QHBoxLayout>

#include "FluLabel.h"
#include "FluLineEdit.h"
#include <QStyleOption>
#include <QPainter>

class FluColorView : public FluWidget
{
    Q_OBJECT
  public:
      FluColorView(QWidget* parent = nullptr) : FluWidget(parent)
      {
          setFixedSize(320, 420);
          m_vMainLayout = new QVBoxLayout;
          m_vMainLayout->setContentsMargins(5, 5, 5, 5);
          setLayout(m_vMainLayout);

          auto hLayout = new QHBoxLayout;
          auto colorViewGradient = new FluColorViewGradient;
          colorViewGradient->setFixedSize(256, 256);

          auto colorViewVHandle = new FluColorViewVHandle;
          colorViewVHandle->setFixedSize(45, 256);

          hLayout->addWidget(colorViewGradient);
          hLayout->addWidget(colorViewVHandle);

          m_vMainLayout->addLayout(hLayout);

          auto colorViewHHandle = new FluColorViewHHandle;
          colorViewHHandle->setFixedHeight(13);
          m_vMainLayout->addWidget(colorViewHHandle);

          hLayout = new QHBoxLayout;
          auto rLabel = new FluLabel;
          rLabel->setLabelStyle(FluLabelStyle::BodyTextBlockStyle);
          rLabel->setFixedWidth(50);
          rLabel->setText("Red:");
          auto rEdit = new FluLineEdit;
          rEdit->setFixedSize(120, 35);
          

          hLayout->addWidget(rLabel);
          hLayout->addWidget(rEdit);
          hLayout->addStretch();

          m_vMainLayout->addLayout(hLayout);

          hLayout = new QHBoxLayout;
          auto gLabel = new FluLabel;
          gLabel->setLabelStyle(FluLabelStyle::BodyTextBlockStyle);
          gLabel->setText("Green:");
          gLabel->setFixedWidth(50);

          auto gEdit = new FluLineEdit;
          gEdit->setFixedSize(120, 35);

          hLayout->addWidget(gLabel);
          hLayout->addWidget(gEdit);
          hLayout->addStretch();


          m_vMainLayout->addLayout(hLayout);


          hLayout = new QHBoxLayout;
          auto bLabel = new FluLabel;
          bLabel->setLabelStyle(FluLabelStyle::BodyTextBlockStyle);
          bLabel->setText("Blue:");
          bLabel->setFixedWidth(50);
          

          auto bEdit = new FluLineEdit;
          bEdit->setFixedSize(120, 35);
          

          hLayout->addWidget(bLabel);
          hLayout->addWidget(bEdit);
          hLayout->addStretch();


          m_vMainLayout->addLayout(hLayout);

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
          if (FluThemeUtils::isLightTheme())
          {
              FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluColorView.qss", this);

          }
          else
          {
              FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluColorView.qss", this);

          }
      }
  protected:
      QVBoxLayout* m_vMainLayout;
};
