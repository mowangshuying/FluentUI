#pragma once

#include "FluAEmptyPage.h"
#include "../FluUtils/FluUtils.h"
#include <QStyleOption>
#include <QPainter>
#include "../FluControls/FluVScrollView.h"
#include "../FluControls/FluFlowLayout.h"
#include "../FluControls/FluDisplayIconBox.h"
#include "../FluControls/FluFWScrollView.h"

class FluIconsPage : public FluAEmptyPage
{
    Q_OBJECT
  public:
      FluIconsPage(QWidget* parent = nullptr) : FluAEmptyPage(parent)
      {
          m_mainLayout->setAlignment(Qt::AlignTop);
          m_titleLabel->setText("IconsPage");
          m_infoLabel->setText("Segoe FluentIcons instructions.");

          auto wrapWidget = new QWidget;
          wrapWidget->setObjectName("wrapWidget");

          auto wrapLayout = new QHBoxLayout;
          wrapWidget->setLayout(wrapLayout);
          m_vScrollView->getMainLayout()->addWidget(wrapWidget, 1);

          auto wrapWidget1 = new FluFWScrollView;
          wrapWidget1->setObjectName("wrapWidget1");
          //m_vScrollView->getMainLayout()->addWidget(wrapWidget1, 1);
          wrapLayout->addWidget(wrapWidget1);

          auto wrapWidget2 = new QWidget;
          wrapWidget2->setObjectName("wrapWidget2");
          wrapWidget2->setFixedWidth(200);

          auto warpWidget2Layout = new QVBoxLayout;
       //   auto wrapWidget2AwesomeTypeLayout = new QHBoxLayout;

          auto titleLabel = new QLabel;
          auto iconLabel = new QLabel;
          auto awesomeTypeKeyLabel = new QLabel;
          auto awesomeTypeValueLabel = new QLabel;
         // wrapWidget2AwesomeTypeLayout->addWidget(awesomeTypeKeyLabel);

          warpWidget2Layout->addWidget(titleLabel);
          warpWidget2Layout->addWidget(iconLabel);
          warpWidget2Layout->addWidget(awesomeTypeKeyLabel);
          warpWidget2Layout->addWidget(awesomeTypeValueLabel);

          wrapLayout->addWidget(wrapWidget2);


       //   auto flowLayout = new FluFlowLayout;
       //   wrapWidget1->setLayout(flowLayout);

          //auto wrapScrollView = new FluVScrollView;

          //wrapScrollView->getMainLayout()->addWidget(wrapWidget1);
          //m_vScrollView->getMainLayout()->addWidget(wrapScrollView, 1);

          m_sDisplayIconBox = nullptr;

          // add icons to display it!
          QMetaEnum metaEnum = QMetaEnum::fromType<FluAwesomeType>();
          for (int i = 0; i < metaEnum.keyCount(); i++)
          {
#ifdef _DEBUG
        //      if (i >= 256)
        //          return;
#endif
              //addIcon((FluAwesomeType)metaEnum.value(i));
              auto displayIconBox = new FluDisplayIconBox((FluAwesomeType)metaEnum.value(i));
              //flowLayout->addWidget(displayIconBox);
              wrapWidget1->getMainLayout()->addWidget(displayIconBox);
              connect(displayIconBox, &FluDisplayIconBox::clicked, [=]() {

                  //tmpDisplayBox = (FluDisplayIconBox*)wrapWidget1->getMainLayout()->itemAt(i)->widget();
                  if (m_sDisplayIconBox != nullptr)
                  {
                      m_sDisplayIconBox->setSelected(false);
                      m_sDisplayIconBox->style()->polish(m_sDisplayIconBox);
                  }

                  m_sDisplayIconBox = displayIconBox;
                  displayIconBox->setSelected(true);
                  displayIconBox->style()->polish(displayIconBox);
              });
          }

           FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluIconsPage.qss", this);
      }

    //  void paintEvent(QPaintEvent* event)
   //   {
    //      QStyleOption opt;
          //opt.initFrom(this);
    //      QPainter painter(this);
     //     style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
    //  }

      protected:
      FluDisplayIconBox* m_sDisplayIconBox;

};
