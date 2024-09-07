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
    FluVRadioGroupBox(QWidget* parent = nullptr);

    FluVRadioGroupBox(QString title, QWidget* parent = nullptr);

    void addRadioButton(FluRadioButton* radioButton);

  public slots:
    void onThemeChanged();

  protected:
    QVBoxLayout* m_vMainLayout;
};
