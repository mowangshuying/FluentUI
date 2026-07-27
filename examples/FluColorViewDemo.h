#pragma once

#include "FluTemplateDemo.h"
#include "../controls/FluColorViewGradient.h"
#include "../controls/FluColorViewVHandle.h"
#include "../controls/FluColorViewHHandle.h"
#include "../controls/FluLabel.h"
#include "../controls/FluLineEdit.h"
#include "../controls/FluColorView.h"
#include "../controls/FluPushButton.h"

class FluColorViewDemo : public FluTemplateDemo
{
    Q_OBJECT
  public:
    FluColorViewDemo(QWidget* parent = nullptr);
};
