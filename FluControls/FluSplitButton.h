#pragma once

#include <QWidget>
#include <QPushButton>
#include <QHBoxLayout>
#include "../FluUtils/FluUtils.h"

class FluSplitButton : public QWidget
{
    Q_OBJECT
  public:
      FluSplitButton(QWidget* parent = nullptr) : QWidget(parent)
      {
          m_hMainLayout = new QHBoxLayout;
          setLayout(m_hMainLayout);

          m_hMainLayout->setContentsMargins(0, 0, 0, 0);
          m_hMainLayout->addWidget(m_dropDownBtn);
          m_hMainLayout->addWidget(m_textBtn);
          FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluSplitButton.qss", this);
          connect(FluThemeUtils::getUtils(), &FluThemeUtils::themeChanged, [=](FluTheme theme) { onThemeChanged(); });
      }

  public slots:
      void onThemeChanged()
      {
          if (FluThemeUtils::getUtils()->getTheme() == FluTheme::Light)
          {
              FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluSplitButton.qss", this);
          }
          else
          {
              FluStyleSheetUitls::setQssByFileName("../StyleSheet/dark/FluSplitButton.qss", this);
          }
      }

  protected:
      QHBoxLayout* m_hMainLayout;
      QPushButton* m_dropDownBtn;
      QPushButton* m_textBtn;
};
