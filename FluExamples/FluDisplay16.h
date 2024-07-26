#pragma once

#include "../FluControls/FluWidget.h"
#include "FluTemplateDemo.h"
#include <QGridLayout>

// to display widget max can display 16 wdigets.
class FluDisplay16 : public FluTemplateDemo
{
    Q_OBJECT
  public:
    FluDisplay16(QWidget* parent = nullptr) : FluTemplateDemo(parent)
    {
        auto widget = new FluWidget;
        m_contentLayout->addWidget(widget);

        gridLayout = new QGridLayout;
        widget->setLayout(gridLayout);
        // gridLayout->setSpacing(15);
        // gridLayout->setContentsMargins(0, 0, 0, 0);
        // m_contentLayout->addLayout(gridLayout, 1);
    }

    void addDemo(QWidget* widget)
    {
        if (gridLayout->count() >= 16)
            return;

        int count = gridLayout->count();
        int row = count / 4;
        int col = count % 4;

        gridLayout->addWidget(widget, row, col);
    }

  protected:
    QGridLayout* gridLayout;
};
