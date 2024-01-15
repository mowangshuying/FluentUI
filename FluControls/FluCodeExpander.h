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
        m_wrap2->layout()->setSpacing(0);
        m_wrap2->layout()->addWidget(m_displayCodeBox);
        //  setWrap2Height(m_displayCodeBox->s);
        // setWrap2Height(66);
        // m_wrap2->setFixedHeight(66);
        // connect(m_displayCodeBox, &FluDisplayCodeBox::resize)
        // connect(m_displayCodeBox, &FluDisplayCodeBox::sizeChanged, [=]() {
        //  if (m_bDown)
        //  {
        //      return;
        //  }
        //     m_wrap2->setFixedHeight(8 + m_displayCodeBox->height());
        //  });
    }

    void setCode(QString code)
    {
        m_displayCodeBox->setCode(code);
    }

    void setCodeByPath(QString fileName)
    {
        QString code;

        QFile file(fileName);
        if (file.open(QIODevice::ReadOnly))
        {
            code = file.readAll();
            file.close();
        }

        setCode(code);
    }

    void resizeEvent(QResizeEvent*)
    {
        // setFixedHeight(m_wrap1->height() + m_wrap2->height());
        // m_wrap2->setFixedHeight(m_displayCodeBox->height());
        // setWrap2Height();
        //  setWrap2Height(m_wrap2->sizeHint().height());
    }

  protected:
    FluDisplayCodeBox* m_displayCodeBox;
};
