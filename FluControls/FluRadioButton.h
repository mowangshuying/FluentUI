#pragma once

#include <QRadioButton>
#include "../FluUtils/FluUtils.h"
#include <QProxyStyle>
#include <QPainter>
#include <QStyleOptionButton>

class FluRadioButton : public QRadioButton
{
    Q_OBJECT
  public:
    explicit FluRadioButton(QWidget* parent = nullptr);

    explicit FluRadioButton(const QString& text, QWidget* parent = nullptr);

  public slots:
    void onThemeChanged();
};
