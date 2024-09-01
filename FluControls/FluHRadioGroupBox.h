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
    FluHRadioGroupBox(QWidget* parent = nullptr);

    FluHRadioGroupBox(QString title, QWidget* parent = nullptr);

    void addRadioButton(FluRadioButton* radioButton);

  public slots:
    void onThemeChanged();

  protected:
    QVBoxLayout* m_hMainLayout;
};
