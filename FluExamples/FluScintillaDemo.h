#pragma once

#include "FluTemplateDemo.h"
#include "../FluControls/FluScrollDelegate.h"
#include <Qsci/qsciscintilla.h>
#include <Qsci/qscilexercpp.h>

class FluScintillaDemo : public FluTemplateDemo
{
    Q_OBJECT
  public:
    FluScintillaDemo(QWidget* parent = nullptr);
};