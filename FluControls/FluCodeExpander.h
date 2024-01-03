#pragma once

#include "FluExpander.h"
#include <QWidget>
#include "FluDisplayCodeBox.h"

class FluCodeExpander : public FluExpander
{
    Q_OBJECT
  public:
    FluCodeExpander(QWidget* parent = nullptr) : FluExpander(parent)
    {
        m_displayCodeBox = new FluDisplayCodeBox;
        m_displayCodeBox->setProperty("transparent", true);
        m_wrap2->layout()->setContentsMargins(4, 4, 4, 4);
        m_wrap2->layout()->addWidget(m_displayCodeBox);
    }

    void setCode(QString code)
    {
        m_displayCodeBox->setCode(code);
    }

  protected:
    FluDisplayCodeBox* m_displayCodeBox;
};
