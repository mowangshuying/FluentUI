#pragma once

#include <QWidget>
#include <QLabel>
#include "FluComboBox.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "../FluUtils/FluUtils.h"

class FluSettingsSelectBox : public QWidget
{
	Q_OBJECT
  public:
      FluSettingsSelectBox(QWidget* parent = nullptr) : QWidget(parent)
      {
          m_mainLayout = new QHBoxLayout;
          setLayout(m_mainLayout);

          m_iconLabel = new QLabel;
          m_mainLayout->addWidget(m_iconLabel);

          m_vLayout = new QVBoxLayout;
          m_titleLabel = new QLabel;
          m_infoLabel = new QLabel;

          m_mainLayout->addLayout(m_vLayout);
          m_comboBox = new FluComboBox;
          m_comboBox->setFixedWidth(120);
          m_mainLayout->addWidget(m_comboBox);

          setFixedHeight(70);
          FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluSettingsSelectBox.qss", this);
      }

      void setIcon(QIcon icon)
      {
          m_iconLabel->setPixmap(icon.pixmap(40,40));
      }

      void paintEvent(QPaintEvent* event)
      {
          QStyleOption opt;
          opt.initFrom(this);
          QPainter painter(this);
          style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
      }

  protected:
    QHBoxLayout* m_mainLayout;
    QVBoxLayout* m_vLayout;
    QLabel* m_iconLabel;
    QLabel* m_titleLabel;
    QLabel* m_infoLabel;
    FluComboBox* m_comboBox;
};
