#pragma once

#include "FluWidget.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include "FluLabel.h"
#include "FluTimeLineIcon.h"
#include <QPainter>
#include "../FluUtils/FluUtils.h"

class FluTimeLineItem : public FluWidget
{
    Q_OBJECT
  public:
      FluTimeLineItem(QWidget* parent = nullptr) : FluWidget(parent)
      {
          m_hMainLayout = new QHBoxLayout;
          setLayout(m_hMainLayout);
          m_hMainLayout->setContentsMargins(0, 20, 0, 20);

          m_vIconLayout = new QVBoxLayout;
          m_vIconLayout->setAlignment(Qt::AlignTop);
          m_vIconLayout->setContentsMargins(0, 0, 0, 0);

          m_vItemLayout = new QVBoxLayout;
          m_vItemLayout->setContentsMargins(0, 0, 0, 0);

          m_icon = new FluTimeLineIcon;
          m_vIconLayout->addWidget(m_icon, 0, Qt::AlignTop);

          m_hMainLayout->addLayout(m_vIconLayout);
          m_hMainLayout->addLayout(m_vItemLayout);
          setMinimumHeight(40);
      }

      void addTextItem(QString text)
      {
          auto label = new FluLabel;
          label->setWordWrap(true);
          label->setLabelStyle(FluLabelStyle::CaptionTextBlockSylte);
          label->setText(text);
          label->setMinimumHeight(40);
          m_vItemLayout->addWidget(label);
          setMinimumHeight(m_vItemLayout->count() * 40);
      }

      FluLabel* getLabelAt(int nIndex)
      {
          if (nIndex < 0 || nIndex >= m_vItemLayout->count())
              return nullptr;

          return static_cast<FluLabel*>(m_vItemLayout->itemAt(nIndex)->widget());
      }

      void paintEvent(QPaintEvent* event)
      {
          QPainter painter(this);
          painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);

          // draw line;
          painter.setPen(Qt::NoPen);
          painter.setBrush(QColor(29, 29, 29));
          if (FluThemeUtils::isDarkTheme())
              painter.setBrush(QColor(229, 229, 229));
          
          painter.drawRect(QRectF(20 - 1.5, 0, 3, 20));

          // draw line;
          //painter.setPen(Qt::NoPen);
          //painter.setBrush(Qt::lightGray);
          painter.drawRect(QRectF(20-1.5, 60, 3, height() - 60));
      }
  protected:
      FluTimeLineIcon* m_icon;
      QHBoxLayout* m_hMainLayout;
      QVBoxLayout* m_vItemLayout;
      QVBoxLayout* m_vIconLayout;
};
