#include "FluDisplay16.h"

FluDisplay16::FluDisplay16(QWidget* parent /*= nullptr*/) : FluTemplateDemo(parent)
{
    auto widget = new FluWidget;
    m_contentLayout->addWidget(widget);

    gridLayout = new QGridLayout;
    widget->setLayout(gridLayout);
    // gridLayout->setSpacing(15);
    // gridLayout->setContentsMargins(0, 0, 0, 0);
    // m_contentLayout->addLayout(gridLayout, 1);
}

void FluDisplay16::addDemo(QWidget* widget)
{
    if (gridLayout->count() >= 16)
        return;

    int count = gridLayout->count();
    int row = count / 4;
    int col = count % 4;

    gridLayout->addWidget(widget, row, col);
}
