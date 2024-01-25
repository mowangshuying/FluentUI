#pragma once

#include <QPushButton>
#include <QWidget>
#include <QHBoxLayout>
#include "../FluUtils/FluUtils.h"
#include <QStyleOption>
#include <QPainter>
#include "FluMenu.h"
#include <QIcon>

class FluDropDownButton : public QWidget 
{
	Q_OBJECT
  public:
      FluDropDownButton(QWidget* parent = nullptr) : QWidget(parent)
      {
          m_hMainLayout = new QHBoxLayout;
          m_hMainLayout->setContentsMargins(3, 3, 3, 3);
          m_hMainLayout->setSpacing(0);

          setLayout(m_hMainLayout);

          // add text and icon
          m_textBtn = new QPushButton;
          m_iconBtn = new QPushButton;

          m_textBtn->setObjectName("textBtn");
          m_iconBtn->setObjectName("iconBtn");

          m_iconBtn->setFixedSize(24, 24);
          m_textBtn->setFixedHeight(24);

          m_iconBtn->setFixedSize(24, 24);
          m_iconBtn->setIcon(FluIconUtils::getFluentIcon(FluAwesomeType::ChevronDown));

          m_hMainLayout->addWidget(m_textBtn, 1);
          m_hMainLayout->addSpacing(3);
          m_hMainLayout->addWidget(m_iconBtn);
          setFixedHeight(30);

          m_menu = new FluMenu;

          connect(m_textBtn, &QPushButton::clicked, [=](bool b) { emit clicked(); });
          connect(m_iconBtn, &QPushButton::clicked, [=](bool b) { emit clicked(); });
          connect(this, &FluDropDownButton::clicked, [=]() {
                QPoint leftBottomPos = rect().bottomLeft();
                leftBottomPos = mapToGlobal(leftBottomPos);
                leftBottomPos.setY(leftBottomPos.y() + 3);
                m_menu->exec(leftBottomPos);
              //  m_menu->show();
          });

          FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluDropDownButton.qss", this);
      }

      QPushButton* getTextBtn()
      {
          return m_textBtn;
      }

      QPushButton* getIconBtn()
      {
          return m_iconBtn;
      }

      void setText(QString text)
      {
          m_textBtn->setText(text);
      }

      void addTextItem(QString text)
      {
          m_menu->addAction(new QAction(text));
      }

      void addIconTextItem(QIcon icon, QString text)
      {
          m_menu->addAction(new QAction(icon, text));
      }

    //  void mousePressedEvent(QMouseEvent* event)
    //  {

    //  }

      void mouseReleaseEvent(QMouseEvent* e)
      {
        //  QPoint leftBottomPos = rect().bottomLeft();
        //  leftBottomPos = mapToGlobal(leftBottomPos);
        //  leftBottomPos.setY(leftBottomPos.y() + 3);
        //  m_menu->exec(leftBottomPos);
        //  m_menu->show();
          emit clicked();
      }

      void paintEvent(QPaintEvent* event)
      {
          QStyleOption opt;
          opt.initFrom(this);
          QPainter painter(this);
          style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
      }
signals:
      void clicked();
  protected:
    QPushButton* m_textBtn;
    QPushButton* m_iconBtn;
    QHBoxLayout* m_hMainLayout;
    FluMenu* m_menu;
};
