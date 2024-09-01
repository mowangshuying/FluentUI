#pragma once

#include <QComboBox>
#include "../FluUtils/FluStyleSheetUitls.h"
#include <QAbstractItemView>
#include <QStyleOptionComplex>
#include <QProxyStyle>
#include <QPainter>
#include <QStyleOptionComboBox>
#include <QListWidget>
#include <QLabel>
#include <QHBoxLayout>
#include "FluComboBoxTextItem.h"

class FluComboBox : public QComboBox
{
  public:
    FluComboBox(QWidget* parent = nullptr);

  public slots:
    void onThemeChanged();

  protected:
};
