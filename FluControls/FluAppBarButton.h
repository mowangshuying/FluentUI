#pragma once

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QStyleOption>
#include <QPainter>
#include <QVBoxLayout>
#include <QShortcut>
#include <QKeySequence>

#include "../FluUtils/FluUtils.h"

class FluAppBarButton : public QWidget
{
    Q_OBJECT
  public:
    FluAppBarButton(FluAwesomeType awesomeType, QWidget* parent = nullptr) : QWidget(parent), m_awesomeType(awesomeType), m_shortCut(nullptr)
      {
          m_vMainLayout = new QVBoxLayout;
          setLayout(m_vMainLayout);

         // m_vMainLayout->setContentsMargins(5, 5, 5, 5);
          m_vMainLayout->setAlignment(Qt::AlignHCenter);

          setFixedSize(70, 50);

          // icon and text;
          m_iconBtn = new QPushButton;
          //m_iconBtn->setFixedSize(25, 25);
          m_iconBtn->setIconSize(QSize(20, 20));
          m_iconBtn->setObjectName("iconBtn");
          m_vMainLayout->addWidget(m_iconBtn);

          m_textLabel = new QLabel;
          m_textLabel->setAlignment(Qt::AlignHCenter);
          m_textLabel->setObjectName("textLabel");
          m_vMainLayout->addWidget(m_textLabel);

          m_iconBtn->setIcon(FluIconUtils::getFluentIconPixmap(awesomeType, FluThemeUtils::getUtils()->getTheme()));
          FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluAppBarButton.qss", this);
          connect(FluThemeUtils::getUtils(), &FluThemeUtils::themeChanged, [=](FluTheme theme) { onThemeChanged(); });
      }

      void setAwesomeType(FluAwesomeType awesomeType)
      {
          m_awesomeType = awesomeType;
      }

      FluAwesomeType getAwesomeType()
      {
          return m_awesomeType;
      }

      void setText(QString text)
      {
          m_textLabel->setText(text);
      }

      QString getText()
      {
          return m_textLabel->text();
      }

      void setShortCut(QKeySequence keySequence)
      {
          if (m_shortCut != nullptr)
              delete m_shortCut;

          m_shortCut = new QShortcut(this);
          m_shortCut->setKey(keySequence);
          m_shortCut->setContext(Qt::ApplicationShortcut);
          connect(m_shortCut, &QShortcut::activated, [=]() { 
              emit clicked();
              LOG_DEBUG << "called";
          });
      }

      void mouseReleaseEvent(QMouseEvent* event)
      {
          QWidget::mouseReleaseEvent(event);
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
    public slots:
      void onThemeChanged()
      {
          if (FluThemeUtils::getUtils()->getTheme() == FluTheme::Light)
          {
              m_iconBtn->setIcon(FluIconUtils::getFluentIcon(m_awesomeType, FluTheme::Light));
              FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluAppBarButton.qss", this);
          }
          else
          {
              m_iconBtn->setIcon(FluIconUtils::getFluentIcon(m_awesomeType, FluTheme::Dark));
              FluStyleSheetUitls::setQssByFileName("../StyleSheet/dark/FluAppBarButton.qss", this);
          }
      }
 protected:
      FluAwesomeType m_awesomeType;
      QVBoxLayout* m_vMainLayout;
      QPushButton* m_iconBtn;
      QLabel* m_textLabel;

      QShortcut* m_shortCut;
};
