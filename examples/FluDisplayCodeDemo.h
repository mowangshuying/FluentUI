#pragma once

#include <QPlainTextEdit>
#include <QSyntaxHighlighter>
#include <QRegularExpression>
#include <QTextCharFormat>

#include "../Utils/FluUtils.h"
#include "../Controls/FluCodeExpander.h"
#include "../Controls/FluCodeBox.h"
#include "FluTemplateDemo.h"

class FluDisplayCodeDemo : public FluWidget
{
    Q_OBJECT
  public:
    FluDisplayCodeDemo(QWidget* parent = nullptr);
};
