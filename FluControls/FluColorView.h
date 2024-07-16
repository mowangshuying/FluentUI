#pragma once

#include "FluColorViewGradient.h"
#include "FluColorViewHHandle.h"
#include "FluColorViewVHandle.h"

#include <QVBoxLayout>
#include <QHBoxLayout>

#include "FluLabel.h"
#include "FluLineEdit.h"
#include "FluPushButton.h"
#include "FluStyleButton.h"
#include <QStyleOption>
#include <QPainter>
#include <QDialog>
#include <QEvent>
#include <QResizeEvent>


class FluColorView : public QDialog
{
    Q_OBJECT
  public:
      FluColorView(QWidget* parent = nullptr) : QDialog(parent)
      {
          m_parentWidget = parent;

          m_hMainLayout = new QHBoxLayout(this);
          m_windowMask = new QWidget(this);
          m_windowMask->setObjectName("windowMask");

          initContentWidget();


          setWindowFlags(Qt::FramelessWindowHint);
          setAttribute(Qt::WA_TranslucentBackground);
          setGeometry(0, 0, m_parentWidget->width(), m_parentWidget->height());
          m_windowMask->resize(m_parentWidget->size());

          m_parentWidget->installEventFilter(this);
          onThemeChanged();
      }

      void initContentWidget()
      {
          m_widget = new QFrame(this);
          m_widget->setObjectName("centerWidget");
          m_widget->setFixedSize(320, 460);
          m_hMainLayout->addWidget(m_widget, 1, Qt::AlignCenter);
          

          m_vContentWidgetLayout = new QVBoxLayout;
          m_vContentWidgetLayout->setContentsMargins(5, 5, 5, 5);
          
          m_widget->setLayout(m_vContentWidgetLayout);

          auto hLayout = new QHBoxLayout;
          auto colorViewGradient = new FluColorViewGradient;
          colorViewGradient->setFixedSize(256, 256);

          auto colorViewVHandle = new FluColorViewVHandle;
          colorViewVHandle->setFixedSize(45, 256);

          hLayout->addWidget(colorViewGradient);
          hLayout->addWidget(colorViewVHandle);

          m_vContentWidgetLayout->addLayout(hLayout);

          auto colorViewHHandle = new FluColorViewHHandle;
          colorViewHHandle->setFixedHeight(17);
          m_vContentWidgetLayout->addWidget(colorViewHHandle);

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

          m_vContentWidgetLayout->addLayout(hLayout);

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

          m_vContentWidgetLayout->addLayout(hLayout);

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

          m_vContentWidgetLayout->addLayout(hLayout);

          hLayout = new QHBoxLayout;
          auto okBtn = new FluStyleButton;
          okBtn->setText("Ok");
          okBtn->setFixedWidth(150);

          auto cancelBtn = new FluPushButton;
          cancelBtn->setText("cancel");
          cancelBtn->setFixedWidth(150);

          hLayout->addWidget(okBtn);
          //hLayout->addSpacing(15);
          hLayout->addWidget(cancelBtn);

          m_vContentWidgetLayout->addLayout(hLayout);

          connect(okBtn, &FluStyleButton::clicked, this, [=]() { 
              accept();
          });

          connect(cancelBtn, &FluPushButton::clicked, this, [=]() { 
              reject();
          });
      }

      void resizeEvent(QResizeEvent* event)
      {
          QDialog::resizeEvent(event);
          m_windowMask->resize(m_parentWidget->size());
          resize(m_parentWidget->size());
      }

      bool eventFilter(QObject* watched, QEvent* event)
      {
          if (watched == m_parentWidget && event->type() == QEvent::Resize)
          {
              QResizeEvent* resizeEvent = (QResizeEvent*)event;
              m_windowMask->resize(m_parentWidget->size());
              resize(m_parentWidget->size());
              return true;
          }

          return QDialog::eventFilter(watched, event);
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
      QWidget* m_parentWidget;
      QWidget* m_windowMask;

      QHBoxLayout* m_hMainLayout;

      // content widget;
      QFrame* m_widget;
      QVBoxLayout* m_vContentWidgetLayout;
};
