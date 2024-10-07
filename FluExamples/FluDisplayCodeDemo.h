#pragma once

#include <QPlainTextEdit>
#include <QSyntaxHighlighter>
#include <QRegularExpression>
#include <QTextCharFormat>

#include "../FluUtils/FluUtils.h"
#include "../FluControls/FluCodeExpander.h"
#include "../FluControls/FluCodeBox.h"
#include "FluTemplateDemo.h"

class FluDisplayCodeDemo : public FluWidget
{
    Q_OBJECT
  public:
    FluDisplayCodeDemo(QWidget* parent = nullptr);
};
