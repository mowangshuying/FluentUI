#pragma once

#include <QWidget>
#include "FluLoopView.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include "../FluUtils/FluUtils.h"
#include <QPainter>
#include <QStyleOption>

class FluTimePicker24HView : public QWidget
{
    Q_OBJECT
  public:
      FluTimePicker24HView(QWidget* parent = nullptr) : QWidget(parent)
      {
          m_vMainLayout = new QVBoxLayout;
          setLayout(m_vMainLayout);

          m_hViewLayout = new QHBoxLayout;
         // setLayout(m_hViewLayout);
          m_vMainLayout->addLayout(m_hViewLayout);

          m_hourView = new FluLoopView;
          m_minuteView = new FluLoopView;

          // set hour data;
          std::vector<QString> datas;
          for (int i = 0; i < 24; i++)
          {
              QString str = QString::asprintf("%02d", i);
              datas.push_back(str);
          }
          m_hourView->setAllItems(datas);

          // set minute data;
          datas.clear();
          for (int i = 0; i < 60; i++)
          {
              QString str = QString::asprintf("%02d", i);
              datas.push_back(str);
          }
          m_minuteView->setAllItems(datas);

          m_hViewLayout->setSpacing(0);
          m_hViewLayout->addWidget(m_hourView);
          m_hViewLayout->addWidget(m_minuteView);


          m_hBtnLayout = new QHBoxLayout;
          m_okBtn = new QPushButton;
          m_cancelBtn = new QPushButton;

          m_okBtn->setObjectName("okBtn");
          m_cancelBtn->setObjectName("cancelBtn");

          m_okBtn->setFixedHeight(30);
          m_cancelBtn->setFixedHeight(30);


          m_okBtn->setIconSize(QSize(25, 25));
          m_okBtn->setIcon(FluIconUtils::getFluentIcon(FluAwesomeType::Accept));

          m_cancelBtn->setIconSize(QSize(25, 25));
          m_cancelBtn->setIcon(FluIconUtils::getFluentIconPixmap(FluAwesomeType::Cancel));

          m_hBtnLayout->addWidget(m_okBtn);
          m_hBtnLayout->addWidget(m_cancelBtn);

          m_vMainLayout->addLayout(m_hBtnLayout);

          FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluTimePicker24HView.qss", this);
      }


      void paintEvent(QPaintEvent* event)
      {
          QStyleOption opt;
          opt.initFrom(this);
          QPainter painter(this);
          style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
      }
  protected:
      QVBoxLayout* m_vMainLayout;
      QHBoxLayout* m_hViewLayout;
      QHBoxLayout* m_hBtnLayout;
      
      FluLoopView* m_hourView;
      FluLoopView* m_minuteView;

      QPushButton* m_okBtn;
      QPushButton* m_cancelBtn;
};
