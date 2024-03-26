#pragma once

#include <QWidget>
#include "../FluControls/FluTextEdit.h"

class FluTextEditDemo : public QWidget
{
    Q_OBJECT
  public:
    FluTextEditDemo(QWidget* parent = nullptr) : QWidget(parent)
    {
        auto textEdit = new FluTextEdit(this);
        textEdit->setFixedWidth(300);
        textEdit->move(50, 50);

        connect(textEdit->document(), &QTextDocument::contentsChanged, this, [=]() { 
            QTextDocument* document = textEdit->document();
            textEdit->setFixedHeight(document->size().height() + 4);
        });
        resize(600, 400);
    }
};
