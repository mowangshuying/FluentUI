#pragma once

#include "FluExpander.h"
#include "../FluUtils/FluUtils.h"
#include <QVBoxLayout>
#include "FluVSplitLine.h"

class FluIntructions : public FluExpander
{
    Q_OBJECT
  public:
    FluIntructions(QWidget* parent = nullptr) : FluExpander(parent)
    {
        m_titleLabel = new QLabel;
        m_titleLabel->setObjectName("wrap1TitleLabel");
        m_titleLabel->setWordWrap(true);
        getWrap1Layout()->addWidget(m_titleLabel);
    }

    QLabel* getTitleLabel()
    {
        return m_titleLabel;
    }

    void setTitleLabelText(QString text)
    {
        m_titleLabel->setText(text);
    }

    void addTitleContent(QString title, QString content)
    {
        auto titleLabel = new QLabel;
        titleLabel->setObjectName("wrap2TitleLabel");
        titleLabel->setWordWrap(true);
        auto contentLabel = new QLabel;
        contentLabel->setObjectName("wrap2ContentLabel");
        contentLabel->setWordWrap(true);
        getWrap2Layout()->addWidget(titleLabel);
        getWrap2Layout()->addWidget(contentLabel);
    }

    void addVSplitLine()
    {
        getWrap2Layout()->addWidget(new FluVSplitLine);
    }

protected:
    QLabel* m_titleLabel;
};
