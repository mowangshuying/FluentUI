#pragma once

#include <QPlainTextEdit>
#include <QSyntaxHighlighter>
#include <QRegularExpression>
#include <QTextCharFormat>

#include "../FluUtils/FluUtils.h"
#include "../FluControls/FluCodeExpander.h"
#include "../FluControls/FluDisplayCodeBox.h"

class FluDisplayCodeDemo : public QWidget
{
    Q_OBJECT
  public:
    FluDisplayCodeDemo(QWidget* parent = nullptr) : QWidget(parent)
    {
        auto display = new FluDisplayCodeBox(this);
        display->setFixedSize(300, 50);
        display->move(50, 50);

        QString code = "std::cout << \"hello, world\" << std::endl; // this just a text";
        display->setCodeText(code);
        setStyleSheet("background-color:rgb(249, 249, 249);");
    }
};
