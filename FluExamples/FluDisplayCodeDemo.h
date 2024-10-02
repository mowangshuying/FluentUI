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
    FluDisplayCodeDemo(QWidget* parent = nullptr) : FluWidget(parent)
    {
        auto display = new FluCodeBox(this);
        display->setFixedSize(300, 50);
        display->move(50, 50);

        QString code = "std::cout << \"hello, world\" << std::endl; // this just a text";
        display->setCodeText(code);
        setStyleSheet("background-color:rgb(249, 249, 249);");
    }
};
