#pragma once

#include "../FluUtils/FluUtils.h"
#include "../FluControls/FluMenu.h"

#include <QWidget>
#include <QVBoxLayout>
#include <QMenu>
#include <QHBoxLayout>

#include <QLabel>
#include <QFrame>
#include <QWidgetAction>
#include <QContextMenuEvent>
#include <QPropertyAnimation>

class FluMenuDemoItem : public QFrame
{
    Q_OBJECT
  public:
      FluMenuDemoItem(QWidget* parent = nullptr) : QFrame(parent)
      {
          m_hMainLayout = new QHBoxLayout;
          setFixedHeight(30);
          m_hMainLayout->setSpacing(0);
          setLayout(m_hMainLayout);
          m_hMainLayout->setContentsMargins(4,4,4,4);


          m_iconLabel = new QLabel;
          m_iconLabel->setFixedSize(18, 18);
          QPixmap pixmap = FluIconUtils::getFluentIconPixmap(FluAwesomeType::Cut);
          pixmap = pixmap.scaled(18, 18, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
          m_iconLabel->setPixmap(pixmap);
          m_iconLabel->setObjectName("iconLabel");

          m_hMainLayout->addWidget(m_iconLabel);
          m_hMainLayout->addSpacing(10);

          m_textLabel = new QLabel;
          m_textLabel->setText("aaa-aaa");
          m_textLabel->setObjectName("textLabel");
          m_hMainLayout->addWidget(m_textLabel);

         // m_hMainLayout->addStretch();
          m_hMainLayout->addSpacing(35);

          m_shortcutKeysLabel = new QLabel;
          m_shortcutKeysLabel->setText("bbb-bbb");
          m_shortcutKeysLabel->setObjectName("shortcutKeysLabel");
          m_hMainLayout->addWidget(m_shortcutKeysLabel, 0,  Qt::AlignRight);
      }


      QLabel* getIconLabel()
      {
          return m_iconLabel;
      }

      QLabel* getTextLabel()
      {
          return m_textLabel;
      }

      QLabel* getShortcutKeysLabel()
      {
          return m_shortcutKeysLabel;
      }

    protected:
      QHBoxLayout* m_hMainLayout;
      QLabel* m_iconLabel;
      QLabel* m_textLabel;
      QLabel* m_shortcutKeysLabel;
};

class FluMenuDemo : public QWidget
{
    Q_OBJECT
    public:
        FluMenuDemo(QWidget* parent = nullptr) : QWidget(parent)
        {
           m_menu = new FluMenu(this);

         ///*  m_menu->setWindowFlags(m_menu->windowFlags() | Qt::FramelessWindowHint | Qt::NoDropShadowWindowHint);
         //  m_menu->setAttribute(Qt::WA_TranslucentBackground, true);*/

           auto item1 = new FluMenuDemoItem(m_menu);
           item1->getTextLabel()->setText("Share");
           item1->getShortcutKeysLabel()->setText("Ctrl+S");
           auto action1 = new QWidgetAction(m_menu);
           action1->setDefaultWidget(item1);
           m_menu->addAction(action1);

           auto item2 = new FluMenuDemoItem(m_menu);
           item2->getTextLabel()->setText("Copy");
           item2->getShortcutKeysLabel()->setText("Ctrl+C");
           auto action2 = new QWidgetAction(m_menu);
           action2->setDefaultWidget(item2);
           m_menu->addAction(action2);

           auto item3 = new FluMenuDemoItem(m_menu);
           item3->getTextLabel()->setText("Delete");
           item3->getShortcutKeysLabel()->setText("Delete");
           auto action3 = new QWidgetAction(m_menu);
           action3->setDefaultWidget(item3);
           m_menu->addAction(action3);

           auto item4 = new FluMenuDemoItem(m_menu);
           item4->getTextLabel()->setText("More");
           item4->getShortcutKeysLabel()->setText("More");
           auto action4 = new QWidgetAction(m_menu);
           action4->setDefaultWidget(item4);
           m_menu->addAction(action4);

           m_menu->addSeparator();

           auto subMenu = new FluMenu(m_menu);
           action4->setMenu(subMenu);
           //("More", m_menu);
           //subMenu->setTitle("More");
          // subMenu->setTitle("More");
          // subMenu->setWindowFlags(m_menu->windowFlags() | Qt::FramelessWindowHint | Qt::NoDropShadowWindowHint);
          // subMenu->setAttribute(Qt::WA_TranslucentBackground, true);

           auto item41 = new FluMenuDemoItem(m_menu);
           item41->getTextLabel()->setText("Share");
           item41->getShortcutKeysLabel()->setText("Ctrl+S");
           auto action41 = new QWidgetAction(m_menu);
           action41->setDefaultWidget(item41);
           subMenu->addAction(action41);

           auto item42 = new FluMenuDemoItem(m_menu);
           item42->getTextLabel()->setText("Copy");
           item42->getShortcutKeysLabel()->setText("Ctrl+C");
           auto action42 = new QWidgetAction(m_menu);
           action42->setDefaultWidget(item42);
           subMenu->addAction(action42);

           auto item43 = new FluMenuDemoItem(m_menu);
           item43->getTextLabel()->setText("Delete");
           item43->getShortcutKeysLabel()->setText("Delete");
           auto action43 = new QWidgetAction(m_menu);
           action43->setDefaultWidget(item43);
           subMenu->addAction(action43);

          // m_menu->addMenu(subMenu);

           // the ani
           m_animation = new QPropertyAnimation(m_menu, "geometry");
           m_animation->setDuration(500);

           connect(m_menu, &QMenu::aboutToShow, [=]() { m_animation->start();
               });

           setStyleSheet("background-color:white;");
        }

        void contextMenuEvent(QContextMenuEvent* event)
        {
          // m_animation->setStartValue(QRect(event->globalPos(), QSize(m_menu->sizeHint().width(), 0)));
          // m_animation->setEndValue(QRect(event->globalPos(), QSize(m_menu->sizeHint())));
          // m_animation->start();
           m_menu->exec(event->globalPos());
        //   m_animation->start();
        }

   protected:
     FluMenu* m_menu;
     QPropertyAnimation* m_animation;
};
