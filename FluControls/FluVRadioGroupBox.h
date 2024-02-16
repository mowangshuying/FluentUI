#pragma once

#include <QButtonGroup>
#include <QGroupBox>
#include "../FluUtils/FluUtils.h"
#include <QVBoxLayout>
#include "FluRadioButton.h"
class FluVRadioGroupBox : public QGroupBox
{
    Q_OBJECT
  public:
    FluVRadioGroupBox(QWidget* parent = nullptr) : QGroupBox(parent)
    {
        m_vMainLayout = new QVBoxLayout;
        // m_vMainLayout->setContentsMargins(0,0,0,0);

        setLayout(m_vMainLayout);
        m_vMainLayout->addSpacing(15);
        FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluVRadioGroupBox.qss", this);
    }

    FluVRadioGroupBox(QString title, QWidget* parent = nullptr) : QGroupBox(title, parent)
    {
        m_vMainLayout = new QVBoxLayout;
        // m_vMainLayout->setContentsMargins(5, 5, 5, 5);
        // m_vMainLayout->setContentsMargins(0, 0, 0, 0);
        setLayout(m_vMainLayout);
        m_vMainLayout->addSpacing(15);
        FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluVRadioGroupBox.qss", this);
    }

    void addRadioButton(FluRadioButton* radioButton)
    {
        m_vMainLayout->addWidget(radioButton);
    }

  protected:
    QVBoxLayout* m_vMainLayout;
};
