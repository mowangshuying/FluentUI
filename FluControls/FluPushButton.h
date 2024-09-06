#pragma once

#include <QPaintEvent>
#include <QPainter>
#include <QPushButton>

#include "../FluUtils/FluUtils.h"

class FluPushButton : public QPushButton
{
    Q_OBJECT
  public:
    FluPushButton(QWidget *parent = nullptr);

    FluPushButton(const QString &text, QWidget *parent = nullptr);
  public slots:
    void onThemeChanged();

  protected:
};