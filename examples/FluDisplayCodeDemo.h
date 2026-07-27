#pragma once

#include <QPlainTextEdit>
#include <QSyntaxHighlighter>
#include <QRegularExpression>
#include <QTextCharFormat>

#include "../utils/FluUtils.h"
#include "../controls/FluCodeExpander.h"
#include "../controls/FluCodeBox.h"
#include "FluTemplateDemo.h"

class FluDisplayCodeDemo : public FluWidget
{
    Q_OBJECT
  public:
    FluDisplayCodeDemo(QWidget* parent = nullptr);
};
