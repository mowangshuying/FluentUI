#pragma once

#include <QWidget>
#include <QPushButton>
#include "../FluUtils/FluUtils.h"
#include <QStyleOption>
#include <QPainter>
#include "FluMenu.h"
#include <QIcon>

class FluComboBoxEx : public QWidget
{
    Q_OBJECT
  public:
      FluComboBoxEx(QWidget* parent = nullptr) : QWidget(parent)
      {
          //m_nMaxTextLen = 0;
          m_textAwesomeType = FluAwesomeType::None;
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

         // m_textBtn->setAlignment(Qt::AlignLeft);

          m_iconBtn->setFixedSize(24, 24);
          m_iconBtn->setIcon(FluIconUtils::getFluentIcon(FluAwesomeType::ChevronDown));

          m_hMainLayout->addWidget(m_textBtn, 1);
          m_hMainLayout->addSpacing(3);
          m_hMainLayout->addWidget(m_iconBtn);
          setFixedHeight(30);

          m_menu = new FluMenu;

          connect(m_textBtn, &QPushButton::clicked, [=](bool b) { emit clicked(); });
          connect(m_iconBtn, &QPushButton::clicked, [=](bool b) { emit clicked(); });
          connect(this, &FluComboBoxEx::clicked, [=]() {
              QPoint leftBottomPos = rect().bottomLeft();
              leftBottomPos = mapToGlobal(leftBottomPos);
              leftBottomPos.setY(leftBottomPos.y() + 3);
              m_menu->setMinimumWidth(width());
              m_menu->exec(leftBottomPos);
          });

          FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluComboBoxEx.qss", this);
          connect(FluThemeUtils::getUtils(), &FluThemeUtils::themeChanged, [=](FluTheme theme) { onThemeChanged(); });
          connect(m_menu, &FluMenu::triggered, [=](QAction* action) { 
              m_textBtn->setText(action->text());
              emit currentTextChanged(action->text());
              int nIndex = 0;
              for (auto tmpAct : m_menu->actions())
              {
                  if (tmpAct == action)
                  {
                      break;
                  }

                  nIndex++;
              }
              emit currentIndexChanged(nIndex);
          });
      }

      QPushButton* getTextBtn()
      {
          return m_textBtn;
      }

      QPushButton* getIconBtn()
      {
          return m_iconBtn;
      }

      void setIcon(FluAwesomeType type)
      {
          m_textAwesomeType = type;
          m_textBtn->setIconSize(QSize(18, 18));
          m_textBtn->setIcon(FluIconUtils::getFluentIconPixmap(type, FluThemeUtils::getUtils()->getTheme()));
      }

      void setText(QString text)
      {
          m_textBtn->setText(text);
      }

      void addItem(QString text)
      {
          addTextItem(text);
      }

      void addItem(FluAwesomeType type, QString text)
      {
          addIconTextItem(type, text);
      }

      void addTextItem(QString text)
      {
          m_menu->addAction(new FluAction(text));
          if (m_menu->actions().size() == 1)
              m_textBtn->setText(text);
      }

      void addIconTextItem(FluAwesomeType type, QString text)
      {
          m_menu->addAction(new FluAction(type, text));
          if (m_menu->actions().size() == 1)
              m_textBtn->setText(text);
      }

      void mouseReleaseEvent(QMouseEvent* e)
      {
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
      void currentTextChanged(QString text);
      void currentIndexChanged(int nIndex);
    public slots:
      void onThemeChanged()
      {
          if (FluThemeUtils::getUtils()->getTheme() == FluTheme::Light)
          {
              m_iconBtn->setIcon(FluIconUtils::getFluentIcon(FluAwesomeType::ChevronDown, FluTheme::Light));
              if (m_textAwesomeType != FluAwesomeType::None)
                  m_textBtn->setIcon(FluIconUtils::getFluentIcon(m_textAwesomeType, FluTheme::Light));
              FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluComboBoxEx.qss", this);
          }
          else
          {
              m_iconBtn->setIcon(FluIconUtils::getFluentIcon(FluAwesomeType::ChevronDown, FluTheme::Dark));
              if (m_textAwesomeType != FluAwesomeType::None)
                  m_textBtn->setIcon(FluIconUtils::getFluentIcon(m_textAwesomeType, FluTheme::Dark));
              FluStyleSheetUitls::setQssByFileName("../StyleSheet/dark/FluComboBoxEx.qss", this);
          }
      }

    protected:
      QPushButton* m_textBtn;
      QPushButton* m_iconBtn;  // dropdown button;

      FluAwesomeType m_textAwesomeType;
      //  FluAwesomeType* m_iconAwesomeType;

      QHBoxLayout* m_hMainLayout;
      FluMenu* m_menu;

    //  QString m_sText;
};
