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
    FluCodeExpander(QWidget* parent = nullptr) : FluExpander(parent)
    {
        m_displayCodeBox = new FluCodeBox;
        m_displayCodeBox->setProperty("transparent", true);
        m_wrap2->layout()->addWidget(m_displayCodeBox);
    }

    void setCodeText(QString code)
    {
        m_displayCodeBox->setCodeText(code);
    }

    void setCodeByPath(QString fileName)
    {
        QString code;

        QFile file(fileName);
        if (file.open(QIODevice::ReadOnly))
        {
            code = file.readAll();
            file.close();
            setCodeText(code);
            return;
        }

        LOG_ERR << "open code file failed: " << fileName;
    }

    void paintEvent(QPaintEvent* event)
    {
        QStyleOption opt;
        opt.initFrom(this);
        QPainter painter(this);
        style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
    }

  protected:
    FluCodeBox* m_displayCodeBox;
};
