#pragma once

#include <QScrollArea>
#include <QWidget>
#include <QHBoxLayout>
#include "../FluUtils/FluUtils.h"

class FluHScrollView : public QScrollArea
{
    Q_OBJECT
  public:
      FluHScrollView(QWidget* parent = nullptr) : QScrollArea(parent)
      {
          setWidgetResizable(true);
          setMinimumSize(0, 0);

          setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
          m_contextWidget = new QWidget(this);
          setWidget(m_contextWidget);

          m_hMainLayout = new QHBoxLayout(m_contextWidget);
          m_contextWidget->setObjectName("contextWidget");

          FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluHScrollView.qss", this);
          connect(FluThemeUtils::getUtils(), &FluThemeUtils::themeChanged, this, [=](FluTheme theme) { onThemeChanged(); });
      }

        ~FluHScrollView()
      {
      }

      QHBoxLayout* getMainLayout()
      {
          return m_hMainLayout;
      }

    public slots:
      void onThemeChanged()
      {
          if (FluThemeUtils::getUtils()->getTheme() == FluTheme::Light)
          {
              FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluHScrollView.qss", this);
          }
          else
          {
              FluStyleSheetUitls::setQssByFileName("../StyleSheet/dark/FluHScrollView.qss", this);
          }
      }
  protected:
      QWidget* m_contextWidget;
      QHBoxLayout* m_hMainLayout;
};
