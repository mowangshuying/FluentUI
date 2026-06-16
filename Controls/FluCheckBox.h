#pragma once

#include <QCheckBox>
#include "../Utils/FluUtils.h"

class FluCheckBox : public QCheckBox
{
    Q_OBJECT
  public:
    explicit FluCheckBox(QWidget* parent = nullptr);

    explicit FluCheckBox(const QString& text, QWidget* parent = nullptr);

  public slots:
    void onThemeChanged();
};
