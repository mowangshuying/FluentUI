#pragma 

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include "../FluUtils/FluUtils.h"
#include <QStyleOption>
#include <QPainter>

enum class FluShortInfoBarType
{
    Info,
    Suc,
    Warn,
    Error,
};

class FluShortInfoBar : public QWidget
{
    Q_OBJECT
  public:
      FluShortInfoBar(FluShortInfoBarType infobarType, QWidget* parent = nullptr);


      void setInfoBarTypeProperty(QString infoBarType)
      {
          setProperty("infoBarType", infoBarType);
          m_iconLabel->setProperty("infoBarType", infoBarType);
          m_infoLabel->setProperty("infoBarType", infoBarType);
          m_closeBtn->setProperty("infoBarType", infoBarType);
          style()->polish(this);
          m_iconLabel->style()->polish(this);
          m_infoLabel->style()->polish(this);
          m_closeBtn->style()->polish(this);
      }

      void updateInfoBarTypeProperty(FluShortInfoBarType infoBarType)
      {
          switch (infoBarType)
          {
              case FluShortInfoBarType::Info:
                  setInfoBarTypeProperty("Info");
                  m_iconLabel->setPixmap(FluIconUtils::getFluentIconPixmap(FluAwesomeType::Info, QColor(239, 239, 239), 18, 18));
                  break;
              case FluShortInfoBarType::Suc:
                  setInfoBarTypeProperty("Suc");
                  m_iconLabel->setPixmap(FluIconUtils::getFluentIconPixmap(FluAwesomeType::CheckMark, QColor(239, 239, 239), 18, 18));
                  break;
              case FluShortInfoBarType::Warn:
                  setInfoBarTypeProperty("Warn");
                  m_iconLabel->setPixmap(FluIconUtils::getFluentIconPixmap(FluAwesomeType::Info, QColor(239, 239, 239), 18, 18));
                  break;
              case FluShortInfoBarType::Error:
                  setInfoBarTypeProperty("Error");
                  m_iconLabel->setPixmap(FluIconUtils::getFluentIconPixmap(FluAwesomeType::ChromeClose, QColor(239, 239, 239), 18, 18));
                  break;
              default:
                  break;
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
      QHBoxLayout* m_hMainLayout;
      QLabel* m_iconLabel;
      QLabel* m_infoLabel;
      QPushButton* m_closeBtn;
};
