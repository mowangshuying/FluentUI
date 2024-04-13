#pragma once

#include <QWidget>
#include "FluLoopView.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "../FluUtils/FluUtils.h"
#include <QPushButton>
#include <QPainter>
#include <QStyleOption>
#include "FluAmPmView.h"
#include "FluHSplitLine.h"
#include "FluVSplitLine.h"

class FluTimePickerAPView : public QWidget
{
    Q_OBJECT
  public:
    FluTimePickerAPView(QWidget* parent = nullptr) : QWidget(parent), m_bAm(true), m_hour(0), m_minute(0)
      {
          setWindowFlags(Qt::Popup | Qt::FramelessWindowHint | Qt::NoDropShadowWindowHint);
          setAttribute(Qt::WA_TranslucentBackground);

          m_vMainLayout = new QVBoxLayout;
          m_vMainLayout->setContentsMargins(0, 0, 0, 0);
          m_vMainLayout->setSpacing(0);
          setLayout(m_vMainLayout);

           m_hViewLayout = new QHBoxLayout;
          // setLayout(m_hViewLayout);
          m_vMainLayout->addLayout(m_hViewLayout);

          m_hourView = new FluLoopView(80);
          m_minuteView = new FluLoopView(80);
          m_ampmView = new FluAmPmView(80);


          // set hour data;
          std::vector<QString> datas;
          for (int i = 0; i < 12; i++)
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
          m_hViewLayout->addWidget(new FluHSplitLine);
          m_hViewLayout->addWidget(m_minuteView);
          m_hViewLayout->addWidget(new FluHSplitLine);
          m_hViewLayout->addWidget(m_ampmView);

          m_hBtnLayout = new QHBoxLayout;
          m_hBtnLayout->setContentsMargins(5, 5, 5, 5);

          m_okBtn = new QPushButton;
          m_cancelBtn = new QPushButton;

          m_okBtn->setObjectName("okBtn");
          m_cancelBtn->setObjectName("cancelBtn");

          m_okBtn->setFixedHeight(40);
          m_cancelBtn->setFixedHeight(40);

          m_okBtn->setIconSize(QSize(25, 25));
          m_okBtn->setIcon(FluIconUtils::getFluentIcon(FluAwesomeType::Accept));

          m_cancelBtn->setIconSize(QSize(25, 25));
          m_cancelBtn->setIcon(FluIconUtils::getFluentIconPixmap(FluAwesomeType::Cancel));

          m_hBtnLayout->addWidget(m_okBtn);
          m_hBtnLayout->addWidget(m_cancelBtn);

          m_vMainLayout->addWidget(new FluVSplitLine);
          m_vMainLayout->addLayout(m_hBtnLayout);
          FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluTimePickerAPView.qss", this);
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
      FluAmPmView* m_ampmView;

      QPushButton* m_okBtn;
      QPushButton* m_cancelBtn;

      int m_hour;
      int m_minute;
      bool m_bAm;
};
