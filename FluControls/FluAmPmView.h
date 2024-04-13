#pragma once

#include <QWidget>
#include <QListWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QKeyEvent>

#include "../FluUtils/FluUtils.h"

#include <QStyleOption>
#include <QPainter>


class FluAmPmView : public QWidget
{
    Q_OBJECT
  public:
    FluAmPmView(int nFixedW = 80, QWidget* parent = nullptr) : QWidget(parent), m_nFixedW(nFixedW)
      {
          m_vMainLayout = new QVBoxLayout;
          m_vMainLayout->setContentsMargins(0, 0, 0, 0);
          m_vMainLayout->setSpacing(0);
          setLayout(m_vMainLayout);

          m_apView = new QListWidget;

          m_scrollDownBtn = new QPushButton(this);
          m_scrollDownBtn->setFixedSize(nFixedW, 40);
          m_scrollUpBtn = new QPushButton(this);
          m_scrollUpBtn->setFixedSize(nFixedW, 40);

          m_vMainLayout->addStretch(1);
          m_vMainLayout->addSpacing(40);
          m_vMainLayout->addWidget(m_apView);
          m_vMainLayout->addStretch(1);

          m_apView->setObjectName("apView");
          m_apView->setFixedHeight(80);
          m_apView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
          m_apView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
          m_apView->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);

          m_scrollUpBtn->setIcon(QIcon(FluIconUtils::getFluentIcon(FluAwesomeType::CaretSolidUp)));
          m_scrollDownBtn->setIcon(QIcon(FluIconUtils::getFluentIcon(FluAwesomeType::CaretSolidDown)));

          m_scrollDownBtn->setObjectName("scrollDownBtn");
          m_scrollUpBtn->setObjectName("scrollUpBtn");

          m_scrollUpBtn->hide();
          m_scrollDownBtn->hide();

          connect(m_scrollUpBtn, &QPushButton::clicked, [=]() { scrollUp(); });
          connect(m_scrollDownBtn, &QPushButton::clicked, [=]() { scrollDown(); });

          m_apView->setFixedWidth(nFixedW);
          setFixedWidth(nFixedW);

          setAmPm("Am", "Pm");
          FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluAmPmView.qss", this);
      }


    void setAmPm(QString am, QString pm)
    {
          m_apView->clear();

           auto amItem = new QListWidgetItem;
          amItem->setSizeHint(QSize(m_nFixedW, 40));
           amItem->setText(am);
          amItem->setTextAlignment(Qt::AlignCenter);
           m_apView->addItem(amItem);
          
           auto pmItem = new QListWidgetItem;
          pmItem->setSizeHint(QSize(m_nFixedW, 40));
           pmItem->setText(pm);
          pmItem->setTextAlignment(Qt::AlignCenter);
           m_apView->addItem(pmItem);

           m_apView->setFixedHeight(40 * 2 + 4 * 2);
    }

    void scrollUp()
    {

    }

    void scrollDown()
    {

    }

    void enterEvent(QEnterEvent* event)
    {
          m_scrollUpBtn->move(0, 0);
          m_scrollDownBtn->move(0, height() - m_scrollDownBtn->height());
          m_scrollUpBtn->show();
          m_scrollDownBtn->show();
    }

    void leaveEvent(QEvent* event)
    {
          m_scrollUpBtn->move(0, 0);
          m_scrollDownBtn->move(0, height() - m_scrollDownBtn->height());
          m_scrollUpBtn->hide();
          m_scrollDownBtn->hide();
    }

    void wheelEvent(QWheelEvent* e)
    {
          if (e->angleDelta().y() < 0)
          {
              scrollDown();
          }
          else
          {
              scrollUp();
          }
    }

    void keyPressEvent(QKeyEvent* event)
    {
          if (event->key() == Qt::Key_Down)
          {
              scrollDown();
              return;
          }

          if (event->key() == Qt::Key_Up)
          {
              scrollUp();
              return;
          }
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
      QListWidget* m_apView;

      QPushButton* m_scrollDownBtn;
      QPushButton* m_scrollUpBtn;

      int m_nFixedW;
};
