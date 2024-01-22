#pragma once

#include <QCombobox>
#include "../FluUtils/FluStyleSheetUitls.h"
#include <QAbstractItemView>
#include <QStyleOptionComplex>
#include <QProxyStyle>

class FluComboBox :public QComboBox
{
  public:
      FluComboBox(QWidget* parent = nullptr) : QComboBox(parent)
      {
          //SC_ComboBoxArrow;
          setFixedHeight(30);
          view()->window()->setWindowFlags(Qt::Popup | Qt::FramelessWindowHint | Qt::NoDropShadowWindowHint);
          view()->window()->setAttribute(Qt::WA_TranslucentBackground);
          FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluComboBox.qss", this);
      }
};
