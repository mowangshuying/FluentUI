#pragma once

#include <QCalendarWidget>
#include <QWidget>
#include "../FluUtils/FluUtils.h"
#include <QPainter>
#include <QStyleOption>
#include <QPushButton>
#include <QHBoxLayout>
#include "FluPushButton.h"
#include "FluIconButton.h"
#include <QVBoxLayout>
#include <QLabel>

class FluCalendarViewTitle : public QWidget
{
    Q_OBJECT
  public:
      FluCalendarViewTitle(QWidget* parent = nullptr) : QWidget(parent)
      {
          m_hMainLayout = new QHBoxLayout;
          setLayout(m_hMainLayout);

          m_yearMonthBtn = new FluPushButton;
          m_yearMonthBtn->setText("January 1924");
          m_hMainLayout->addWidget(m_yearMonthBtn);

          m_preBtn = new FluIconButton(FluAwesomeType::CaretSolidUp);
          m_nextBtn = new FluIconButton(FluAwesomeType::CaretSolidDown);

          m_hMainLayout->addWidget(m_preBtn);
          m_hMainLayout->addWidget(m_nextBtn);

          m_yearMonthBtn->setObjectName("yearMonthBtn");
          m_preBtn->setObjectName("preBtn");
          m_nextBtn->setObjectName("nextBtn");

          setFixedHeight(50);

          FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluCalendarViewTitle.qss", m_yearMonthBtn);
          FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluCalendarViewTitle.qss", m_preBtn);
          FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluCalendarViewTitle.qss", m_nextBtn);
          FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluCalendarViewTitle.qss", this);
      }

      void paintEvent(QPaintEvent* event)
      {
          QStyleOption opt;
          opt.initFrom(this);
          QPainter painter(this);
          style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
      }

  protected:
      FluPushButton* m_yearMonthBtn;
      FluIconButton* m_preBtn;
      FluIconButton* m_nextBtn;

      QHBoxLayout* m_hMainLayout;

      
};

class FluCalendarViewWeakTitle : public QWidget
{
    public:
      FluCalendarViewWeakTitle(QWidget* parent = nullptr) : QWidget(parent)
      {
          //QLabel* m_label = new QLabel("Su");
          m_hMainLayout = new QHBoxLayout;
          m_hMainLayout->setContentsMargins(5, 0, 5, 0);
          setLayout(m_hMainLayout);



          QList<QString> weekTexts = {"Su", "Mo", "Tu", "We", "Th", "Fr", "Sa"};
          for (int i = 0; i < weekTexts.size(); i++)
          {
              QLabel* label = new QLabel;
              label->setFixedWidth(40);
              label->setObjectName("label");
              label->setAlignment(Qt::AlignCenter);
              label->setText(weekTexts.at(i));

              m_hMainLayout->addWidget(label);
          }

          setFixedHeight(30);
          FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluCalendarViewWeakTitle.qss", this);
      }

      void paintEvent(QPaintEvent* event)
      {
          QStyleOption opt;
          opt.initFrom(this);
          QPainter painter(this);
          style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
      }

  protected:
      QHBoxLayout* m_hMainLayout;
};

class FluCalendarView : public QWidget
{
	Q_OBJECT
  public:
	  FluCalendarView(QWidget* parent = nullptr) : QWidget(parent)
	  {
           m_vMainLayout = new QVBoxLayout;
           m_vMainLayout->setContentsMargins(0, 0, 0, 0);
           setLayout(m_vMainLayout);

           auto title = new FluCalendarViewTitle;
           m_vMainLayout->addWidget(title);

           auto weekTitle = new FluCalendarViewWeakTitle;
           m_vMainLayout->addWidget(weekTitle);
           m_vMainLayout->addStretch();

           setFixedSize(300, 360);
           FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluCalendarView.qss", this);
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
};
