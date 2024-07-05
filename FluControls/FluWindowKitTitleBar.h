#pragma once

#include <QFrame>
#include <QHBoxLayout>
#include <QSpacerItem>
#include <QLabel>
#include <QPushButton>
#include <QEvent>

class FluWindowKitTitleBar : public QFrame
{
    Q_OBJECT
  public:
    enum FluWKTitleBarItem
    {
        IconButton,
        MenuWidget,
        TitleLabel,
        MinimumButton,
        MaximumButton,
        CloseButton,
    };
  public:
      FluWindowKitTitleBar(QWidget* parent = nullptr);

      void init();

      inline void insertDefaultSpace(int nIndex)
      {
          m_hMainLayout->insertSpacerItem(nIndex, new QSpacerItem(0,0));
      }

      inline QWidget* widgetAt(int nIndex) const
      {
          return m_hMainLayout->itemAt(nIndex)->widget();
      }

      void setWidgetAt(int nIndex, QWidget* widget)
      {
          auto item = m_hMainLayout->takeAt(nIndex);
          auto orgWidget = item->widget();
          if (orgWidget)
          {
              orgWidget->deleteLater();
          }
          delete item;

          if (!widget)
          {
              insertDefaultSpace(nIndex);
          }
          else
          {
              m_hMainLayout->insertWidget(nIndex, widget);
          }
      }

      QWidget* takeWidgetAt(int nIndex)
      {
          auto item = m_hMainLayout->itemAt(nIndex);
          auto orgWidget = item->widget();
          if (orgWidget)
          {
              item = m_hMainLayout->takeAt(nIndex);
              delete item;
              insertDefaultSpace(nIndex);
          }
          
          return orgWidget;
      }

      QPushButton* iconButton() const 
      {
          return static_cast<QPushButton*>(widgetAt(IconButton));
      }

      QLabel* titleLabel() const
      {
          return static_cast<QLabel*>(widgetAt(TitleLabel));
      }

      QPushButton* minButton() const
      {
          return static_cast<QPushButton*>(widgetAt(MinimumButton));
      }

       QPushButton* maxButton() const
      {
          return static_cast<QPushButton*>(widgetAt(MaximumButton));
      }

       QPushButton* closeButton() const
      {
          return static_cast<QPushButton*>(widgetAt(CloseButton));
      }

       void setTitleLabel(QLabel* label)
       {
           auto org = takeTitleLabel();
           if (org)
               org->deleteLater();

           if (!label)
               return;

           setWidgetAt(TitleLabel, label);
           if (m_autoTitle && m_w)
           {
               label->setText(m_w->windowTitle());
           }
           label->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
       }

       void setIconButton(QPushButton* btn)
       {
           auto org = takeIconButton();
           if (org)
               org->deleteLater();
           if (!btn)
               return;
           setWidgetAt(IconButton, btn);
           if (m_autoIcon && m_w)
           {
               btn->setIcon(m_w->windowIcon());
           }

           btn->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
       }

       void setMinButton(QPushButton* btn)
       {
           auto org = takeMinButton();
           if (org)
           {
               org->deleteLater();
           }

           if (!btn)
           {
               return;
           }

           setWidgetAt(MinimumButton, btn);
           connect(btn, &QPushButton::clicked, this, &FluWindowKitTitleBar::minimizeRequested);
       }

       void setMaxButton(QPushButton* btn)
       {
           auto org = takeMaxButton();
           if (org)
           {
               org->deleteLater();
           }

           if (!btn)
               return;

           setWidgetAt(MaximumButton, btn);
           connect(btn, &QPushButton::clicked, this, &FluWindowKitTitleBar::maximizeRequested);
       }

       void setCloseButton(QPushButton* btn)
       {
           auto org = takeCloseButton();
           if (org)
           {
               org->deleteLater();
           }

           if (!btn)
               return;

           setWidgetAt(CloseButton, btn);
           connect(btn, &QPushButton::clicked, this, &FluWindowKitTitleBar::closeRequested);
       }

       QLabel* takeTitleLabel()
       {
           return static_cast<QLabel*>(takeWidgetAt(TitleLabel));
       }

       QPushButton* takeIconButton()
       {
           return static_cast<QPushButton*>(takeWidgetAt(IconButton));
       }

       QPushButton* takeMinButton()
       {
           return static_cast<QPushButton*>(takeWidgetAt(MinimumButton));
       }

       QPushButton* takeMaxButton()
       {
           return static_cast<QPushButton*>(takeWidgetAt(MaximumButton));
       }

       QPushButton* takeCloseButton()
       {
           return static_cast<QPushButton*>(takeWidgetAt(CloseButton));
       }

       QWidget* hostWidget()
       {
           return m_w;
       }

       void setHostWidget(QWidget* w)
       {
           //m_w = w;
           auto org = m_w;
           if (org)
           {
               org->removeEventFilter(this);
           }

           m_w = w;
           if (w)
           {
               w->installEventFilter(this);
           }
       }

       bool iconFollowWindow()
       {
           return m_autoIcon;
       }

       void setIconFollowWindow(bool value)
       {
           m_autoIcon = value;
       }


       void titleChanged(const QString& text)
       {
           Q_UNUSED(text);
       }

       void iconChanged(const QIcon& icon)
       {
           Q_UNUSED(icon);
       }


       bool eventFilter(QObject* watched, QEvent* event)
       {
           auto w = m_w;
           if (watched == w)
           {
               QAbstractButton* iconBtn = iconButton();
               QLabel* label = titleLabel();
               QAbstractButton* maxBtn = maxButton();
               switch (event->type())
               {
                   case QEvent::WindowIconChange:
                   {
                       if (m_autoIcon && iconButton())
                       {
                           iconBtn->setIcon(w->windowIcon());
                           iconChanged(w->windowIcon());
                       }
                       break;
                   }
                   case QEvent::WindowTitleChange:
                   {
                       if (m_autoIcon && label)
                       {
                           label->setText(w->windowTitle());
                           titleChanged(w->windowTitle());
                       }
                       break;
                   }
                   case QEvent::WindowStateChange:
                   {
                       if (maxButton())
                       {
                           maxButton()->setChecked(w->isMaximized());
                       }
                       break;
                   }
                   default:
                       break;
               }
           }

           return QWidget::eventFilter(watched, event);
       }

  signals:
       void minimizeRequested();
       void maximizeRequested(bool max = false);
       void closeRequested();
  protected:
      QHBoxLayout* m_hMainLayout;
      QWidget* m_w;

      bool m_autoTitle;
      bool m_autoIcon;
};
