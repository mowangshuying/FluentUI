#pragma once

#include "FluTemplateDemo.h"
#include "../Controls/FluColorViewGradient.h"
#include "../Controls/FluColorViewVHandle.h"
#include "../Controls/FluColorViewHHandle.h"
#include "../Controls/FluLabel.h"
#include "../Controls/FluLineEdit.h"
#include "../Controls/FluColorView.h"
#include "../Controls/FluPushButton.h"

class FluColorViewDemo : public FluTemplateDemo
{
    Q_OBJECT
  public:
    FluColorViewDemo(QWidget* parent = nullptr);
};
