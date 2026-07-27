#include "FluCodeExpander.h"

FluCodeExpander::FluCodeExpander(QWidget* parent /*= nullptr*/) : FluExpander(parent)
{
    m_displayCodeBox = new FluCodeBox;
    m_displayCodeBox->setProperty("transparent", true);
    m_wrap2->layout()->addWidget(m_displayCodeBox);
}

void FluCodeExpander::setCodeText(QString code)
{
    m_displayCodeBox->setCodeText(code);
}

void FluCodeExpander::setCodeByPath(QString fileName)
{
    QString code;

#ifdef USE_QRC
    fileName = fileName.replace("../code/", ":/code/");
#endif

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

void FluCodeExpander::paintEvent(QPaintEvent* event)
{
    QStyleOption opt;
    opt.initFrom(this);
    QPainter painter(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
}
