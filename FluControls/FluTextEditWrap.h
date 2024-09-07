#pragma once

#include <QWidget>
#include <QEvent>
#include <QResizeEvent>
#include "../FluUtils/FluUtils.h"
#include "FluTextEdit.h"

class FluTextEditWrap : public QWidget
{
    Q_OBJECT
  public:
    FluTextEditWrap(FluTextEdit* parent = nullptr);

    bool eventFilter(QObject* watched, QEvent* event);

    void paintEvent(QPaintEvent* event);

  protected:
    FluTextEdit* m_textEdit;
};
