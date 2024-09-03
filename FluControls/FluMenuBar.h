#pragma once

#include <QMenuBar>
#include "../FluUtils/FluUtils.h"
#include <QPainter>
#include <QStyleOption>
#include <QHBoxLayout>
#include <QVBoxLayout>

class FluMenuBar : public QMenuBar
{
    Q_OBJECT
  public:
    FluMenuBar(QWidget* parent = nullptr);

  public slots:
    void onThemeChanged();
};
