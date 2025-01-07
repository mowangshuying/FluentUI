#pragma once

#include "FluTemplateDemo.h"
#include "../FluControls/FluShortcutPicker.h"

class FluShortcutPickerDemo : public FluTemplateDemo
{
    Q_OBJECT
  public:
    FluShortcutPickerDemo(QWidget* parent = nullptr) : FluTemplateDemo(parent)
    {
        m_contentLayout->setAlignment(Qt::AlignCenter);
        auto picker = new FluShortcutPicker;
        m_contentLayout->addWidget(picker);
    }
};
