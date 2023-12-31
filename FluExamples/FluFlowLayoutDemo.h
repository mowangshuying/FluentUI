#pragma once

#include <QWidget>
#include "../FluControls/FluFlowLayout.h"
#include <QPushButton>
#include "../FluControls/FluVScrollView.h"

// take it from Qt examples
class FluFlowLayoutDemo : public FluVScrollView
{
  public:
    FluFlowLayoutDemo(QWidget* parent = nullptr) : FluVScrollView(parent)
    {
        FluFlowLayout* flowLayout = new FluFlowLayout;
        auto btn1 = new QPushButton(tr("Short"));
        auto btn2 = new QPushButton(tr("Short"));
        auto btn3 = new QPushButton(tr("Short"));
        auto btn4 = new QPushButton(tr("Short"));
        auto btn5 = new QPushButton(tr("Short"));
        flowLayout->addWidget(btn1);
        flowLayout->addWidget(btn2);
        flowLayout->addWidget(btn3);
        flowLayout->addWidget(btn4);
        flowLayout->addWidget(btn5);
        // setLayout(flowLayout);

        m_vMainLayout->addLayout(flowLayout);
        setWindowTitle(tr("Flow Layout"));
    }
};
