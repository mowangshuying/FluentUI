#pragma once

#include <QGroupBox>
#include <QButtonGroup>
#include <QGroupBox>
#include "../FluUtils/FluUtils.h"
#include <QVBoxLayout>
#include "FluRadioButton.h"

class FluHRadioGroupBox : public QGroupBox
{
    Q_OBJECT
  public:
    FluHRadioGroupBox(QWidget* parent = nullptr) : QGroupBox(parent)
    {
        m_hMainLayout = new QVBoxLayout;
        // m_vMainLayout->setContentsMargins(0,0,0,0);

        setLayout(m_hMainLayout);
        m_hMainLayout->addSpacing(15);
        FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluVRadioGroupBox.qss", this);
        connect(FluThemeUtils::getUtils(), &FluThemeUtils::themeChanged, [=](FluTheme theme) { onThemeChanged(); });
    }

    FluHRadioGroupBox(QString title, QWidget* parent = nullptr) : QGroupBox(title, parent)
    {
        m_hMainLayout = new QVBoxLayout;
        // m_vMainLayout->setContentsMargins(5, 5, 5, 5);
        // m_vMainLayout->setContentsMargins(0, 0, 0, 0);
        setLayout(m_hMainLayout);
        m_hMainLayout->addSpacing(15);
        FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluVRadioGroupBox.qss", this);
        connect(FluThemeUtils::getUtils(), &FluThemeUtils::themeChanged, [=](FluTheme theme) { onThemeChanged(); });
    }

    void addRadioButton(FluRadioButton* radioButton)
    {
        m_hMainLayout->addWidget(radioButton);
    }

  public slots:
    void onThemeChanged()
    {
        if (FluThemeUtils::getUtils()->getTheme() == FluTheme::Light)
        {
            FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluVRadioGroupBox.qss", this);
        }
        else
        {
            FluStyleSheetUitls::setQssByFileName("../StyleSheet/dark/FluVRadioGroupBox.qss", this);
        }
    }

  protected:
    QVBoxLayout* m_hMainLayout;
};
