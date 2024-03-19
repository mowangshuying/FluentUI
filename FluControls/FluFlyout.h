#pragma once

#include <QWidget>
#include <QVBoxLayout>
#include "../FluUtils/FluUtils.h"
#include <QStyleOption>
#include <QPainter>
#include "FluLabel.h"
#include "FluPushButton.h"

enum class FlyoutPositon
{
	Top,
	Bottom,
	Left,
	Right,
};

class FluFlyout : public QWidget
{
	Q_OBJECT
  public:
	  FluFlyout(QWidget* parent = nullptr) : QWidget(parent)
	  {
              m_vMainLayout = new QVBoxLayout;
              setLayout(m_vMainLayout);
			  setContentsMargins(8, 8, 8, 8);

			  setFixedWidth(360);
              setMinimumHeight(96);
              setWindowFlags(Qt::Popup | Qt::FramelessWindowHint | Qt::NoDropShadowWindowHint);
              setAttribute(Qt::WA_TranslucentBackground);
           //   setAttribute(Qt::WA_StyledBackground, true);

              auto label = new FluLabel;
         //     label->setStyle(FluLabelStyle::BodyTextBlockStyle);
              label->setText("All item will be remove, Do you want to continue.");
              m_vMainLayout->addWidget(label);

              auto btn = new FluPushButton;
              btn->setText("Yes, empty my cart.");
              btn->setFixedWidth(150);
              m_vMainLayout->addWidget(btn);

              FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluFlyout.qss", this);
	  }

   //   QVBoxLayout* getMainLayout()
   //   {
   //           return m_vMainLayout;
   //   }

      void paintEvent(QPaintEvent* event)
          {
              QStyleOption opt;
              opt.initFrom(this);
              QPainter painter(this);
              style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
          }


	  static void setFlyout(QWidget* target, QWidget* parent, FlyoutPositon postion = FlyoutPositon::Top)
	  {
            if (target == nullptr)
            {
                LOG_WARN << "target nullptr!";
                return;
            }

            int nX = 0;
            int nY = 0;

            QPoint targetPos = target->mapToGlobal(QPoint(0, 0));
            FluFlyout* flyout = new FluFlyout(parent);
            flyout->show();

            LOG_DEBUG << "flyout size:" << flyout->size();
		    switch (postion)
            {
                case FlyoutPositon::Top:
                {
                    nX = targetPos.x() + (target->width() - flyout->width()) / 2;
                    nY = targetPos.y() - flyout->height() - 5; // 5 is spacing.
                }
                break;
                case FlyoutPositon::Bottom:
                {

                }
                break;
                case FlyoutPositon::Left:
                {

                }
                break;
                case FlyoutPositon::Right:
                {

                }
                break;
                default:
                    break;
            }

            flyout->move(nX, nY);
            flyout->show();

	  }
  protected:
      QVBoxLayout* m_vMainLayout;
};
