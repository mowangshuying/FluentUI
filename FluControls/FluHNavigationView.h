#pragma once

#include "FluWidget.h"
#include <QHBoxLayout>

#include "FluHScrollView.h"

#include <QStyleOption>
#include <QPainter>

class FluHNavigationIconTextItem;
class FluHNavigationView : public FluWidget
{
    Q_OBJECT
  public:
      FluHNavigationView(QWidget* parent = nullptr) : FluWidget(parent)
      {
          m_hLayout = new QHBoxLayout;
          setLayout(m_hLayout);
          m_hLayout->setContentsMargins(8, 4, 8, 4);
          m_leftWrapWidget = new QWidget(this);
          m_midHScrollView = new FluHScrollView(this);
          m_rightWrapWidget = new QWidget(this);

          m_hLeftWrapLayout = new QHBoxLayout;
          m_hRightWrapLayout = new QHBoxLayout;

          m_leftWrapWidget->setLayout(m_hLeftWrapLayout);
          m_rightWrapWidget->setLayout(m_hRightWrapLayout);

          m_hLeftWrapLayout->setContentsMargins(0, 0, 0, 0);
          m_midHScrollView->getMainLayout()->setContentsMargins(0, 0, 0, 0);
          m_hRightWrapLayout->setContentsMargins(0, 0, 0, 0);

          m_hLeftWrapLayout->setSpacing(5);
          m_hRightWrapLayout->setSpacing(5);

          m_hLeftWrapLayout->setAlignment(Qt::AlignLeft);
          m_midHScrollView->getMainLayout()->setAlignment(Qt::AlignLeft);
          m_hRightWrapLayout->setAlignment(Qt::AlignRight);

          m_hLayout->addWidget(m_leftWrapWidget);
          m_hLayout->addWidget(m_midHScrollView);
          m_hLayout->addWidget(m_rightWrapWidget);

          setFixedHeight(48);
          FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluHNavigationView.qss", this);
      }

      void addItemToLeftLayout(QWidget* item)
      {
          m_hLeftWrapLayout->addWidget(item, Qt::AlignLeft);
      }

      void addItemToMidLayout(QWidget* item)
      {
          m_midHScrollView->getMainLayout()->addWidget(item, 0, Qt::AlignLeft);
      }

      void addItemToRightLayout(QWidget* item)
      {
          m_hRightWrapLayout->addWidget(item, 0, Qt::AlignRight);
      }

      void paintEvent(QPaintEvent* event)
      {
          QStyleOption opt;
          opt.initFrom(this);
          QPainter painter(this);
          style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
      }

  protected:
    QHBoxLayout* m_hLayout;
    QWidget* m_leftWrapWidget;
    FluHScrollView* m_midHScrollView;
    QWidget* m_rightWrapWidget;

    QHBoxLayout* m_hLeftWrapLayout;
    QHBoxLayout* m_hRightWrapLayout;

};
