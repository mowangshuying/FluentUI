#pragma once

#include "FluExpander.h"
#include "FluWidget.h"
#include "FluCodeBox.h"
#include <QStyleOption>
#include <QPainter>

class FluCodeExpander : public FluExpander
{
    Q_OBJECT
  public:
    FluCodeExpander(QWidget* parent = nullptr);

    void setCodeText(QString code);

    void setCodeByPath(QString fileName);

    void paintEvent(QPaintEvent* event);

  protected:
    FluCodeBox* m_displayCodeBox;
};
