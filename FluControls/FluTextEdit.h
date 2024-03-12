#pragma once

#include <QTextEdit>
#include "../FluUtils/FluUtils.h"

class FluTextEdit : public QTextEdit
{
	Q_OBJECT
  public:
	  FluTextEdit(QWidget* parent = nullptr) : QTextEdit(parent)
	  {
           FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluTextEdit.qss", this);
	  }
};
